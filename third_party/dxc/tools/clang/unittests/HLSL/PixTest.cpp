///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// PixTest.cpp                                                               //
// Copyright (C) Microsoft Corporation. All rights reserved.                 //
// This file is distributed under the University of Illinois Open Source     //
// License. See LICENSE.TXT for details.                                     //
//                                                                           //
// Provides tests for the PIX-specific components                            //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

// This whole file is win32-only
#ifdef _WIN32


#ifndef UNICODE
#define UNICODE
#endif

#include <memory>
#include <vector>
#include <string>
#include <map>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <cfloat>

#include "dxc/Support/WinIncludes.h"

#include "dxc/DxilContainer/DxilContainer.h"
#include "dxc/DxilContainer/DxilRuntimeReflection.h"
#include "dxc/DxilRootSignature/DxilRootSignature.h"
#include "dxc/Support/WinIncludes.h"
#include "dxc/dxcapi.h"
#include "dxc/dxcpix.h"
#include <atlfile.h>
#include "dia2.h"

#include "dxc/DXIL/DxilModule.h"

#include "dxc/Test/HLSLTestData.h"
#include "dxc/Test/HlslTestUtils.h"
#include "dxc/Test/DxcTestUtils.h"

#include "llvm/Support/raw_os_ostream.h"
#include "dxc/Support/Global.h"
#include "dxc/Support/dxcapi.use.h"
#include "dxc/Support/microcom.h"
#include "dxc/Support/HLSLOptions.h"
#include "dxc/Support/Unicode.h"
#include "dxc/DXIL/DxilUtil.h"

#include <fstream>
#include "llvm/Bitcode/ReaderWriter.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/ModuleSlotTracker.h"
#include "llvm/IR/Operator.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/MSFileSystem.h"
#include "llvm/Support/Path.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/ADT/StringSwitch.h"


#include <../lib/DxilDia/DxilDiaSession.h>
#include <../lib/DxilDia/DxcPixLiveVariables.h>
#include <../lib/DxilDia/DxcPixLiveVariables_FragmentIterator.h>
#include <dxc/DxilPIXPasses/DxilPIXVirtualRegisters.h>

using namespace std;
using namespace hlsl;
using namespace hlsl_test;

// Aligned to SymTagEnum.
const char *SymTagEnumText[] = {
    "Null",               // SymTagNull
    "Exe",                // SymTagExe
    "Compiland",          // SymTagCompiland
    "CompilandDetails",   // SymTagCompilandDetails
    "CompilandEnv",       // SymTagCompilandEnv
    "Function",           // SymTagFunction
    "Block",              // SymTagBlock
    "Data",               // SymTagData
    "Annotation",         // SymTagAnnotation
    "Label",              // SymTagLabel
    "PublicSymbol",       // SymTagPublicSymbol
    "UDT",                // SymTagUDT
    "Enum",               // SymTagEnum
    "FunctionType",       // SymTagFunctionType
    "PointerType",        // SymTagPointerType
    "ArrayType",          // SymTagArrayType
    "BaseType",           // SymTagBaseType
    "Typedef",            // SymTagTypedef
    "BaseClass",          // SymTagBaseClass
    "Friend",             // SymTagFriend
    "FunctionArgType",    // SymTagFunctionArgType
    "FuncDebugStart",     // SymTagFuncDebugStart
    "FuncDebugEnd",       // SymTagFuncDebugEnd
    "UsingNamespace",     // SymTagUsingNamespace
    "VTableShape",        // SymTagVTableShape
    "VTable",             // SymTagVTable
    "Custom",             // SymTagCustom
    "Thunk",              // SymTagThunk
    "CustomType",         // SymTagCustomType
    "ManagedType",        // SymTagManagedType
    "Dimension",          // SymTagDimension
    "CallSite",           // SymTagCallSite
    "InlineSite",         // SymTagInlineSite
    "BaseInterface",      // SymTagBaseInterface
    "VectorType",         // SymTagVectorType
    "MatrixType",         // SymTagMatrixType
    "HLSLType",           // SymTagHLSLType
    "Caller",             // SymTagCaller
    "Callee",             // SymTagCallee
    "Export",             // SymTagExport
    "HeapAllocationSite", // SymTagHeapAllocationSite
    "CoffGroup",          // SymTagCoffGroup
};

// Aligned to LocationType.
const char* LocationTypeText[] =
{
  "Null",
  "Static",
  "TLS",
  "RegRel",
  "ThisRel",
  "Enregistered",
  "BitField",
  "Slot",
  "IlRel",
  "MetaData",
  "Constant",
};

// Aligned to DataKind.
const char* DataKindText[] =
{
  "Unknown",
  "Local",
  "StaticLocal",
  "Param",
  "ObjectPtr",
  "FileStatic",
  "Global",
  "Member",
  "StaticMember",
  "Constant",
};

// Aligned to UdtKind.
const char* UdtKindText[] =
{
  "Struct",
  "Class",
  "Union",
  "Interface",
};

static std::vector<std::string> Tokenize(const std::string &str,
                                         const char *delimiters) {
  std::vector<std::string> tokens;
  std::string copy = str;

  for (auto i = strtok(&copy[0], delimiters); i != nullptr;
       i = strtok(nullptr, delimiters)) {
    tokens.push_back(i);
  }

  return tokens;
}

class PixTest {
public:
  BEGIN_TEST_CLASS(PixTest)
    TEST_CLASS_PROPERTY(L"Parallel", L"true")
    TEST_METHOD_PROPERTY(L"Priority", L"0")
  END_TEST_CLASS()

  TEST_CLASS_SETUP(InitSupport);

  TEST_METHOD(CompileWhenDebugThenDIPresent)
  
  TEST_METHOD(CompileDebugPDB)
  TEST_METHOD(CompileDebugDisasmPDB)
  
  TEST_METHOD(DiaLoadBadBitcodeThenFail)
  TEST_METHOD(DiaLoadDebugThenOK)
  TEST_METHOD(DiaTableIndexThenOK)
  TEST_METHOD(DiaLoadDebugSubrangeNegativeThenOK)
  TEST_METHOD(DiaLoadRelocatedBitcode)
  TEST_METHOD(DiaLoadBitcodePlusExtraData)
  TEST_METHOD(DiaCompileArgs)
  TEST_METHOD(PixDebugCompileInfo)

  TEST_METHOD(AddToASPayload)

  TEST_METHOD(PixStructAnnotation_Lib_DualRaygen)
  TEST_METHOD(PixStructAnnotation_Lib_RaygenAllocaStructAlignment)

  TEST_METHOD(PixStructAnnotation_Simple)
  TEST_METHOD(PixStructAnnotation_CopiedStruct)
  TEST_METHOD(PixStructAnnotation_MixedSizes)
  TEST_METHOD(PixStructAnnotation_StructWithinStruct)
  TEST_METHOD(PixStructAnnotation_1DArray)
  TEST_METHOD(PixStructAnnotation_2DArray)
  TEST_METHOD(PixStructAnnotation_EmbeddedArray)
  TEST_METHOD(PixStructAnnotation_FloatN)
  TEST_METHOD(PixStructAnnotation_SequentialFloatN)
  TEST_METHOD(PixStructAnnotation_EmbeddedFloatN)
  TEST_METHOD(PixStructAnnotation_Matrix)
  TEST_METHOD(PixStructAnnotation_MemberFunction)
  TEST_METHOD(PixStructAnnotation_BigMess)
  TEST_METHOD(PixStructAnnotation_AlignedFloat4Arrays)
  TEST_METHOD(PixStructAnnotation_Inheritance)
  TEST_METHOD(PixStructAnnotation_ResourceAsMember)
  TEST_METHOD(PixStructAnnotation_WheresMyDbgValue)

  TEST_METHOD(PixTypeManager_InheritancePointerStruct)
  TEST_METHOD(PixTypeManager_InheritancePointerTypedef)
  TEST_METHOD(PixTypeManager_MatricesInBase)
  TEST_METHOD(PixTypeManager_SamplersAndResources)
  TEST_METHOD(PixTypeManager_XBoxDiaAssert)

  TEST_METHOD(DxcPixDxilDebugInfo_InstructionOffsets)
  TEST_METHOD(DxcPixDxilDebugInfo_GlobalBackedGlobalStaticEmbeddedArrays_NoDbgValue)
  TEST_METHOD(DxcPixDxilDebugInfo_GlobalBackedGlobalStaticEmbeddedArrays_WithDbgValue)
  TEST_METHOD(DxcPixDxilDebugInfo_GlobalBackedGlobalStaticEmbeddedArrays_ArrayInValues)
  TEST_METHOD(DxcPixDxilDebugInfo_StructInheritance)
  TEST_METHOD(DxcPixDxilDebugInfo_StructContainedResource)
  TEST_METHOD(DxcPixDxilDebugInfo_StructStaticInit)
  TEST_METHOD(DxcPixDxilDebugInfo_StructMemberFnFirst)

  TEST_METHOD(VirtualRegisters_InstructionCounts)
  TEST_METHOD(VirtualRegisters_AlignedOffsets)

  TEST_METHOD(RootSignatureUpgrade_SubObjects)
  TEST_METHOD(RootSignatureUpgrade_Annotation)

  TEST_METHOD(SymbolManager_Embedded2DArray)

  dxc::DxcDllSupport m_dllSupport;
  VersionSupportInfo m_ver;

  void CreateBlobPinned(_In_bytecount_(size) LPCVOID data, SIZE_T size,
                        UINT32 codePage, _Outptr_ IDxcBlobEncoding **ppBlob) {
    CComPtr<IDxcLibrary> library;
    IFT(m_dllSupport.CreateInstance(CLSID_DxcLibrary, &library));
    IFT(library->CreateBlobWithEncodingFromPinned(data, size, codePage,
                                                  ppBlob));
  }

  void CreateBlobFromFile(LPCWSTR name, _Outptr_ IDxcBlobEncoding **ppBlob) {
    CComPtr<IDxcLibrary> library;
    IFT(m_dllSupport.CreateInstance(CLSID_DxcLibrary, &library));
    const std::wstring path = hlsl_test::GetPathToHlslDataFile(name);
    IFT(library->CreateBlobFromFile(path.c_str(), nullptr, ppBlob));
  }

  void CreateBlobFromText(_In_z_ const char *pText,
                          _Outptr_ IDxcBlobEncoding **ppBlob) {
    CreateBlobPinned(pText, strlen(pText) + 1, CP_UTF8, ppBlob);
  }

  HRESULT CreateCompiler(IDxcCompiler **ppResult) {
    return m_dllSupport.CreateInstance(CLSID_DxcCompiler, ppResult);
  }

  HRESULT CreateContainerBuilder(IDxcContainerBuilder **ppResult) {
    return m_dllSupport.CreateInstance(CLSID_DxcContainerBuilder, ppResult);
  }

  template <typename T, typename TDefault, typename TIface>
  void WriteIfValue(TIface *pSymbol, std::wstringstream &o,
                    TDefault defaultValue, LPCWSTR valueLabel,
                    HRESULT (__stdcall TIface::*pFn)(T *)) {
    T value;
    HRESULT hr = (pSymbol->*(pFn))(&value);
    if (SUCCEEDED(hr) && value != defaultValue) {
      o << L", " << valueLabel << L": " << value;
    }
  }

  template <typename TIface>
  void WriteIfValue(TIface *pSymbol, std::wstringstream &o,
    LPCWSTR valueLabel, HRESULT(__stdcall TIface::*pFn)(BSTR *)) {
    CComBSTR value;
    HRESULT hr = (pSymbol->*(pFn))(&value);
    if (SUCCEEDED(hr) && value.Length()) {
      o << L", " << valueLabel << L": " << (LPCWSTR)value;
    }
  }
  template <typename TIface>
  void WriteIfValue(TIface *pSymbol, std::wstringstream &o,
    LPCWSTR valueLabel, HRESULT(__stdcall TIface::*pFn)(VARIANT *)) {
    CComVariant value;
    HRESULT hr = (pSymbol->*(pFn))(&value);
    if (SUCCEEDED(hr) && value.vt != VT_NULL && value.vt != VT_EMPTY) {
      if (SUCCEEDED(value.ChangeType(VT_BSTR))) {
        o << L", " << valueLabel << L": " << (LPCWSTR)value.bstrVal;
      }
    }
  }
  template <typename TIface>
  void WriteIfValue(TIface *pSymbol, std::wstringstream &o,
    LPCWSTR valueLabel, HRESULT(__stdcall TIface::*pFn)(IDiaSymbol **)) {
    CComPtr<IDiaSymbol> value;
    HRESULT hr = (pSymbol->*(pFn))(&value);
    if (SUCCEEDED(hr) && value.p != nullptr) {
      DWORD symId;
      value->get_symIndexId(&symId);
      o << L", " << valueLabel << L": id=" << symId;
    }
  }

  std::wstring GetDebugInfoAsText(_In_ IDiaDataSource* pDataSource) {
    CComPtr<IDiaSession> pSession;
    CComPtr<IDiaTable> pTable;
    CComPtr<IDiaEnumTables> pEnumTables;
    std::wstringstream o;

    VERIFY_SUCCEEDED(pDataSource->openSession(&pSession));
    VERIFY_SUCCEEDED(pSession->getEnumTables(&pEnumTables));
    LONG count;
    VERIFY_SUCCEEDED(pEnumTables->get_Count(&count));
    for (LONG i = 0; i < count; ++i) {
      pTable.Release();
      ULONG fetched;
      VERIFY_SUCCEEDED(pEnumTables->Next(1, &pTable, &fetched));
      VERIFY_ARE_EQUAL(fetched, 1);
      CComBSTR tableName;
      VERIFY_SUCCEEDED(pTable->get_name(&tableName));
      o << L"Table: " << (LPWSTR)tableName << std::endl;
      LONG rowCount;
      IFT(pTable->get_Count(&rowCount));
      o << L" Row count: " << rowCount << std::endl;

      for (LONG rowIndex = 0; rowIndex < rowCount; ++rowIndex) {
        CComPtr<IUnknown> item;
        o << L'#' << rowIndex;
        IFT(pTable->Item(rowIndex, &item));
        CComPtr<IDiaSymbol> pSymbol;
        if (SUCCEEDED(item.QueryInterface(&pSymbol))) {
          DWORD symTag;
          DWORD dataKind;
          DWORD locationType;
          DWORD registerId;
          pSymbol->get_symTag(&symTag);
          pSymbol->get_dataKind(&dataKind);
          pSymbol->get_locationType(&locationType);
          pSymbol->get_registerId(&registerId);
          //pSymbol->get_value(&value);

          WriteIfValue(pSymbol.p, o, 0, L"symIndexId", &IDiaSymbol::get_symIndexId);
          o << L", " << SymTagEnumText[symTag];
          if (dataKind != 0) o << L", " << DataKindText[dataKind];
          WriteIfValue(pSymbol.p, o, L"name", &IDiaSymbol::get_name);
          WriteIfValue(pSymbol.p, o, L"lexicalParent", &IDiaSymbol::get_lexicalParent);
          WriteIfValue(pSymbol.p, o, L"type", &IDiaSymbol::get_type);
          WriteIfValue(pSymbol.p, o, 0, L"slot", &IDiaSymbol::get_slot);
          WriteIfValue(pSymbol.p, o, 0, L"platform", &IDiaSymbol::get_platform);
          WriteIfValue(pSymbol.p, o, 0, L"language", &IDiaSymbol::get_language);
          WriteIfValue(pSymbol.p, o, 0, L"frontEndMajor", &IDiaSymbol::get_frontEndMajor);
          WriteIfValue(pSymbol.p, o, 0, L"frontEndMinor", &IDiaSymbol::get_frontEndMinor);
          WriteIfValue(pSymbol.p, o, 0, L"token", &IDiaSymbol::get_token);
          WriteIfValue(pSymbol.p, o,    L"value", &IDiaSymbol::get_value);
          WriteIfValue(pSymbol.p, o, 0, L"code", &IDiaSymbol::get_code);
          WriteIfValue(pSymbol.p, o, 0, L"function", &IDiaSymbol::get_function);
          WriteIfValue(pSymbol.p, o, 0, L"udtKind", &IDiaSymbol::get_udtKind);
          WriteIfValue(pSymbol.p, o, 0, L"hasDebugInfo", &IDiaSymbol::get_hasDebugInfo);
          WriteIfValue(pSymbol.p, o,    L"compilerName", &IDiaSymbol::get_compilerName);
          WriteIfValue(pSymbol.p, o, 0, L"isLocationControlFlowDependent", &IDiaSymbol::get_isLocationControlFlowDependent);
          WriteIfValue(pSymbol.p, o, 0, L"numberOfRows", &IDiaSymbol::get_numberOfRows);
          WriteIfValue(pSymbol.p, o, 0, L"numberOfColumns", &IDiaSymbol::get_numberOfColumns);
          WriteIfValue(pSymbol.p, o, 0, L"length", &IDiaSymbol::get_length);
          WriteIfValue(pSymbol.p, o, 0, L"isMatrixRowMajor", &IDiaSymbol::get_isMatrixRowMajor);
          WriteIfValue(pSymbol.p, o, 0, L"builtInKind", &IDiaSymbol::get_builtInKind);
          WriteIfValue(pSymbol.p, o, 0, L"textureSlot", &IDiaSymbol::get_textureSlot);
          WriteIfValue(pSymbol.p, o, 0, L"memorySpaceKind", &IDiaSymbol::get_memorySpaceKind);
          WriteIfValue(pSymbol.p, o, 0, L"isHLSLData", &IDiaSymbol::get_isHLSLData);
        }

        CComPtr<IDiaSourceFile> pSourceFile;
        if (SUCCEEDED(item.QueryInterface(&pSourceFile))) {
          WriteIfValue(pSourceFile.p, o, 0, L"uniqueId", &IDiaSourceFile::get_uniqueId);
          WriteIfValue(pSourceFile.p, o, L"fileName", &IDiaSourceFile::get_fileName);
        }

        CComPtr<IDiaLineNumber> pLineNumber;
        if (SUCCEEDED(item.QueryInterface(&pLineNumber))) {
          WriteIfValue(pLineNumber.p, o, L"compiland", &IDiaLineNumber::get_compiland);
          //WriteIfValue(pLineNumber.p, o, L"sourceFile", &IDiaLineNumber::get_sourceFile);
          WriteIfValue(pLineNumber.p, o, 0, L"lineNumber", &IDiaLineNumber::get_lineNumber);
          WriteIfValue(pLineNumber.p, o, 0, L"lineNumberEnd", &IDiaLineNumber::get_lineNumberEnd);
          WriteIfValue(pLineNumber.p, o, 0, L"columnNumber", &IDiaLineNumber::get_columnNumber);
          WriteIfValue(pLineNumber.p, o, 0, L"columnNumberEnd", &IDiaLineNumber::get_columnNumberEnd);
          WriteIfValue(pLineNumber.p, o, 0, L"addressSection", &IDiaLineNumber::get_addressSection);
          WriteIfValue(pLineNumber.p, o, 0, L"addressOffset", &IDiaLineNumber::get_addressOffset);
          WriteIfValue(pLineNumber.p, o, 0, L"relativeVirtualAddress", &IDiaLineNumber::get_relativeVirtualAddress);
          WriteIfValue(pLineNumber.p, o, 0, L"virtualAddress", &IDiaLineNumber::get_virtualAddress);
          WriteIfValue(pLineNumber.p, o, 0, L"length", &IDiaLineNumber::get_length);
          WriteIfValue(pLineNumber.p, o, 0, L"sourceFileId", &IDiaLineNumber::get_sourceFileId);
          WriteIfValue(pLineNumber.p, o, 0, L"statement", &IDiaLineNumber::get_statement);
          WriteIfValue(pLineNumber.p, o, 0, L"compilandId", &IDiaLineNumber::get_compilandId);
        }

        CComPtr<IDiaSectionContrib> pSectionContrib;
        if (SUCCEEDED(item.QueryInterface(&pSectionContrib))) {
          WriteIfValue(pSectionContrib.p, o, L"compiland", &IDiaSectionContrib::get_compiland);
          WriteIfValue(pSectionContrib.p, o, 0, L"addressSection", &IDiaSectionContrib::get_addressSection);
          WriteIfValue(pSectionContrib.p, o, 0, L"addressOffset", &IDiaSectionContrib::get_addressOffset);
          WriteIfValue(pSectionContrib.p, o, 0, L"relativeVirtualAddress", &IDiaSectionContrib::get_relativeVirtualAddress);
          WriteIfValue(pSectionContrib.p, o, 0, L"virtualAddress", &IDiaSectionContrib::get_virtualAddress);
          WriteIfValue(pSectionContrib.p, o, 0, L"length", &IDiaSectionContrib::get_length);
          WriteIfValue(pSectionContrib.p, o, 0, L"notPaged", &IDiaSectionContrib::get_notPaged);
          WriteIfValue(pSectionContrib.p, o, 0, L"code", &IDiaSectionContrib::get_code);
          WriteIfValue(pSectionContrib.p, o, 0, L"initializedData", &IDiaSectionContrib::get_initializedData);
          WriteIfValue(pSectionContrib.p, o, 0, L"uninitializedData", &IDiaSectionContrib::get_uninitializedData);
          WriteIfValue(pSectionContrib.p, o, 0, L"remove", &IDiaSectionContrib::get_remove);
          WriteIfValue(pSectionContrib.p, o, 0, L"comdat", &IDiaSectionContrib::get_comdat);
          WriteIfValue(pSectionContrib.p, o, 0, L"discardable", &IDiaSectionContrib::get_discardable);
          WriteIfValue(pSectionContrib.p, o, 0, L"notCached", &IDiaSectionContrib::get_notCached);
          WriteIfValue(pSectionContrib.p, o, 0, L"share", &IDiaSectionContrib::get_share);
          WriteIfValue(pSectionContrib.p, o, 0, L"execute", &IDiaSectionContrib::get_execute);
          WriteIfValue(pSectionContrib.p, o, 0, L"read", &IDiaSectionContrib::get_read);
          WriteIfValue(pSectionContrib.p, o, 0, L"write", &IDiaSectionContrib::get_write);
          WriteIfValue(pSectionContrib.p, o, 0, L"dataCrc", &IDiaSectionContrib::get_dataCrc);
          WriteIfValue(pSectionContrib.p, o, 0, L"relocationsCrc", &IDiaSectionContrib::get_relocationsCrc);
          WriteIfValue(pSectionContrib.p, o, 0, L"compilandId", &IDiaSectionContrib::get_compilandId);
        }

        CComPtr<IDiaSegment> pSegment;
        if (SUCCEEDED(item.QueryInterface(&pSegment))) {
          WriteIfValue(pSegment.p, o, 0, L"frame", &IDiaSegment::get_frame);
          WriteIfValue(pSegment.p, o, 0, L"offset", &IDiaSegment::get_offset);
          WriteIfValue(pSegment.p, o, 0, L"length", &IDiaSegment::get_length);
          WriteIfValue(pSegment.p, o, 0, L"read", &IDiaSegment::get_read);
          WriteIfValue(pSegment.p, o, 0, L"write", &IDiaSegment::get_write);
          WriteIfValue(pSegment.p, o, 0, L"execute", &IDiaSegment::get_execute);
          WriteIfValue(pSegment.p, o, 0, L"addressSection", &IDiaSegment::get_addressSection);
          WriteIfValue(pSegment.p, o, 0, L"relativeVirtualAddress", &IDiaSegment::get_relativeVirtualAddress);
          WriteIfValue(pSegment.p, o, 0, L"virtualAddress", &IDiaSegment::get_virtualAddress);
        }

        CComPtr<IDiaInjectedSource> pInjectedSource;
        if (SUCCEEDED(item.QueryInterface(&pInjectedSource))) {
          WriteIfValue(pInjectedSource.p, o, 0, L"crc", &IDiaInjectedSource::get_crc);
          WriteIfValue(pInjectedSource.p, o, 0, L"length", &IDiaInjectedSource::get_length);
          WriteIfValue(pInjectedSource.p, o, L"filename", &IDiaInjectedSource::get_filename);
          WriteIfValue(pInjectedSource.p, o, L"objectFilename", &IDiaInjectedSource::get_objectFilename);
          WriteIfValue(pInjectedSource.p, o, L"virtualFilename", &IDiaInjectedSource::get_virtualFilename);
          WriteIfValue(pInjectedSource.p, o, 0, L"sourceCompression", &IDiaInjectedSource::get_sourceCompression);
          // get_source is also available
        }

        CComPtr<IDiaFrameData> pFrameData;
        if (SUCCEEDED(item.QueryInterface(&pFrameData))) {
        }

        o << std::endl;
      }
    }

    return o.str();
  }
  std::wstring GetDebugFileContent(_In_ IDiaDataSource *pDataSource) {
    CComPtr<IDiaSession> pSession;
    CComPtr<IDiaTable> pTable;

    CComPtr<IDiaTable> pSourcesTable;

    CComPtr<IDiaEnumTables> pEnumTables;
    std::wstringstream o;

    VERIFY_SUCCEEDED(pDataSource->openSession(&pSession));
    VERIFY_SUCCEEDED(pSession->getEnumTables(&pEnumTables));

    ULONG fetched = 0;
    while (pEnumTables->Next(1, &pTable, &fetched) == S_OK && fetched == 1) {
      CComBSTR name;
      IFT(pTable->get_name(&name));

      if (wcscmp(name, L"SourceFiles") == 0) {
        pSourcesTable = pTable.Detach();
        continue;
      }

      pTable.Release();
    }

    if (!pSourcesTable) {
      return L"cannot find source";
    }

    // Get source file contents.
    // NOTE: "SourceFiles" has the root file first while "InjectedSources" is in
    // alphabetical order.
    //       It is important to keep the root file first for recompilation, so
    //       iterate "SourceFiles" and look up the corresponding injected
    //       source.
    LONG count;
    IFT(pSourcesTable->get_Count(&count));

    CComPtr<IDiaSourceFile> pSourceFile;
    CComBSTR pName;
    CComPtr<IUnknown> pSymbolUnk;
    CComPtr<IDiaEnumInjectedSources> pEnumInjectedSources;
    CComPtr<IDiaInjectedSource> pInjectedSource;
    std::wstring sourceText, sourceFilename;

    while (SUCCEEDED(pSourcesTable->Next(1, &pSymbolUnk, &fetched)) &&
           fetched == 1) {
      sourceText = sourceFilename = L"";

      IFT(pSymbolUnk->QueryInterface(&pSourceFile));
      IFT(pSourceFile->get_fileName(&pName));

      IFT(pSession->findInjectedSource(pName, &pEnumInjectedSources));

      if (SUCCEEDED(pEnumInjectedSources->get_Count(&count)) && count == 1) {
        IFT(pEnumInjectedSources->Item(0, &pInjectedSource));

        DWORD cbData = 0;
        std::string tempString;
        CComBSTR bstr;
        IFT(pInjectedSource->get_filename(&bstr));
        IFT(pInjectedSource->get_source(0, &cbData, nullptr));

        tempString.resize(cbData);
        IFT(pInjectedSource->get_source(
            cbData, &cbData, reinterpret_cast<BYTE *>(&tempString[0])));

        CA2W tempWString(tempString.data());
        o << tempWString.m_psz;
      }
      pSymbolUnk.Release();
    }

    return o.str();
  }

