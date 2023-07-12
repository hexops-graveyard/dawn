//===---- RawBufferMethods.cpp ---- Raw Buffer Methods ----------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//===----------------------------------------------------------------------===//

#include "RawBufferMethods.h"
#include "AlignmentSizeCalculator.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/CharUnits.h"
#include "clang/AST/RecordLayout.h"
#include "clang/AST/Type.h"
#include "clang/SPIRV/AstTypeProbe.h"
#include "clang/SPIRV/SpirvBuilder.h"
#include "clang/SPIRV/SpirvInstruction.h"
#include <cstdint>

namespace {
/// Rounds the given value up to the given power of 2.
inline uint32_t roundToPow2(uint32_t val, uint32_t pow2) {
  assert(pow2 != 0);
  return (val + pow2 - 1) & ~(pow2 - 1);
}
} // anonymous namespace

namespace clang {
namespace spirv {

SpirvInstruction *RawBufferHandler::bitCastToNumericalOrBool(
    SpirvInstruction *instr, QualType fromType, QualType toType,
    SourceLocation loc, SourceRange range) {
  if (isSameType(astContext, fromType, toType))
    return instr;

  if (toType->isBooleanType() || fromType->isBooleanType())
    return theEmitter.castToType(instr, fromType, toType, loc, range);

  // Perform a bitcast
  return spvBuilder.createUnaryOp(spv::Op::OpBitcast, toType, instr, loc,
                                  range);
}

SpirvInstruction *RawBufferHandler::load16BitsAtBitOffset0(
    SpirvInstruction *buffer, SpirvInstruction *&index,
    QualType target16BitType, uint32_t &bitOffset, SourceRange range) {
  assert(bitOffset == 0);
  const auto loc = buffer->getSourceLocation();
  SpirvInstruction *result = nullptr;
  auto *constUint0 =
      spvBuilder.getConstantInt(astContext.UnsignedIntTy, llvm::APInt(32, 0));
  // The underlying element type of the ByteAddressBuffer is uint. So we
  // need to load 32-bits at the very least.
  auto *loadPtr = spvBuilder.createAccessChain(astContext.UnsignedIntTy, buffer,
                                               {constUint0, index}, loc, range);
  result = spvBuilder.createLoad(astContext.UnsignedIntTy, loadPtr, loc, range);
  // Only need to mask the lowest 16 bits of the loaded 32-bit uint.
  // OpUConvert can perform truncation in this case.
  result = spvBuilder.createUnaryOp(
      spv::Op::OpUConvert, astContext.UnsignedShortTy, result, loc, range);
  result = bitCastToNumericalOrBool(result, astContext.UnsignedShortTy,
                                    target16BitType, loc, range);
  result->setRValue();

  // Now that a 16-bit load at bit-offset 0 has been performed, the next load
  // should be done at *the same base index* at bit-offset 16.
  bitOffset = (bitOffset + 16) % 32;
  return result;
}

SpirvInstruction *RawBufferHandler::load32BitsAtBitOffset0(
    SpirvInstruction *buffer, SpirvInstruction *&index,
    QualType target32BitType, uint32_t &bitOffset, SourceRange range) {
  assert(bitOffset == 0);
  const auto loc = buffer->getSourceLocation();
  SpirvInstruction *result = nullptr;
  // Only need to perform one 32-bit uint load.
  auto *constUint0 =
      spvBuilder.getConstantInt(astContext.UnsignedIntTy, llvm::APInt(32, 0));
  auto *constUint1 =
      spvBuilder.getConstantInt(astContext.UnsignedIntTy, llvm::APInt(32, 1));
  auto *loadPtr = spvBuilder.createAccessChain(astContext.UnsignedIntTy, buffer,
                                               {constUint0, index}, loc, range);
  result = spvBuilder.createLoad(astContext.UnsignedIntTy, loadPtr, loc, range);
  result = bitCastToNumericalOrBool(result, astContext.UnsignedIntTy,
                                    target32BitType, loc, range);
  result->setRValue();
  // Now that a 32-bit load at bit-offset 0 has been performed, the next load
  // should be done at *the next base index* at bit-offset 0.
  bitOffset = (bitOffset + 32) % 32;
  index = spvBuilder.createBinaryOp(spv::Op::OpIAdd, astContext.UnsignedIntTy,
                                    index, constUint1, loc, range);

  return result;
}

SpirvInstruction *RawBufferHandler::load64BitsAtBitOffset0(
    SpirvInstruction *buffer, SpirvInstruction *&index,
    QualType target64BitType, uint32_t &bitOffset, SourceRange range) {
  assert(bitOffset == 0);
  const auto loc = buffer->getSourceLocation();
  SpirvInstruction *result = nullptr;
  SpirvInstruction *ptr = nullptr;
  auto *constUint0 =
      spvBuilder.getConstantInt(astContext.UnsignedIntTy, llvm::APInt(32, 0));
  auto *constUint1 =
      spvBuilder.getConstantInt(astContext.UnsignedIntTy, llvm::APInt(32, 1));
  auto *constUint32 =
      spvBuilder.getConstantInt(astContext.UnsignedIntTy, llvm::APInt(32, 32));

  // Need to perform two 32-bit uint loads and construct a 64-bit value.

  // Load the first 32-bit uint (word0).
  ptr = spvBuilder.createAccessChain(astContext.UnsignedIntTy, buffer,
                                     {constUint0, index}, loc, range);
  SpirvInstruction *word0 =
      spvBuilder.createLoad(astContext.UnsignedIntTy, ptr, loc, range);
  // Increment the base index
  index = spvBuilder.createBinaryOp(spv::Op::OpIAdd, astContext.UnsignedIntTy,
                                    index, constUint1, loc, range);
  // Load the second 32-bit uint (word1).
  ptr = spvBuilder.createAccessChain(astContext.UnsignedIntTy, buffer,
                                     {constUint0, index}, loc, range);
  SpirvInstruction *word1 =
      spvBuilder.createLoad(astContext.UnsignedIntTy, ptr, loc, range);

  // Convert both word0 and word1 to 64-bit uints.
  word0 = spvBuilder.createUnaryOp(
      spv::Op::OpUConvert, astContext.UnsignedLongLongTy, word0, loc, range);
  word1 = spvBuilder.createUnaryOp(
      spv::Op::OpUConvert, astContext.UnsignedLongLongTy, word1, loc, range);

  // Shift word1 to the left by 32 bits.
  word1 = spvBuilder.createBinaryOp(spv::Op::OpShiftLeftLogical,
                                    astContext.UnsignedLongLongTy, word1,
                                    constUint32, loc, range);

  // BitwiseOr word0 and word1.
  result = spvBuilder.createBinaryOp(spv::Op::OpBitwiseOr,
                                     astContext.UnsignedLongLongTy, word0,
                                     word1, loc, range);
  result = bitCastToNumericalOrBool(result, astContext.UnsignedLongLongTy,
                                    target64BitType, loc, range);
  result->setRValue();
  // Now that a 64-bit load at bit-offset 0 has been performed, the next load
  // should be done at *the base index + 2* at bit-offset 0. The index has
  // already been incremented once. Need to increment it once more.
  bitOffset = (bitOffset + 64) % 32;
  index = spvBuilder.createBinaryOp(spv::Op::OpIAdd, astContext.UnsignedIntTy,
                                    index, constUint1, loc, range);

  return result;
}

SpirvInstruction *RawBufferHandler::load16BitsAtBitOffset16(
    SpirvInstruction *buffer, SpirvInstruction *&index,
    QualType target16BitType, uint32_t &bitOffset, SourceRange range) {
  assert(bitOffset == 16);
  const auto loc = buffer->getSourceLocation();
  SpirvInstruction *result = nullptr;
  auto *constUint0 =
      spvBuilder.getConstantInt(astContext.UnsignedIntTy, llvm::APInt(32, 0));
  auto *constUint1 =
      spvBuilder.getConstantInt(astContext.UnsignedIntTy, llvm::APInt(32, 1));
  auto *constUint16 =
      spvBuilder.getConstantInt(astContext.UnsignedIntTy, llvm::APInt(32, 16));

  // The underlying element type of the ByteAddressBuffer is uint. So we
  // need to load 32-bits at the very least.
  auto *ptr = spvBuilder.createAccessChain(astContext.UnsignedIntTy, buffer,
                                           {constUint0, index}, loc, range);
  result = spvBuilder.createLoad(astContext.UnsignedIntTy, ptr, loc, range);
  result = spvBuilder.createBinaryOp(spv::Op::OpShiftRightLogical,
                                     astContext.UnsignedIntTy, result,
                                     constUint16, loc, range);
  result = spvBuilder.createUnaryOp(
      spv::Op::OpUConvert, astContext.UnsignedShortTy, result, loc, range);
  result = bitCastToNumericalOrBool(result, astContext.UnsignedShortTy,
                                    target16BitType, loc, range);
  result->setRValue();

  // Now that a 16-bit load at bit-offset 16 has been performed, the next load
  // should be done at *the next base index* at bit-offset 0.
  bitOffset = (bitOffset + 16) % 32;
  index = spvBuilder.createBinaryOp(spv::Op::OpIAdd, astContext.UnsignedIntTy,
                                    index, constUint1, loc, range);
  return result;
}

SpirvInstruction *RawBufferHandler::processTemplatedLoadFromBuffer(
    SpirvInstruction *buffer, SpirvInstruction *&index,
    const QualType targetType, uint32_t &bitOffset, SourceRange range) {
  const auto loc = buffer->getSourceLocation();
  SpirvInstruction *result = nullptr;

  // TODO: If 8-bit types are to be supported in the future, we should also
  // add code to support bitOffset 8 and 24.
  assert(bitOffset == 0 || bitOffset == 16);

  // Scalar types
  if (isScalarType(targetType)) {
    SpirvInstruction *scalarResult = nullptr;
    auto loadWidth = getElementSpirvBitwidth(
        astContext, targetType, theEmitter.getSpirvOptions().enable16BitTypes);
    switch (bitOffset) {
    case 0: {
      switch (loadWidth) {
      case 16:
        scalarResult =
            load16BitsAtBitOffset0(buffer, index, targetType, bitOffset, range);
        break;
      case 32:
        scalarResult =
            load32BitsAtBitOffset0(buffer, index, targetType, bitOffset, range);
        break;
      case 64:
        scalarResult =
            load64BitsAtBitOffset0(buffer, index, targetType, bitOffset, range);
        break;
      default:
        theEmitter.emitError(
            "templated load of ByteAddressBuffer is only implemented for "
            "16, 32, and 64-bit types",
            loc);
        return nullptr;
      }
      break;
    }
    case 16: {
      switch (loadWidth) {
      case 16:
        scalarResult = load16BitsAtBitOffset16(buffer, index, targetType,
                                               bitOffset, range);
        break;
      case 32:
      case 64:
        theEmitter.emitError(
            "templated buffer load should not result in loading "
            "32-bit or 64-bit values at bit offset 16",
            loc);
        return nullptr;
      default:
        theEmitter.emitError(
            "templated load of ByteAddressBuffer is only implemented for "
            "16, 32, and 64-bit types",
            loc);
        return nullptr;
      }
      break;
    }
    default:
      theEmitter.emitError(
          "templated load of ByteAddressBuffer is only implemented for "
          "16, 32, and 64-bit types",
          loc);
      return nullptr;
    }
    assert(scalarResult != nullptr);
    // We set the layout rule for scalars. Other types are built up from the
    // scalars, and should inherit this layout rule or default to Void.
    scalarResult->setLayoutRule(SpirvLayoutRule::Void);
    return scalarResult;
  }

  // Vector types
  {
    QualType elemType = {};
    uint32_t elemCount = 0;
    if (isVectorType(targetType, &elemType, &elemCount)) {
      llvm::SmallVector<SpirvInstruction *, 4> loadedElems;
      for (uint32_t i = 0; i < elemCount; ++i) {
        loadedElems.push_back(processTemplatedLoadFromBuffer(
            buffer, index, elemType, bitOffset, range));
      }
      result = spvBuilder.createCompositeConstruct(targetType, loadedElems, loc,
                                                   range);
      result->setRValue();
      return result;
    }
  }

  // Array types
  {
    QualType elemType = {};
    uint32_t elemCount = 0;
    if (const auto *arrType = astContext.getAsConstantArrayType(targetType)) {
      elemCount = static_cast<uint32_t>(arrType->getSize().getZExtValue());
      elemType = arrType->getElementType();
      llvm::SmallVector<SpirvInstruction *, 4> loadedElems;
      for (uint32_t i = 0; i < elemCount; ++i) {
        loadedElems.push_back(processTemplatedLoadFromBuffer(
            buffer, index, elemType, bitOffset, range));
      }
      result = spvBuilder.createCompositeConstruct(targetType, loadedElems, loc,
                                                   range);
      result->setRValue();
      return result;
    }
  }

  // Matrix types
  {
    QualType elemType = {};
    uint32_t numRows = 0;
    uint32_t numCols = 0;
    if (isMxNMatrix(targetType, &elemType, &numRows, &numCols)) {
      // In DX, the default matrix orientation in ByteAddressBuffer is column
      // major. If HLSL/DXIL support the `column_major` and `row_major`
      // attributes in the future, we will have to check for them here and
      // override the behavior.
      //
      // The assume buffer matrix order is controlled by the
      // `-fspv-use-legacy-buffer-matrix-order` flag:
      //   (a) false --> assume the matrix is stored column major
      //   (b) true  --> assume the matrix is stored row major
      //
      // We provide (b) for compatibility with legacy shaders that depend on
      // the previous, incorrect, raw buffer matrix order assumed by the SPIR-V
      // codegen.
      const bool isBufferColumnMajor =
          !theEmitter.getSpirvOptions().useLegacyBufferMatrixOrder;
      const uint32_t numElements = numRows * numCols;
      llvm::SmallVector<SpirvInstruction *, 16> loadedElems(numElements);
      for (uint32_t i = 0; i != numElements; ++i)
        loadedElems[i] = processTemplatedLoadFromBuffer(buffer, index, elemType,
                                                        bitOffset, range);

      llvm::SmallVector<SpirvInstruction *, 4> loadedRows;
      for (uint32_t i = 0; i < numRows; ++i) {
        llvm::SmallVector<SpirvInstruction *, 4> loadedColumn;
        for (uint32_t j = 0; j < numCols; ++j) {
          const uint32_t elementIndex =
              isBufferColumnMajor ? (j * numRows + i) : (i * numCols + j);
          loadedColumn.push_back(loadedElems[elementIndex]);
        }
        const auto rowType = astContext.getExtVectorType(elemType, numCols);
        loadedRows.push_back(spvBuilder.createCompositeConstruct(
            rowType, loadedColumn, loc, range));
      }

      result = spvBuilder.createCompositeConstruct(targetType, loadedRows, loc,
                                                   range);
      result->setRValue();
      return result;
    }
  }

  // Struct types
  // The "natural" layout for structure types dictates that structs are
  // aligned like their field with the largest alignment.
  // As a result, there might exist some padding after some struct members.
  if (const auto *structType = targetType->getAs<RecordType>()) {
    const auto *decl = structType->getDecl();
    SpirvInstruction *originalIndex = index;
    uint32_t originalBitOffset = bitOffset;
    llvm::SmallVector<SpirvInstruction *, 4> loadedElems;
    uint32_t fieldOffsetInBytes = 0;
    uint32_t structAlignment = 0, structSize = 0, stride = 0;
    std::tie(structAlignment, structSize) =
        AlignmentSizeCalculator(astContext, theEmitter.getSpirvOptions())
            .getAlignmentAndSize(targetType,
                                 theEmitter.getSpirvOptions().sBufferLayoutRule,
                                 llvm::None, &stride);
    for (const auto *field : decl->fields()) {
      AlignmentSizeCalculator alignmentCalc(astContext,
                                            theEmitter.getSpirvOptions());
      uint32_t fieldSize = 0, fieldAlignment = 0;
      std::tie(fieldAlignment, fieldSize) = alignmentCalc.getAlignmentAndSize(
          field->getType(), theEmitter.getSpirvOptions().sBufferLayoutRule,
          /*isRowMajor*/ llvm::None, &stride);
      fieldOffsetInBytes = roundToPow2(fieldOffsetInBytes, fieldAlignment);
      const auto wordOffset =
          ((originalBitOffset / 8) + fieldOffsetInBytes) / 4;
      bitOffset = (((originalBitOffset / 8) + fieldOffsetInBytes) % 4) * 8;

      if (wordOffset != 0) {
        // Divide the fieldOffset by 4 to figure out how much to increment the
        // index into the buffer (increment occurs by 32-bit words since the
        // underlying type is an array of uints).
        // The remainder by four tells us the *byte offset* (then multiply by 8
        // to get bit offset).
        index = spvBuilder.createBinaryOp(
            spv::Op::OpIAdd, astContext.UnsignedIntTy, originalIndex,
            spvBuilder.getConstantInt(astContext.UnsignedIntTy,
                                      llvm::APInt(32, wordOffset)),
            loc, range);
      }
      loadedElems.push_back(processTemplatedLoadFromBuffer(
          buffer, index, field->getType(), bitOffset, range));

      fieldOffsetInBytes += fieldSize;
    }

    // After we're done with loading the entire struct, we need to update the
    // index and bitOffset (in case we are loading an array of structs).
    //
    // Example: struct alignment = 8. struct size = 34 bytes
    // (34 / 8) = 4 full words
    // (34 % 8) = 2 > 0, therefore need to move to the next aligned address
    // So the starting byte offset after loading the entire struct is:
    // 8 * (4 + 1) = 40
    assert(structAlignment != 0);
    uint32_t newByteOffset = roundToPow2(structSize, structAlignment);
    uint32_t newWordOffset = ((originalBitOffset / 8) + newByteOffset) / 4;
    bitOffset = 8 * (((originalBitOffset / 8) + newByteOffset) % 4);
    index = spvBuilder.createBinaryOp(
        spv::Op::OpIAdd, astContext.UnsignedIntTy, originalIndex,
        spvBuilder.getConstantInt(astContext.UnsignedIntTy,
                                  llvm::APInt(32, newWordOffset)),
        loc, range);

    result = spvBuilder.createCompositeConstruct(targetType, loadedElems, loc,
                                                 range);
    result->setRValue();
    return result;
  }

  llvm_unreachable("templated buffer load unimplemented for type");
}

void RawBufferHandler::store16BitsAtBitOffset0(SpirvInstruction *value,
                                               SpirvInstruction *buffer,
                                               SpirvInstruction *&index,
                                               const QualType valueType,
                                               SourceRange range) {
  const auto loc = buffer->getSourceLocation();
  SpirvInstruction *result = nullptr;
  auto *constUint0 =
      spvBuilder.getConstantInt(astContext.UnsignedIntTy, llvm::APInt(32, 0));
  // The underlying element type of the ByteAddressBuffer is uint. So we
  // need to store a 32-bit value.
  auto *ptr = spvBuilder.createAccessChain(astContext.UnsignedIntTy, buffer,
                                           {constUint0, index}, loc, range);
  result = bitCastToNumericalOrBool(value, valueType,
                                    astContext.UnsignedShortTy, loc, range);
  result = spvBuilder.createUnaryOp(
      spv::Op::OpUConvert, astContext.UnsignedIntTy, result, loc, range);
  spvBuilder.createStore(ptr, result, loc, range);
}

void RawBufferHandler::store16BitsAtBitOffset16(SpirvInstruction *value,
                                                SpirvInstruction *buffer,
                                                SpirvInstruction *&index,
                                                const QualType valueType,
                                                SourceRange range) {
  const auto loc = buffer->getSourceLocation();
  SpirvInstruction *result = nullptr;
  auto *constUint0 =
      spvBuilder.getConstantInt(astContext.UnsignedIntTy, llvm::APInt(32, 0));
  auto *constUint1 =
      spvBuilder.getConstantInt(astContext.UnsignedIntTy, llvm::APInt(32, 1));
  auto *constUint16 =
      spvBuilder.getConstantInt(astContext.UnsignedIntTy, llvm::APInt(32, 16));
  // The underlying element type of the ByteAddressBuffer is uint. So we
  // need to store a 32-bit value.
  auto *ptr = spvBuilder.createAccessChain(astContext.UnsignedIntTy, buffer,
                                           {constUint0, index}, loc, range);
  result = bitCastToNumericalOrBool(value, valueType,
                                    astContext.UnsignedShortTy, loc, range);
  result = spvBuilder.createUnaryOp(
      spv::Op::OpUConvert, astContext.UnsignedIntTy, result, loc, range);
  result = spvBuilder.createBinaryOp(spv::Op::OpShiftLeftLogical,
                                     astContext.UnsignedIntTy, result,
                                     constUint16, loc, range);
  result = spvBuilder.createBinaryOp(
      spv::Op::OpBitwiseOr, astContext.UnsignedIntTy,
      spvBuilder.createLoad(astContext.UnsignedIntTy, ptr, loc), result, loc,
      range);
  spvBuilder.createStore(ptr, result, loc, range);
  index = spvBuilder.createBinaryOp(spv::Op::OpIAdd, astContext.UnsignedIntTy,
                                    index, constUint1, loc, range);
}

void RawBufferHandler::store32BitsAtBitOffset0(SpirvInstruction *value,
                                               SpirvInstruction *buffer,
                                               SpirvInstruction *&index,
                                               const QualType valueType,
                                               SourceRange range) {
  const auto loc = buffer->getSourceLocation();
  auto *constUint0 =
      spvBuilder.getConstantInt(astContext.UnsignedIntTy, llvm::APInt(32, 0));
  auto *constUint1 =
      spvBuilder.getConstantInt(astContext.UnsignedIntTy, llvm::APInt(32, 1));
  // The underlying element type of the ByteAddressBuffer is uint. So we
  // need to store a 32-bit value.
  auto *ptr = spvBuilder.createAccessChain(astContext.UnsignedIntTy, buffer,
                                           {constUint0, index}, loc, range);
  value = bitCastToNumericalOrBool(value, valueType, astContext.UnsignedIntTy,
                                   loc, range);
  spvBuilder.createStore(ptr, value, loc, range);
  index = spvBuilder.createBinaryOp(spv::Op::OpIAdd, astContext.UnsignedIntTy,
                                    index, constUint1, loc, range);
}

void RawBufferHandler::store64BitsAtBitOffset0(SpirvInstruction *value,
                                               SpirvInstruction *buffer,
                                               SpirvInstruction *&index,
                                               const QualType valueType,
                                               SourceRange range) {
  const auto loc = buffer->getSourceLocation();
  auto *constUint0 =
      spvBuilder.getConstantInt(astContext.UnsignedIntTy, llvm::APInt(32, 0));
  auto *constUint1 =
      spvBuilder.getConstantInt(astContext.UnsignedIntTy, llvm::APInt(32, 1));
  auto *constUint32 =
      spvBuilder.getConstantInt(astContext.UnsignedIntTy, llvm::APInt(32, 32));

  // The underlying element type of the ByteAddressBuffer is uint. So we
  // need to store two 32-bit values.
  auto *ptr = spvBuilder.createAccessChain(astContext.UnsignedIntTy, buffer,
                                           {constUint0, index}, loc, range);
  // First convert the 64-bit value to uint64_t. Then extract two 32-bit words
  // from it.
  value = bitCastToNumericalOrBool(value, valueType,
                                   astContext.UnsignedLongLongTy, loc, range);

  // Use OpUConvert to perform truncation (produces the least significant bits).
  SpirvInstruction *lsb = spvBuilder.createUnaryOp(
      spv::Op::OpUConvert, astContext.UnsignedIntTy, value, loc, range);

  // Shift uint64_t to the right by 32 bits and truncate to get the most
  // significant bits.
  SpirvInstruction *msb = spvBuilder.createUnaryOp(
      spv::Op::OpUConvert, astContext.UnsignedIntTy,
      spvBuilder.createBinaryOp(spv::Op::OpShiftRightLogical,
                                astContext.UnsignedLongLongTy, value,
                                constUint32, loc, range),
      loc, range);

  spvBuilder.createStore(ptr, lsb, loc, range);
  index = spvBuilder.createBinaryOp(spv::Op::OpIAdd, astContext.UnsignedIntTy,
                                    index, constUint1, loc, range);
  ptr = spvBuilder.createAccessChain(astContext.UnsignedIntTy, buffer,
                                     {constUint0, index}, loc, range);
  spvBuilder.createStore(ptr, msb, loc, range);
  index = spvBuilder.createBinaryOp(spv::Op::OpIAdd, astContext.UnsignedIntTy,
                                    index, constUint1, loc, range);
}

void RawBufferHandler::storeArrayOfScalars(
    std::deque<SpirvInstruction *> values, SpirvInstruction *buffer,
    SpirvInstruction *&index, const QualType valueType, uint32_t &bitOffset,
    SourceLocation loc, SourceRange range) {
  auto *constUint0 =
      spvBuilder.getConstantInt(astContext.UnsignedIntTy, llvm::APInt(32, 0));
  auto *constUint1 =
      spvBuilder.getConstantInt(astContext.UnsignedIntTy, llvm::APInt(32, 1));
  auto *constUint16 =
      spvBuilder.getConstantInt(astContext.UnsignedIntTy, llvm::APInt(32, 16));
  const auto storeWidth = getElementSpirvBitwidth(
      astContext, valueType, theEmitter.getSpirvOptions().enable16BitTypes);
  const uint32_t elemCount = values.size();

  if (storeWidth == 16u) {
    uint32_t elemIndex = 0;
    if (bitOffset == 16) {
      // First store the first element at offset 16 of the last memory index.
      store16BitsAtBitOffset16(values[0], buffer, index, valueType, range);
      bitOffset = 0;
      ++elemIndex;
    }
    // Do a custom store based on the number of elements.
    for (; elemIndex < elemCount; elemIndex = elemIndex + 2) {
      // The underlying element type of the ByteAddressBuffer is uint. So we
      // need to store a 32-bit value by combining two 16-bit values.
      SpirvInstruction *word = nullptr;
      word = bitCastToNumericalOrBool(values[elemIndex], valueType,
                                      astContext.UnsignedShortTy, loc, range);
      // Zero-extend to 32 bits.
      word = spvBuilder.createUnaryOp(
          spv::Op::OpUConvert, astContext.UnsignedIntTy, word, loc, range);
      if (elemIndex + 1 < elemCount) {
        SpirvInstruction *msb = nullptr;
        msb = bitCastToNumericalOrBool(values[elemIndex + 1], valueType,
                                       astContext.UnsignedShortTy, loc, range);
        msb = spvBuilder.createUnaryOp(
            spv::Op::OpUConvert, astContext.UnsignedIntTy, msb, loc, range);
        msb = spvBuilder.createBinaryOp(spv::Op::OpShiftLeftLogical,
                                        astContext.UnsignedIntTy, msb,
                                        constUint16, loc, range);
        word = spvBuilder.createBinaryOp(spv::Op::OpBitwiseOr,
                                         astContext.UnsignedIntTy, word, msb,
                                         loc, range);
        // We will store two 16-bit values.
        bitOffset = (bitOffset + 32) % 32;
      } else {
        // We will store one 16-bit value.
        bitOffset = (bitOffset + 16) % 32;
      }

      auto *ptr = spvBuilder.createAccessChain(astContext.UnsignedIntTy, buffer,
                                               {constUint0, index}, loc, range);
      spvBuilder.createStore(ptr, word, loc, range);
      index =
          spvBuilder.createBinaryOp(spv::Op::OpIAdd, astContext.UnsignedIntTy,
                                    index, constUint1, loc, range);
    }
  } else if (storeWidth == 32u || storeWidth == 64u) {
    assert(bitOffset == 0);
    for (uint32_t i = 0; i < elemCount; ++i)
      processTemplatedStoreToBuffer(values[i], buffer, index, valueType,
                                    bitOffset, range);
  }
}

QualType RawBufferHandler::serializeToScalarsOrStruct(
    std::deque<SpirvInstruction *> *values, QualType valueType,
    SourceLocation loc, SourceRange range) {
  uint32_t size = values->size();

  // Vector type
  {
    QualType elemType = {};
    uint32_t elemCount = 0;
    if (isVectorType(valueType, &elemType, &elemCount)) {
      for (uint32_t i = 0; i < size; ++i) {
        for (uint32_t j = 0; j < elemCount; ++j) {
          values->push_back(spvBuilder.createCompositeExtract(
              elemType, values->front(), {j}, loc, range));
        }
        values->pop_front();
      }
      return elemType;
    }
  }

  // Matrix type
  {
    QualType elemType = {};
    uint32_t numRows = 0, numCols = 0;
    if (isMxNMatrix(valueType, &elemType, &numRows, &numCols)) {
      // Check if the destination buffer expects matrices in column major or row
      // major order. In the future, we may also need to consider the
      // `row_major` and `column_major` attribures. This is not handled by
      // HLSL/DXIL at the moment, so we ignore them too.
      const bool isBufferColumnMajor =
          !theEmitter.getSpirvOptions().useLegacyBufferMatrixOrder;
      for (uint32_t i = 0; i < size; ++i) {
        if (isBufferColumnMajor) {
          // Access the matrix in the column major order.
          for (uint32_t j = 0; j != numCols; ++j) {
            for (uint32_t k = 0; k != numRows; ++k) {
              values->push_back(spvBuilder.createCompositeExtract(
                  elemType, values->front(), {k, j}, loc, range));
            }
          }
        } else {
          // Access the matrix in the row major order.
          for (uint32_t j = 0; j != numRows; ++j) {
            for (uint32_t k = 0; k != numCols; ++k) {
              values->push_back(spvBuilder.createCompositeExtract(
                  elemType, values->front(), {j, k}, loc, range));
            }
          }
        }
        values->pop_front();
      }
      return serializeToScalarsOrStruct(values, elemType, loc, range);
    }
  }

  // Array type
  {
    if (const auto *arrType = astContext.getAsConstantArrayType(valueType)) {
      const uint32_t arrElemCount =
          static_cast<uint32_t>(arrType->getSize().getZExtValue());
      const QualType arrElemType = arrType->getElementType();
      for (uint32_t i = 0; i < size; ++i) {
        for (uint32_t j = 0; j < arrElemCount; ++j) {
          values->push_back(spvBuilder.createCompositeExtract(
              arrElemType, values->front(), {j}, loc, range));
        }
        values->pop_front();
      }
      return serializeToScalarsOrStruct(values, arrElemType, loc, range);
    }
  }

  if (isScalarType(valueType))
    return valueType;

  if (valueType->getAs<RecordType>())
    return valueType;

  llvm_unreachable("unhandled type when serializing an array");
}

void RawBufferHandler::processTemplatedStoreToBuffer(
    SpirvInstruction *value, SpirvInstruction *buffer, SpirvInstruction *&index,
    const QualType valueType, uint32_t &bitOffset, SourceRange range) {
  assert(bitOffset == 0 || bitOffset == 16);
  const auto loc = buffer->getSourceLocation();

  // Scalar types
  if (isScalarType(valueType)) {
    auto storeWidth = getElementSpirvBitwidth(
        astContext, valueType, theEmitter.getSpirvOptions().enable16BitTypes);
    switch (bitOffset) {
    case 0: {
      switch (storeWidth) {
      case 16:
        store16BitsAtBitOffset0(value, buffer, index, valueType, range);
        return;
      case 32:
        store32BitsAtBitOffset0(value, buffer, index, valueType, range);
        return;
      case 64:
        store64BitsAtBitOffset0(value, buffer, index, valueType, range);
        return;
      default:
        theEmitter.emitError(
            "templated load of ByteAddressBuffer is only implemented for "
            "16, 32, and 64-bit types",
            loc);
        return;
      }
    }
    case 16: {
      // The only legal store at offset 16 is by a 16-bit value.
      assert(storeWidth == 16);
      store16BitsAtBitOffset16(value, buffer, index, valueType, range);
      return;
    }
    default:
      theEmitter.emitError(
          "templated load of ByteAddressBuffer is only implemented for "
          "16, 32, and 64-bit types",
          loc);
      return;
    }
  }

  // Vectors, Matrices, and Arrays can all be serialized and stored.
  if (isVectorType(valueType) || isMxNMatrix(valueType) ||
      isConstantArrayType(astContext, valueType)) {
    std::deque<SpirvInstruction *> elems;
    elems.push_back(value);
    auto serializedType =
        serializeToScalarsOrStruct(&elems, valueType, loc, range);
    if (isScalarType(serializedType)) {
      storeArrayOfScalars(elems, buffer, index, serializedType, bitOffset, loc,
                          range);
    } else if (serializedType->getAs<RecordType>()) {
      for (auto elem : elems)
        processTemplatedStoreToBuffer(elem, buffer, index, serializedType,
                                      bitOffset, range);
    }
    return;
  }

  // Struct types
  // The "natural" layout for structure types dictates that structs are
  // aligned like their field with the largest alignment.
  // As a result, there might exist some padding after some struct members.
  if (const auto *structType = valueType->getAs<RecordType>()) {
    const auto *decl = structType->getDecl();
    SpirvInstruction *originalIndex = index;
    const auto originalBitOffset = bitOffset;
    uint32_t fieldOffsetInBytes = 0;
    uint32_t structAlignment = 0, structSize = 0, stride = 0;
    std::tie(structAlignment, structSize) =
        AlignmentSizeCalculator(astContext, theEmitter.getSpirvOptions())
            .getAlignmentAndSize(valueType,
                                 theEmitter.getSpirvOptions().sBufferLayoutRule,
                                 llvm::None, &stride);
    uint32_t fieldIndex = 0;
    for (const auto *field : decl->fields()) {
      AlignmentSizeCalculator alignmentCalc(astContext,
                                            theEmitter.getSpirvOptions());
      uint32_t fieldSize = 0, fieldAlignment = 0;
      std::tie(fieldAlignment, fieldSize) = alignmentCalc.getAlignmentAndSize(
          field->getType(), theEmitter.getSpirvOptions().sBufferLayoutRule,
          /*isRowMajor*/ llvm::None, &stride);
      fieldOffsetInBytes = roundToPow2(fieldOffsetInBytes, fieldAlignment);
      const auto wordOffset =
          ((originalBitOffset / 8) + fieldOffsetInBytes) / 4;
      bitOffset = (((originalBitOffset / 8) + fieldOffsetInBytes) % 4) * 8;

      if (wordOffset != 0) {
        // Divide the fieldOffset by 4 to figure out how much to increment the
        // index into the buffer (increment occurs by 32-bit words since the
        // underlying type is an array of uints).
        // The remainder by four tells us the *byte offset* (then multiply by 8
        // to get bit offset).
        index = spvBuilder.createBinaryOp(
            spv::Op::OpIAdd, astContext.UnsignedIntTy, originalIndex,
            spvBuilder.getConstantInt(astContext.UnsignedIntTy,
                                      llvm::APInt(32, wordOffset)),
            loc, range);
      }

      processTemplatedStoreToBuffer(
          spvBuilder.createCompositeExtract(field->getType(), value,
                                            {fieldIndex}, loc, range),
          buffer, index, field->getType(), bitOffset, range);

      fieldOffsetInBytes += fieldSize;
      ++fieldIndex;
    }

    // After we're done with storing the entire struct, we need to update the
    // index (in case we are stroring an array of structs).
    //
    // Example: struct alignment = 8. struct size = 34 bytes
    // (34 / 8) = 4 full words
    // (34 % 8) = 2 > 0, therefore need to move to the next aligned address
    // So the starting byte offset after loading the entire struct is:
    // 8 * (4 + 1) = 40
    assert(structAlignment != 0);
    uint32_t newByteOffset = roundToPow2(structSize, structAlignment);
    uint32_t newWordOffset = ((originalBitOffset / 8) + newByteOffset) / 4;
    bitOffset = 8 * (((originalBitOffset / 8) + newByteOffset) % 4);
    index = spvBuilder.createBinaryOp(
        spv::Op::OpIAdd, astContext.UnsignedIntTy, originalIndex,
        spvBuilder.getConstantInt(astContext.UnsignedIntTy,
                                  llvm::APInt(32, newWordOffset)),
        loc, range);

    return;
  }

  llvm_unreachable("templated buffer store unimplemented for type");
}

} // namespace spirv
} // namespace clang