  struct LineNumber { DWORD line; DWORD rva; };
  std::vector<LineNumber> ReadLineNumbers(IDiaEnumLineNumbers *pEnumLineNumbers) {
    std::vector<LineNumber> lines;
    CComPtr<IDiaLineNumber> pLineNumber;
    DWORD lineCount;
    while (SUCCEEDED(pEnumLineNumbers->Next(1, &pLineNumber, &lineCount)) && lineCount == 1)
    {
      DWORD line;
      DWORD rva;
      VERIFY_SUCCEEDED(pLineNumber->get_lineNumber(&line));
      VERIFY_SUCCEEDED(pLineNumber->get_relativeVirtualAddress(&rva));
      lines.push_back({ line, rva });
      pLineNumber.Release();
    }
    return lines;
  }
 
  std::string GetOption(std::string &cmd, char *opt) {
    std::string option = cmd.substr(cmd.find(opt));
    option = option.substr(option.find_first_of(' '));
    option = option.substr(option.find_first_not_of(' '));
    return option.substr(0, option.find_first_of(' '));
  }

  HRESULT CreateDiaSourceForCompile(const char* hlsl,
    IDiaDataSource** ppDiaSource)
  {
    if (!ppDiaSource)
      return E_POINTER;

    CComPtr<IDxcCompiler> pCompiler;
    CComPtr<IDxcOperationResult> pResult;
    CComPtr<IDxcBlobEncoding> pSource;
    CComPtr<IDxcBlob> pProgram;

    VERIFY_SUCCEEDED(CreateCompiler(&pCompiler));
    CreateBlobFromText(hlsl, &pSource);
    LPCWSTR args[] = { L"/Zi", L"/Qembed_debug", L"/Od" };
    VERIFY_SUCCEEDED(pCompiler->Compile(pSource, L"source.hlsl", L"main",
      L"ps_6_0", args, _countof(args), nullptr, 0, nullptr, &pResult));
    
    HRESULT compilationStatus;
    VERIFY_SUCCEEDED(pResult->GetStatus(&compilationStatus));
    if (FAILED(compilationStatus))
    {
      CComPtr<IDxcBlobEncoding> pErrros;
      VERIFY_SUCCEEDED(pResult->GetErrorBuffer(&pErrros));
      CA2W errorTextW(static_cast<const char *>(pErrros->GetBufferPointer()), CP_UTF8);
      WEX::Logging::Log::Error(errorTextW);
    }

    VERIFY_SUCCEEDED(pResult->GetResult(&pProgram));

    // Disassemble the compiled (stripped) program.
    {
      CComPtr<IDxcBlobEncoding> pDisassembly;
      VERIFY_SUCCEEDED(pCompiler->Disassemble(pProgram, &pDisassembly));
      std::string disText = BlobToUtf8(pDisassembly);
      CA2W disTextW(disText.c_str(), CP_UTF8);
      //WEX::Logging::Log::Comment(disTextW);
    }

    auto annotated = WrapInNewContainer(RunAnnotationPasses(pProgram).blob);

    // CONSIDER: have the dia data source look for the part if passed a whole container.
    CComPtr<IDiaDataSource> pDiaSource;
    CComPtr<IStream> pProgramStream;
    CComPtr<IDxcLibrary> pLib;
    VERIFY_SUCCEEDED(m_dllSupport.CreateInstance(CLSID_DxcLibrary, &pLib));
    const hlsl::DxilContainerHeader *pContainer = hlsl::IsDxilContainerLike(
        annotated->GetBufferPointer(), annotated->GetBufferSize());
    VERIFY_IS_NOT_NULL(pContainer);
    hlsl::DxilPartIterator partIter =
        std::find_if(hlsl::begin(pContainer), hlsl::end(pContainer),
                     hlsl::DxilPartIsType(hlsl::DFCC_ShaderDebugInfoDXIL));
    const hlsl::DxilProgramHeader *pProgramHeader =
        (const hlsl::DxilProgramHeader *)hlsl::GetDxilPartData(*partIter);
    uint32_t bitcodeLength;
    const char *pBitcode;
    CComPtr<IDxcBlob> pProgramPdb;
    hlsl::GetDxilProgramBitcode(pProgramHeader, &pBitcode, &bitcodeLength);
    VERIFY_SUCCEEDED(pLib->CreateBlobFromBlob(
        annotated, pBitcode - (char *)annotated->GetBufferPointer(),
        bitcodeLength,
        &pProgramPdb));

    // Disassemble the program with debug information.
    {
      CComPtr<IDxcBlobEncoding> pDbgDisassembly;
      VERIFY_SUCCEEDED(pCompiler->Disassemble(pProgramPdb, &pDbgDisassembly));
      std::string disText = BlobToUtf8(pDbgDisassembly);
      CA2W disTextW(disText.c_str(), CP_UTF8);
      //WEX::Logging::Log::Comment(disTextW);
    }

    // Create a short text dump of debug information.
    VERIFY_SUCCEEDED(pLib->CreateStreamFromBlobReadOnly(pProgramPdb, &pProgramStream));
    VERIFY_SUCCEEDED(m_dllSupport.CreateInstance(CLSID_DxcDiaDataSource, &pDiaSource));
    VERIFY_SUCCEEDED(pDiaSource->loadDataFromIStream(pProgramStream));
    *ppDiaSource = pDiaSource.Detach();
    return S_OK;
  }

  CComPtr<IDxcBlob> Compile(
    const char* hlsl,
    const wchar_t* target,
    std::vector<const wchar_t*> extraArgs = {},
    const wchar_t* entry = L"main")
  {
    CComPtr<IDxcCompiler> pCompiler;
    CComPtr<IDxcOperationResult> pResult;
    CComPtr<IDxcBlobEncoding> pSource;

    VERIFY_SUCCEEDED(CreateCompiler(&pCompiler));
    CreateBlobFromText(hlsl, &pSource);
    std::vector<const wchar_t*>  args = { L"/Zi", L"/Qembed_debug" };
    args.insert(args.end(), extraArgs.begin(), extraArgs.end());
    VERIFY_SUCCEEDED(pCompiler->Compile(pSource, L"source.hlsl", entry,
      target, args.data(), static_cast<UINT32>(args.size()), nullptr, 0, nullptr, &pResult));

    HRESULT compilationStatus;
    VERIFY_SUCCEEDED(pResult->GetStatus(&compilationStatus));
    if (FAILED(compilationStatus))
    {
      CComPtr<IDxcBlobEncoding> pErrros;
      VERIFY_SUCCEEDED(pResult->GetErrorBuffer(&pErrros));
      CA2W errorTextW(static_cast<const char*>(pErrros->GetBufferPointer()), CP_UTF8);
      WEX::Logging::Log::Error(errorTextW);
      return {};
    }

#if 0 //handy for debugging
    {
      CComPtr<IDxcBlob> pProgram;
      CheckOperationSucceeded(pResult, &pProgram);

      CComPtr<IDxcLibrary> pLib;
      VERIFY_SUCCEEDED(m_dllSupport.CreateInstance(CLSID_DxcLibrary, &pLib));
      const hlsl::DxilContainerHeader *pContainer = hlsl::IsDxilContainerLike(
          pProgram->GetBufferPointer(), pProgram->GetBufferSize());
      VERIFY_IS_NOT_NULL(pContainer);
      hlsl::DxilPartIterator partIter =
          std::find_if(hlsl::begin(pContainer), hlsl::end(pContainer),
                       hlsl::DxilPartIsType(hlsl::DFCC_ShaderDebugInfoDXIL));
      const hlsl::DxilProgramHeader *pProgramHeader =
          (const hlsl::DxilProgramHeader *)hlsl::GetDxilPartData(*partIter);
      uint32_t bitcodeLength;
      const char *pBitcode;
      CComPtr<IDxcBlob> pProgramPdb;
      hlsl::GetDxilProgramBitcode(pProgramHeader, &pBitcode, &bitcodeLength);
      VERIFY_SUCCEEDED(pLib->CreateBlobFromBlob(
          pProgram, pBitcode - (char *)pProgram->GetBufferPointer(),
          bitcodeLength, &pProgramPdb));

      CComPtr<IDxcBlobEncoding> pDbgDisassembly;
      VERIFY_SUCCEEDED(pCompiler->Disassemble(pProgramPdb, &pDbgDisassembly));
      std::string disText = BlobToUtf8(pDbgDisassembly);
      CA2W disTextW(disText.c_str(), CP_UTF8);
      WEX::Logging::Log::Comment(disTextW);
    }
#endif

    CComPtr<IDxcBlob> pProgram;
    VERIFY_SUCCEEDED(pResult->GetResult(&pProgram));

    return pProgram;
  }

  CComPtr<IDxcBlob> ExtractDxilPart(IDxcBlob *pProgram) {
    CComPtr<IDxcLibrary> pLib;
    VERIFY_SUCCEEDED(m_dllSupport.CreateInstance(CLSID_DxcLibrary, &pLib));
    const hlsl::DxilContainerHeader *pContainer = hlsl::IsDxilContainerLike(
        pProgram->GetBufferPointer(), pProgram->GetBufferSize());
    VERIFY_IS_NOT_NULL(pContainer);
    hlsl::DxilPartIterator partIter =
        std::find_if(hlsl::begin(pContainer), hlsl::end(pContainer),
                     hlsl::DxilPartIsType(hlsl::DFCC_DXIL));
    const hlsl::DxilProgramHeader *pProgramHeader =
        (const hlsl::DxilProgramHeader *)hlsl::GetDxilPartData(*partIter);
    uint32_t bitcodeLength;
    const char *pBitcode;
    CComPtr<IDxcBlob> pDxilBits;
    hlsl::GetDxilProgramBitcode(pProgramHeader, &pBitcode, &bitcodeLength);
    VERIFY_SUCCEEDED(pLib->CreateBlobFromBlob(
        pProgram, pBitcode - (char *)pProgram->GetBufferPointer(),
        bitcodeLength, &pDxilBits));
    return pDxilBits;
  }

  struct ValueLocation
  {
    int base;
    int count;
  };

  struct PassOutput
  {
    CComPtr<IDxcBlob> blob;
    std::vector<ValueLocation> valueLocations;
    std::vector<std::string> lines;
  };

  std::string ExtractBracedSubstring(std::string const &line) {
    auto open = line.find('{');
    auto close = line.find('}');
    if (open != std::string::npos && close != std::string::npos &&
        open + 1 < close) {
      return line.substr(open + 1, close - open - 1);
    }
    return "";
  }

  int ExtractMetaInt32Value(std::string const &token) {
    if (token.substr(0, 5) == " i32 ") {
      return atoi(token.c_str() + 5);
    }
    return -1;
  }

  std::map<int, std::pair<int, int>>
  MetaDataKeyToRegisterNumber(std::vector<std::string> const &lines) {
    // Find lines of the exemplary form
    // "!249 = !{i32 0, i32 20}"  (in the case of a DXIL value)
    // "!196 = !{i32 1, i32 5, i32 1}" (in the case of a DXIL alloca reg)
    // The first i32 is a tag indicating what type of metadata this is.
    // It doesn't matter if we parse poorly and find some data that don't match
    // this pattern, as long as we do find all the data that do match (we won't
    // be looking up the non-matchers in the resultant map anyway).

    constexpr char *valueMetaDataAssignment = "= !{i32 0, ";
    constexpr char *allocaMetaDataAssignment = "= !{i32 1, ";

    std::map<int, std::pair<int, int>> ret;
    for (auto const &line : lines) {
      if (line[0] == '!') {
        if (line.find(valueMetaDataAssignment) != std::string::npos ||
            line.find(allocaMetaDataAssignment) != std::string::npos) {
          int key = atoi(line.c_str() + 1);
          if (key != 0) {
            std::string bitInBraces = ExtractBracedSubstring(line); 
            if (bitInBraces != "") {
              auto tokens = Tokenize(bitInBraces.c_str(), ",");
              if (tokens.size() == 2) {
                auto value = ExtractMetaInt32Value(tokens[1]);
                if (value != -1) {
                  ret[key] = {value, 1};
                }
              }
              if (tokens.size() == 3) {
                auto value0 = ExtractMetaInt32Value(tokens[1]);
                if (value0 != -1) {
                  auto value1 = ExtractMetaInt32Value(tokens[2]);
                  if (value1 != -1) {
                    ret[key] = {value0, value1};
                  }
                }
              }
            }
          }
        }
      }
    }
    return ret;
  }

  std::string ExtractValueName(std::string const &line) {
    auto foundEquals = line.find('=');
    if (foundEquals != std::string::npos && foundEquals > 4) {
      return line.substr(2, foundEquals - 3);
    }
    return "";
  }

    using DxilRegisterToNameMap = std::map<std::pair<int, int>, std::string>;

  void CheckForAndInsertMapEntryIfFound(
        DxilRegisterToNameMap &registerToNameMap,
      std::map<int, std::pair<int, int>> const &metaDataKeyToValue,
      std::string const &line, char const *tag, size_t tagLength) {
    auto foundAlloca = line.find(tag); 
    if (foundAlloca != std::string::npos) {
      auto valueName = ExtractValueName(line);
      if (valueName != "") {
        int key = atoi(line.c_str() + foundAlloca + tagLength);
        auto foundKey = metaDataKeyToValue.find(key);
        if (foundKey != metaDataKeyToValue.end()) {
          registerToNameMap[foundKey->second] = valueName;
        }
      }
    }
  }

  // Here's some exemplary DXIL to help understand what's going on:
  //
  //  %5 = alloca [1 x float], i32 0, !pix-alloca-reg !196
  //  %25 = call float @dx.op.loadInput.f32(...), !pix-dxil-reg !255
  //
  // The %5 is an alloca name, and the %25 is a regular llvm value.
  // The meta-data tags !pix-alloca-reg and !pix-dxil-reg denote this,
  // and provide keys !196 and !255 respectively.
  // Those keys are then given values later on in the DXIL like this:
  //
  // !196 = !{i32 1, i32 5, i32 1}  (5 is the base alloca, 1 is the offset into
  // it) !255 = !{i32 0, i32 23}
  //
  // So the task is first to find all of those key/value pairs and make a map
  // from e.g. !196 to, e.g., (5,1), and then to find all of the alloca and reg
  // tags and look up the keys in said map to build the map we're actually
  // looking for, with key->values like e.g. "%5"->(5,1) and "%25"->(23)

DxilRegisterToNameMap BuildDxilRegisterToNameMap(char const *disassembly) {
    DxilRegisterToNameMap ret;

    auto lines = Tokenize(disassembly, "\n");

    auto metaDataKeyToValue = MetaDataKeyToRegisterNumber(lines);

    for (auto const &line : lines) {
      if (line[0] == '!') {
        // Stop searching for values when we've run into the metadata region of
        // the disassembly
        break;
      }
      const char allocaTag[] = "!pix-alloca-reg !";
      CheckForAndInsertMapEntryIfFound(ret, metaDataKeyToValue, line, allocaTag,
                                       _countof(allocaTag) - 1);
      const char valueTag[] = "!pix-dxil-reg !";
      CheckForAndInsertMapEntryIfFound(ret, metaDataKeyToValue, line, valueTag,
                                       _countof(valueTag) - 1);
    }
    return ret;
  }

static std::string ToString(std::wstring from)
{
    std::string ret;
    ret.assign(from.data(), from.data() + from.size());
    return ret;
}

  PassOutput RunValueToDeclarePass(IDxcBlob * dxil, int startingLineNumber = 0)
  {
    CComPtr<IDxcOptimizer> pOptimizer;
    VERIFY_SUCCEEDED(
        m_dllSupport.CreateInstance(CLSID_DxcOptimizer, &pOptimizer));
    std::vector<LPCWSTR> Options;
    Options.push_back(L"-opt-mod-passes");
    Options.push_back(L"-dxil-dbg-value-to-dbg-declare");

    CComPtr<IDxcBlob> pOptimizedModule;
    CComPtr<IDxcBlobEncoding> pText;
    VERIFY_SUCCEEDED(pOptimizer->RunOptimizer(
        dxil, Options.data(), Options.size(), &pOptimizedModule, &pText));

    std::string outputText;
    if (pText->GetBufferSize() != 0)
    {
      outputText = reinterpret_cast<const char*>(pText->GetBufferPointer());
    }

    return {
        std::move(pOptimizedModule), {}, Tokenize(outputText.c_str(), "\n")};
  }

  PassOutput RunAnnotationPasses(IDxcBlob *dxil, int startingLineNumber = 0) {
    CComPtr<IDxcOptimizer> pOptimizer;
    VERIFY_SUCCEEDED(
        m_dllSupport.CreateInstance(CLSID_DxcOptimizer, &pOptimizer));
    std::vector<LPCWSTR> Options;
    Options.push_back(L"-opt-mod-passes");
    Options.push_back(L"-dxil-dbg-value-to-dbg-declare");
    std::wstring annotationCommandLine =
        L"-dxil-annotate-with-virtual-regs,startInstruction=" +
        std::to_wstring(startingLineNumber);
    Options.push_back(annotationCommandLine.c_str());

    CComPtr<IDxcBlob> pOptimizedModule;
    CComPtr<IDxcBlobEncoding> pText;
    VERIFY_SUCCEEDED(pOptimizer->RunOptimizer(
        dxil, Options.data(), Options.size(), &pOptimizedModule, &pText));

    std::string outputText;
    if (pText->GetBufferSize() != 0) {
      outputText = reinterpret_cast<const char *>(pText->GetBufferPointer());
    }

    auto disasm = ToString(Disassemble(pOptimizedModule));

    auto registerToName = BuildDxilRegisterToNameMap(disasm.c_str());

    std::vector<ValueLocation> valueLocations;

    for (auto const &r2n : registerToName) {
      valueLocations.push_back({r2n.first.first, r2n.first.second});
    }

    return {std::move(pOptimizedModule), std::move(valueLocations),
            Tokenize(outputText.c_str(), "\n")};
  }

  std::wstring Disassemble(IDxcBlob * pProgram)
  {
    CComPtr<IDxcCompiler> pCompiler;
    VERIFY_SUCCEEDED(CreateCompiler(&pCompiler));

    CComPtr<IDxcBlobEncoding> pDbgDisassembly;
    VERIFY_SUCCEEDED(pCompiler->Disassemble(pProgram, &pDbgDisassembly));
    std::string disText = BlobToUtf8(pDbgDisassembly);
    CA2W disTextW(disText.c_str(), CP_UTF8);
    return std::wstring(disTextW);
  }

  CComPtr<IDxcBlob> FindModule(hlsl::DxilFourCC fourCC, IDxcBlob *pSource)
  {
    const UINT32 BC_C0DE = ((INT32)(INT8)'B' | (INT32)(INT8)'C' << 8 |
                            (INT32)0xDEC0 << 16); // BC0xc0de in big endian
    const char *pBitcode = nullptr;
    const hlsl::DxilPartHeader *pDxilPartHeader =
        (hlsl::DxilPartHeader *)
            pSource->GetBufferPointer(); // Initialize assuming that source is
                                         // starting with DXIL part

    if (BC_C0DE == *(UINT32 *)pSource->GetBufferPointer()) {
      return pSource;
    }
    if (hlsl::IsValidDxilContainer(
            (hlsl::DxilContainerHeader *)pSource->GetBufferPointer(),
            pSource->GetBufferSize())) {
      hlsl::DxilContainerHeader *pDxilContainerHeader =
          (hlsl::DxilContainerHeader *)pSource->GetBufferPointer();
      pDxilPartHeader =
          *std::find_if(begin(pDxilContainerHeader), end(pDxilContainerHeader),
                        hlsl::DxilPartIsType(fourCC));
    }
    if (fourCC == pDxilPartHeader->PartFourCC) {
      UINT32 pBlobSize;
      hlsl::DxilProgramHeader *pDxilProgramHeader =
          (hlsl::DxilProgramHeader *)(pDxilPartHeader + 1);
      hlsl::GetDxilProgramBitcode(pDxilProgramHeader, &pBitcode, &pBlobSize);
      UINT32 offset =
          (UINT32)(pBitcode - (const char *)pSource->GetBufferPointer());
      CComPtr<IDxcLibrary> library;
      IFT(m_dllSupport.CreateInstance(CLSID_DxcLibrary, &library));
      CComPtr<IDxcBlob> targetBlob;
      library->CreateBlobFromBlob(pSource, offset, pBlobSize, &targetBlob);
      return targetBlob;
    }
    return {};
  }


  void ReplaceDxilBlobPart(
      const void *originalShaderBytecode, SIZE_T originalShaderLength,
      IDxcBlob *pNewDxilBlob, IDxcBlob **ppNewShaderOut)
  {
    CComPtr<IDxcLibrary> pLibrary;
    IFT(m_dllSupport.CreateInstance(CLSID_DxcLibrary, &pLibrary));

    CComPtr<IDxcBlob> pNewContainer;

    // Use the container assembler to build a new container from the
    // recently-modified DXIL bitcode. This container will contain new copies of
    // things like input signature etc., which will supersede the ones from the
    // original compiled shader's container.
    {
      CComPtr<IDxcAssembler> pAssembler;
      IFT(m_dllSupport.CreateInstance(CLSID_DxcAssembler, &pAssembler));

      CComPtr<IDxcOperationResult> pAssembleResult;
      VERIFY_SUCCEEDED(
          pAssembler->AssembleToContainer(pNewDxilBlob, &pAssembleResult));

      CComPtr<IDxcBlobEncoding> pAssembleErrors;
      VERIFY_SUCCEEDED(
          pAssembleResult->GetErrorBuffer(&pAssembleErrors));

      if (pAssembleErrors && pAssembleErrors->GetBufferSize() != 0) {
        OutputDebugStringA(
            static_cast<LPCSTR>(pAssembleErrors->GetBufferPointer()));
        VERIFY_SUCCEEDED(E_FAIL);
      }

      VERIFY_SUCCEEDED(pAssembleResult->GetResult(&pNewContainer));
    }

    // Now copy over the blobs from the original container that won't have been
    // invalidated by changing the shader code itself, using the container
    // reflection API
    { 
      // Wrap the original code in a container blob
      CComPtr<IDxcBlobEncoding> pContainer;
      VERIFY_SUCCEEDED(
          pLibrary->CreateBlobWithEncodingFromPinned(
              static_cast<LPBYTE>(const_cast<void *>(originalShaderBytecode)),
              static_cast<UINT32>(originalShaderLength), CP_ACP, &pContainer));

      CComPtr<IDxcContainerReflection> pReflection;
      IFT(m_dllSupport.CreateInstance(CLSID_DxcContainerReflection, &pReflection));

      // Load the reflector from the original shader
      VERIFY_SUCCEEDED(pReflection->Load(pContainer));

      UINT32 partIndex;

      if (SUCCEEDED(pReflection->FindFirstPartKind(hlsl::DFCC_PrivateData,
                                                   &partIndex))) {
        CComPtr<IDxcBlob> pPart;
        VERIFY_SUCCEEDED(
            pReflection->GetPartContent(partIndex, &pPart));

        CComPtr<IDxcContainerBuilder> pContainerBuilder;
        IFT(m_dllSupport.CreateInstance(CLSID_DxcContainerBuilder,
                                        &pContainerBuilder));

        VERIFY_SUCCEEDED(
            pContainerBuilder->Load(pNewContainer));

        VERIFY_SUCCEEDED(
            pContainerBuilder->AddPart(hlsl::DFCC_PrivateData, pPart));

        CComPtr<IDxcOperationResult> pBuildResult;

        VERIFY_SUCCEEDED(
            pContainerBuilder->SerializeContainer(&pBuildResult));

        CComPtr<IDxcBlobEncoding> pBuildErrors;
        VERIFY_SUCCEEDED(
            pBuildResult->GetErrorBuffer(&pBuildErrors));

        if (pBuildErrors && pBuildErrors->GetBufferSize() != 0) {
          OutputDebugStringA(
              reinterpret_cast<LPCSTR>(pBuildErrors->GetBufferPointer()));
          VERIFY_SUCCEEDED(E_FAIL);
        }

        VERIFY_SUCCEEDED(
            pBuildResult->GetResult(&pNewContainer));
      }
    }

    *ppNewShaderOut = pNewContainer.Detach();
  }

  class ModuleAndHangersOn
  {
    std::unique_ptr<llvm::LLVMContext> llvmContext;
    std::unique_ptr<llvm::Module> llvmModule;
    DxilModule* dxilModule;

  public:
    ModuleAndHangersOn(IDxcBlob* pBlob)
    {
      // Verify we have a valid dxil container.
      const DxilContainerHeader *pContainer = IsDxilContainerLike(
          pBlob->GetBufferPointer(), pBlob->GetBufferSize());
      VERIFY_IS_NOT_NULL(pContainer);
      VERIFY_IS_TRUE(IsValidDxilContainer(pContainer, pBlob->GetBufferSize()));

      // Get Dxil part from container.
      DxilPartIterator it =
          std::find_if(begin(pContainer), end(pContainer),
                       DxilPartIsType(DFCC_ShaderDebugInfoDXIL));
      VERIFY_IS_FALSE(it == end(pContainer));

      const DxilProgramHeader *pProgramHeader =
          reinterpret_cast<const DxilProgramHeader *>(GetDxilPartData(*it));
      VERIFY_IS_TRUE(IsValidDxilProgramHeader(pProgramHeader, (*it)->PartSize));

      // Get a pointer to the llvm bitcode.
      const char *pIL;
      uint32_t pILLength;
      GetDxilProgramBitcode(pProgramHeader, &pIL, &pILLength);

      // Parse llvm bitcode into a module.
      std::unique_ptr<llvm::MemoryBuffer> pBitcodeBuf(
          llvm::MemoryBuffer::getMemBuffer(llvm::StringRef(pIL, pILLength), "",
                                           false));

      llvmContext.reset(new llvm::LLVMContext);

      llvm::ErrorOr<std::unique_ptr<llvm::Module>> pModule(
          llvm::parseBitcodeFile(pBitcodeBuf->getMemBufferRef(),
                                 *llvmContext));
      if (std::error_code ec = pModule.getError()) {
        VERIFY_FAIL();
      }

      llvmModule = std::move(pModule.get());

      dxilModule =
          DxilModule::TryGetDxilModule(llvmModule.get());
    }

    DxilModule& GetDxilModule()
    {
      return *dxilModule;
    }
  };

  struct AggregateOffsetAndSize
  {
    unsigned countOfMembers;
    unsigned offset;
    unsigned size;
  };
  struct AllocaWrite {
    std::string memberName;
    uint32_t regBase;
    uint32_t regSize;
    uint64_t index;
  };
  struct TestableResults
  {
    std::vector<AggregateOffsetAndSize> OffsetAndSizes;
    std::vector<AllocaWrite> AllocaWrites;
  };

  TestableResults TestStructAnnotationCase(const char *hlsl,
                                           const wchar_t *optimizationLevel,
                                           bool validateCoverage = true,
                                           const wchar_t *profile = L"as_6_5");
  void ValidateAllocaWrite(std::vector<AllocaWrite> const& allocaWrites, size_t index, const char* name);
  CComPtr<IDxcBlob> RunShaderAccessTrackingPass(IDxcBlob* blob);
  std::string RunDxilPIXAddTidToAmplificationShaderPayloadPass(IDxcBlob *
                                                                 blob);
  CComPtr<IDxcBlob> RunDxilPIXMeshShaderOutputPass(IDxcBlob* blob);
  void CompileAndRunAnnotationAndGetDebugPart(
      dxc::DxcDllSupport &dllSupport, const char *source, const wchar_t *profile,
      IDxcBlob **ppDebugPart, std::vector<const wchar_t *> extraArgs = {});
  void CompileAndRunValueToDeclareAndGetDebugPart(
      dxc::DxcDllSupport &dllSupport, const char *source, wchar_t *profile,
      IDxcBlob **ppDebugPart);
  void CompileAndRunAnnotationAndLoadDiaSource(
      dxc::DxcDllSupport &dllSupport, const char *source, const wchar_t *profile,
      IDiaDataSource **ppDataSource,
      std::vector<const wchar_t *> extraArgs = {});

  struct VariableComponentInfo {
    std::wstring Name;
    std::wstring Type;
  };
  void TestGlobalStaticCase(
      const char *hlsl, const wchar_t * profile, const char *lineAtWhichToExamineVariables,
      std::vector<VariableComponentInfo> const &ExpectedVariables);
  CComPtr<IDxcPixDxilDebugInfo>
  CompileAndCreateDxcDebug(const char *hlsl, const wchar_t *profile);
  CComPtr<IDxcPixDxilLiveVariables>
  GetLiveVariablesAt(const char *hlsl,
                     const char *lineAtWhichToExamineVariables,
                     IDxcPixDxilDebugInfo *dxilDebugger);
private:
  CComPtr<IDxcBlob> WrapInNewContainer(IDxcBlob * part);
};


bool PixTest::InitSupport() {
  if (!m_dllSupport.IsEnabled()) {
    VERIFY_SUCCEEDED(m_dllSupport.Initialize());
    m_ver.Initialize(m_dllSupport);
  }
  return true;
}

TEST_F(PixTest, CompileWhenDebugThenDIPresent) {
  // BUG: the first test written was of this form:
  // float4 local = 0; return local;
  //
  // However we get no numbers because of the _wrapper form
  // that exports the zero initialization from main into
  // a global can't be attributed to any particular location
  // within main, and everything in main is eventually folded away.
  //
  // Making the function do a bit more work by calling an intrinsic
  // helps this case.
  CComPtr<IDiaDataSource> pDiaSource;
  VERIFY_SUCCEEDED(CreateDiaSourceForCompile(
    "float4 main(float4 pos : SV_Position) : SV_Target {\r\n"
    "  float4 local = abs(pos);\r\n"
    "  return local;\r\n"
    "}", &pDiaSource));
  std::wstring diaDump = GetDebugInfoAsText(pDiaSource).c_str();
  //WEX::Logging::Log::Comment(GetDebugInfoAsText(pDiaSource).c_str());

  // Very basic tests - we have basic symbols, line numbers, and files with sources.
  VERIFY_IS_NOT_NULL(wcsstr(diaDump.c_str(), L"symIndexId: 5, CompilandEnv, name: hlslTarget, lexicalParent: id=2, value: ps_6_0"));
  VERIFY_IS_NOT_NULL(wcsstr(diaDump.c_str(), L"lineNumber: 2"));
  VERIFY_IS_NOT_NULL(wcsstr(diaDump.c_str(), L"length: 99, filename: source.hlsl"));
  std::wstring diaFileContent = GetDebugFileContent(pDiaSource).c_str();
  VERIFY_IS_NOT_NULL(wcsstr(diaFileContent.c_str(), L"loat4 main(float4 pos : SV_Position) : SV_Target"));
#if SUPPORT_FXC_PDB
  // Now, fake it by loading from a .pdb!
  VERIFY_SUCCEEDED(CoInitializeEx(0, COINITBASE_MULTITHREADED));
  const wchar_t path[] = L"path-to-fxc-blob.bin";
  pDiaSource.Release();
  pProgramStream.Release();
  CComPtr<IDxcBlobEncoding> fxcBlob;
  CComPtr<IDxcBlob> pdbBlob;
  VERIFY_SUCCEEDED(pLib->CreateBlobFromFile(path, nullptr, &fxcBlob));
  std::string s = DumpParts(fxcBlob);
  CA2W sW(s.c_str(), CP_UTF8);
  WEX::Logging::Log::Comment(sW);
  VERIFY_SUCCEEDED(CreateDiaSourceFromDxbcBlob(pLib, fxcBlob, &pDiaSource));
  WEX::Logging::Log::Comment(GetDebugInfoAsText(pDiaSource).c_str());
#endif
}

TEST_F(PixTest, CompileDebugDisasmPDB) {
  const char *hlsl = R"(
    [RootSignature("")]
    float main(float pos : A) : SV_Target {
      float x = abs(pos);
      float y = sin(pos);
      float z = x + y;
      return z;
    }
  )";
  CComPtr<IDxcLibrary> pLib;
  VERIFY_SUCCEEDED(m_dllSupport.CreateInstance(CLSID_DxcLibrary, &pLib));

  CComPtr<IDxcCompiler> pCompiler;
  CComPtr<IDxcCompiler2> pCompiler2;

  CComPtr<IDxcOperationResult> pResult;
  CComPtr<IDxcBlobEncoding> pSource;
  CComPtr<IDxcBlob> pProgram;
  CComPtr<IDxcBlob> pPdbBlob;
  WCHAR *pDebugName = nullptr;

  VERIFY_SUCCEEDED(CreateCompiler(&pCompiler));
  VERIFY_SUCCEEDED(pCompiler.QueryInterface(&pCompiler2));
  CreateBlobFromText(hlsl, &pSource);
  LPCWSTR args[] = { L"/Zi", L"/Qembed_debug" };
  VERIFY_SUCCEEDED(pCompiler2->CompileWithDebug(pSource, L"source.hlsl", L"main",
    L"ps_6_0", args, _countof(args), nullptr, 0, nullptr, &pResult, &pDebugName, &pPdbBlob));
  VERIFY_SUCCEEDED(pResult->GetResult(&pProgram));

  // Test that disassembler can consume a PDB container
  CComPtr<IDxcBlobEncoding> pDisasm;
  VERIFY_SUCCEEDED(pCompiler->Disassemble(pPdbBlob, &pDisasm));
}

// Test that the new PDB format still works with Dia
TEST_F(PixTest, CompileDebugPDB) {
  const char *hlsl = R"(
    [RootSignature("")]
    float main(float pos : A) : SV_Target {
      float x = abs(pos);
      float y = sin(pos);
      float z = x + y;
      return z;
    }
  )";
  CComPtr<IDxcLibrary> pLib;
  VERIFY_SUCCEEDED(m_dllSupport.CreateInstance(CLSID_DxcLibrary, &pLib));

  CComPtr<IDxcCompiler> pCompiler;
  CComPtr<IDxcCompiler2> pCompiler2;

  CComPtr<IDxcOperationResult> pResult;
  CComPtr<IDxcBlobEncoding> pSource;
  CComPtr<IDxcBlob> pProgram;
  CComPtr<IDxcBlob> pPdbBlob;
  WCHAR *pDebugName = nullptr;

  VERIFY_SUCCEEDED(CreateCompiler(&pCompiler));
  VERIFY_SUCCEEDED(pCompiler.QueryInterface(&pCompiler2));
  CreateBlobFromText(hlsl, &pSource);
  LPCWSTR args[] = { L"/Zi", L"/Qembed_debug" };
  VERIFY_SUCCEEDED(pCompiler2->CompileWithDebug(pSource, L"source.hlsl", L"main",
    L"ps_6_0", args, _countof(args), nullptr, 0, nullptr, &pResult, &pDebugName, &pPdbBlob));
  VERIFY_SUCCEEDED(pResult->GetResult(&pProgram));

  CComPtr<IDiaDataSource> pDiaSource;
  CComPtr<IStream> pProgramStream;

  VERIFY_SUCCEEDED(pLib->CreateStreamFromBlobReadOnly(pPdbBlob, &pProgramStream));
  VERIFY_SUCCEEDED(m_dllSupport.CreateInstance(CLSID_DxcDiaDataSource, &pDiaSource));
  VERIFY_SUCCEEDED(pDiaSource->loadDataFromIStream(pProgramStream));

  // Test that IDxcContainerReflection can consume a PDB container
  CComPtr<IDxcContainerReflection> pReflection;
  VERIFY_SUCCEEDED(m_dllSupport.CreateInstance(CLSID_DxcContainerReflection, &pReflection));
  VERIFY_SUCCEEDED(pReflection->Load(pPdbBlob));

  UINT32 uDebugInfoIndex = 0;
  VERIFY_SUCCEEDED(pReflection->FindFirstPartKind(hlsl::DFCC_ShaderDebugInfoDXIL, &uDebugInfoIndex));
}

TEST_F(PixTest, DiaLoadBadBitcodeThenFail) {
  CComPtr<IDxcBlob> pBadBitcode;
  CComPtr<IDiaDataSource> pDiaSource;
  CComPtr<IStream> pStream;
  CComPtr<IDxcLibrary> pLib;

  Utf8ToBlob(m_dllSupport, "badcode", &pBadBitcode);
  VERIFY_SUCCEEDED(m_dllSupport.CreateInstance(CLSID_DxcLibrary, &pLib));
  VERIFY_SUCCEEDED(pLib->CreateStreamFromBlobReadOnly(pBadBitcode, &pStream));
  VERIFY_SUCCEEDED(m_dllSupport.CreateInstance(CLSID_DxcDiaDataSource, &pDiaSource));
  VERIFY_FAILED(pDiaSource->loadDataFromIStream(pStream));
}

static void CompileAndGetDebugPart(dxc::DxcDllSupport &dllSupport, const char *source, wchar_t *profile, IDxcBlob **ppDebugPart) {
  CComPtr<IDxcBlob> pContainer;
  CComPtr<IDxcLibrary> pLib;
  CComPtr<IDxcContainerReflection> pReflection;
  UINT32 index;
  std::vector<LPCWSTR> args;
  args.push_back(L"/Zi");
  args.push_back(L"/Qembed_debug");

  VerifyCompileOK(dllSupport, source, profile, args, &pContainer);
  VERIFY_SUCCEEDED(dllSupport.CreateInstance(CLSID_DxcLibrary, &pLib));
  VERIFY_SUCCEEDED(dllSupport.CreateInstance(CLSID_DxcContainerReflection, &pReflection));
  VERIFY_SUCCEEDED(pReflection->Load(pContainer));
  VERIFY_SUCCEEDED(pReflection->FindFirstPartKind(hlsl::DFCC_ShaderDebugInfoDXIL, &index));
  VERIFY_SUCCEEDED(pReflection->GetPartContent(index, ppDebugPart));
}

static void CompileTestAndLoadDiaSource(dxc::DxcDllSupport &dllSupport, const char *source, wchar_t *profile, IDiaDataSource **ppDataSource) {
  CComPtr<IDxcBlob> pDebugContent;
  CComPtr<IStream> pStream;
  CComPtr<IDiaDataSource> pDiaSource;
  CComPtr<IDxcLibrary> pLib;
  VERIFY_SUCCEEDED(dllSupport.CreateInstance(CLSID_DxcLibrary, &pLib));

  CompileAndGetDebugPart(dllSupport, source, profile, &pDebugContent);
  VERIFY_SUCCEEDED(pLib->CreateStreamFromBlobReadOnly(pDebugContent, &pStream));
  VERIFY_SUCCEEDED(dllSupport.CreateInstance(CLSID_DxcDiaDataSource, &pDiaSource));
  VERIFY_SUCCEEDED(pDiaSource->loadDataFromIStream(pStream));
  if (ppDataSource) {
    *ppDataSource = pDiaSource.Detach();
  }
}

static const char EmptyCompute[] = "[numthreads(8,8,1)] void main() { }";

static void CompileTestAndLoadDia(dxc::DxcDllSupport &dllSupport, IDiaDataSource **ppDataSource) {
  CompileTestAndLoadDiaSource(dllSupport, EmptyCompute, L"cs_6_0", ppDataSource);
}

TEST_F(PixTest, DiaLoadDebugSubrangeNegativeThenOK) {
  static const char source[] = R"(
    SamplerState  samp0 : register(s0);
    Texture2DArray tex0 : register(t0);

    float4 foo(Texture2DArray textures[], int idx, SamplerState samplerState, float3 uvw) {
      return textures[NonUniformResourceIndex(idx)].Sample(samplerState, uvw);
    }

    [RootSignature( "DescriptorTable(SRV(t0)), DescriptorTable(Sampler(s0)) " )]
    float4 main(int index : INDEX, float3 uvw : TEXCOORD) : SV_Target {
      Texture2DArray textures[] = {
        tex0,
      };
      return foo(textures, index, samp0, uvw);
    }
  )";

  CComPtr<IDiaDataSource> pDiaDataSource;
  CComPtr<IDiaSession> pDiaSession;
  CompileTestAndLoadDiaSource(m_dllSupport, source, L"ps_6_0", &pDiaDataSource);

  VERIFY_SUCCEEDED(pDiaDataSource->openSession(&pDiaSession));
}

TEST_F(PixTest, DiaLoadRelocatedBitcode) {

  static const char source[] = R"(
    SamplerState  samp0 : register(s0);
    Texture2DArray tex0 : register(t0);

    float4 foo(Texture2DArray textures[], int idx, SamplerState samplerState, float3 uvw) {
      return textures[NonUniformResourceIndex(idx)].Sample(samplerState, uvw);
    }

    [RootSignature( "DescriptorTable(SRV(t0)), DescriptorTable(Sampler(s0)) " )]
    float4 main(int index : INDEX, float3 uvw : TEXCOORD) : SV_Target {
      Texture2DArray textures[] = {
        tex0,
      };
      return foo(textures, index, samp0, uvw);
    }
  )";

  CComPtr<IDxcBlob> pPart;
  CComPtr<IDiaDataSource> pDiaSource;
  CComPtr<IStream> pStream;

  CComPtr<IDxcLibrary> pLib;
  VERIFY_SUCCEEDED(m_dllSupport.CreateInstance(CLSID_DxcLibrary, &pLib));

  CompileAndGetDebugPart(m_dllSupport, source, L"ps_6_0", &pPart);
  const char *pPartData = (char *)pPart->GetBufferPointer();

  // Get program header
  const hlsl::DxilProgramHeader *programHeader = (hlsl::DxilProgramHeader *)pPartData;

  const char *pBitcode = nullptr;
  uint32_t uBitcodeSize = 0;
  hlsl::GetDxilProgramBitcode(programHeader, &pBitcode, &uBitcodeSize);
  VERIFY_IS_TRUE(uBitcodeSize % sizeof(UINT32) == 0);

  size_t uNewGapSize = 4 * 10; // Size of some bytes between program header and bitcode
  size_t uNewSuffixeBytes = 4 * 10; // Size of some random bytes after the program

  hlsl::DxilProgramHeader newProgramHeader = {};
  memcpy(&newProgramHeader, programHeader, sizeof(newProgramHeader));
  newProgramHeader.BitcodeHeader.BitcodeOffset = uNewGapSize + sizeof(newProgramHeader.BitcodeHeader);

  unsigned uNewSizeInBytes = sizeof(newProgramHeader) + uNewGapSize + uBitcodeSize + uNewSuffixeBytes;
  VERIFY_IS_TRUE(uNewSizeInBytes % sizeof(UINT32) == 0);
  newProgramHeader.SizeInUint32 = uNewSizeInBytes / sizeof(UINT32);

  llvm::SmallVector<char, 0> buffer;
  llvm::raw_svector_ostream OS(buffer);

  // Write the header
  OS.write((char *)&newProgramHeader, sizeof(newProgramHeader));

  // Write some garbage between the header and the bitcode
  for (unsigned i = 0; i < uNewGapSize; i++) {
    OS.write(0xFF);
  }

  // Write the actual bitcode
  OS.write(pBitcode, uBitcodeSize);

  // Write some garbage after the bitcode
  for (unsigned i = 0; i < uNewSuffixeBytes; i++) {
    OS.write(0xFF);
  }
  OS.flush();

  // Try to load this new program, make sure dia is still okay.
  CComPtr<IDxcBlobEncoding> pNewProgramBlob;
  VERIFY_SUCCEEDED(pLib->CreateBlobWithEncodingFromPinned(buffer.data(), buffer.size(), CP_ACP, &pNewProgramBlob));

  CComPtr<IStream> pNewProgramStream;
  VERIFY_SUCCEEDED(pLib->CreateStreamFromBlobReadOnly(pNewProgramBlob, &pNewProgramStream));

  CComPtr<IDiaDataSource> pDiaDataSource;
  VERIFY_SUCCEEDED(m_dllSupport.CreateInstance(CLSID_DxcDiaDataSource, &pDiaDataSource));

  VERIFY_SUCCEEDED(pDiaDataSource->loadDataFromIStream(pNewProgramStream));
}

TEST_F(PixTest, DiaCompileArgs) {
  static const char source[] = R"(
    SamplerState  samp0 : register(s0);
    Texture2DArray tex0 : register(t0);

    float4 foo(Texture2DArray textures[], int idx, SamplerState samplerState, float3 uvw) {
      return textures[NonUniformResourceIndex(idx)].Sample(samplerState, uvw);
    }

    [RootSignature( "DescriptorTable(SRV(t0)), DescriptorTable(Sampler(s0)) " )]
    float4 main(int index : INDEX, float3 uvw : TEXCOORD) : SV_Target {
      Texture2DArray textures[] = {
        tex0,
      };
      return foo(textures, index, samp0, uvw);
    }
  )";

  CComPtr<IDxcBlob> pPart;
  CComPtr<IDiaDataSource> pDiaSource;
  CComPtr<IStream> pStream;

  CComPtr<IDxcLibrary> pLib;
  VERIFY_SUCCEEDED(m_dllSupport.CreateInstance(CLSID_DxcLibrary, &pLib));

  const WCHAR *FlagList[] = {
    L"/Zi",
    L"-Zpr",
    L"/Qembed_debug",
    L"/Fd", L"F:\\my dir\\",
    L"-Fo", L"F:\\my dir\\file.dxc",
  };
  const WCHAR *DefineList[] = {
    L"MY_SPECIAL_DEFINE",
    L"MY_OTHER_SPECIAL_DEFINE=\"MY_STRING\"",
  };

  std::vector<LPCWSTR> args;
  for (unsigned i = 0; i < _countof(FlagList); i++) {
    args.push_back(FlagList[i]);
  }
  for (unsigned i = 0; i < _countof(DefineList); i++) {
    args.push_back(L"/D");
    args.push_back(DefineList[i]);
  }

  auto CompileAndGetDebugPart = [&args](dxc::DxcDllSupport &dllSupport, const char *source, wchar_t *profile, IDxcBlob **ppDebugPart) {
    CComPtr<IDxcBlob> pContainer;
    CComPtr<IDxcLibrary> pLib;
    CComPtr<IDxcContainerReflection> pReflection;
    UINT32 index;

    VerifyCompileOK(dllSupport, source, profile, args, &pContainer);
    VERIFY_SUCCEEDED(dllSupport.CreateInstance(CLSID_DxcLibrary, &pLib));
    VERIFY_SUCCEEDED(dllSupport.CreateInstance(CLSID_DxcContainerReflection, &pReflection));
    VERIFY_SUCCEEDED(pReflection->Load(pContainer));
    VERIFY_SUCCEEDED(pReflection->FindFirstPartKind(hlsl::DFCC_ShaderDebugInfoDXIL, &index));
    VERIFY_SUCCEEDED(pReflection->GetPartContent(index, ppDebugPart));
  };

  CompileAndGetDebugPart(m_dllSupport, source, L"ps_6_0", &pPart);

  CComPtr<IStream> pNewProgramStream;
  VERIFY_SUCCEEDED(pLib->CreateStreamFromBlobReadOnly(pPart, &pNewProgramStream));

  CComPtr<IDiaDataSource> pDiaDataSource;
  VERIFY_SUCCEEDED(m_dllSupport.CreateInstance(CLSID_DxcDiaDataSource, &pDiaDataSource));

  VERIFY_SUCCEEDED(pDiaDataSource->loadDataFromIStream(pNewProgramStream));

  CComPtr<IDiaSession> pSession;
  VERIFY_SUCCEEDED(pDiaDataSource->openSession(&pSession));

  CComPtr<IDiaEnumTables> pEnumTables;
  VERIFY_SUCCEEDED(pSession->getEnumTables(&pEnumTables));

  CComPtr<IDiaTable> pSymbolTable;

  LONG uCount = 0;
  VERIFY_SUCCEEDED(pEnumTables->get_Count(&uCount));
  for (int i = 0; i < uCount; i++) {
    CComPtr<IDiaTable> pTable;
    VARIANT index = {};
    index.vt = VT_I4;
    index.intVal = i;
    VERIFY_SUCCEEDED(pEnumTables->Item(index, &pTable));

    CComBSTR pName;
    VERIFY_SUCCEEDED(pTable->get_name(&pName));

    if (pName == "Symbols") {
      pSymbolTable = pTable;
      break;
    }
  }

  std::wstring Args;
  std::wstring Entry;
  std::wstring Target;
  std::vector<std::wstring> Defines;
  std::vector<std::wstring> Flags;

  auto ReadNullSeparatedTokens = [](BSTR Str) -> std::vector<std::wstring> {
    std::vector<std::wstring> Result;
    while (*Str) {
      Result.push_back(std::wstring(Str));
      Str += wcslen(Str)+1;
    }
    return Result;
  };

  VERIFY_SUCCEEDED(pSymbolTable->get_Count(&uCount));
  for (int i = 0; i < uCount; i++) {
    CComPtr<IUnknown> pSymbolUnk;
    CComPtr<IDiaSymbol> pSymbol;
    CComVariant pValue;
    CComBSTR pName;
    VERIFY_SUCCEEDED(pSymbolTable->Item(i, &pSymbolUnk));
    VERIFY_SUCCEEDED(pSymbolUnk->QueryInterface(&pSymbol));
    VERIFY_SUCCEEDED(pSymbol->get_name(&pName));
    VERIFY_SUCCEEDED(pSymbol->get_value(&pValue));
    if (pName == "hlslTarget") {
      if (pValue.vt == VT_BSTR)
        Target = pValue.bstrVal;
    }
    else if (pName == "hlslEntry") {
      if (pValue.vt == VT_BSTR)
        Entry = pValue.bstrVal;
    }
    else if (pName == "hlslFlags") {
      if (pValue.vt == VT_BSTR)
        Flags = ReadNullSeparatedTokens(pValue.bstrVal);
    }
    else if (pName == "hlslArguments") {
      if (pValue.vt == VT_BSTR)
        Args = pValue.bstrVal;
    }
    else if (pName == "hlslDefines") {
      if (pValue.vt == VT_BSTR)
        Defines = ReadNullSeparatedTokens(pValue.bstrVal);
    }
  }

  auto VectorContains = [](std::vector<std::wstring> &Tokens, std::wstring Sub) {
    for (unsigned i = 0; i < Tokens.size(); i++) {
      if (Tokens[i].find(Sub) != std::wstring::npos)
        return true;
    }
    return false;
  };

  VERIFY_IS_TRUE(Target == L"ps_6_0");
  VERIFY_IS_TRUE(Entry == L"main");

  VERIFY_IS_TRUE(_countof(FlagList) == Flags.size());
  for (unsigned i = 0; i < _countof(FlagList); i++) {
    VERIFY_IS_TRUE(Flags[i] == FlagList[i]);
  }
  for (unsigned i = 0; i < _countof(DefineList); i++) {
    VERIFY_IS_TRUE(VectorContains(Defines, DefineList[i]));
  }
}

TEST_F(PixTest, DiaLoadBitcodePlusExtraData) {
  // Test that dia doesn't crash when bitcode has unused extra data at the end

  static const char source[] = R"(
    SamplerState  samp0 : register(s0);
    Texture2DArray tex0 : register(t0);

    float4 foo(Texture2DArray textures[], int idx, SamplerState samplerState, float3 uvw) {
      return textures[NonUniformResourceIndex(idx)].Sample(samplerState, uvw);
    }

    [RootSignature( "DescriptorTable(SRV(t0)), DescriptorTable(Sampler(s0)) " )]
    float4 main(int index : INDEX, float3 uvw : TEXCOORD) : SV_Target {
      Texture2DArray textures[] = {
        tex0,
      };
      return foo(textures, index, samp0, uvw);
    }
  )";

  CComPtr<IDxcBlob> pPart;
  CComPtr<IDiaDataSource> pDiaSource;
  CComPtr<IStream> pStream;

  CComPtr<IDxcLibrary> pLib;
  VERIFY_SUCCEEDED(m_dllSupport.CreateInstance(CLSID_DxcLibrary, &pLib));

  CompileAndGetDebugPart(m_dllSupport, source, L"ps_6_0", &pPart);
  const char *pPartData = (char *)pPart->GetBufferPointer();

  // Get program header
  const hlsl::DxilProgramHeader *programHeader = (hlsl::DxilProgramHeader *)pPartData;

  const char *pBitcode = nullptr;
  uint32_t uBitcodeSize = 0;
  hlsl::GetDxilProgramBitcode(programHeader, &pBitcode, &uBitcodeSize);

  llvm::SmallVector<char, 0> buffer;
  llvm::raw_svector_ostream OS(buffer);

  // Write the bitcode
  OS.write(pBitcode, uBitcodeSize);
  for (unsigned i = 0; i < 12; i++) {
    OS.write(0xFF);
  }
  OS.flush();

  // Try to load this new program, make sure dia is still okay.
  CComPtr<IDxcBlobEncoding> pNewProgramBlob;
  VERIFY_SUCCEEDED(pLib->CreateBlobWithEncodingFromPinned(buffer.data(), buffer.size(), CP_ACP, &pNewProgramBlob));

  CComPtr<IStream> pNewProgramStream;
  VERIFY_SUCCEEDED(pLib->CreateStreamFromBlobReadOnly(pNewProgramBlob, &pNewProgramStream));

  CComPtr<IDiaDataSource> pDiaDataSource;
  VERIFY_SUCCEEDED(m_dllSupport.CreateInstance(CLSID_DxcDiaDataSource, &pDiaDataSource));

  VERIFY_SUCCEEDED(pDiaDataSource->loadDataFromIStream(pNewProgramStream));
}

TEST_F(PixTest, DiaLoadDebugThenOK) {
  CompileTestAndLoadDia(m_dllSupport, nullptr);
}

TEST_F(PixTest, DiaTableIndexThenOK) {
  CComPtr<IDiaDataSource> pDiaSource;
  CComPtr<IDiaSession> pDiaSession;
  CComPtr<IDiaEnumTables> pEnumTables;
  CComPtr<IDiaTable> pTable;
  VARIANT vtIndex;
  CompileTestAndLoadDia(m_dllSupport, &pDiaSource);
  VERIFY_SUCCEEDED(pDiaSource->openSession(&pDiaSession));
  VERIFY_SUCCEEDED(pDiaSession->getEnumTables(&pEnumTables));

  vtIndex.vt = VT_EMPTY;
  VERIFY_FAILED(pEnumTables->Item(vtIndex, &pTable));

  vtIndex.vt = VT_I4;
  vtIndex.intVal = 1;
  VERIFY_SUCCEEDED(pEnumTables->Item(vtIndex, &pTable));
  VERIFY_IS_NOT_NULL(pTable.p);
  pTable.Release();

  vtIndex.vt = VT_UI4;
  vtIndex.uintVal = 1;
  VERIFY_SUCCEEDED(pEnumTables->Item(vtIndex, &pTable));
  VERIFY_IS_NOT_NULL(pTable.p);
  pTable.Release();

  vtIndex.uintVal = 100;
  VERIFY_FAILED(pEnumTables->Item(vtIndex, &pTable));
}

TEST_F(PixTest, PixDebugCompileInfo) {
  static const char source[] = R"(
    SamplerState  samp0 : register(s0);
    Texture2DArray tex0 : register(t0);

    float4 foo(Texture2DArray textures[], int idx, SamplerState samplerState, float3 uvw) {
      return textures[NonUniformResourceIndex(idx)].Sample(samplerState, uvw);
    }

    [RootSignature( "DescriptorTable(SRV(t0)), DescriptorTable(Sampler(s0)) " )]
    float4 main(int index : INDEX, float3 uvw : TEXCOORD) : SV_Target {
      Texture2DArray textures[] = {
        tex0,
      };
      return foo(textures, index, samp0, uvw);
    }
  )";

  CComPtr<IDxcBlob> pPart;
  CComPtr<IDiaDataSource> pDiaSource;
  CComPtr<IStream> pStream;

  CComPtr<IDxcLibrary> pLib;
  VERIFY_SUCCEEDED(m_dllSupport.CreateInstance(CLSID_DxcLibrary, &pLib));

  const WCHAR *FlagList[] = {
      L"/Zi",          L"-Zpr", L"/Qembed_debug",        L"/Fd",
      L"F:\\my dir\\", L"-Fo",  L"F:\\my dir\\file.dxc",
  };
  const WCHAR *DefineList[] = {
      L"MY_SPECIAL_DEFINE",
      L"MY_OTHER_SPECIAL_DEFINE=\"MY_STRING\"",
  };

  std::vector<LPCWSTR> args;
  for (unsigned i = 0; i < _countof(FlagList); i++) {
    args.push_back(FlagList[i]);
  }
  for (unsigned i = 0; i < _countof(DefineList); i++) {
    args.push_back(L"/D");
    args.push_back(DefineList[i]);
  }

  auto CompileAndGetDebugPart = [&args](dxc::DxcDllSupport &dllSupport,
                                        const char *source, wchar_t *profile,
                                        IDxcBlob **ppDebugPart) {
    CComPtr<IDxcBlob> pContainer;
    CComPtr<IDxcLibrary> pLib;
    CComPtr<IDxcContainerReflection> pReflection;
    UINT32 index;

    VerifyCompileOK(dllSupport, source, profile, args, &pContainer);
    VERIFY_SUCCEEDED(dllSupport.CreateInstance(CLSID_DxcLibrary, &pLib));
    VERIFY_SUCCEEDED(
        dllSupport.CreateInstance(CLSID_DxcContainerReflection, &pReflection));
    VERIFY_SUCCEEDED(pReflection->Load(pContainer));
    VERIFY_SUCCEEDED(
        pReflection->FindFirstPartKind(hlsl::DFCC_ShaderDebugInfoDXIL, &index));
    VERIFY_SUCCEEDED(pReflection->GetPartContent(index, ppDebugPart));
  };

  constexpr wchar_t *profile = L"ps_6_0";
  CompileAndGetDebugPart(m_dllSupport, source, profile, &pPart);

  CComPtr<IStream> pNewProgramStream;
  VERIFY_SUCCEEDED(
      pLib->CreateStreamFromBlobReadOnly(pPart, &pNewProgramStream));

  CComPtr<IDiaDataSource> pDiaDataSource;
  VERIFY_SUCCEEDED(
      m_dllSupport.CreateInstance(CLSID_DxcDiaDataSource, &pDiaDataSource));

  VERIFY_SUCCEEDED(pDiaDataSource->loadDataFromIStream(pNewProgramStream));

  CComPtr<IDiaSession> pSession;
  VERIFY_SUCCEEDED(pDiaDataSource->openSession(&pSession));

  CComPtr<IDxcPixDxilDebugInfoFactory> factory;
  VERIFY_SUCCEEDED(pSession->QueryInterface(IID_PPV_ARGS(&factory)));

  CComPtr<IDxcPixCompilationInfo> compilationInfo;
  VERIFY_SUCCEEDED(factory->NewDxcPixCompilationInfo(&compilationInfo));

  CComBSTR arguments;
  VERIFY_SUCCEEDED(compilationInfo->GetArguments(&arguments));
  for (unsigned i = 0; i < _countof(FlagList); i++) {
    VERIFY_IS_TRUE(nullptr != wcsstr(arguments, FlagList[i]));
  }

  CComBSTR macros;
  VERIFY_SUCCEEDED(compilationInfo->GetMacroDefinitions(&macros));
  for (unsigned i = 0; i < _countof(DefineList); i++) {
    std::wstring MacroDef = std::wstring(L"-D") + DefineList[i];
    VERIFY_IS_TRUE(nullptr != wcsstr(macros, MacroDef.c_str()));
  }

  CComBSTR entryPointFile;
  VERIFY_SUCCEEDED(compilationInfo->GetEntryPointFile(&entryPointFile));
  VERIFY_ARE_EQUAL(std::wstring(L"source.hlsl"), std::wstring(entryPointFile));

  CComBSTR entryPointFunction;
  VERIFY_SUCCEEDED(compilationInfo->GetEntryPoint(&entryPointFunction));
  VERIFY_ARE_EQUAL(std::wstring(L"main"), std::wstring(entryPointFunction));

  CComBSTR hlslTarget;
  VERIFY_SUCCEEDED(compilationInfo->GetHlslTarget(&hlslTarget));
  VERIFY_ARE_EQUAL(std::wstring(profile), std::wstring(hlslTarget));
}

static LPCWSTR defaultFilename = L"source.hlsl";

static void CompileAndLogErrors(dxc::DxcDllSupport &dllSupport, LPCSTR pText,
                     LPCWSTR pTargetProfile, std::vector<LPCWSTR> &args,
                     _Outptr_ IDxcBlob **ppResult) {
  CComPtr<IDxcCompiler> pCompiler;
  CComPtr<IDxcBlobEncoding> pSource;
  CComPtr<IDxcOperationResult> pResult;
  HRESULT hrCompile;
  *ppResult = nullptr;
  VERIFY_SUCCEEDED(dllSupport.CreateInstance(CLSID_DxcCompiler, &pCompiler));
  Utf8ToBlob(dllSupport, pText, &pSource);
  VERIFY_SUCCEEDED(pCompiler->Compile(pSource, defaultFilename, L"main",
                                      pTargetProfile, args.data(), args.size(),
                                      nullptr, 0, nullptr, &pResult));

  VERIFY_SUCCEEDED(pResult->GetStatus(&hrCompile));
  if (FAILED(hrCompile)) {
    CComPtr<IDxcBlobEncoding> textBlob;
    VERIFY_SUCCEEDED(pResult->GetErrorBuffer(&textBlob));
    std::wstring text = BlobToWide(textBlob);
    WEX::Logging::Log::Comment(text.c_str());
  }
  VERIFY_SUCCEEDED(hrCompile);
  VERIFY_SUCCEEDED(pResult->GetResult(ppResult));
}

static CComPtr<IDxcBlob> GetDebugPart(dxc::DxcDllSupport &dllSupport,
                                      IDxcBlob *container) {

  CComPtr<IDxcLibrary> pLib;
  VERIFY_SUCCEEDED(dllSupport.CreateInstance(CLSID_DxcLibrary, &pLib));
  CComPtr<IDxcContainerReflection> pReflection;

  VERIFY_SUCCEEDED(
      dllSupport.CreateInstance(CLSID_DxcContainerReflection, &pReflection));
  VERIFY_SUCCEEDED(pReflection->Load(container));

  UINT32 index;
  VERIFY_SUCCEEDED(
      pReflection->FindFirstPartKind(hlsl::DFCC_ShaderDebugInfoDXIL, &index));

  CComPtr<IDxcBlob> debugPart;
  VERIFY_SUCCEEDED(pReflection->GetPartContent(index, &debugPart));

  return debugPart;
}

void PixTest::CompileAndRunValueToDeclareAndGetDebugPart(
    dxc::DxcDllSupport &dllSupport, const char *source, wchar_t *profile,
    IDxcBlob **ppDebugPart) {
  CComPtr<IDxcBlob> pContainer;
  std::vector<LPCWSTR> args;
  args.push_back(L"/Zi");
  args.push_back(L"/Od");
  args.push_back(L"/Qembed_debug");

  CompileAndLogErrors(dllSupport, source, profile, args, &pContainer);

  auto annotated = RunValueToDeclarePass(pContainer);

  CComPtr<IDxcBlob> pNewContainer = WrapInNewContainer(annotated.blob);

  *ppDebugPart = GetDebugPart(dllSupport, pNewContainer).Detach();
}

void PixTest::CompileAndRunAnnotationAndGetDebugPart(
    dxc::DxcDllSupport &dllSupport, const char *source, const wchar_t *profile,
    IDxcBlob **ppDebugPart, std::vector<const wchar_t *> extraArgs) {

  CComPtr<IDxcBlob> pContainer;
  std::vector<LPCWSTR> args;
  args.push_back(L"/Zi");
  args.push_back(L"/Qembed_debug");
  args.insert(args.end(), extraArgs.begin(), extraArgs.end());

  CompileAndLogErrors(dllSupport, source, profile, args, &pContainer);

  auto annotated = RunAnnotationPasses(pContainer);

  CComPtr<IDxcBlob> pNewContainer = WrapInNewContainer(annotated.blob);

  *ppDebugPart = GetDebugPart(dllSupport, pNewContainer).Detach();
}

void PixTest::CompileAndRunAnnotationAndLoadDiaSource(
    dxc::DxcDllSupport &dllSupport, const char *source, const wchar_t *profile,
    IDiaDataSource **ppDataSource,
    std::vector<const wchar_t *> extraArgs) {
  CComPtr<IDxcBlob> pDebugContent;
  CComPtr<IStream> pStream;
  CComPtr<IDiaDataSource> pDiaSource;
  CComPtr<IDxcLibrary> pLib;
  VERIFY_SUCCEEDED(dllSupport.CreateInstance(CLSID_DxcLibrary, &pLib));

  CompileAndRunAnnotationAndGetDebugPart(dllSupport, source, profile,
                                         &pDebugContent, extraArgs);
  VERIFY_SUCCEEDED(pLib->CreateStreamFromBlobReadOnly(pDebugContent, &pStream));
  VERIFY_SUCCEEDED(
      dllSupport.CreateInstance(CLSID_DxcDiaDataSource, &pDiaSource));
  VERIFY_SUCCEEDED(pDiaSource->loadDataFromIStream(pStream));
  if (ppDataSource) {
    *ppDataSource = pDiaSource.Detach();
  }
}

CComPtr<IDxcBlob> PixTest::WrapInNewContainer(IDxcBlob *part) {
  CComPtr<IDxcAssembler> pAssembler;
  IFT(m_dllSupport.CreateInstance(CLSID_DxcAssembler, &pAssembler));

  CComPtr<IDxcOperationResult> pAssembleResult;
  VERIFY_SUCCEEDED(pAssembler->AssembleToContainer(part, &pAssembleResult));

  CComPtr<IDxcBlobEncoding> pAssembleErrors;
  VERIFY_SUCCEEDED(pAssembleResult->GetErrorBuffer(&pAssembleErrors));

  if (pAssembleErrors && pAssembleErrors->GetBufferSize() != 0) {
    OutputDebugStringA(
        static_cast<LPCSTR>(pAssembleErrors->GetBufferPointer()));
    VERIFY_SUCCEEDED(E_FAIL);
  }

  CComPtr<IDxcBlob> pNewContainer;
  VERIFY_SUCCEEDED(pAssembleResult->GetResult(&pNewContainer));

  return pNewContainer;
}

TEST_F(PixTest, PixTypeManager_InheritancePointerStruct) {
  if (m_ver.SkipDxilVersion(1, 5))
    return;

  const char *hlsl = R"(
struct Base
{
    float floatValue;
};

struct Derived : Base
{
	int intValue;
};

RaytracingAccelerationStructure Scene : register(t0, space0);

[shader("raygeneration")]
void main()
{
    RayDesc ray;
    ray.Origin = float3(0,0,0);
    ray.Direction = float3(0,0,1);
    // Set TMin to a non-zero small value to avoid aliasing issues due to floating - point errors.
    // TMin should be kept small to prevent missing geometry at close contact areas.
    ray.TMin = 0.001;
    ray.TMax = 10000.0;
    Derived payload;
    payload.floatValue = 1;
    payload.intValue = 2;
    TraceRay(Scene, RAY_FLAG_CULL_BACK_FACING_TRIANGLES, ~0, 0, 1, 0, ray, payload);}

)";

  CComPtr<IDiaDataSource> pDiaDataSource;
  CComPtr<IDiaSession> pDiaSession;
  CompileAndRunAnnotationAndLoadDiaSource(m_dllSupport, hlsl, L"lib_6_6",
                                          &pDiaDataSource);

  VERIFY_SUCCEEDED(pDiaDataSource->openSession(&pDiaSession));
}

TEST_F(PixTest, PixTypeManager_InheritancePointerTypedef) {
  if (m_ver.SkipDxilVersion(1, 5))
    return;

  const char *hlsl = R"(
struct Base
{
    float floatValue;
};
typedef Base BaseTypedef;

struct Derived : BaseTypedef
{
	int intValue;
};

RaytracingAccelerationStructure Scene : register(t0, space0);

[shader("raygeneration")]
void main()
{
    RayDesc ray;
    ray.Origin = float3(0,0,0);
    ray.Direction = float3(0,0,1);
    // Set TMin to a non-zero small value to avoid aliasing issues due to floating - point errors.
    // TMin should be kept small to prevent missing geometry at close contact areas.
    ray.TMin = 0.001;
    ray.TMax = 10000.0;
    Derived payload;
    payload.floatValue = 1;
    payload.intValue = 2;
    TraceRay(Scene, RAY_FLAG_CULL_BACK_FACING_TRIANGLES, ~0, 0, 1, 0, ray, payload);}

)";

  CComPtr<IDiaDataSource> pDiaDataSource;
  CComPtr<IDiaSession> pDiaSession;
  CompileAndRunAnnotationAndLoadDiaSource(m_dllSupport, hlsl, L"lib_6_6",
                                          &pDiaDataSource);

  VERIFY_SUCCEEDED(pDiaDataSource->openSession(&pDiaSession));
}

TEST_F(PixTest, PixTypeManager_MatricesInBase) {
  if (m_ver.SkipDxilVersion(1, 5))
    return;

  const char *hlsl = R"(
struct Base
{
    float4x4 mat;
};
typedef Base BaseTypedef;

struct Derived : BaseTypedef
{
	int intValue;
};

RaytracingAccelerationStructure Scene : register(t0, space0);

[shader("raygeneration")]
void main()
{
    RayDesc ray;
    ray.Origin = float3(0,0,0);
    ray.Direction = float3(0,0,1);
    // Set TMin to a non-zero small value to avoid aliasing issues due to floating - point errors.
    // TMin should be kept small to prevent missing geometry at close contact areas.
    ray.TMin = 0.001;
    ray.TMax = 10000.0;
    Derived payload;
    payload.mat[0][0] = 1;
    payload.intValue = 2;
    TraceRay(Scene, RAY_FLAG_CULL_BACK_FACING_TRIANGLES, ~0, 0, 1, 0, ray, payload);}

)";

  CComPtr<IDiaDataSource> pDiaDataSource;
  CComPtr<IDiaSession> pDiaSession;
  CompileAndRunAnnotationAndLoadDiaSource(m_dllSupport, hlsl, L"lib_6_6",
                                          &pDiaDataSource);

  VERIFY_SUCCEEDED(pDiaDataSource->openSession(&pDiaSession));
}

TEST_F(PixTest, PixTypeManager_SamplersAndResources) {
  if (m_ver.SkipDxilVersion(1, 5))
    return;

  const char *hlsl = R"(

static const SamplerState SamplerRef = SamplerDescriptorHeap[1];

Texture3D<uint4> Tex3DTemplated ;
Texture3D Tex3d ;
Texture2D Tex2D ;
Texture2D<uint> Tex2DTemplated ;
StructuredBuffer<float4> StructBuf ;
Texture2DArray Tex2DArray ;
Buffer<float4> Buff ;

static const struct
{
	float  AFloat;
	SamplerState Samp1;
	Texture3D<uint4> Tex1;
	Texture3D Tex2;
	Texture2D Tex3;
	Texture2D<uint> Tex4;
	StructuredBuffer<float4> Buff1;
	Texture2DArray Tex5;
	Buffer<float4> Buff2;
	float  AnotherFloat;
} View = {
1,
SamplerRef,
Tex3DTemplated,
Tex3d,
Tex2D,
Tex2DTemplated,
StructBuf,
Tex2DArray,
Buff,
2
};

struct Payload
{
	int intValue;
};

RaytracingAccelerationStructure Scene : register(t0, space0);

[shader("raygeneration")]
void main()
{
    RayDesc ray;
    ray.Origin = float3(0,0,0);
    ray.Direction = float3(0,0,1);
    ray.TMin = 0.001;
    ray.TMax = 10000.0;
    Payload payload;
    payload.intValue = View.AFloat;
    TraceRay(Scene, RAY_FLAG_CULL_BACK_FACING_TRIANGLES, ~0, 0, 1, 0, ray, payload);}
)";

  CComPtr<IDiaDataSource> pDiaDataSource;
  CComPtr<IDiaSession> pDiaSession;
  CompileAndRunAnnotationAndLoadDiaSource(m_dllSupport, hlsl, L"lib_6_6",
                                          &pDiaDataSource);

  VERIFY_SUCCEEDED(pDiaDataSource->openSession(&pDiaSession));
}

TEST_F(PixTest, PixTypeManager_XBoxDiaAssert) {
  if (m_ver.SkipDxilVersion(1, 5))
    return;

  const char *hlsl = R"(
struct VSOut
{
    float4 vPosition : SV_POSITION;
    float4 vLightAndFog : COLOR0_center;
    float4 vTexCoords : TEXCOORD1;
};

struct HSPatchData
{
    float edges[3] : SV_TessFactor;
    float inside : SV_InsideTessFactor;
};

HSPatchData HSPatchFunc(const InputPatch<VSOut, 3> tri)
{

    float dist = (tri[0].vPosition.w + tri[1].vPosition.w + tri[2].vPosition.w) / 3;


    float tf = max(1, dist / 100.f);

    HSPatchData pd;
    pd.edges[0] = pd.edges[1] = pd.edges[2] = tf;
    pd.inside = tf;

    return pd;
}

[domain("tri")]
[partitioning("fractional_odd")]
[outputtopology("triangle_cw")]
[patchconstantfunc("HSPatchFunc")]
[outputcontrolpoints(3)]
[RootSignature("RootFlags(ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT), " "DescriptorTable(SRV(t0, numDescriptors=2), visibility=SHADER_VISIBILITY_ALL)," "DescriptorTable(Sampler(s0, numDescriptors=2), visibility=SHADER_VISIBILITY_PIXEL)," "DescriptorTable(CBV(b0, numDescriptors=1), visibility=SHADER_VISIBILITY_ALL)," "DescriptorTable(CBV(b1, numDescriptors=1), visibility=SHADER_VISIBILITY_ALL)," "DescriptorTable(CBV(b2, numDescriptors=1), visibility=SHADER_VISIBILITY_ALL)," "DescriptorTable(SRV(t3, numDescriptors=1), visibility=SHADER_VISIBILITY_ALL)," "DescriptorTable(UAV(u9, numDescriptors=2), visibility=SHADER_VISIBILITY_ALL),")]
VSOut main( const uint id : SV_OutputControlPointID,
              const InputPatch< VSOut, 3 > triIn )
{
    return triIn[id];
}
)";

  CComPtr<IDiaDataSource> pDiaDataSource;
  CComPtr<IDiaSession> pDiaSession;
  CompileAndRunAnnotationAndLoadDiaSource(m_dllSupport, hlsl, L"hs_6_0",
                                          &pDiaDataSource);

  VERIFY_SUCCEEDED(pDiaDataSource->openSession(&pDiaSession));
}

std::vector<std::string> SplitAndPreserveEmptyLines(std::string const & str, char delimeter) {
  std::vector<std::string> lines;

  auto const *p = str.data();
  auto const *justPastPreviousDelimiter = p;
  while (p < str.data() + str.length()) {
    if (*p == delimeter) {
      lines.emplace_back(justPastPreviousDelimiter, p - justPastPreviousDelimiter);
      justPastPreviousDelimiter = p + 1;
      p = justPastPreviousDelimiter;
    } else {
      p++;
    }
  }

  lines.emplace_back(std::string(justPastPreviousDelimiter,
                                      p - justPastPreviousDelimiter));

  return lines;
}

TEST_F(PixTest, DxcPixDxilDebugInfo_InstructionOffsets) {

  if (m_ver.SkipDxilVersion(1, 5))
    return;

  const char *hlsl = R"(RaytracingAccelerationStructure Scene : register(t0, space0);
RWTexture2D<float4> RenderTarget : register(u0);

struct SceneConstantBuffer
{
    float4x4 projectionToWorld;
    float4 cameraPosition;
    float4 lightPosition;
    float4 lightAmbientColor;
    float4 lightDiffuseColor;
};

ConstantBuffer<SceneConstantBuffer> g_sceneCB : register(b0);

struct RayPayload
{
    float4 color;
};

inline void GenerateCameraRay(uint2 index, out float3 origin, out float3 direction)
{
    float2 xy = index + 0.5f; // center in the middle of the pixel.
    float2 screenPos = xy;// / DispatchRaysDimensions().xy * 2.0 - 1.0;

    // Invert Y for DirectX-style coordinates.
    screenPos.y = -screenPos.y;

    // Unproject the pixel coordinate into a ray.
    float4 world = /*mul(*/float4(screenPos, 0, 1)/*, g_sceneCB.projectionToWorld)*/;

    //world.xyz /= world.w;
    origin = world.xyz; //g_sceneCB.cameraPosition.xyz;
    direction = float3(1,0,0);//normalize(world.xyz - origin);
}

void RaygenCommon()
{
    float3 rayDir;
    float3 origin;
    
    // Generate a ray for a camera pixel corresponding to an index from the dispatched 2D grid.
    GenerateCameraRay(DispatchRaysIndex().xy, origin, rayDir);

    // Trace the ray.
    // Set the ray's extents.
    RayDesc ray;
    ray.Origin = origin;
    ray.Direction = rayDir;
    // Set TMin to a non-zero small value to avoid aliasing issues due to floating - point errors.
    // TMin should be kept small to prevent missing geometry at close contact areas.
    ray.TMin = 0.001;
    ray.TMax = 10000.0;
    RayPayload payload = { float4(0, 0, 0, 0) };
    TraceRay(Scene, RAY_FLAG_CULL_BACK_FACING_TRIANGLES, ~0, 0, 1, 0, ray, payload);

    // Write the raytraced color to the output texture.
   // RenderTarget[DispatchRaysIndex().xy] = payload.color;
}

[shader("raygeneration")]
void Raygen()
{
    RaygenCommon();
}

typedef BuiltInTriangleIntersectionAttributes MyAttributes;

[shader("closesthit")]
void InnerClosestHitShader(inout RayPayload payload, in MyAttributes attr)
{
    payload.color = float4(0,1,0,0);
}


[shader("miss")]
void MyMissShader(inout RayPayload payload)
{
    payload.color = float4(1, 0, 0, 0);
})";

  auto lines = SplitAndPreserveEmptyLines(std::string(hlsl), '\n');
  DWORD countOfSourceLines = static_cast<DWORD>(lines.size());

  CComPtr<IDiaDataSource> pDiaDataSource;
  CompileAndRunAnnotationAndLoadDiaSource(m_dllSupport, hlsl, L"lib_6_6",
                                          &pDiaDataSource);

  CComPtr<IDiaSession> session;
  VERIFY_SUCCEEDED(pDiaDataSource->openSession(&session));

  CComPtr<IDxcPixDxilDebugInfoFactory> Factory;
  VERIFY_SUCCEEDED(session->QueryInterface(IID_PPV_ARGS(&Factory)));

  CComPtr<IDxcPixDxilDebugInfo> dxilDebugger;
  VERIFY_SUCCEEDED(Factory->NewDxcPixDxilDebugInfo(&dxilDebugger));

  // Quick crash test for wrong filename:
  CComPtr<IDxcPixDxilInstructionOffsets> garbageOffsets;
  dxilDebugger->InstructionOffsetsFromSourceLocation(L"garbage", 0, 0,
                                                     &garbageOffsets);

  // Since the API offers both source-from-instruction and
  // instruction-from-source, we'll compare them against each other:
  for (size_t line = 0; line < lines.size(); ++line) {

    auto lineNumber = static_cast<DWORD>(line);

    constexpr DWORD sourceLocationReaderOnlySupportsColumnZero = 0;
    CComPtr<IDxcPixDxilInstructionOffsets> offsets;
    dxilDebugger->InstructionOffsetsFromSourceLocation(
        defaultFilename, lineNumber, sourceLocationReaderOnlySupportsColumnZero,
        &offsets);

    auto offsetCount = offsets->GetCount();
    for (DWORD offsetOrdinal = 0; offsetOrdinal < offsetCount;
         ++offsetOrdinal) {

      DWORD instructionOffsetFromSource =
          offsets->GetOffsetByIndex(offsetOrdinal);

      CComPtr<IDxcPixDxilSourceLocations> sourceLocations;
      VERIFY_SUCCEEDED(dxilDebugger->SourceLocationsFromInstructionOffset(
          instructionOffsetFromSource, &sourceLocations));

      auto count = sourceLocations->GetCount();
      for (DWORD sourceLocationOrdinal = 0; sourceLocationOrdinal < count;
           ++sourceLocationOrdinal) {
        DWORD lineNumber =
            sourceLocations->GetLineNumberByIndex(sourceLocationOrdinal);
        DWORD column = sourceLocations->GetColumnByIndex(sourceLocationOrdinal);
        CComBSTR filename;
        VERIFY_SUCCEEDED(sourceLocations->GetFileNameByIndex(
            sourceLocationOrdinal, &filename));

        VERIFY_IS_TRUE(lineNumber < countOfSourceLines);

        constexpr DWORD lineNumbersAndColumnsStartAtOne = 1;
        VERIFY_IS_TRUE(
            column - lineNumbersAndColumnsStartAtOne  <=
            static_cast<DWORD>(lines.at(lineNumber - lineNumbersAndColumnsStartAtOne).size()));
        VERIFY_IS_TRUE(0 == wcscmp(filename, defaultFilename));
      }
    }
  }
}

static HRESULT UnAliasType(IDxcPixType *MaybeAlias,
                           IDxcPixType **OriginalType) {
  *OriginalType = nullptr;
  CComPtr<IDxcPixType> Tmp(MaybeAlias);

  do {
    HRESULT hr;

    CComPtr<IDxcPixType> Alias;
    hr = Tmp->UnAlias(&Alias);
    if (FAILED(hr)) {
      return hr;
    }
    if (hr == S_FALSE) {
      break;
    }
    Tmp = Alias;
  } while (true);

  *OriginalType = Tmp.Detach();
  return S_OK;
}

static bool AddStorageComponents(
    IDxcPixDxilStorage *pStorage, std::wstring Name,
    std::vector<PixTest::VariableComponentInfo> &VariableComponents) {
  CComPtr<IDxcPixType> StorageType;
  if (FAILED(pStorage->GetType(&StorageType))) {
    return false;
  }

  CComPtr<IDxcPixType> UnAliasedType;
  if (FAILED(UnAliasType(StorageType, &UnAliasedType))) {
    return false;
  }

  CComPtr<IDxcPixArrayType> ArrayType;
  CComPtr<IDxcPixScalarType> ScalarType;
  CComPtr<IDxcPixStructType2> StructType;

  if (!FAILED(UnAliasedType->QueryInterface(&ScalarType))) {
    CComBSTR TypeName;
    // StorageType is the type that the storage was defined in HLSL, i.e.,
    // it could be a typedef, const etc.
    if (FAILED(StorageType->GetName(&TypeName))) {
      return false;
    }

    VariableComponents.emplace_back(PixTest::VariableComponentInfo{
        std::move(Name), std::wstring(TypeName)});
    return true;
  } else if (!FAILED(UnAliasedType->QueryInterface(&ArrayType))) {
    DWORD NumElements;
    if (FAILED(ArrayType->GetNumElements(&NumElements))) {
      return false;
    }

    std::wstring BaseName = Name + L'[';
    for (DWORD i = 0; i < NumElements; ++i) {
      CComPtr<IDxcPixDxilStorage> EntryStorage;
      if (FAILED(pStorage->Index(i, &EntryStorage))) {
        return false;
      }

      if (!AddStorageComponents(EntryStorage,
                                      BaseName + std::to_wstring(i) + L"]",
                                      VariableComponents)) {
        return false;
      }
    }
  } else if (!FAILED(UnAliasedType->QueryInterface(&StructType))) {
    DWORD NumFields;
    if (FAILED(StructType->GetNumFields(&NumFields))) {
      return false;
    }

    std::wstring BaseName = Name + L'.';
    for (DWORD i = 0; i < NumFields; ++i) {
      CComPtr<IDxcPixStructField> Field;
      if (FAILED(StructType->GetFieldByIndex(i, &Field))) {
        return false;
      }

      CComBSTR FieldName;
      if (FAILED(Field->GetName(&FieldName))) {
        return false;
      }

      CComPtr<IDxcPixDxilStorage> FieldStorage;
      if (FAILED(pStorage->AccessField(FieldName, &FieldStorage))) {
        return false;
      }

      if (!AddStorageComponents(FieldStorage,
                                      BaseName + std::wstring(FieldName),
                                      VariableComponents)) {
        return false;
      }
    }

    CComPtr<IDxcPixType> BaseType;
    if (SUCCEEDED(StructType->GetBaseType(&BaseType))) {
      CComPtr<IDxcPixDxilStorage> BaseStorage;
      if (FAILED(pStorage->AccessField(L"", &BaseStorage))) {
        return false;
      }
      if (!AddStorageComponents(BaseStorage, Name, VariableComponents)) {
        return false;
      }
    }
  }

  return true;
}

static bool ContainedBy(std::vector<PixTest::VariableComponentInfo> const &v1,
                        std::vector<PixTest::VariableComponentInfo> const &v2) {
  for (auto const &c1 : v1) {
    bool FoundThis = false;
    for (auto const &c2 : v2) {
      if (c1.Name == c2.Name && c1.Type == c2.Type) {
        FoundThis = true;
        break;
      }
    }
    if (!FoundThis) {
      return false;
    }
  }
  return true;
}

CComPtr<IDxcPixDxilDebugInfo> PixTest::CompileAndCreateDxcDebug(const char* hlsl, const wchar_t* profile) {

  CComPtr<IDiaDataSource> pDiaDataSource;
  CompileAndRunAnnotationAndLoadDiaSource(m_dllSupport, hlsl, profile,
                                          &pDiaDataSource, {L"-Od"});

  CComPtr<IDiaSession> session;
  VERIFY_SUCCEEDED(pDiaDataSource->openSession(&session));

  CComPtr<IDxcPixDxilDebugInfoFactory> Factory;
  VERIFY_SUCCEEDED(session->QueryInterface(IID_PPV_ARGS(&Factory)));

  CComPtr<IDxcPixDxilDebugInfo> dxilDebugger;
  VERIFY_SUCCEEDED(Factory->NewDxcPixDxilDebugInfo(&dxilDebugger));
  return dxilDebugger;
}

CComPtr<IDxcPixDxilLiveVariables>
PixTest::GetLiveVariablesAt(const char *hlsl,
                            const char *lineAtWhichToExamineVariables,
                            IDxcPixDxilDebugInfo *dxilDebugger) {

  auto lines = SplitAndPreserveEmptyLines(std::string(hlsl), '\n');
  auto FindInterestingLine = std::find_if(
      lines.begin(), lines.end(),
      [&lineAtWhichToExamineVariables](std::string const &line) {
        return line.find(lineAtWhichToExamineVariables) != std::string::npos;
      });
  auto InterestingLine =
      static_cast<DWORD>(FindInterestingLine - lines.begin()) + 1;

  CComPtr<IDxcPixDxilLiveVariables> liveVariables;
  for (; InterestingLine <= static_cast<DWORD>(lines.size());
       ++InterestingLine) {
    CComPtr<IDxcPixDxilInstructionOffsets> instructionOffsets;
    if (SUCCEEDED(dxilDebugger->InstructionOffsetsFromSourceLocation(
            defaultFilename, InterestingLine, 0, &instructionOffsets))) {
      if (instructionOffsets->GetCount() > 0) {
        auto instructionOffset = instructionOffsets->GetOffsetByIndex(0);
        if (SUCCEEDED(dxilDebugger->GetLiveVariablesAt(instructionOffset,
                                                       &liveVariables))) {
          break;
        }
      }
    }
  }
  VERIFY_IS_TRUE(liveVariables != nullptr);

  return liveVariables;
}

void PixTest::TestGlobalStaticCase(
          const char *hlsl,
  const wchar_t * profile,
  const char *lineAtWhichToExamineVariables,
  std::vector<VariableComponentInfo> const &ExpectedVariables) {

  auto dxilDebugger = CompileAndCreateDxcDebug(hlsl, profile);

  auto liveVariables =
      GetLiveVariablesAt(hlsl, lineAtWhichToExamineVariables, dxilDebugger);

  DWORD count;
  VERIFY_SUCCEEDED(liveVariables->GetCount(&count));
  bool FoundGlobal = false;
  for (DWORD i = 0; i < count; ++i) {
    CComPtr<IDxcPixVariable> variable;
    VERIFY_SUCCEEDED(liveVariables->GetVariableByIndex(i, &variable));
    CComBSTR name;
    variable->GetName(&name);
    if (0 == wcscmp(name, L"global.globalStruct")) {
      FoundGlobal = true;
      CComPtr<IDxcPixDxilStorage> storage;
      VERIFY_SUCCEEDED(variable->GetStorage(&storage));
      std::vector<VariableComponentInfo> ActualVariableComponents;
      VERIFY_IS_TRUE(AddStorageComponents(storage, L"global.globalStruct",
                                          ActualVariableComponents));
      VERIFY_IS_TRUE(ContainedBy(ActualVariableComponents, ExpectedVariables));
      break;
    }
  }
  VERIFY_IS_TRUE(FoundGlobal);
}

TEST_F(PixTest,
       DxcPixDxilDebugInfo_GlobalBackedGlobalStaticEmbeddedArrays_NoDbgValue) {
  if (m_ver.SkipDxilVersion(1, 5))
    return;

  const char *hlsl = R"(
RWStructuredBuffer<float> floatRWUAV: register(u0);

struct GlobalStruct
{
    int IntArray[2];
    float FloatArray[2];
};

static GlobalStruct globalStruct;
[noinline]
void fn()
{
    float Accumulator;
    globalStruct.IntArray[0] = floatRWUAV[0];
    globalStruct.IntArray[1] = floatRWUAV[1];
    globalStruct.FloatArray[0] = floatRWUAV[4];
    globalStruct.FloatArray[1] = floatRWUAV[5];
    Accumulator = 0;

    uint killSwitch = 0;

    [loop] // do not unroll this
    while (true)
    {
        Accumulator += globalStruct.FloatArray[killSwitch % 2];

        if (killSwitch++ == 4) break;
    }

    floatRWUAV[0] = Accumulator + globalStruct.IntArray[0] + globalStruct.IntArray[1];
}

[numthreads(1, 1, 1)]
void main()
{
  fn();
}

)";
  // The above HLSL should generate a module that represents the FloatArray
  // member as a global, and the IntArray as an alloca. Since only embedded
  // arrays are present in GlobalStruct, no dbg.value will be present for
  // globalStruct. We expect the value-to-declare pass to generate its own
  // dbg.value for stores into FloatArray. We will observe those dbg.value here
  // via the PIX-specific debug data API.

  std::vector<VariableComponentInfo> Expected;
  Expected.push_back({L"global.globalStruct.IntArray[0]", L"int"});
  Expected.push_back({L"global.globalStruct.IntArray[1]", L"int"});
  Expected.push_back({L"global.globalStruct.FloatArray[0]", L"float"});
  Expected.push_back({L"global.globalStruct.FloatArray[1]", L"float"});
  TestGlobalStaticCase(hlsl, L"lib_6_6", "float Accumulator", Expected);
}

TEST_F(PixTest,
       DxcPixDxilDebugInfo_GlobalBackedGlobalStaticEmbeddedArrays_WithDbgValue) {
  if (m_ver.SkipDxilVersion(1, 5))
    return;

  const char *hlsl = R"(
RWStructuredBuffer<float> floatRWUAV: register(u0);

struct GlobalStruct
{
    float Accumulator;
    int IntArray[2];
    float FloatArray[2];
};

static GlobalStruct globalStruct;
[numthreads(1, 1, 1)]
void main()
{
    globalStruct.IntArray[0] = floatRWUAV[0];
    globalStruct.IntArray[1] = floatRWUAV[1];
    globalStruct.FloatArray[0] = floatRWUAV[4];
    globalStruct.FloatArray[1] = floatRWUAV[5];
    globalStruct.Accumulator = 0;

    uint killSwitch = 0;

    [loop] // do not unroll this
    while (true)
    {
        globalStruct.Accumulator += globalStruct.FloatArray[killSwitch % 2];

        if (killSwitch++ == 4) break;
    }

    floatRWUAV[0] = globalStruct.Accumulator + globalStruct.IntArray[0] + globalStruct.IntArray[1];
}

)";
  // The above HLSL should generate a module that represents the FloatArray
  // member as a global, and the IntArray as an alloca. The presence of Accumulator 
  // in the GlobalStruct will force a dbg.value to be present for
  // globalStruct. We expect the value-to-declare pass to find that dbg.value.

  std::vector<VariableComponentInfo> Expected;
  Expected.push_back({L"global.globalStruct.Accumulator", L"float"});
  Expected.push_back({L"global.globalStruct.IntArray[0]", L"int"});
  Expected.push_back({L"global.globalStruct.IntArray[1]", L"int"});
  Expected.push_back({L"global.globalStruct.FloatArray[0]", L"float"});
  Expected.push_back({L"global.globalStruct.FloatArray[1]", L"float"});
  TestGlobalStaticCase(hlsl, L"cs_6_6", "float Accumulator", Expected);
}


TEST_F(PixTest,
    DxcPixDxilDebugInfo_GlobalBackedGlobalStaticEmbeddedArrays_ArrayInValues) {
  if (m_ver.SkipDxilVersion(1, 5))
    return;

  const char *hlsl = R"(
RWStructuredBuffer<float> floatRWUAV: register(u0);

struct GlobalStruct
{
    float Accumulator;
    int IntArray[2];
    float FloatArray[2];
};

static GlobalStruct globalStruct;
[numthreads(1, 1, 1)]
void main()
{
    globalStruct.IntArray[0] =0;
    globalStruct.IntArray[1] =1;
    globalStruct.FloatArray[0] = floatRWUAV[4];
    globalStruct.FloatArray[1] = floatRWUAV[5];
    globalStruct.Accumulator = 0;

    uint killSwitch = 0;

    [loop] // do not unroll this
    while (true)
    {
        globalStruct.Accumulator += globalStruct.FloatArray[killSwitch % 2];

        if (killSwitch++ == 4) break;
    }

    floatRWUAV[0] = globalStruct.Accumulator + globalStruct.IntArray[0] + globalStruct.IntArray[1];
}

)";
  // The above HLSL should generate a module that represents the FloatArray
  // member as a global, and the IntArray as individual values. 

  std::vector<VariableComponentInfo> Expected;
  Expected.push_back({L"global.globalStruct.Accumulator", L"float"});
  Expected.push_back({L"global.globalStruct.IntArray[0]", L"int"});
  Expected.push_back({L"global.globalStruct.IntArray[1]", L"int"});
  Expected.push_back({L"global.globalStruct.FloatArray[0]", L"float"});
  Expected.push_back({L"global.globalStruct.FloatArray[1]", L"float"});
  TestGlobalStaticCase(hlsl, L"lib_6_6", "float Accumulator", Expected);
}

TEST_F(PixTest,
    DxcPixDxilDebugInfo_StructInheritance) {
  if (m_ver.SkipDxilVersion(1, 5))
    return;

  const char *hlsl = R"(
RWStructuredBuffer<float> floatRWUAV: register(u0);

struct AStruct
{
    float f;
    int i[2];
};

struct ADerivedStruct : AStruct
{
  bool b[2];
};

int AFunction(ADerivedStruct theStruct)
{
  return theStruct.i[0] + theStruct.i[1] + theStruct.f + (theStruct.b[0] ? 1 : 0) + (theStruct.b[1] ? 2 : 3); // InterestingLine
}

[numthreads(1, 1, 1)]
void main()
{
  ADerivedStruct aStruct;
  aStruct.f = floatRWUAV[1];
  aStruct.i[0] = floatRWUAV[2];
  aStruct.i[1] = floatRWUAV[3];
  aStruct.b[0] = floatRWUAV[4] != 0.0;
  aStruct.b[1] = floatRWUAV[5] != 0.0;
  floatRWUAV[0] = AFunction(aStruct);
}

)";
  auto dxilDebugger = CompileAndCreateDxcDebug(hlsl, L"cs_6_6");

  auto liveVariables =
      GetLiveVariablesAt(hlsl, "InterestingLine", dxilDebugger);

  DWORD count;
  VERIFY_SUCCEEDED(liveVariables->GetCount(&count));
  bool FoundTheStruct = false;
  for (DWORD i = 0; i < count; ++i) {
    CComPtr<IDxcPixVariable> variable;
    VERIFY_SUCCEEDED(liveVariables->GetVariableByIndex(i, &variable));
    CComBSTR name;
    variable->GetName(&name);
    if (0 == wcscmp(name, L"theStruct")) {
      FoundTheStruct = true;
      CComPtr<IDxcPixDxilStorage> storage;
      VERIFY_SUCCEEDED(variable->GetStorage(&storage));
      std::vector<VariableComponentInfo> ActualVariableComponents;
      VERIFY_IS_TRUE(AddStorageComponents(storage, L"theStruct",
                                          ActualVariableComponents));
      std::vector<VariableComponentInfo> Expected;
      Expected.push_back({L"theStruct.b[0]", L"bool"});
      Expected.push_back({L"theStruct.b[1]", L"bool"});
      Expected.push_back({L"theStruct.f", L"float"});
      Expected.push_back({L"theStruct.i[0]", L"int"});
      Expected.push_back({L"theStruct.i[1]", L"int"});
      VERIFY_IS_TRUE(ContainedBy(ActualVariableComponents, Expected));
      break;
    }
  }
  VERIFY_IS_TRUE(FoundTheStruct);
}

TEST_F(PixTest, DxcPixDxilDebugInfo_StructContainedResource) {
  if (m_ver.SkipDxilVersion(1, 5))
    return;

  const char *hlsl = R"(
RWStructuredBuffer<float> floatRWUAV: register(u0);
Texture2D srv2DTexture : register(t0, space1);
struct AStruct
{
    float f;
    Texture2D tex;
};

float4 AFunction(AStruct theStruct)
{
  return theStruct.tex.Load(int3(0, 0, 0)) + theStruct.f.xxxx; // InterestingLine
}

[numthreads(1, 1, 1)]
void main()
{
  AStruct aStruct;
  aStruct.f = floatRWUAV[1];
  aStruct.tex = srv2DTexture;
  floatRWUAV[0] = AFunction(aStruct).x;
}

)";
  auto dxilDebugger = CompileAndCreateDxcDebug(hlsl, L"cs_6_6");

  auto liveVariables =
      GetLiveVariablesAt(hlsl, "InterestingLine", dxilDebugger);

  DWORD count;
  VERIFY_SUCCEEDED(liveVariables->GetCount(&count));
  bool FoundTheStruct = false;
  for (DWORD i = 0; i < count; ++i) {
    CComPtr<IDxcPixVariable> variable;
    VERIFY_SUCCEEDED(liveVariables->GetVariableByIndex(i, &variable));
    CComBSTR name;
    variable->GetName(&name);
    if (0 == wcscmp(name, L"theStruct")) {
      FoundTheStruct = true;
      CComPtr<IDxcPixDxilStorage> storage;
      VERIFY_SUCCEEDED(variable->GetStorage(&storage));
      std::vector<VariableComponentInfo> ActualVariableComponents;
      VERIFY_IS_TRUE(AddStorageComponents(storage, L"theStruct",
                                          ActualVariableComponents));
      std::vector<VariableComponentInfo> Expected;
      Expected.push_back({L"theStruct.f", L"float"});
      VERIFY_IS_TRUE(ContainedBy(ActualVariableComponents, Expected));
      break;
    }
  }
  VERIFY_IS_TRUE(FoundTheStruct);
}

TEST_F(PixTest, DxcPixDxilDebugInfo_StructStaticInit) {
  if (m_ver.SkipDxilVersion(1, 5))
    return;

  const char *hlsl = R"(
RWStructuredBuffer<float> floatRWUAV: register(u0);
struct AStruct
{
    float f;
    static AStruct Init(float fi)
    {
        AStruct ret;
        ret.f = fi;
        for(int i =0; i < 4; ++i)
        {
          ret.f += floatRWUAV[i+2];
        }
        return ret;
    }
};

[numthreads(1, 1, 1)]
void main()
{
  AStruct aStruct = AStruct::Init(floatRWUAV[1]);
  floatRWUAV[0] = aStruct.f; // InterestingLine
}

)";
  auto dxilDebugger = CompileAndCreateDxcDebug(hlsl, L"cs_6_6");

  auto liveVariables =
      GetLiveVariablesAt(hlsl, "InterestingLine", dxilDebugger);

  DWORD count;
  VERIFY_SUCCEEDED(liveVariables->GetCount(&count));
  bool FoundTheStruct = false;
  for (DWORD i = 0; i < count; ++i) {
    CComPtr<IDxcPixVariable> variable;
    VERIFY_SUCCEEDED(liveVariables->GetVariableByIndex(i, &variable));
    CComBSTR name;
    variable->GetName(&name);
    if (0 == wcscmp(name, L"aStruct")) {
      FoundTheStruct = true;
      CComPtr<IDxcPixDxilStorage> storage;
      VERIFY_SUCCEEDED(variable->GetStorage(&storage));
      std::vector<VariableComponentInfo> ActualVariableComponents;
      VERIFY_IS_TRUE(AddStorageComponents(storage, L"aStruct",
                                          ActualVariableComponents));
      std::vector<VariableComponentInfo> Expected;
      Expected.push_back({L"aStruct.f", L"float"});
      VERIFY_IS_TRUE(ContainedBy(ActualVariableComponents, Expected));
      break;
    }
  }
  VERIFY_IS_TRUE(FoundTheStruct);
}

TEST_F(PixTest, DxcPixDxilDebugInfo_StructMemberFnFirst) {
  if (m_ver.SkipDxilVersion(1, 5))
    return;

  const char *hlsl = R"(
RWStructuredBuffer<float> floatRWUAV: register(u0);
struct AStruct
{
    void Init(float fi);
    float f;
};

void AStruct::Init(float fi)
{
    AStruct ret;
    f = fi;
    for(int i =0; i < 4; ++i)
    {
      f += floatRWUAV[i+2];
    }
}
  
[numthreads(1, 1, 1)]
void main()
{
  AStruct aStruct;
  aStruct.Init(floatRWUAV[1]);
  floatRWUAV[0] = aStruct.f; // InterestingLine
}

)";
  auto dxilDebugger = CompileAndCreateDxcDebug(hlsl, L"cs_6_6");

  auto liveVariables =
      GetLiveVariablesAt(hlsl, "InterestingLine", dxilDebugger);

  DWORD count;
  VERIFY_SUCCEEDED(liveVariables->GetCount(&count));
  bool FoundTheStruct = false;
  for (DWORD i = 0; i < count; ++i) {
    CComPtr<IDxcPixVariable> variable;
    VERIFY_SUCCEEDED(liveVariables->GetVariableByIndex(i, &variable));
    CComBSTR name;
    variable->GetName(&name);
    if (0 == wcscmp(name, L"aStruct")) {
      FoundTheStruct = true;
      CComPtr<IDxcPixDxilStorage> storage;
      VERIFY_SUCCEEDED(variable->GetStorage(&storage));
      std::vector<VariableComponentInfo> ActualVariableComponents;
      VERIFY_IS_TRUE(AddStorageComponents(storage, L"aStruct",
                                          ActualVariableComponents));
      std::vector<VariableComponentInfo> Expected;
      Expected.push_back({L"aStruct.f", L"float"});
      VERIFY_IS_TRUE(ContainedBy(ActualVariableComponents, Expected));
      break;
    }
  }
  VERIFY_IS_TRUE(FoundTheStruct);
}

CComPtr<IDxcBlob> PixTest::RunShaderAccessTrackingPass(IDxcBlob *blob) {
  CComPtr<IDxcOptimizer> pOptimizer;
  VERIFY_SUCCEEDED(
      m_dllSupport.CreateInstance(CLSID_DxcOptimizer, &pOptimizer));
  std::vector<LPCWSTR> Options;
  Options.push_back(L"-opt-mod-passes");
  Options.push_back(L"-hlsl-dxil-pix-shader-access-instrumentation,config=");

  CComPtr<IDxcBlob> pOptimizedModule;
  CComPtr<IDxcBlobEncoding> pText;
  VERIFY_SUCCEEDED(pOptimizer->RunOptimizer(
      blob, Options.data(), Options.size(), &pOptimizedModule, &pText));

  CComPtr<IDxcAssembler> pAssembler;
  VERIFY_SUCCEEDED(
      m_dllSupport.CreateInstance(CLSID_DxcAssembler, &pAssembler));

  CComPtr<IDxcOperationResult> pAssembleResult;
  VERIFY_SUCCEEDED(
      pAssembler->AssembleToContainer(pOptimizedModule, &pAssembleResult));

  HRESULT hr;
  VERIFY_SUCCEEDED(pAssembleResult->GetStatus(&hr));
  VERIFY_SUCCEEDED(hr);

  CComPtr<IDxcBlob> pNewContainer;
  VERIFY_SUCCEEDED(pAssembleResult->GetResult(&pNewContainer));

  return pNewContainer;
}

CComPtr<IDxcBlob> PixTest::RunDxilPIXMeshShaderOutputPass(IDxcBlob *blob) {
  CComPtr<IDxcBlob> dxil = FindModule(DFCC_ShaderDebugInfoDXIL, blob);
  CComPtr<IDxcOptimizer> pOptimizer;
  VERIFY_SUCCEEDED(
      m_dllSupport.CreateInstance(CLSID_DxcOptimizer, &pOptimizer));
  std::vector<LPCWSTR> Options;
  Options.push_back(L"-opt-mod-passes");
  Options.push_back(L"-hlsl-dxil-pix-meshshader-output-instrumentation,expand-payload=1,UAVSize=8192");

  CComPtr<IDxcBlob> pOptimizedModule;
  CComPtr<IDxcBlobEncoding> pText;
  VERIFY_SUCCEEDED(pOptimizer->RunOptimizer(
      dxil, Options.data(), Options.size(), &pOptimizedModule, &pText));

  std::string outputText;
  if (pText->GetBufferSize() != 0) {
    outputText = reinterpret_cast<const char *>(pText->GetBufferPointer());
  }

  return pOptimizedModule;
}

std::string
PixTest::RunDxilPIXAddTidToAmplificationShaderPayloadPass(IDxcBlob *blob) {
  CComPtr<IDxcBlob> dxil = FindModule(DFCC_ShaderDebugInfoDXIL, blob);
  CComPtr<IDxcOptimizer> pOptimizer;
  VERIFY_SUCCEEDED(
      m_dllSupport.CreateInstance(CLSID_DxcOptimizer, &pOptimizer));
  std::vector<LPCWSTR> Options;
  Options.push_back(L"-opt-mod-passes");
  Options.push_back(L"-hlsl-dxil-PIX-add-tid-to-as-payload,dispatchArgY=1,dispatchArgZ=2");

  CComPtr<IDxcBlob> pOptimizedModule;
  CComPtr<IDxcBlobEncoding> pText;
  VERIFY_SUCCEEDED(pOptimizer->RunOptimizer(
      dxil, Options.data(), Options.size(), &pOptimizedModule, &pText));

  std::string outputText;
  if (pText->GetBufferSize() != 0) {
    outputText = reinterpret_cast<const char *>(pText->GetBufferPointer());
  }

  return outputText;
}

TEST_F(PixTest, AddToASPayload) {

  const char *dynamicResourceDecriptorHeapAccess = R"(
struct MyPayload
{
    float f1;
    float f2;
};

[numthreads(1, 1, 1)]
void ASMain(uint gid : SV_GroupID)
{
    MyPayload payload;
    payload.f1 = (float)gid / 4.f;
    payload.f2 = (float)gid * 4.f;
    DispatchMesh(1, 1, 1, payload);
}

struct PSInput
{
    float4 position : SV_POSITION;
};


[outputtopology("triangle")]
[numthreads(3,1,1)]
void MSMain(
    in payload MyPayload small,
    in uint tid : SV_GroupThreadID,
    in uint3 dtid : SV_DispatchThreadID,
    out vertices PSInput verts[3],
    out indices uint3 triangles[1])
{
    SetMeshOutputCounts(3, 1);
    verts[tid].position = float4(small.f1, small.f2, 0, 0);
    triangles[0] = uint3(0, 1, 2);
}

  )";

  auto as = Compile(dynamicResourceDecriptorHeapAccess, L"as_6_6", {}, L"ASMain");
  RunDxilPIXAddTidToAmplificationShaderPayloadPass(as);
 
  auto ms = Compile(dynamicResourceDecriptorHeapAccess, L"ms_6_6", {}, L"MSMain");
  RunDxilPIXMeshShaderOutputPass(ms);

}

static llvm::DIType *PeelTypedefs(llvm::DIType *diTy) {
  using namespace llvm;
  const llvm::DITypeIdentifierMap EmptyMap;
  while (1) {
    DIDerivedType *diDerivedTy = dyn_cast<DIDerivedType>(diTy);
    if (!diDerivedTy)
      return diTy;

    switch (diTy->getTag()) {
    case dwarf::DW_TAG_member:
    case dwarf::DW_TAG_inheritance:
    case dwarf::DW_TAG_typedef:
    case dwarf::DW_TAG_reference_type:
    case dwarf::DW_TAG_const_type:
    case dwarf::DW_TAG_restrict_type:
      diTy = diDerivedTy->getBaseType().resolve(EmptyMap);
      break;
    default:
      return diTy;
    }
  }

  return diTy;
}

static unsigned GetDITypeSizeInBits(llvm::DIType *diTy) {
  return PeelTypedefs(diTy)->getSizeInBits();
}

static unsigned GetDITypeAlignmentInBits(llvm::DIType *diTy) {
  return PeelTypedefs(diTy)->getAlignInBits();
}

static bool FindStructMemberFromStore(llvm::StoreInst *S, std::string *OutMemberName) {
  using namespace llvm;
  Value *Ptr = S->getPointerOperand();
  AllocaInst *Alloca = nullptr;

  auto &DL = S->getModule()->getDataLayout();

  unsigned OffsetInAlloca = 0;
  while (Ptr) {
    if (auto AI = dyn_cast<AllocaInst>(Ptr)) {
      Alloca = AI;
      break;
    }
    else if (auto Gep = dyn_cast<GEPOperator>(Ptr)) {
      if (Gep->getNumIndices() < 2 ||
        !Gep->hasAllConstantIndices() ||
        0 != cast<ConstantInt>(Gep->getOperand(1))->getLimitedValue())
      {
        return false;
      }

      auto GepSrcPtr = Gep->getPointerOperand();
      Type *GepSrcPtrTy = GepSrcPtr->getType()->getPointerElementType();

      Type *PeelingType = GepSrcPtrTy;
      for (unsigned i = 1; i < Gep->getNumIndices(); i++) {
        uint64_t Idx = cast<ConstantInt>(Gep->getOperand(1 + i))->getLimitedValue();

        if (PeelingType->isStructTy()) {
          auto StructTy = cast<StructType>(PeelingType);
          unsigned Offset = DL.getStructLayout(StructTy)->getElementOffsetInBits(Idx);
          OffsetInAlloca += Offset;
          PeelingType = StructTy->getElementType(Idx);
        }
        else if (PeelingType->isVectorTy()) {
          OffsetInAlloca += DL.getTypeSizeInBits(PeelingType->getVectorElementType()) * Idx;
          PeelingType = PeelingType->getVectorElementType();
        }
        else if (PeelingType->isArrayTy()) {
          OffsetInAlloca += DL.getTypeSizeInBits(PeelingType->getArrayElementType()) * Idx;
          PeelingType = PeelingType->getArrayElementType();
        }
        else {
          return false;
        }
      }

      Ptr = GepSrcPtr;
    }
    else {
      return false;
    }
  }

  // If there's not exactly one dbg.* inst, give up for now.
  if (hlsl::dxilutil::mdv_user_empty(Alloca) ||
    std::next(hlsl::dxilutil::mdv_users_begin(Alloca)) != hlsl::dxilutil::mdv_users_end(Alloca))
  {
    return false;
  }

  auto DI = dyn_cast<DbgDeclareInst>(*hlsl::dxilutil::mdv_users_begin(Alloca));
  if (!DI)
    return false;

  DILocalVariable *diVar = DI->getVariable();
  DIExpression *diExpr = DI->getExpression();
  const llvm::DITypeIdentifierMap EmptyMap;
  DIType *diType = diVar->getType().resolve(EmptyMap);

  unsigned MemberOffset = OffsetInAlloca;
  if (diExpr->isBitPiece()) {
    MemberOffset += diExpr->getBitPieceOffset();
  }

  diType = PeelTypedefs(diType);
  if (!isa<DICompositeType>(diType))
    return false;

  unsigned OffsetInDI = 0;
  std::string MemberName;

  //=====================================================
  // Find the correct member based on size
  while (diType) {
    diType = PeelTypedefs(diType);
    if (DICompositeType *diCompType = dyn_cast<DICompositeType>(diType)) {
      if (diCompType->getTag() == dwarf::DW_TAG_structure_type ||
          diCompType->getTag() == dwarf::DW_TAG_class_type)
      {
        bool FoundCompositeMember = false;
        for (DINode *Elem : diCompType->getElements()) {
          auto diElemType = dyn_cast<DIType>(Elem);
          if (!diElemType)
            return false;

          StringRef CurMemberName;
          if (diElemType->getTag() == dwarf::DW_TAG_member) {
            CurMemberName = diElemType->getName();
          }
          else if (diElemType->getTag() == dwarf::DW_TAG_inheritance) {}
          else {
            return false;
          }

          unsigned CompositeMemberSize = GetDITypeSizeInBits(diElemType);
          unsigned CompositeMemberAlignment = GetDITypeAlignmentInBits(diElemType);

          assert(CompositeMemberAlignment);
          OffsetInDI = llvm::RoundUpToAlignment(OffsetInDI, CompositeMemberAlignment);

          if (OffsetInDI <= MemberOffset && MemberOffset < OffsetInDI + CompositeMemberSize) {
            diType = diElemType;
            if (CurMemberName.size()) {
              if (MemberName.size())
                MemberName += ".";
              MemberName += CurMemberName;
            }
            FoundCompositeMember = true;
            break;
          }

          // TODO: How will we match up the padding?
          OffsetInDI += CompositeMemberSize;
        }

        if (!FoundCompositeMember)
          return false;
      }
      // For arrays, just flatten it for now.
      // TODO: multi-dimension array
      else if (diCompType->getTag() == dwarf::DW_TAG_array_type) {
        if (MemberOffset < OffsetInDI || MemberOffset >= OffsetInDI + diCompType->getSizeInBits())
          return false;
        DIType *diArrayElemType = diCompType->getBaseType().resolve(EmptyMap);

        {
          unsigned CurSize = diCompType->getSizeInBits();
          unsigned CurOffset = MemberOffset - OffsetInDI;
          for (DINode *SubrangeMD : diCompType->getElements()) {
            DISubrange *Range = cast<DISubrange>(SubrangeMD);

            unsigned ElemSize = CurSize / Range->getCount();
            unsigned Idx = CurOffset / ElemSize;

            CurOffset -= ElemSize * Idx;
            CurSize = ElemSize;

            MemberName += "[";
            MemberName += std::to_string(Idx);
            MemberName += "]";
          }
        }

        unsigned ArrayElemSize = GetDITypeSizeInBits(diArrayElemType);
        unsigned FlattenedIdx = (MemberOffset - OffsetInDI) / ArrayElemSize;
        OffsetInDI += FlattenedIdx * ArrayElemSize;
        diType = diArrayElemType;
      }
      else {
        return false;
      }
    }
    else if (DIBasicType *diBasicType = dyn_cast<DIBasicType>(diType)) {
      if (OffsetInDI == MemberOffset) {
        *OutMemberName = MemberName;
        return true;
      }

      OffsetInDI += diBasicType->getSizeInBits();
      return false;
    }
    else {
      return false;
    }
  }

  return false;
}

// This function lives in lib\DxilPIXPasses\DxilAnnotateWithVirtualRegister.cpp
// Declared here so we can test it.
uint32_t CountStructMembers(llvm::Type const* pType);

PixTest::TestableResults PixTest::TestStructAnnotationCase(
    const char* hlsl, 
    const wchar_t * optimizationLevel,
    bool validateCoverage,
    const wchar_t *profile) {
  CComPtr<IDxcBlob> pBlob = Compile(hlsl, profile,
              {optimizationLevel, L"-HV", L"2018", L"-enable-16bit-types"});

  CComPtr<IDxcBlob> pDxil = FindModule(DFCC_ShaderDebugInfoDXIL, pBlob);

  PassOutput passOutput = RunAnnotationPasses(pDxil);

  auto pAnnotated = passOutput.blob;

  CComPtr<IDxcBlob> pAnnotatedContainer;
  ReplaceDxilBlobPart(
    pBlob->GetBufferPointer(),
    pBlob->GetBufferSize(),
    pAnnotated,
    &pAnnotatedContainer);

#if 0 // handy for debugging
  auto disTextW = Disassemble(pAnnotatedContainer);
  WEX::Logging::Log::Comment(disTextW.c_str());
#endif

  ModuleAndHangersOn moduleEtc(pAnnotatedContainer);
    PixTest::TestableResults ret;

  // For every dbg.declare, run the member iterator and record what it finds:
  auto entryPoints = moduleEtc.GetDxilModule().GetExportedFunctions();
    for (auto &entryFunction : entryPoints) {
      for (auto &block : entryFunction->getBasicBlockList()) {
        for (auto &instruction : block.getInstList()) {
          if (auto *dbgDeclare =
                  llvm::dyn_cast<llvm::DbgDeclareInst>(&instruction)) {
            llvm::Value *Address = dbgDeclare->getAddress();
            auto *AddressAsAlloca = llvm::dyn_cast<llvm::AllocaInst>(Address);
            if (AddressAsAlloca != nullptr) {
              auto *Expression = dbgDeclare->getExpression();

              std::unique_ptr<dxil_debug_info::MemberIterator> iterator =
                  dxil_debug_info::CreateMemberIterator(
                      dbgDeclare,
                      moduleEtc.GetDxilModule().GetModule()->getDataLayout(),
                      AddressAsAlloca, Expression);

              unsigned int startingBit = 0;
              unsigned int coveredBits = 0;
              unsigned int memberIndex = 0;
              unsigned int memberCount = 0;
              while (iterator->Next(&memberIndex)) {
                memberCount++;
                if (memberIndex == 0) {
                  startingBit = iterator->OffsetInBits(memberIndex);
                  coveredBits = iterator->SizeInBits(memberIndex);
                } else {
                  coveredBits = std::max<unsigned int>(
                      coveredBits, iterator->OffsetInBits(memberIndex) +
                                       iterator->SizeInBits(memberIndex));
                }
              }

              AggregateOffsetAndSize OffsetAndSize = {};
              OffsetAndSize.countOfMembers = memberCount;
              OffsetAndSize.offset = startingBit;
              OffsetAndSize.size = coveredBits;
              ret.OffsetAndSizes.push_back(OffsetAndSize);

              // Use this independent count of number of struct members to test
              // the function that operates on the alloca type:
              llvm::Type *pAllocaTy =
                  AddressAsAlloca->getType()->getElementType();
              if (auto *AT = llvm::dyn_cast<llvm::ArrayType>(pAllocaTy)) {
                // This is the case where a struct is passed to a function, and
                // in these tests there should be only one struct behind the
                // pointer.
                VERIFY_ARE_EQUAL(AT->getNumElements(), 1);
                pAllocaTy = AT->getArrayElementType();
              }

              if (auto *ST = llvm::dyn_cast<llvm::StructType>(pAllocaTy)) {
                uint32_t countOfMembers = CountStructMembers(ST);
                // memberIndex might be greater, because the fragment iterator
                // also includes contained derived types as fragments, in
                // addition to the members of that contained derived types.
                // CountStructMembers only counts the leaf-node types.
                VERIFY_ARE_EQUAL(countOfMembers, memberCount);
              } else if (pAllocaTy->isFloatingPointTy() ||
                         pAllocaTy->isIntegerTy()) {
                // If there's only one member in the struct in the
                // pass-to-function (by pointer) case, then the underlying type
                // will have been reduced to the contained type.
                VERIFY_ARE_EQUAL(1, memberCount);
              } else {
                VERIFY_IS_TRUE(false);
              }
            }
          }
        }
      }

      // The member iterator should find a solid run of bits that is exactly
      // covered by exactly one of the members found by the annotation pass:
      if (validateCoverage) {
        unsigned CurRegIdx = 0;
        for (AggregateOffsetAndSize const &cover :
             ret.OffsetAndSizes) // For each entry read from member iterators
                                 // and dbg.declares
        {
          bool found = false;
          for (ValueLocation const &valueLocation :
               passOutput.valueLocations) // For each allocas and dxil values
          {
            if (CurRegIdx == valueLocation.base && 
                valueLocation.count == cover.countOfMembers) {
              VERIFY_IS_FALSE(found);
              found = true;
            }
          }
          VERIFY_IS_TRUE(found);
          CurRegIdx += cover.countOfMembers;
        }
      }

      // For every store operation to the struct alloca, check that the
      // annotation pass correctly determined which alloca
      for (auto &block : entryFunction->getBasicBlockList()) {
        for (auto &instruction : block.getInstList()) {
          if (auto *store = llvm::dyn_cast<llvm::StoreInst>(&instruction)) {

            AllocaWrite NewAllocaWrite = {};
            if (FindStructMemberFromStore(store, &NewAllocaWrite.memberName)) {
              llvm::Value *index;
              if (pix_dxil::PixAllocaRegWrite::FromInst(
                      store, &NewAllocaWrite.regBase, &NewAllocaWrite.regSize,
                      &index)) {
                auto *asInt = llvm::dyn_cast<llvm::ConstantInt>(index);
                NewAllocaWrite.index = asInt->getLimitedValue();
                ret.AllocaWrites.push_back(NewAllocaWrite);
              }
            }
          }
        }
      }
    }
  return ret;
}

void PixTest::ValidateAllocaWrite(std::vector<AllocaWrite> const &allocaWrites,
                                  size_t index, const char *name) {
  VERIFY_ARE_EQUAL(index, allocaWrites[index].regBase + allocaWrites[index].index);
#ifndef NDEBUG
  // Compilation may add a prefix to the struct member name:
  VERIFY_IS_TRUE(0 == strncmp(name, allocaWrites[index].memberName.c_str(), strlen(name)));
#endif
}

struct OptimizationChoice {
  const wchar_t *Flag;
  bool IsOptimized;
};
static const OptimizationChoice OptimizationChoices[] = {
  { L"-Od", false },
  { L"-O1", true },
};

TEST_F(PixTest, PixStructAnnotation_Lib_DualRaygen) {
  if (m_ver.SkipDxilVersion(1, 5)) return;

  for (auto choice : OptimizationChoices) {
      auto optimization = choice.Flag;
      const char* hlsl = R"(

RaytracingAccelerationStructure Scene : register(t0, space0);
RWTexture2D<float4> RenderTarget : register(u0);

struct SceneConstantBuffer
{
    float4x4 projectionToWorld;
    float4 cameraPosition;
    float4 lightPosition;
    float4 lightAmbientColor;
    float4 lightDiffuseColor;
};

ConstantBuffer<SceneConstantBuffer> g_sceneCB : register(b0);

struct RayPayload
{
    float4 color;
};

inline void GenerateCameraRay(uint2 index, out float3 origin, out float3 direction)
{
    float2 xy = index + 0.5f; // center in the middle of the pixel.
    float2 screenPos = xy;// / DispatchRaysDimensions().xy * 2.0 - 1.0;

    // Invert Y for DirectX-style coordinates.
    screenPos.y = -screenPos.y;

    // Unproject the pixel coordinate into a ray.
    float4 world = /*mul(*/float4(screenPos, 0, 1)/*, g_sceneCB.projectionToWorld)*/;

    //world.xyz /= world.w;
    origin = world.xyz; //g_sceneCB.cameraPosition.xyz;
    direction = float3(1,0,0);//normalize(world.xyz - origin);
}

void RaygenCommon()
{
    float3 rayDir;
    float3 origin;
    
    // Generate a ray for a camera pixel corresponding to an index from the dispatched 2D grid.
    GenerateCameraRay(DispatchRaysIndex().xy, origin, rayDir);

    // Trace the ray.
    // Set the ray's extents.
    RayDesc ray;
    ray.Origin = origin;
    ray.Direction = rayDir;
    // Set TMin to a non-zero small value to avoid aliasing issues due to floating - point errors.
    // TMin should be kept small to prevent missing geometry at close contact areas.
    ray.TMin = 0.001;
    ray.TMax = 10000.0;
    RayPayload payload = { float4(0, 0, 0, 0) };
    TraceRay(Scene, RAY_FLAG_CULL_BACK_FACING_TRIANGLES, ~0, 0, 1, 0, ray, payload);

    // Write the raytraced color to the output texture.
   // RenderTarget[DispatchRaysIndex().xy] = payload.color;
}

[shader("raygeneration")]
void Raygen0()
{
    RaygenCommon();
}

[shader("raygeneration")]
void Raygen1()
{
    RaygenCommon();
}
)";

      // This is just a crash test until we decide what the right way forward
      // for #DSLTodo is...
      CComPtr<IDxcBlob> pBlob = Compile(hlsl, L"lib_6_6", {optimization});
      CComPtr<IDxcBlob> pDxil = FindModule(DFCC_ShaderDebugInfoDXIL, pBlob);
      RunAnnotationPasses(pDxil);
  }
}

TEST_F(PixTest, PixStructAnnotation_Lib_RaygenAllocaStructAlignment) {
  if (m_ver.SkipDxilVersion(1, 5)) return;

  const char* hlsl = R"(

RaytracingAccelerationStructure Scene : register(t0, space0);
RWTexture2D<float4> RenderTarget : register(u0);

struct SceneConstantBuffer
{
    float4x4 projectionToWorld;
    float4 cameraPosition;
    float4 lightPosition;
    float4 lightAmbientColor;
    float4 lightDiffuseColor;
};

ConstantBuffer<SceneConstantBuffer> g_sceneCB : register(b0);

struct RayPayload
{
    float4 color;
};

inline void GenerateCameraRay(uint2 index, out float3 origin, out float3 direction)
{
    float2 xy = index + 0.5f; // center in the middle of the pixel.
    float2 screenPos = xy;// / DispatchRaysDimensions().xy * 2.0 - 1.0;

    // Invert Y for DirectX-style coordinates.
    screenPos.y = -screenPos.y;

    // Unproject the pixel coordinate into a ray.
    float4 world = /*mul(*/float4(screenPos, 0, 1)/*, g_sceneCB.projectionToWorld)*/;

    //world.xyz /= world.w;
    origin = world.xyz; //g_sceneCB.cameraPosition.xyz;
    direction = float3(1,0,0);//normalize(world.xyz - origin);
}

void RaygenCommon()
{
    float3 rayDir;
    float3 origin;
    
    // Generate a ray for a camera pixel corresponding to an index from the dispatched 2D grid.
    GenerateCameraRay(DispatchRaysIndex().xy, origin, rayDir);

    // Trace the ray.
    // Set the ray's extents.
    RayDesc ray;
    ray.Origin = origin;
    ray.Direction = rayDir;
    // Set TMin to a non-zero small value to avoid aliasing issues due to floating - point errors.
    // TMin should be kept small to prevent missing geometry at close contact areas.
    ray.TMin = 0.001;
    ray.TMax = 10000.0;
    RayPayload payload = { float4(0, 0, 0, 0) };
    TraceRay(Scene, RAY_FLAG_CULL_BACK_FACING_TRIANGLES, ~0, 0, 1, 0, ray, payload);

    // Write the raytraced color to the output texture.
   // RenderTarget[DispatchRaysIndex().xy] = payload.color;
}

[shader("raygeneration")]
void Raygen()
{
    RaygenCommon();
}
)";

  auto Testables = TestStructAnnotationCase(hlsl, L"-Od", true, L"lib_6_6");

  // Built-in type "RayDesc" has this structure: struct { float3 Origin; float
  // TMin; float3 Direction; float TMax; } This is 8 floats, with members at
  // offsets 0,3,4,7 respectively.

  auto FindAtLeastOneOf = [=](char const *name, uint32_t index) {
    VERIFY_IS_TRUE(std::find_if(Testables.AllocaWrites.begin(),
                                Testables.AllocaWrites.end(),
                                [&name, &index](AllocaWrite const &aw) {
                                  return 0 == strcmp(aw.memberName.c_str(),
                                                     name) &&
                                         aw.index == index;
                                }) != Testables.AllocaWrites.end());
  };

  FindAtLeastOneOf("Origin.x", 0);
  FindAtLeastOneOf("TMin", 3);
  FindAtLeastOneOf("Direction.x", 4);
  FindAtLeastOneOf("TMax", 7);
}

TEST_F(PixTest, PixStructAnnotation_Simple) {
  if (m_ver.SkipDxilVersion(1, 5))
    return;

  for (auto choice : OptimizationChoices) {
    auto optimization = choice.Flag;
    const char *hlsl = R"(
struct smallPayload
{
    uint dummy;
};


[numthreads(1, 1, 1)]
void main()
{
    smallPayload p;
    p.dummy = 42;
    DispatchMesh(1, 1, 1, p);
}
)";

    auto Testables = TestStructAnnotationCase(hlsl, optimization);

    if (!Testables.OffsetAndSizes.empty()) {
      VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes.size());
      VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes[0].countOfMembers);
      VERIFY_ARE_EQUAL(0, Testables.OffsetAndSizes[0].offset);
      VERIFY_ARE_EQUAL(32, Testables.OffsetAndSizes[0].size);
    }

    VERIFY_ARE_EQUAL(1, Testables.AllocaWrites.size());
    ValidateAllocaWrite(Testables.AllocaWrites, 0, "dummy");
  }
}


TEST_F(PixTest, PixStructAnnotation_CopiedStruct) {
  if (m_ver.SkipDxilVersion(1, 5)) return;
  for (auto choice : OptimizationChoices) {
      auto optimization = choice.Flag;

      const char* hlsl = R"(
struct smallPayload
{
    uint dummy;
};


[numthreads(1, 1, 1)]
void main()
{
    smallPayload p;
    p.dummy = 42;
    smallPayload p2 = p;
    DispatchMesh(1, 1, 1, p2);
}
)";

    auto Testables = TestStructAnnotationCase(hlsl, optimization);

    // 2 in unoptimized case (one for each instance of smallPayload)
    // 1 in optimized case (cuz p2 aliases over p)
    VERIFY_IS_TRUE(Testables.OffsetAndSizes.size() >= 1);

    for (const auto& os : Testables.OffsetAndSizes) {
      VERIFY_ARE_EQUAL(1, os.countOfMembers);
      VERIFY_ARE_EQUAL(0, os.offset);
      VERIFY_ARE_EQUAL(32, os.size);
    }

    VERIFY_ARE_EQUAL(1, Testables.AllocaWrites.size());
  }
}

TEST_F(PixTest, PixStructAnnotation_MixedSizes) {
    if (m_ver.SkipDxilVersion(1, 5)) return;

    for (auto choice : OptimizationChoices) {
        auto optimization = choice.Flag;

        const char* hlsl = R"(
struct smallPayload
{
    bool b1;
    uint16_t sixteen;
    uint32_t thirtytwo;
    uint64_t sixtyfour;
};


[numthreads(1, 1, 1)]
void main()
{
    smallPayload p;
    p.b1 = true;
    p.sixteen = 16;
    p.thirtytwo = 32;
    p.sixtyfour = 64;
    DispatchMesh(1, 1, 1, p);
}
)";

        auto Testables = TestStructAnnotationCase(hlsl, optimization);

        if (!choice.IsOptimized) {
            VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes.size());
            VERIFY_ARE_EQUAL(4, Testables.OffsetAndSizes[0].countOfMembers);
            VERIFY_ARE_EQUAL(0, Testables.OffsetAndSizes[0].offset);
            // 8 bytes align for uint64_t:
            VERIFY_ARE_EQUAL(32 + 16 + 16 /*alignment for next field*/ + 32 + 32/*alignment for max align*/ + 64,
                Testables.OffsetAndSizes[0].size);
        }
        else {
            VERIFY_ARE_EQUAL(4, Testables.OffsetAndSizes.size());

            VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes[0].countOfMembers);
            VERIFY_ARE_EQUAL(0, Testables.OffsetAndSizes[0].offset);
            VERIFY_ARE_EQUAL(32, Testables.OffsetAndSizes[0].size);

            VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes[1].countOfMembers);
            VERIFY_ARE_EQUAL(32, Testables.OffsetAndSizes[1].offset);
            VERIFY_ARE_EQUAL(16, Testables.OffsetAndSizes[1].size);

            VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes[2].countOfMembers);
            VERIFY_ARE_EQUAL(32+32, Testables.OffsetAndSizes[2].offset);
            VERIFY_ARE_EQUAL(32, Testables.OffsetAndSizes[2].size);

            VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes[3].countOfMembers);
            VERIFY_ARE_EQUAL(32+32+32+/*padding for alignment*/32, Testables.OffsetAndSizes[3].offset);
            VERIFY_ARE_EQUAL(64, Testables.OffsetAndSizes[3].size);
        }

        VERIFY_ARE_EQUAL(4, Testables.AllocaWrites.size());
        ValidateAllocaWrite(Testables.AllocaWrites, 0, "b1");
        ValidateAllocaWrite(Testables.AllocaWrites, 1, "sixteen");
        ValidateAllocaWrite(Testables.AllocaWrites, 2, "thirtytwo");
        ValidateAllocaWrite(Testables.AllocaWrites, 3, "sixtyfour");
    }
}

TEST_F(PixTest, PixStructAnnotation_StructWithinStruct) {
  if (m_ver.SkipDxilVersion(1, 5)) return;

    for (auto choice : OptimizationChoices) {
      auto optimization = choice.Flag;

      const char* hlsl = R"(

struct Contained
{
  uint32_t one;
  uint32_t two;
};

struct smallPayload
{
  uint32_t before;
  Contained contained;
  uint32_t after;
};


[numthreads(1, 1, 1)]
void main()
{
    smallPayload p;
    p.before = 0xb4;
    p.contained.one = 1;
    p.contained.two = 2;
    p.after = 3;
    DispatchMesh(1, 1, 1, p);
}
)";

      auto Testables = TestStructAnnotationCase(hlsl, optimization);

      if (!choice.IsOptimized) {
          VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes.size());
          VERIFY_ARE_EQUAL(4, Testables.OffsetAndSizes[0].countOfMembers);
          VERIFY_ARE_EQUAL(0, Testables.OffsetAndSizes[0].offset);
          VERIFY_ARE_EQUAL(4 * 32, Testables.OffsetAndSizes[0].size);
      }
      else {
          VERIFY_ARE_EQUAL(4, Testables.OffsetAndSizes.size());
          for (int i = 0; i < 4; i++) {
              VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes[i].countOfMembers);
              VERIFY_ARE_EQUAL(i * 32, Testables.OffsetAndSizes[i].offset);
              VERIFY_ARE_EQUAL(32, Testables.OffsetAndSizes[i].size);
          }
      }

      ValidateAllocaWrite(Testables.AllocaWrites, 0, "before");
      ValidateAllocaWrite(Testables.AllocaWrites, 1, "contained.one");
      ValidateAllocaWrite(Testables.AllocaWrites, 2, "contained.two");
      ValidateAllocaWrite(Testables.AllocaWrites, 3, "after");
  }
}

TEST_F(PixTest, PixStructAnnotation_1DArray) {
  if (m_ver.SkipDxilVersion(1, 5)) return;

    for (auto choice : OptimizationChoices) {
      auto optimization = choice.Flag;

      const char* hlsl = R"(
struct smallPayload
{
    uint32_t Array[2];
};


[numthreads(1, 1, 1)]
void main()
{
    smallPayload p;
    p.Array[0] = 250;
    p.Array[1] = 251;
    DispatchMesh(1, 1, 1, p);
}
)";

      auto Testables = TestStructAnnotationCase(hlsl, optimization);
      if (!choice.IsOptimized) {
          VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes.size());
          VERIFY_ARE_EQUAL(2, Testables.OffsetAndSizes[0].countOfMembers);
          VERIFY_ARE_EQUAL(0, Testables.OffsetAndSizes[0].offset);
          VERIFY_ARE_EQUAL(2 * 32, Testables.OffsetAndSizes[0].size);
      }
      else {
          VERIFY_ARE_EQUAL(2, Testables.OffsetAndSizes.size());
          for (int i = 0; i < 2; i++) {
              VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes[i].countOfMembers);
              VERIFY_ARE_EQUAL(i * 32, Testables.OffsetAndSizes[i].offset);
              VERIFY_ARE_EQUAL(32, Testables.OffsetAndSizes[i].size);
          }
      }
      VERIFY_ARE_EQUAL(2, Testables.AllocaWrites.size());

      int Idx = 0;
      ValidateAllocaWrite(Testables.AllocaWrites, Idx++, "Array[0]");
      ValidateAllocaWrite(Testables.AllocaWrites, Idx++, "Array[1]");
  }
}

TEST_F(PixTest, PixStructAnnotation_2DArray) {
  if (m_ver.SkipDxilVersion(1, 5)) return;

    for (auto choice : OptimizationChoices) {
      auto optimization = choice.Flag;
      const char* hlsl = R"(
struct smallPayload
{
    uint32_t TwoDArray[2][3];
};


[numthreads(1, 1, 1)]
void main()
{
    smallPayload p;
    p.TwoDArray[0][0] = 250;
    p.TwoDArray[0][1] = 251;
    p.TwoDArray[0][2] = 252;
    p.TwoDArray[1][0] = 253;
    p.TwoDArray[1][1] = 254;
    p.TwoDArray[1][2] = 255;
    DispatchMesh(1, 1, 1, p);
}
)";

      auto Testables = TestStructAnnotationCase(hlsl, optimization);
      if (!choice.IsOptimized) {
          VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes.size());
          VERIFY_ARE_EQUAL(6, Testables.OffsetAndSizes[0].countOfMembers);
          VERIFY_ARE_EQUAL(0, Testables.OffsetAndSizes[0].offset);
          VERIFY_ARE_EQUAL(2 * 3 * 32, Testables.OffsetAndSizes[0].size);
      }
      else {
          VERIFY_ARE_EQUAL(6, Testables.OffsetAndSizes.size());
          for (int i = 0; i < 6; i++) {
              VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes[i].countOfMembers);
              VERIFY_ARE_EQUAL(i * 32, Testables.OffsetAndSizes[i].offset);
              VERIFY_ARE_EQUAL(32, Testables.OffsetAndSizes[i].size);
          }
      }
      VERIFY_ARE_EQUAL(6, Testables.AllocaWrites.size());

      int Idx = 0;
      ValidateAllocaWrite(Testables.AllocaWrites, Idx++, "TwoDArray[0][0]");
      ValidateAllocaWrite(Testables.AllocaWrites, Idx++, "TwoDArray[0][1]");
      ValidateAllocaWrite(Testables.AllocaWrites, Idx++, "TwoDArray[0][2]");
      ValidateAllocaWrite(Testables.AllocaWrites, Idx++, "TwoDArray[1][0]");
      ValidateAllocaWrite(Testables.AllocaWrites, Idx++, "TwoDArray[1][1]");
      ValidateAllocaWrite(Testables.AllocaWrites, Idx++, "TwoDArray[1][2]");
  }
}

TEST_F(PixTest, PixStructAnnotation_EmbeddedArray) {
  if (m_ver.SkipDxilVersion(1, 5)) return;

    for (auto choice : OptimizationChoices) {
      auto optimization = choice.Flag;
      const char* hlsl = R"(

struct Contained
{
  uint32_t array[3];
};

struct smallPayload
{
  uint32_t before;
  Contained contained;
  uint32_t after;
};


[numthreads(1, 1, 1)]
void main()
{
    smallPayload p;
    p.before = 0xb4;
    p.contained.array[0] = 0;
    p.contained.array[1] = 1;
    p.contained.array[2] = 2;
    p.after = 3;
    DispatchMesh(1, 1, 1, p);
}
)";

      auto Testables = TestStructAnnotationCase(hlsl, optimization);

      if (!choice.IsOptimized) {
          VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes.size());
          VERIFY_ARE_EQUAL(5, Testables.OffsetAndSizes[0].countOfMembers);
          VERIFY_ARE_EQUAL(0, Testables.OffsetAndSizes[0].offset);
          VERIFY_ARE_EQUAL(5 * 32, Testables.OffsetAndSizes[0].size);
      }
      else {
          VERIFY_ARE_EQUAL(5, Testables.OffsetAndSizes.size());
          for (int i = 0; i < 5; i++) {
            VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes[i].countOfMembers);
            VERIFY_ARE_EQUAL(i * 32, Testables.OffsetAndSizes[i].offset);
            VERIFY_ARE_EQUAL(32, Testables.OffsetAndSizes[i].size);
          }
      }

      ValidateAllocaWrite(Testables.AllocaWrites, 0, "before");
      ValidateAllocaWrite(Testables.AllocaWrites, 1, "contained.array[0]");
      ValidateAllocaWrite(Testables.AllocaWrites, 2, "contained.array[1]");
      ValidateAllocaWrite(Testables.AllocaWrites, 3, "contained.array[2]");
      ValidateAllocaWrite(Testables.AllocaWrites, 4, "after");
  }
}

TEST_F(PixTest, PixStructAnnotation_FloatN) {
  if (m_ver.SkipDxilVersion(1, 5)) return;

    for (auto choice : OptimizationChoices) {
      auto optimization = choice.Flag;
      auto IsOptimized = choice.IsOptimized;
      const char* hlsl = R"(
struct smallPayload
{
    float2 f2;
};


[numthreads(1, 1, 1)]
void main()
{
    smallPayload p;
    p.f2 = float2(1,2);
    DispatchMesh(1, 1, 1, p);
}
)";

      auto Testables = TestStructAnnotationCase(hlsl, optimization);

      if (IsOptimized) {
        VERIFY_ARE_EQUAL(2, Testables.OffsetAndSizes.size());
        VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes[0].countOfMembers);
        VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes[1].countOfMembers);
        VERIFY_ARE_EQUAL(0, Testables.OffsetAndSizes[0].offset);
        VERIFY_ARE_EQUAL(32, Testables.OffsetAndSizes[0].size);
        VERIFY_ARE_EQUAL(32, Testables.OffsetAndSizes[1].offset);
        VERIFY_ARE_EQUAL(32, Testables.OffsetAndSizes[1].size);
      }
      else {
        VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes.size());
        VERIFY_ARE_EQUAL(2, Testables.OffsetAndSizes[0].countOfMembers);
        VERIFY_ARE_EQUAL(0, Testables.OffsetAndSizes[0].offset);
        VERIFY_ARE_EQUAL(32 + 32, Testables.OffsetAndSizes[0].size);
      }

      VERIFY_ARE_EQUAL(Testables.AllocaWrites.size(), 2);
      ValidateAllocaWrite(Testables.AllocaWrites, 0, "f2.x");
      ValidateAllocaWrite(Testables.AllocaWrites, 1, "f2.y");
  }
}


TEST_F(PixTest, PixStructAnnotation_SequentialFloatN) {
  if (m_ver.SkipDxilVersion(1, 5)) return;

    for (auto choice : OptimizationChoices) {
      auto optimization = choice.Flag;
      const char* hlsl = R"(
struct smallPayload
{
    float3 color;
    float3 dir;
};


[numthreads(1, 1, 1)]
void main()
{
    smallPayload p;
    p.color = float3(1,2,3);
    p.dir = float3(4,5,6);

    DispatchMesh(1, 1, 1, p);
}
)";

      auto Testables = TestStructAnnotationCase(hlsl, optimization);

      if (choice.IsOptimized) {
        VERIFY_ARE_EQUAL(6, Testables.OffsetAndSizes.size());
        for (int i = 0; i < 6; i++) {
          VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes[i].countOfMembers);
          VERIFY_ARE_EQUAL(i * 32, Testables.OffsetAndSizes[i].offset);
          VERIFY_ARE_EQUAL(32, Testables.OffsetAndSizes[i].size);
        }
      }
      else {
        VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes.size());
        VERIFY_ARE_EQUAL(6, Testables.OffsetAndSizes[0].countOfMembers);
        VERIFY_ARE_EQUAL(0, Testables.OffsetAndSizes[0].offset);
        VERIFY_ARE_EQUAL(32 * 6, Testables.OffsetAndSizes[0].size);
      }

      VERIFY_ARE_EQUAL(6, Testables.AllocaWrites.size());
      ValidateAllocaWrite(Testables.AllocaWrites, 0, "color.x");
      ValidateAllocaWrite(Testables.AllocaWrites, 1, "color.y");
      ValidateAllocaWrite(Testables.AllocaWrites, 2, "color.z");
      ValidateAllocaWrite(Testables.AllocaWrites, 3, "dir.x");
      ValidateAllocaWrite(Testables.AllocaWrites, 4, "dir.y");
      ValidateAllocaWrite(Testables.AllocaWrites, 5, "dir.z");
  }
}

TEST_F(PixTest, PixStructAnnotation_EmbeddedFloatN) {
  if (m_ver.SkipDxilVersion(1, 5)) return;

    for (auto choice : OptimizationChoices) {
      auto optimization = choice.Flag;
      const char* hlsl = R"(

struct Embedded
{
    float2 f2;
};

struct smallPayload
{
  uint32_t i32;
  Embedded e;
};


[numthreads(1, 1, 1)]
void main()
{
    smallPayload p;
    p.i32 = 32;
    p.e.f2 = float2(1,2);
    DispatchMesh(1, 1, 1, p);
}
)";

      auto Testables = TestStructAnnotationCase(hlsl, optimization);

      if (choice.IsOptimized) {
        VERIFY_ARE_EQUAL(3, Testables.OffsetAndSizes.size());
        for (int i = 0; i < 3; i++) {
          VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes[i].countOfMembers);
          VERIFY_ARE_EQUAL(i * 32, Testables.OffsetAndSizes[i].offset);
          VERIFY_ARE_EQUAL(32, Testables.OffsetAndSizes[i].size);
        }
      }
      else {
        VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes.size());
        VERIFY_ARE_EQUAL(3, Testables.OffsetAndSizes[0].countOfMembers);
        VERIFY_ARE_EQUAL(0, Testables.OffsetAndSizes[0].offset);
        VERIFY_ARE_EQUAL(32 * 3, Testables.OffsetAndSizes[0].size);
      }

      VERIFY_ARE_EQUAL(3, Testables.AllocaWrites.size());
      ValidateAllocaWrite(Testables.AllocaWrites, 0, "i32");
      ValidateAllocaWrite(Testables.AllocaWrites, 1, "e.f2.x");
      ValidateAllocaWrite(Testables.AllocaWrites, 2, "e.f2.y");
  }
}

TEST_F(PixTest, PixStructAnnotation_Matrix) {
  if (m_ver.SkipDxilVersion(1, 5)) return;

    for (auto choice : OptimizationChoices) {
      auto optimization = choice.Flag;
      const char* hlsl = R"(
struct smallPayload
{
  float4x4 mat;
};


[numthreads(1, 1, 1)]
void main()
{
  smallPayload p;
  p.mat = float4x4( 1,2,3,4, 5,6,7,8, 9,10,11,12, 13,14,15, 16);
  DispatchMesh(1, 1, 1, p);
}
)";

      auto Testables = TestStructAnnotationCase(hlsl, optimization);
      // Can't test member iterator until dbg.declare instructions are emitted when structs
      // contain pointers-to-pointers
      VERIFY_ARE_EQUAL(16, Testables.AllocaWrites.size());
      for (int i = 0; i < 4; ++i)
      {
        for (int j = 0; j < 4; ++j)
        {
          std::string expected = std::string("mat._") + std::to_string(i + 1) + std::to_string(j + 1);
          ValidateAllocaWrite(Testables.AllocaWrites, i*4 + j, expected.c_str());
        }
      }
  }
}

TEST_F(PixTest, PixStructAnnotation_MemberFunction) {
  if (m_ver.SkipDxilVersion(1, 5))
    return;

    for (auto choice : OptimizationChoices) {
      auto optimization = choice.Flag;
      const char* hlsl = R"(

RWStructuredBuffer<float> floatRWUAV: register(u0);

struct smallPayload
{
    int i;
};

float2 signNotZero(float2 v)
{
 return (v > 0.0f ? float(1).xx : float(-1).xx);
}

float2 unpackUnorm2(uint packed)
{
 return (1.0 / 65535.0) * float2((packed >> 16) & 0xffff, packed & 0xffff);
}

float3 unpackOctahedralSnorm(float2 e)
{
 float3 v = float3(e.xy, 1.0f - abs(e.x) - abs(e.y));
 if (v.z < 0.0f) v.xy = (1.0f - abs(v.yx)) * signNotZero(v.xy);
 return normalize(v);
}

float3 unpackOctahedralUnorm(float2 e)
{
 return unpackOctahedralSnorm(e * 2.0f - 1.0f);
}

float2 unpackHalf2(uint packed)
{
 return float2(f16tof32(packed >> 16), f16tof32(packed & 0xffff));
}

struct Gbuffer
{
	float3 worldNormal;
	float3 objectNormal; //offset:12
	
	float linearZ; //24
	float prevLinearZ; //28
	
	
	float fwidthLinearZ; //32
	float fwidthObjectNormal; //36
	
	
	uint materialType; //40
	uint2 materialParams0; //44
	uint4 materialParams1; //52  <--------- this is the variable that's being covered twice (52*8 = 416 416)
	
	uint instanceId;  //68  <------- and there's one dword left over, as expected
	
	
	void load(int2 pixelPos, Texture2DArray<uint4> gbTex)
	{
	uint4 data0 = gbTex.Load(int4(pixelPos, 0, 0));
	uint4 data1 = gbTex.Load(int4(pixelPos, 1, 0));
	uint4 data2 = gbTex.Load(int4(pixelPos, 2, 0));
	
	
	worldNormal = unpackOctahedralUnorm(unpackUnorm2(data0.x));
	linearZ = f16tof32((data0.y >> 8) & 0xffff);
	materialType = (data0.y & 0xff);
	materialParams0 = data0.zw;
	
	
	materialParams1 = data1.xyzw;
	
	
	instanceId = data2.x;
	prevLinearZ = asfloat(data2.y);
	objectNormal = unpackOctahedralUnorm(unpackUnorm2(data2.z));
	float2 fwidth = unpackHalf2(data2.w);
	fwidthLinearZ = fwidth.x;
	fwidthObjectNormal = fwidth.y;
	}
};

Gbuffer loadGbuffer(int2 pixelPos, Texture2DArray<uint4> gbTex)
{
	Gbuffer output;
	output.load(pixelPos, gbTex);
	return output;
}

Texture2DArray<uint4> g_gbuffer : register(t0, space0);

[numthreads(1, 1, 1)]
void main()
{	
	const Gbuffer gbuffer = loadGbuffer(int2(0,0), g_gbuffer);
    smallPayload p;
    p.i = gbuffer.materialParams1.x + gbuffer.materialParams1.y + gbuffer.materialParams1.z + gbuffer.materialParams1.w;
    DispatchMesh(1, 1, 1, p);
}


)";
      auto Testables = TestStructAnnotationCase(hlsl, optimization, true);

      // TODO: Make 'this' work

      // Can't validate # of writes: rel and dbg are different
      //VERIFY_ARE_EQUAL(43, Testables.AllocaWrites.size());

      // Can't test individual writes until struct member names are returned:
      //for (int i = 0; i < 51; ++i)
      //{
      //  ValidateAllocaWrite(Testables.AllocaWrites, i, "");
      //}
  }
}

TEST_F(PixTest, PixStructAnnotation_BigMess) {
    if (m_ver.SkipDxilVersion(1, 5)) return;

    for (auto choice : OptimizationChoices) {
        auto optimization = choice.Flag;

        const char* hlsl = R"(

struct BigStruct
{
    uint64_t bigInt;
    double bigDouble;
};

struct EmbeddedStruct
{
    uint32_t OneInt;
    uint32_t TwoDArray[2][2];
};

struct smallPayload
{
    uint dummy;
    uint vertexCount;
    uint primitiveCount;
    EmbeddedStruct embeddedStruct;
#ifdef PAYLOAD_MATRICES
    float4x4 mat;
#endif
    uint64_t bigOne;
    half littleOne;
    BigStruct bigStruct[2];
    uint lastCheck;
};


[numthreads(1, 1, 1)]
void main()
{
    smallPayload p;
    // Adding enough instructions to make the shader interesting to debug:
    p.dummy = 42;
    p.vertexCount = 3;
    p.primitiveCount = 1;
    p.embeddedStruct.OneInt = 123;
    p.embeddedStruct.TwoDArray[0][0] = 252;
    p.embeddedStruct.TwoDArray[0][1] = 253;
    p.embeddedStruct.TwoDArray[1][0] = 254;
    p.embeddedStruct.TwoDArray[1][1] = 255;
#ifdef PAYLOAD_MATRICES
    p.mat = float4x4( 1,2,3,4, 5,6,7,8, 9,10,11,12, 13,14,15, 16);
#endif
    p.bigOne = 123456789;
    p.littleOne = 1.0;
    p.bigStruct[0].bigInt = 10;
    p.bigStruct[0].bigDouble = 2.0;
    p.bigStruct[1].bigInt = 20;
    p.bigStruct[1].bigDouble = 4.0;
    p.lastCheck = 27;
    DispatchMesh(1, 1, 1, p);
}
)";

        auto Testables = TestStructAnnotationCase(hlsl, optimization);
        if (!choice.IsOptimized) {
            VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes.size());
            VERIFY_ARE_EQUAL(15, Testables.OffsetAndSizes[0].countOfMembers);
            VERIFY_ARE_EQUAL(0, Testables.OffsetAndSizes[0].offset);
            constexpr uint32_t BigStructBitSize = 64 * 2;
            constexpr uint32_t EmbeddedStructBitSize = 32 * 5;
            VERIFY_ARE_EQUAL(3 * 32 + EmbeddedStructBitSize + 64 + 16 + 16/*alignment for next field*/ + BigStructBitSize * 2 + 32 + 32/*align to max align*/, Testables.OffsetAndSizes[0].size);
        }
        else {
            VERIFY_ARE_EQUAL(15, Testables.OffsetAndSizes.size());

            // First 8 members
            for (int i = 0; i < 8; i++) {
              VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes[i].countOfMembers);
              VERIFY_ARE_EQUAL(i * 32, Testables.OffsetAndSizes[i].offset);
              VERIFY_ARE_EQUAL(32, Testables.OffsetAndSizes[i].size);
            }

            // bigOne
            VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes[8].countOfMembers);
            VERIFY_ARE_EQUAL(256, Testables.OffsetAndSizes[8].offset);
            VERIFY_ARE_EQUAL(64, Testables.OffsetAndSizes[8].size);

            // littleOne
            VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes[9].countOfMembers);
            VERIFY_ARE_EQUAL(320, Testables.OffsetAndSizes[9].offset);
            VERIFY_ARE_EQUAL(16, Testables.OffsetAndSizes[9].size);

            // Each member of BigStruct[2]
            for (int i = 0; i < 4; i++) {
              int idx = i + 10;
              VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes[idx].countOfMembers);
              VERIFY_ARE_EQUAL(384 + i*64, Testables.OffsetAndSizes[idx].offset);
              VERIFY_ARE_EQUAL(64, Testables.OffsetAndSizes[idx].size);
            }

            VERIFY_ARE_EQUAL(1, Testables.OffsetAndSizes[14].countOfMembers);
            VERIFY_ARE_EQUAL(640, Testables.OffsetAndSizes[14].offset);
            VERIFY_ARE_EQUAL(32, Testables.OffsetAndSizes[14].size);
        }

        VERIFY_ARE_EQUAL(15, Testables.AllocaWrites.size());

        size_t Index = 0;
        ValidateAllocaWrite(Testables.AllocaWrites, Index++, "dummy");
        ValidateAllocaWrite(Testables.AllocaWrites, Index++, "vertexCount");
        ValidateAllocaWrite(Testables.AllocaWrites, Index++, "primitiveCount");
        ValidateAllocaWrite(Testables.AllocaWrites, Index++, "embeddedStruct.OneInt");
        ValidateAllocaWrite(Testables.AllocaWrites, Index++, "embeddedStruct.TwoDArray[0][0]");
        ValidateAllocaWrite(Testables.AllocaWrites, Index++, "embeddedStruct.TwoDArray[0][1]");
        ValidateAllocaWrite(Testables.AllocaWrites, Index++, "embeddedStruct.TwoDArray[1][0]");
        ValidateAllocaWrite(Testables.AllocaWrites, Index++, "embeddedStruct.TwoDArray[1][1]");
        ValidateAllocaWrite(Testables.AllocaWrites, Index++, "bigOne");
        ValidateAllocaWrite(Testables.AllocaWrites, Index++, "littleOne");
        ValidateAllocaWrite(Testables.AllocaWrites, Index++, "bigStruct[0].bigInt");
        ValidateAllocaWrite(Testables.AllocaWrites, Index++, "bigStruct[0].bigDouble");
        ValidateAllocaWrite(Testables.AllocaWrites, Index++, "bigStruct[1].bigInt");
        ValidateAllocaWrite(Testables.AllocaWrites, Index++, "bigStruct[1].bigDouble");
        ValidateAllocaWrite(Testables.AllocaWrites, Index++, "lastCheck");
    }
}

TEST_F(PixTest, PixStructAnnotation_AlignedFloat4Arrays) {
    if (m_ver.SkipDxilVersion(1, 5)) return;

    for (auto choice : OptimizationChoices) {
        auto optimization = choice.Flag;

        const char* hlsl = R"(

struct LinearSHSampleData
{
	float4 linearTerms[3];
	float4 hdrColorAO;
	float4 visibilitySH;
} g_lhSampleData;

struct smallPayload
{
    LinearSHSampleData lhSampleData;
};


[numthreads(1, 1, 1)]
void main()
{
    smallPayload p;
    p.lhSampleData.linearTerms[0].x = g_lhSampleData.linearTerms[0].x;
    DispatchMesh(1, 1, 1, p);
}
)";

        auto Testables = TestStructAnnotationCase(hlsl, optimization);
        // Can't test offsets and sizes until dbg.declare instructions are emitted when floatn is used (https://github.com/microsoft/DirectXShaderCompiler/issues/2920)
        //VERIFY_ARE_EQUAL(20, Testables.AllocaWrites.size());
    }
}

TEST_F(PixTest, PixStructAnnotation_Inheritance) {
    if (m_ver.SkipDxilVersion(1, 5)) return;

    for (auto choice : OptimizationChoices) {
      auto optimization = choice.Flag;

        const char* hlsl = R"(
struct Base
{
    float floatValue;
};
typedef Base BaseTypedef;

struct Derived : BaseTypedef
{
	int intValue;
};

[numthreads(1, 1, 1)]
void main()
{
    Derived p;
    p.floatValue = 1.;
    p.intValue = 2;
    DispatchMesh(1, 1, 1, p);
}
)";

        auto Testables = TestStructAnnotationCase(hlsl, optimization);

        // Can't test offsets and sizes until dbg.declare instructions are emitted when floatn is used (https://github.com/microsoft/DirectXShaderCompiler/issues/2920)
        //VERIFY_ARE_EQUAL(20, Testables.AllocaWrites.size());
    }
}

TEST_F(PixTest, PixStructAnnotation_ResourceAsMember) {
    if (m_ver.SkipDxilVersion(1, 5)) return;

    for (auto choice : OptimizationChoices) {
      auto optimization = choice.Flag;

        const char* hlsl = R"(

Buffer g_texture;

struct smallPayload
{
    float value;
};

struct WithEmbeddedObject
{
	Buffer texture;
};

void DispatchIt(WithEmbeddedObject eo)
{
    smallPayload p;
    p.value = eo.texture.Load(0);
    DispatchMesh(1, 1, 1, p);
}

[numthreads(1, 1, 1)]
void main()
{
    WithEmbeddedObject eo;
    eo.texture = g_texture;
    DispatchIt(eo);
}
)";

        auto Testables = TestStructAnnotationCase(hlsl, optimization);
        // Can't test offsets and sizes until dbg.declare instructions are emitted when floatn is used (https://github.com/microsoft/DirectXShaderCompiler/issues/2920)
        //VERIFY_ARE_EQUAL(20, Testables.AllocaWrites.size());
    }
}

TEST_F(PixTest, PixStructAnnotation_WheresMyDbgValue) {
    if (m_ver.SkipDxilVersion(1, 5)) return;

    for (auto choice : OptimizationChoices) {
      auto optimization = choice.Flag;

        const char* hlsl = R"(

struct smallPayload
{
    float f1;
    float2 f2;
};


[numthreads(1, 1, 1)]
void main()
{
    smallPayload p;
    p.f1 = 1;
    p.f2 = float2(2,3);
    DispatchMesh(1, 1, 1, p);
}
)";

        auto Testables = TestStructAnnotationCase(hlsl, optimization);
        // Can't test offsets and sizes until dbg.declare instructions are emitted when floatn is used (https://github.com/microsoft/DirectXShaderCompiler/issues/2920)
        VERIFY_ARE_EQUAL(3, Testables.AllocaWrites.size());
    }
}

TEST_F(PixTest, VirtualRegisters_InstructionCounts) {
  if (m_ver.SkipDxilVersion(1, 5))
    return;

  for (auto choice : OptimizationChoices) {
    auto optimization = choice.Flag;
    const char *hlsl = R"(

RaytracingAccelerationStructure Scene : register(t0, space0);
RWTexture2D<float4> RenderTarget : register(u0);

struct SceneConstantBuffer
{
    float4x4 projectionToWorld;
    float4 cameraPosition;
    float4 lightPosition;
    float4 lightAmbientColor;
    float4 lightDiffuseColor;
};

ConstantBuffer<SceneConstantBuffer> g_sceneCB : register(b0);

struct RayPayload
{
    float4 color;
};

inline void GenerateCameraRay(uint2 index, out float3 origin, out float3 direction)
{
    float2 xy = index + 0.5f; // center in the middle of the pixel.
    float2 screenPos = xy;// / DispatchRaysDimensions().xy * 2.0 - 1.0;

    // Invert Y for DirectX-style coordinates.
    screenPos.y = -screenPos.y;

    // Unproject the pixel coordinate into a ray.
    float4 world = /*mul(*/float4(screenPos, 0, 1)/*, g_sceneCB.projectionToWorld)*/;

    //world.xyz /= world.w;
    origin = world.xyz; //g_sceneCB.cameraPosition.xyz;
    direction = float3(1,0,0);//normalize(world.xyz - origin);
}

void RaygenCommon()
{
    float3 rayDir;
    float3 origin;
    
    // Generate a ray for a camera pixel corresponding to an index from the dispatched 2D grid.
    GenerateCameraRay(DispatchRaysIndex().xy, origin, rayDir);

    // Trace the ray.
    // Set the ray's extents.
    RayDesc ray;
    ray.Origin = origin;
    ray.Direction = rayDir;
    // Set TMin to a non-zero small value to avoid aliasing issues due to floating - point errors.
    // TMin should be kept small to prevent missing geometry at close contact areas.
    ray.TMin = 0.001;
    ray.TMax = 10000.0;
    RayPayload payload = { float4(0, 0, 0, 0) };
    TraceRay(Scene, RAY_FLAG_CULL_BACK_FACING_TRIANGLES, ~0, 0, 1, 0, ray, payload);

    // Write the raytraced color to the output texture.
   // RenderTarget[DispatchRaysIndex().xy] = payload.color;
}

[shader("raygeneration")]
void Raygen0()
{
    RaygenCommon();
}

[shader("raygeneration")]
void Raygen1()
{
    RaygenCommon();
}

typedef BuiltInTriangleIntersectionAttributes MyAttributes;

[shader("closesthit")]
void InnerClosestHitShader(inout RayPayload payload, in MyAttributes attr)
{
    payload.color = float4(0,1,0,0);
}


[shader("miss")]
void MyMissShader(inout RayPayload payload)
{
    payload.color = float4(1, 0, 0, 0);
})";

    CComPtr<IDxcBlob> pBlob = Compile(hlsl, L"lib_6_6", {optimization});
    CComPtr<IDxcBlob> pDxil = FindModule(DFCC_ShaderDebugInfoDXIL, pBlob);
    auto outputLines = RunAnnotationPasses(pDxil).lines;

    const char instructionRangeLabel[] = "InstructionRange:";

    // The numbering pass should have counted  instructions for each "interesting" (to PIX)
    // function and output its start and (end+1) instruction ordinal. End should always
    // be a reasonable number of instructions (>10) and end should always be higher
    // than start, and all four functions above should be represented.
    int countOfInstructionRangeLines = 0;
    for (auto const &line : outputLines) {
      auto tokens = Tokenize(line, " ");
      if (tokens.size() >= 4) {
        if (tokens[0] == instructionRangeLabel) {
          countOfInstructionRangeLines++;
          int instructionStart = atoi(tokens[1].c_str());
          int instructionEnd = atoi(tokens[2].c_str());
          VERIFY_IS_TRUE(instructionEnd > 10);
          VERIFY_IS_TRUE(instructionEnd > instructionStart);
          auto found1 = tokens[3].find("Raygen0@@YAXXZ") != std::string::npos;
          auto found2 = tokens[3].find("Raygen1@@YAXXZ") != std::string::npos;
          auto foundClosest = tokens[3].find("InnerClosestHit") != std::string::npos;
          auto foundMiss = tokens[3].find("MyMiss") != std::string::npos;
          VERIFY_IS_TRUE(found1 || found2 || foundClosest || foundMiss);
        }
      }
    }
    VERIFY_ARE_EQUAL(4, countOfInstructionRangeLines);

    // Non-library target:
    const char *PixelShader= R"(
    [RootSignature("")]
    float main(float pos : A) : SV_Target {
      float x = abs(pos);
      float y = sin(pos);
      float z = x + y;
      return z;
    }
  )";
    pBlob = Compile(PixelShader, L"ps_6_6", {optimization});
    pDxil = FindModule(DFCC_ShaderDebugInfoDXIL, pBlob);
    outputLines = RunAnnotationPasses(pDxil).lines;

    countOfInstructionRangeLines = 0;
    for (auto const &line : outputLines) {
      auto tokens = Tokenize(line, " ");
      if (tokens.size() >= 4) {
        if (tokens[0] == instructionRangeLabel) {
          countOfInstructionRangeLines++;
          int instructionStart = atoi(tokens[1].c_str());
          int instructionEnd = atoi(tokens[2].c_str());
          VERIFY_IS_TRUE(instructionStart == 0);
          VERIFY_IS_TRUE(instructionEnd > 10);
          VERIFY_IS_TRUE(instructionEnd > instructionStart);
          auto foundMain = tokens[3].find("main") != std::string::npos;
          VERIFY_IS_TRUE(foundMain);
        }
      }
    }
    VERIFY_ARE_EQUAL(1, countOfInstructionRangeLines);

    // Now check that the initial value parameter works:
    const int startingInstructionOrdinal = 1234;
    outputLines = RunAnnotationPasses(pDxil, startingInstructionOrdinal).lines;

    countOfInstructionRangeLines = 0;
    for (auto const &line : outputLines) {
      auto tokens = Tokenize(line, " ");
      if (tokens.size() >= 4) {
        if (tokens[0] == instructionRangeLabel) {
          countOfInstructionRangeLines++;
          int instructionStart = atoi(tokens[1].c_str());
          int instructionEnd = atoi(tokens[2].c_str());
          VERIFY_IS_TRUE(instructionStart == startingInstructionOrdinal);
          VERIFY_IS_TRUE(instructionEnd > instructionStart);
          auto foundMain = tokens[3].find("main") != std::string::npos;
          VERIFY_IS_TRUE(foundMain);
        }
      }
    }
    VERIFY_ARE_EQUAL(1, countOfInstructionRangeLines);
  }
}


TEST_F(PixTest, VirtualRegisters_AlignedOffsets) {
  if (m_ver.SkipDxilVersion(1, 5))
    return;

  {
    const char *hlsl = R"(
cbuffer cbEveryFrame : register(b0)
{
    int i32;
    float f32;
};

struct VS_OUTPUT_ENV
{
    float4 Pos        : SV_Position;
    float2 Tex        : TEXCOORD0;
};

float4 main(VS_OUTPUT_ENV input) : SV_Target
{
    // (BTW we load from i32 and f32 (which are resident in a cb) so that these local variables aren't optimized away)
    bool i1 = i32 != 0;
    min16uint u16 = (min16uint)(i32 / 4);
    min16int s16 = (min16int)(i32/4) * -1; // signed s16 gets -8
    min12int s12 = (min12int)(i32/8) * -1; // signed s12 gets -4
    half h = (half) f32 / 2.f; // f32 is initialized to 32.0 in8he CB, so the 16-bit type now has "16.0" in it
    min16float mf16 = (min16float) f32 / -2.f;
    min10float mf10 = (min10float) f32 / -4.f;
    return float4((float)(i1 + u16) / 2.f, (float)(s16 + s12) / -128.f, h / 128.f, mf16 / 128.f + mf10 / 256.f);
}
)";

    //This is little more than a crash test, designed to exercise a previously over-active assert..
    std::vector<std::pair<const wchar_t *,  std::vector<const wchar_t *>>> argSets = {
          {L"ps_6_0", {L"-Od"}}, 
          {L"ps_6_2", {L"-Od", L"-HV", L"2018", L"-enable-16bit-types"}}
    };
    for (auto const &args : argSets) {

      CComPtr<IDxcBlob> pBlob = Compile(hlsl, args.first, args.second);
      CComPtr<IDxcBlob> pDxil = FindModule(DFCC_ShaderDebugInfoDXIL, pBlob);
      RunAnnotationPasses(pDxil).lines;
    }
  }
}

static void VerifyOperationSucceeded(IDxcOperationResult *pResult) 
{
  HRESULT result;
  VERIFY_SUCCEEDED(pResult->GetStatus(&result));
  if (FAILED(result)) {
    CComPtr<IDxcBlobEncoding> pErrors;
    VERIFY_SUCCEEDED(pResult->GetErrorBuffer(&pErrors));
    CA2W errorsWide(BlobToUtf8(pErrors).c_str(), CP_UTF8);
    WEX::Logging::Log::Comment(errorsWide);
  }
  VERIFY_SUCCEEDED(result);
}

TEST_F(PixTest, RootSignatureUpgrade_SubObjects) {

  const char *source = R"x(
GlobalRootSignature so_GlobalRootSignature =
{
	"RootConstants(num32BitConstants=1, b8), "
};

StateObjectConfig so_StateObjectConfig = 
{ 
    STATE_OBJECT_FLAGS_ALLOW_LOCAL_DEPENDENCIES_ON_EXTERNAL_DEFINITONS
};

LocalRootSignature so_LocalRootSignature1 = 
{
	"RootConstants(num32BitConstants=3, b2), "
	"UAV(u6),RootFlags(LOCAL_ROOT_SIGNATURE)" 
};

LocalRootSignature so_LocalRootSignature2 = 
{
	"RootConstants(num32BitConstants=3, b2), "
	"UAV(u8, flags=DATA_STATIC), " 
	"RootFlags(LOCAL_ROOT_SIGNATURE)"
};

RaytracingShaderConfig  so_RaytracingShaderConfig =
{
    128, // max payload size
    32   // max attribute size
};

RaytracingPipelineConfig so_RaytracingPipelineConfig =
{
    2 // max trace recursion depth
};

TriangleHitGroup MyHitGroup =
{
    "MyAnyHit",       // AnyHit
    "MyClosestHit",   // ClosestHit
};

SubobjectToExportsAssociation so_Association1 =
{
	"so_LocalRootSignature1", // subobject name
	"MyRayGen"                // export association 
};

SubobjectToExportsAssociation so_Association2 =
{
	"so_LocalRootSignature2", // subobject name
	"MyAnyHit"                // export association 
};

struct MyPayload
{
    float4 color;
};

[shader("raygeneration")]
void MyRayGen()
{
}

[shader("closesthit")]
void MyClosestHit(inout MyPayload payload, in BuiltInTriangleIntersectionAttributes attr)
{  
}

[shader("anyhit")]
void MyAnyHit(inout MyPayload payload, in BuiltInTriangleIntersectionAttributes attr)
{
}

[shader("miss")]
void MyMiss(inout MyPayload payload)
{
}

)x";

  CComPtr<IDxcCompiler> pCompiler;
  VERIFY_SUCCEEDED(m_dllSupport.CreateInstance(CLSID_DxcCompiler, &pCompiler));

  CComPtr<IDxcBlobEncoding> pSource;
  Utf8ToBlob(m_dllSupport, source, &pSource);

  CComPtr<IDxcOperationResult> pResult;
  VERIFY_SUCCEEDED(pCompiler->Compile(pSource, L"source.hlsl", L"", L"lib_6_6",
                                      nullptr, 0, nullptr, 0, nullptr,
                                      &pResult));
  VerifyOperationSucceeded(pResult);
  CComPtr<IDxcBlob> compiled;
  VERIFY_SUCCEEDED(pResult->GetResult(&compiled));

  auto optimizedContainer = RunShaderAccessTrackingPass(compiled);

  const char *pBlobContent =
      reinterpret_cast<const char *>(optimizedContainer->GetBufferPointer());
  unsigned blobSize = optimizedContainer->GetBufferSize();
  const hlsl::DxilContainerHeader *pContainerHeader =
      hlsl::IsDxilContainerLike(pBlobContent, blobSize);

  const hlsl::DxilPartHeader *pPartHeader =
      GetDxilPartByType(pContainerHeader, hlsl::DFCC_RuntimeData);
  VERIFY_ARE_NOT_EQUAL(pPartHeader, nullptr);

  hlsl::RDAT::DxilRuntimeData rdat(GetDxilPartData(pPartHeader),
                                   pPartHeader->PartSize);

  auto const subObjectTableReader = rdat.GetSubobjectTable();

  // There are 9 subobjects in the HLSL above:
  VERIFY_ARE_EQUAL(subObjectTableReader.Count(), 9u);

  bool foundGlobalRS = false;
  for (uint32_t i = 0; i < subObjectTableReader.Count(); ++i) {
    auto subObject = subObjectTableReader[i];
    hlsl::DXIL::SubobjectKind subobjectKind = subObject.getKind();
    switch (subobjectKind) {
    case hlsl::DXIL::SubobjectKind::GlobalRootSignature: {
      foundGlobalRS = true;
      VERIFY_IS_TRUE(0 ==
                     strcmp(subObject.getName(), "so_GlobalRootSignature"));

      auto rootSigReader = subObject.getRootSignature();
      DxilVersionedRootSignatureDesc const *rootSignature = nullptr;
      DeserializeRootSignature(rootSigReader.getData(),
                               rootSigReader.sizeData(), &rootSignature);
      VERIFY_ARE_EQUAL(rootSignature->Version,
                       DxilRootSignatureVersion::Version_1_1);
      VERIFY_ARE_EQUAL(rootSignature->Desc_1_1.NumParameters, 2);
      VERIFY_ARE_EQUAL(rootSignature->Desc_1_1.pParameters[1].ParameterType,
                       DxilRootParameterType::UAV);
      VERIFY_ARE_EQUAL(rootSignature->Desc_1_1.pParameters[1].ShaderVisibility,
                       DxilShaderVisibility::All);
      VERIFY_ARE_EQUAL(
          rootSignature->Desc_1_1.pParameters[1].Descriptor.RegisterSpace,
          static_cast<uint32_t>(-2));
      VERIFY_ARE_EQUAL(
          rootSignature->Desc_1_1.pParameters[1].Descriptor.ShaderRegister, 0u);
      DeleteRootSignature(rootSignature);
      break;
    }
    }
  }
  VERIFY_IS_TRUE(foundGlobalRS);
}

TEST_F(PixTest, RootSignatureUpgrade_Annotation)
{

  const char *dynamicTextureAccess = R"x(
Texture1D<float4> tex[5] : register(t3);
SamplerState SS[3] : register(s2);

[RootSignature("DescriptorTable(SRV(t3, numDescriptors=5)),\
                DescriptorTable(Sampler(s2, numDescriptors=3))")]
float4 main(int i : A, float j : B) : SV_TARGET
{
  float4 r = tex[i].Sample(SS[i], i);
  return r;
}
  )x";

  auto compiled = Compile(dynamicTextureAccess, L"ps_6_6");
  auto pOptimizedContainer = RunShaderAccessTrackingPass(compiled);

  const char *pBlobContent =
      reinterpret_cast<const char *>(pOptimizedContainer->GetBufferPointer());
  unsigned blobSize = pOptimizedContainer->GetBufferSize();
  const hlsl::DxilContainerHeader *pContainerHeader =
      hlsl::IsDxilContainerLike(pBlobContent, blobSize);

  const hlsl::DxilPartHeader *pPartHeader =
      GetDxilPartByType(pContainerHeader, hlsl::DFCC_RootSignature);
  VERIFY_ARE_NOT_EQUAL(pPartHeader, nullptr);

  hlsl::RootSignatureHandle RSH;
  RSH.LoadSerialized((const uint8_t *)GetDxilPartData(pPartHeader),
                     pPartHeader->PartSize);

  RSH.Deserialize();

  auto const *desc = RSH.GetDesc();
  
  bool foundGlobalRS = false;

  VERIFY_ARE_EQUAL(desc->Version, hlsl::DxilRootSignatureVersion::Version_1_1);
  VERIFY_ARE_EQUAL(desc->Desc_1_1.NumParameters, 3u);
  for (unsigned int i = 0; i < desc->Desc_1_1.NumParameters; ++i) {
    hlsl::DxilRootParameter1 const *param = desc->Desc_1_1.pParameters + i;
    switch (param->ParameterType) {
    case hlsl::DxilRootParameterType::UAV:
      VERIFY_ARE_EQUAL(param->Descriptor.RegisterSpace, static_cast<uint32_t>(-2));
      VERIFY_ARE_EQUAL(param->Descriptor.ShaderRegister, 0u);
      foundGlobalRS = true;
      break;
    }
  }

  VERIFY_IS_TRUE(foundGlobalRS);
}

TEST_F(PixTest, SymbolManager_Embedded2DArray) {
  const char *code = R"x(
struct EmbeddedStruct
{
    uint32_t TwoDArray[2][2];
};

struct smallPayload
{
    uint32_t OneInt;
    EmbeddedStruct embeddedStruct;
    uint64_t bigOne;
};

[numthreads(1, 1, 1)]
void ASMain()
{
    smallPayload p;
    p.OneInt = -137;
    p.embeddedStruct.TwoDArray[0][0] = 252;
    p.embeddedStruct.TwoDArray[0][1] = 253;
    p.embeddedStruct.TwoDArray[1][0] = 254;
    p.embeddedStruct.TwoDArray[1][1] = 255;
    p.bigOne = 123456789;

    DispatchMesh(2, 1, 1, p);
}

)x";

  auto compiled = Compile(code, L"as_6_5", {}, L"ASMain");

  auto debugPart = GetDebugPart(m_dllSupport, WrapInNewContainer(RunAnnotationPasses(compiled).blob));

  CComPtr<IDxcLibrary> library;
  VERIFY_SUCCEEDED(m_dllSupport.CreateInstance(CLSID_DxcLibrary, &library));

  CComPtr<IStream> programStream;
  VERIFY_SUCCEEDED(
      library->CreateStreamFromBlobReadOnly(debugPart, &programStream));

  CComPtr<IDiaDataSource> diaDataSource;
  VERIFY_SUCCEEDED(
      m_dllSupport.CreateInstance(CLSID_DxcDiaDataSource, &diaDataSource));

  VERIFY_SUCCEEDED(diaDataSource->loadDataFromIStream(programStream));

  CComPtr<IDiaSession> session;
  VERIFY_SUCCEEDED(diaDataSource->openSession(&session));

  CComPtr<IDxcPixDxilDebugInfoFactory> Factory;
  VERIFY_SUCCEEDED(session->QueryInterface(&Factory));
  CComPtr<IDxcPixDxilDebugInfo> dxilDebugger;
  VERIFY_SUCCEEDED(Factory->NewDxcPixDxilDebugInfo(&dxilDebugger));

  auto lines = SplitAndPreserveEmptyLines(code, '\n');
  auto DispatchMeshLineFind =
      std::find_if(lines.begin(), lines.end(), [](std::string const &line) {
        return line.find("DispatchMesh") != std::string::npos;
      });
  auto DispatchMeshLine =
      static_cast<DWORD>(DispatchMeshLineFind - lines.begin()) + 2;

  CComPtr<IDxcPixDxilInstructionOffsets> instructionOffsets;
  VERIFY_SUCCEEDED(dxilDebugger->InstructionOffsetsFromSourceLocation(
      L"source.hlsl", DispatchMeshLine, 0, &instructionOffsets));
  VERIFY_IS_TRUE(instructionOffsets->GetCount() > 0);
  DWORD InstructionOrdinal = instructionOffsets->GetOffsetByIndex(0);
  CComPtr<IDxcPixDxilLiveVariables> liveVariables;
  VERIFY_SUCCEEDED(dxilDebugger->GetLiveVariablesAt(InstructionOrdinal, &liveVariables));
  CComPtr<IDxcPixVariable> variable;
  VERIFY_SUCCEEDED(liveVariables->GetVariableByIndex(0, &variable));
  CComBSTR name;
  variable->GetName(&name);
  VERIFY_ARE_EQUAL_WSTR(name, L"p");
  CComPtr<IDxcPixType> type;
  VERIFY_SUCCEEDED(variable->GetType(&type));
  CComPtr<IDxcPixStructType> structType;
  VERIFY_SUCCEEDED(type->QueryInterface(IID_PPV_ARGS(&structType)));
  auto ValidateStructMember = [&structType](DWORD index, const wchar_t *name,
                                            uint64_t offset) {
    CComPtr<IDxcPixStructField> member;
    VERIFY_SUCCEEDED(structType->GetFieldByIndex(index, &member));
    CComBSTR actualName;
    VERIFY_SUCCEEDED(member->GetName(&actualName));
    VERIFY_ARE_EQUAL_WSTR(actualName, name);
    DWORD actualOffset= 0;
    VERIFY_SUCCEEDED(member->GetOffsetInBits(&actualOffset));
    VERIFY_ARE_EQUAL(actualOffset, offset);
  };

  ValidateStructMember(0, L"OneInt", 0);
  ValidateStructMember(1, L"embeddedStruct", 4*8);
  ValidateStructMember(2, L"bigOne", 24*8);
}

#endif
