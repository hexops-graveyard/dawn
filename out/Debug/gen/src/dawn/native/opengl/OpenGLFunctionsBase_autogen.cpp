
#include "dawn/native/opengl/OpenGLFunctionsBase_autogen.h"

namespace dawn::native::opengl {

template<typename T>
MaybeError OpenGLFunctionsBase::LoadProc(GetProcAddress getProc, T* memberProc, const char* name) {
    *memberProc = reinterpret_cast<T>(getProc(name));
    if (DAWN_UNLIKELY(memberProc == nullptr)) {
        return DAWN_INTERNAL_ERROR(std::string("Couldn't load GL proc: ") + name);
    }
    return {};
}

MaybeError OpenGLFunctionsBase::LoadOpenGLESProcs(GetProcAddress getProc, int majorVersion, int minorVersion) {
    // OpenGL ES 2.0
    if (majorVersion > 2 || (majorVersion == 2 && minorVersion >= 0)) {
        DAWN_TRY(LoadProc(getProc, &ActiveTexture, "glActiveTexture"));
        DAWN_TRY(LoadProc(getProc, &AttachShader, "glAttachShader"));
        DAWN_TRY(LoadProc(getProc, &BindAttribLocation, "glBindAttribLocation"));
        DAWN_TRY(LoadProc(getProc, &BindBuffer, "glBindBuffer"));
        DAWN_TRY(LoadProc(getProc, &BindFramebuffer, "glBindFramebuffer"));
        DAWN_TRY(LoadProc(getProc, &BindRenderbuffer, "glBindRenderbuffer"));
        DAWN_TRY(LoadProc(getProc, &BindTexture, "glBindTexture"));
        DAWN_TRY(LoadProc(getProc, &BlendColor, "glBlendColor"));
        DAWN_TRY(LoadProc(getProc, &BlendEquation, "glBlendEquation"));
        DAWN_TRY(LoadProc(getProc, &BlendEquationSeparate, "glBlendEquationSeparate"));
        DAWN_TRY(LoadProc(getProc, &BlendFunc, "glBlendFunc"));
        DAWN_TRY(LoadProc(getProc, &BlendFuncSeparate, "glBlendFuncSeparate"));
        DAWN_TRY(LoadProc(getProc, &BufferData, "glBufferData"));
        DAWN_TRY(LoadProc(getProc, &BufferSubData, "glBufferSubData"));
        DAWN_TRY(LoadProc(getProc, &CheckFramebufferStatus, "glCheckFramebufferStatus"));
        DAWN_TRY(LoadProc(getProc, &Clear, "glClear"));
        DAWN_TRY(LoadProc(getProc, &ClearColor, "glClearColor"));
        DAWN_TRY(LoadProc(getProc, &ClearDepthf, "glClearDepthf"));
        DAWN_TRY(LoadProc(getProc, &ClearStencil, "glClearStencil"));
        DAWN_TRY(LoadProc(getProc, &ColorMask, "glColorMask"));
        DAWN_TRY(LoadProc(getProc, &CompileShader, "glCompileShader"));
        DAWN_TRY(LoadProc(getProc, &CompressedTexImage2D, "glCompressedTexImage2D"));
        DAWN_TRY(LoadProc(getProc, &CompressedTexSubImage2D, "glCompressedTexSubImage2D"));
        DAWN_TRY(LoadProc(getProc, &CopyTexImage2D, "glCopyTexImage2D"));
        DAWN_TRY(LoadProc(getProc, &CopyTexSubImage2D, "glCopyTexSubImage2D"));
        DAWN_TRY(LoadProc(getProc, &CreateProgram, "glCreateProgram"));
        DAWN_TRY(LoadProc(getProc, &CreateShader, "glCreateShader"));
        DAWN_TRY(LoadProc(getProc, &CullFace, "glCullFace"));
        DAWN_TRY(LoadProc(getProc, &DeleteBuffers, "glDeleteBuffers"));
        DAWN_TRY(LoadProc(getProc, &DeleteFramebuffers, "glDeleteFramebuffers"));
        DAWN_TRY(LoadProc(getProc, &DeleteProgram, "glDeleteProgram"));
        DAWN_TRY(LoadProc(getProc, &DeleteRenderbuffers, "glDeleteRenderbuffers"));
        DAWN_TRY(LoadProc(getProc, &DeleteShader, "glDeleteShader"));
        DAWN_TRY(LoadProc(getProc, &DeleteTextures, "glDeleteTextures"));
        DAWN_TRY(LoadProc(getProc, &DepthFunc, "glDepthFunc"));
        DAWN_TRY(LoadProc(getProc, &DepthMask, "glDepthMask"));
        DAWN_TRY(LoadProc(getProc, &DepthRangef, "glDepthRangef"));
        DAWN_TRY(LoadProc(getProc, &DetachShader, "glDetachShader"));
        DAWN_TRY(LoadProc(getProc, &Disable, "glDisable"));
        DAWN_TRY(LoadProc(getProc, &DisableVertexAttribArray, "glDisableVertexAttribArray"));
        DAWN_TRY(LoadProc(getProc, &DrawArrays, "glDrawArrays"));
        DAWN_TRY(LoadProc(getProc, &DrawElements, "glDrawElements"));
        DAWN_TRY(LoadProc(getProc, &Enable, "glEnable"));
        DAWN_TRY(LoadProc(getProc, &EnableVertexAttribArray, "glEnableVertexAttribArray"));
        DAWN_TRY(LoadProc(getProc, &Finish, "glFinish"));
        DAWN_TRY(LoadProc(getProc, &Flush, "glFlush"));
        DAWN_TRY(LoadProc(getProc, &FramebufferRenderbuffer, "glFramebufferRenderbuffer"));
        DAWN_TRY(LoadProc(getProc, &FramebufferTexture2D, "glFramebufferTexture2D"));
        DAWN_TRY(LoadProc(getProc, &FrontFace, "glFrontFace"));
        DAWN_TRY(LoadProc(getProc, &GenBuffers, "glGenBuffers"));
        DAWN_TRY(LoadProc(getProc, &GenerateMipmap, "glGenerateMipmap"));
        DAWN_TRY(LoadProc(getProc, &GenFramebuffers, "glGenFramebuffers"));
        DAWN_TRY(LoadProc(getProc, &GenRenderbuffers, "glGenRenderbuffers"));
        DAWN_TRY(LoadProc(getProc, &GenTextures, "glGenTextures"));
        DAWN_TRY(LoadProc(getProc, &GetActiveAttrib, "glGetActiveAttrib"));
        DAWN_TRY(LoadProc(getProc, &GetActiveUniform, "glGetActiveUniform"));
        DAWN_TRY(LoadProc(getProc, &GetAttachedShaders, "glGetAttachedShaders"));
        DAWN_TRY(LoadProc(getProc, &GetAttribLocation, "glGetAttribLocation"));
        DAWN_TRY(LoadProc(getProc, &GetBooleanv, "glGetBooleanv"));
        DAWN_TRY(LoadProc(getProc, &GetBufferParameteriv, "glGetBufferParameteriv"));
        DAWN_TRY(LoadProc(getProc, &GetError, "glGetError"));
        DAWN_TRY(LoadProc(getProc, &GetFloatv, "glGetFloatv"));
        DAWN_TRY(LoadProc(getProc, &GetFramebufferAttachmentParameteriv, "glGetFramebufferAttachmentParameteriv"));
        DAWN_TRY(LoadProc(getProc, &GetIntegerv, "glGetIntegerv"));
        DAWN_TRY(LoadProc(getProc, &GetProgramiv, "glGetProgramiv"));
        DAWN_TRY(LoadProc(getProc, &GetProgramInfoLog, "glGetProgramInfoLog"));
        DAWN_TRY(LoadProc(getProc, &GetRenderbufferParameteriv, "glGetRenderbufferParameteriv"));
        DAWN_TRY(LoadProc(getProc, &GetShaderiv, "glGetShaderiv"));
        DAWN_TRY(LoadProc(getProc, &GetShaderInfoLog, "glGetShaderInfoLog"));
        DAWN_TRY(LoadProc(getProc, &GetShaderPrecisionFormat, "glGetShaderPrecisionFormat"));
        DAWN_TRY(LoadProc(getProc, &GetShaderSource, "glGetShaderSource"));
        DAWN_TRY(LoadProc(getProc, &GetString, "glGetString"));
        DAWN_TRY(LoadProc(getProc, &GetTexParameterfv, "glGetTexParameterfv"));
        DAWN_TRY(LoadProc(getProc, &GetTexParameteriv, "glGetTexParameteriv"));
        DAWN_TRY(LoadProc(getProc, &GetUniformfv, "glGetUniformfv"));
        DAWN_TRY(LoadProc(getProc, &GetUniformiv, "glGetUniformiv"));
        DAWN_TRY(LoadProc(getProc, &GetUniformLocation, "glGetUniformLocation"));
        DAWN_TRY(LoadProc(getProc, &GetVertexAttribfv, "glGetVertexAttribfv"));
        DAWN_TRY(LoadProc(getProc, &GetVertexAttribiv, "glGetVertexAttribiv"));
        DAWN_TRY(LoadProc(getProc, &GetVertexAttribPointerv, "glGetVertexAttribPointerv"));
        DAWN_TRY(LoadProc(getProc, &Hint, "glHint"));
        DAWN_TRY(LoadProc(getProc, &IsBuffer, "glIsBuffer"));
        DAWN_TRY(LoadProc(getProc, &IsEnabled, "glIsEnabled"));
        DAWN_TRY(LoadProc(getProc, &IsFramebuffer, "glIsFramebuffer"));
        DAWN_TRY(LoadProc(getProc, &IsProgram, "glIsProgram"));
        DAWN_TRY(LoadProc(getProc, &IsRenderbuffer, "glIsRenderbuffer"));
        DAWN_TRY(LoadProc(getProc, &IsShader, "glIsShader"));
        DAWN_TRY(LoadProc(getProc, &IsTexture, "glIsTexture"));
        DAWN_TRY(LoadProc(getProc, &LineWidth, "glLineWidth"));
        DAWN_TRY(LoadProc(getProc, &LinkProgram, "glLinkProgram"));
        DAWN_TRY(LoadProc(getProc, &PixelStorei, "glPixelStorei"));
        DAWN_TRY(LoadProc(getProc, &PolygonOffset, "glPolygonOffset"));
        DAWN_TRY(LoadProc(getProc, &ReadPixels, "glReadPixels"));
        DAWN_TRY(LoadProc(getProc, &ReleaseShaderCompiler, "glReleaseShaderCompiler"));
        DAWN_TRY(LoadProc(getProc, &RenderbufferStorage, "glRenderbufferStorage"));
        DAWN_TRY(LoadProc(getProc, &SampleCoverage, "glSampleCoverage"));
        DAWN_TRY(LoadProc(getProc, &Scissor, "glScissor"));
        DAWN_TRY(LoadProc(getProc, &ShaderBinary, "glShaderBinary"));
        DAWN_TRY(LoadProc(getProc, &ShaderSource, "glShaderSource"));
        DAWN_TRY(LoadProc(getProc, &StencilFunc, "glStencilFunc"));
        DAWN_TRY(LoadProc(getProc, &StencilFuncSeparate, "glStencilFuncSeparate"));
        DAWN_TRY(LoadProc(getProc, &StencilMask, "glStencilMask"));
        DAWN_TRY(LoadProc(getProc, &StencilMaskSeparate, "glStencilMaskSeparate"));
        DAWN_TRY(LoadProc(getProc, &StencilOp, "glStencilOp"));
        DAWN_TRY(LoadProc(getProc, &StencilOpSeparate, "glStencilOpSeparate"));
        DAWN_TRY(LoadProc(getProc, &TexImage2D, "glTexImage2D"));
        DAWN_TRY(LoadProc(getProc, &TexParameterf, "glTexParameterf"));
        DAWN_TRY(LoadProc(getProc, &TexParameterfv, "glTexParameterfv"));
        DAWN_TRY(LoadProc(getProc, &TexParameteri, "glTexParameteri"));
        DAWN_TRY(LoadProc(getProc, &TexParameteriv, "glTexParameteriv"));
        DAWN_TRY(LoadProc(getProc, &TexSubImage2D, "glTexSubImage2D"));
        DAWN_TRY(LoadProc(getProc, &Uniform1f, "glUniform1f"));
        DAWN_TRY(LoadProc(getProc, &Uniform1fv, "glUniform1fv"));
        DAWN_TRY(LoadProc(getProc, &Uniform1i, "glUniform1i"));
        DAWN_TRY(LoadProc(getProc, &Uniform1iv, "glUniform1iv"));
        DAWN_TRY(LoadProc(getProc, &Uniform2f, "glUniform2f"));
        DAWN_TRY(LoadProc(getProc, &Uniform2fv, "glUniform2fv"));
        DAWN_TRY(LoadProc(getProc, &Uniform2i, "glUniform2i"));
        DAWN_TRY(LoadProc(getProc, &Uniform2iv, "glUniform2iv"));
        DAWN_TRY(LoadProc(getProc, &Uniform3f, "glUniform3f"));
        DAWN_TRY(LoadProc(getProc, &Uniform3fv, "glUniform3fv"));
        DAWN_TRY(LoadProc(getProc, &Uniform3i, "glUniform3i"));
        DAWN_TRY(LoadProc(getProc, &Uniform3iv, "glUniform3iv"));
        DAWN_TRY(LoadProc(getProc, &Uniform4f, "glUniform4f"));
        DAWN_TRY(LoadProc(getProc, &Uniform4fv, "glUniform4fv"));
        DAWN_TRY(LoadProc(getProc, &Uniform4i, "glUniform4i"));
        DAWN_TRY(LoadProc(getProc, &Uniform4iv, "glUniform4iv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix2fv, "glUniformMatrix2fv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix3fv, "glUniformMatrix3fv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix4fv, "glUniformMatrix4fv"));
        DAWN_TRY(LoadProc(getProc, &UseProgram, "glUseProgram"));
        DAWN_TRY(LoadProc(getProc, &ValidateProgram, "glValidateProgram"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib1f, "glVertexAttrib1f"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib1fv, "glVertexAttrib1fv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib2f, "glVertexAttrib2f"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib2fv, "glVertexAttrib2fv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib3f, "glVertexAttrib3f"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib3fv, "glVertexAttrib3fv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib4f, "glVertexAttrib4f"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib4fv, "glVertexAttrib4fv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribPointer, "glVertexAttribPointer"));
        DAWN_TRY(LoadProc(getProc, &Viewport, "glViewport"));
    }

    // OpenGL ES 3.0
    if (majorVersion > 3 || (majorVersion == 3 && minorVersion >= 0)) {
        DAWN_TRY(LoadProc(getProc, &ReadBuffer, "glReadBuffer"));
        DAWN_TRY(LoadProc(getProc, &DrawRangeElements, "glDrawRangeElements"));
        DAWN_TRY(LoadProc(getProc, &TexImage3D, "glTexImage3D"));
        DAWN_TRY(LoadProc(getProc, &TexSubImage3D, "glTexSubImage3D"));
        DAWN_TRY(LoadProc(getProc, &CopyTexSubImage3D, "glCopyTexSubImage3D"));
        DAWN_TRY(LoadProc(getProc, &CompressedTexImage3D, "glCompressedTexImage3D"));
        DAWN_TRY(LoadProc(getProc, &CompressedTexSubImage3D, "glCompressedTexSubImage3D"));
        DAWN_TRY(LoadProc(getProc, &GenQueries, "glGenQueries"));
        DAWN_TRY(LoadProc(getProc, &DeleteQueries, "glDeleteQueries"));
        DAWN_TRY(LoadProc(getProc, &IsQuery, "glIsQuery"));
        DAWN_TRY(LoadProc(getProc, &BeginQuery, "glBeginQuery"));
        DAWN_TRY(LoadProc(getProc, &EndQuery, "glEndQuery"));
        DAWN_TRY(LoadProc(getProc, &GetQueryiv, "glGetQueryiv"));
        DAWN_TRY(LoadProc(getProc, &GetQueryObjectuiv, "glGetQueryObjectuiv"));
        DAWN_TRY(LoadProc(getProc, &UnmapBuffer, "glUnmapBuffer"));
        DAWN_TRY(LoadProc(getProc, &GetBufferPointerv, "glGetBufferPointerv"));
        DAWN_TRY(LoadProc(getProc, &DrawBuffers, "glDrawBuffers"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix2x3fv, "glUniformMatrix2x3fv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix3x2fv, "glUniformMatrix3x2fv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix2x4fv, "glUniformMatrix2x4fv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix4x2fv, "glUniformMatrix4x2fv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix3x4fv, "glUniformMatrix3x4fv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix4x3fv, "glUniformMatrix4x3fv"));
        DAWN_TRY(LoadProc(getProc, &BlitFramebuffer, "glBlitFramebuffer"));
        DAWN_TRY(LoadProc(getProc, &RenderbufferStorageMultisample, "glRenderbufferStorageMultisample"));
        DAWN_TRY(LoadProc(getProc, &FramebufferTextureLayer, "glFramebufferTextureLayer"));
        DAWN_TRY(LoadProc(getProc, &MapBufferRange, "glMapBufferRange"));
        DAWN_TRY(LoadProc(getProc, &FlushMappedBufferRange, "glFlushMappedBufferRange"));
        DAWN_TRY(LoadProc(getProc, &BindVertexArray, "glBindVertexArray"));
        DAWN_TRY(LoadProc(getProc, &DeleteVertexArrays, "glDeleteVertexArrays"));
        DAWN_TRY(LoadProc(getProc, &GenVertexArrays, "glGenVertexArrays"));
        DAWN_TRY(LoadProc(getProc, &IsVertexArray, "glIsVertexArray"));
        DAWN_TRY(LoadProc(getProc, &GetIntegeri_v, "glGetIntegeri_v"));
        DAWN_TRY(LoadProc(getProc, &BeginTransformFeedback, "glBeginTransformFeedback"));
        DAWN_TRY(LoadProc(getProc, &EndTransformFeedback, "glEndTransformFeedback"));
        DAWN_TRY(LoadProc(getProc, &BindBufferRange, "glBindBufferRange"));
        DAWN_TRY(LoadProc(getProc, &BindBufferBase, "glBindBufferBase"));
        DAWN_TRY(LoadProc(getProc, &TransformFeedbackVaryings, "glTransformFeedbackVaryings"));
        DAWN_TRY(LoadProc(getProc, &GetTransformFeedbackVarying, "glGetTransformFeedbackVarying"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribIPointer, "glVertexAttribIPointer"));
        DAWN_TRY(LoadProc(getProc, &GetVertexAttribIiv, "glGetVertexAttribIiv"));
        DAWN_TRY(LoadProc(getProc, &GetVertexAttribIuiv, "glGetVertexAttribIuiv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI4i, "glVertexAttribI4i"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI4ui, "glVertexAttribI4ui"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI4iv, "glVertexAttribI4iv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI4uiv, "glVertexAttribI4uiv"));
        DAWN_TRY(LoadProc(getProc, &GetUniformuiv, "glGetUniformuiv"));
        DAWN_TRY(LoadProc(getProc, &GetFragDataLocation, "glGetFragDataLocation"));
        DAWN_TRY(LoadProc(getProc, &Uniform1ui, "glUniform1ui"));
        DAWN_TRY(LoadProc(getProc, &Uniform2ui, "glUniform2ui"));
        DAWN_TRY(LoadProc(getProc, &Uniform3ui, "glUniform3ui"));
        DAWN_TRY(LoadProc(getProc, &Uniform4ui, "glUniform4ui"));
        DAWN_TRY(LoadProc(getProc, &Uniform1uiv, "glUniform1uiv"));
        DAWN_TRY(LoadProc(getProc, &Uniform2uiv, "glUniform2uiv"));
        DAWN_TRY(LoadProc(getProc, &Uniform3uiv, "glUniform3uiv"));
        DAWN_TRY(LoadProc(getProc, &Uniform4uiv, "glUniform4uiv"));
        DAWN_TRY(LoadProc(getProc, &ClearBufferiv, "glClearBufferiv"));
        DAWN_TRY(LoadProc(getProc, &ClearBufferuiv, "glClearBufferuiv"));
        DAWN_TRY(LoadProc(getProc, &ClearBufferfv, "glClearBufferfv"));
        DAWN_TRY(LoadProc(getProc, &ClearBufferfi, "glClearBufferfi"));
        DAWN_TRY(LoadProc(getProc, &GetStringi, "glGetStringi"));
        DAWN_TRY(LoadProc(getProc, &CopyBufferSubData, "glCopyBufferSubData"));
        DAWN_TRY(LoadProc(getProc, &GetUniformIndices, "glGetUniformIndices"));
        DAWN_TRY(LoadProc(getProc, &GetActiveUniformsiv, "glGetActiveUniformsiv"));
        DAWN_TRY(LoadProc(getProc, &GetUniformBlockIndex, "glGetUniformBlockIndex"));
        DAWN_TRY(LoadProc(getProc, &GetActiveUniformBlockiv, "glGetActiveUniformBlockiv"));
        DAWN_TRY(LoadProc(getProc, &GetActiveUniformBlockName, "glGetActiveUniformBlockName"));
        DAWN_TRY(LoadProc(getProc, &UniformBlockBinding, "glUniformBlockBinding"));
        DAWN_TRY(LoadProc(getProc, &DrawArraysInstanced, "glDrawArraysInstanced"));
        DAWN_TRY(LoadProc(getProc, &DrawElementsInstanced, "glDrawElementsInstanced"));
        DAWN_TRY(LoadProc(getProc, &FenceSync, "glFenceSync"));
        DAWN_TRY(LoadProc(getProc, &IsSync, "glIsSync"));
        DAWN_TRY(LoadProc(getProc, &DeleteSync, "glDeleteSync"));
        DAWN_TRY(LoadProc(getProc, &ClientWaitSync, "glClientWaitSync"));
        DAWN_TRY(LoadProc(getProc, &WaitSync, "glWaitSync"));
        DAWN_TRY(LoadProc(getProc, &GetInteger64v, "glGetInteger64v"));
        DAWN_TRY(LoadProc(getProc, &GetSynciv, "glGetSynciv"));
        DAWN_TRY(LoadProc(getProc, &GetInteger64i_v, "glGetInteger64i_v"));
        DAWN_TRY(LoadProc(getProc, &GetBufferParameteri64v, "glGetBufferParameteri64v"));
        DAWN_TRY(LoadProc(getProc, &GenSamplers, "glGenSamplers"));
        DAWN_TRY(LoadProc(getProc, &DeleteSamplers, "glDeleteSamplers"));
        DAWN_TRY(LoadProc(getProc, &IsSampler, "glIsSampler"));
        DAWN_TRY(LoadProc(getProc, &BindSampler, "glBindSampler"));
        DAWN_TRY(LoadProc(getProc, &SamplerParameteri, "glSamplerParameteri"));
        DAWN_TRY(LoadProc(getProc, &SamplerParameteriv, "glSamplerParameteriv"));
        DAWN_TRY(LoadProc(getProc, &SamplerParameterf, "glSamplerParameterf"));
        DAWN_TRY(LoadProc(getProc, &SamplerParameterfv, "glSamplerParameterfv"));
        DAWN_TRY(LoadProc(getProc, &GetSamplerParameteriv, "glGetSamplerParameteriv"));
        DAWN_TRY(LoadProc(getProc, &GetSamplerParameterfv, "glGetSamplerParameterfv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribDivisor, "glVertexAttribDivisor"));
        DAWN_TRY(LoadProc(getProc, &BindTransformFeedback, "glBindTransformFeedback"));
        DAWN_TRY(LoadProc(getProc, &DeleteTransformFeedbacks, "glDeleteTransformFeedbacks"));
        DAWN_TRY(LoadProc(getProc, &GenTransformFeedbacks, "glGenTransformFeedbacks"));
        DAWN_TRY(LoadProc(getProc, &IsTransformFeedback, "glIsTransformFeedback"));
        DAWN_TRY(LoadProc(getProc, &PauseTransformFeedback, "glPauseTransformFeedback"));
        DAWN_TRY(LoadProc(getProc, &ResumeTransformFeedback, "glResumeTransformFeedback"));
        DAWN_TRY(LoadProc(getProc, &GetProgramBinary, "glGetProgramBinary"));
        DAWN_TRY(LoadProc(getProc, &ProgramBinary, "glProgramBinary"));
        DAWN_TRY(LoadProc(getProc, &ProgramParameteri, "glProgramParameteri"));
        DAWN_TRY(LoadProc(getProc, &InvalidateFramebuffer, "glInvalidateFramebuffer"));
        DAWN_TRY(LoadProc(getProc, &InvalidateSubFramebuffer, "glInvalidateSubFramebuffer"));
        DAWN_TRY(LoadProc(getProc, &TexStorage2D, "glTexStorage2D"));
        DAWN_TRY(LoadProc(getProc, &TexStorage3D, "glTexStorage3D"));
        DAWN_TRY(LoadProc(getProc, &GetInternalformativ, "glGetInternalformativ"));
    }

    // OpenGL ES 3.1
    if (majorVersion > 3 || (majorVersion == 3 && minorVersion >= 1)) {
        DAWN_TRY(LoadProc(getProc, &DispatchCompute, "glDispatchCompute"));
        DAWN_TRY(LoadProc(getProc, &DispatchComputeIndirect, "glDispatchComputeIndirect"));
        DAWN_TRY(LoadProc(getProc, &DrawArraysIndirect, "glDrawArraysIndirect"));
        DAWN_TRY(LoadProc(getProc, &DrawElementsIndirect, "glDrawElementsIndirect"));
        DAWN_TRY(LoadProc(getProc, &FramebufferParameteri, "glFramebufferParameteri"));
        DAWN_TRY(LoadProc(getProc, &GetFramebufferParameteriv, "glGetFramebufferParameteriv"));
        DAWN_TRY(LoadProc(getProc, &GetProgramInterfaceiv, "glGetProgramInterfaceiv"));
        DAWN_TRY(LoadProc(getProc, &GetProgramResourceIndex, "glGetProgramResourceIndex"));
        DAWN_TRY(LoadProc(getProc, &GetProgramResourceName, "glGetProgramResourceName"));
        DAWN_TRY(LoadProc(getProc, &GetProgramResourceiv, "glGetProgramResourceiv"));
        DAWN_TRY(LoadProc(getProc, &GetProgramResourceLocation, "glGetProgramResourceLocation"));
        DAWN_TRY(LoadProc(getProc, &UseProgramStages, "glUseProgramStages"));
        DAWN_TRY(LoadProc(getProc, &ActiveShaderProgram, "glActiveShaderProgram"));
        DAWN_TRY(LoadProc(getProc, &CreateShaderProgramv, "glCreateShaderProgramv"));
        DAWN_TRY(LoadProc(getProc, &BindProgramPipeline, "glBindProgramPipeline"));
        DAWN_TRY(LoadProc(getProc, &DeleteProgramPipelines, "glDeleteProgramPipelines"));
        DAWN_TRY(LoadProc(getProc, &GenProgramPipelines, "glGenProgramPipelines"));
        DAWN_TRY(LoadProc(getProc, &IsProgramPipeline, "glIsProgramPipeline"));
        DAWN_TRY(LoadProc(getProc, &GetProgramPipelineiv, "glGetProgramPipelineiv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform1i, "glProgramUniform1i"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform2i, "glProgramUniform2i"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform3i, "glProgramUniform3i"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform4i, "glProgramUniform4i"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform1ui, "glProgramUniform1ui"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform2ui, "glProgramUniform2ui"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform3ui, "glProgramUniform3ui"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform4ui, "glProgramUniform4ui"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform1f, "glProgramUniform1f"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform2f, "glProgramUniform2f"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform3f, "glProgramUniform3f"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform4f, "glProgramUniform4f"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform1iv, "glProgramUniform1iv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform2iv, "glProgramUniform2iv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform3iv, "glProgramUniform3iv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform4iv, "glProgramUniform4iv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform1uiv, "glProgramUniform1uiv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform2uiv, "glProgramUniform2uiv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform3uiv, "glProgramUniform3uiv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform4uiv, "glProgramUniform4uiv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform1fv, "glProgramUniform1fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform2fv, "glProgramUniform2fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform3fv, "glProgramUniform3fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform4fv, "glProgramUniform4fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix2fv, "glProgramUniformMatrix2fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix3fv, "glProgramUniformMatrix3fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix4fv, "glProgramUniformMatrix4fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix2x3fv, "glProgramUniformMatrix2x3fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix3x2fv, "glProgramUniformMatrix3x2fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix2x4fv, "glProgramUniformMatrix2x4fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix4x2fv, "glProgramUniformMatrix4x2fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix3x4fv, "glProgramUniformMatrix3x4fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix4x3fv, "glProgramUniformMatrix4x3fv"));
        DAWN_TRY(LoadProc(getProc, &ValidateProgramPipeline, "glValidateProgramPipeline"));
        DAWN_TRY(LoadProc(getProc, &GetProgramPipelineInfoLog, "glGetProgramPipelineInfoLog"));
        DAWN_TRY(LoadProc(getProc, &BindImageTexture, "glBindImageTexture"));
        DAWN_TRY(LoadProc(getProc, &GetBooleani_v, "glGetBooleani_v"));
        DAWN_TRY(LoadProc(getProc, &MemoryBarrier, "glMemoryBarrier"));
        DAWN_TRY(LoadProc(getProc, &MemoryBarrierByRegion, "glMemoryBarrierByRegion"));
        DAWN_TRY(LoadProc(getProc, &TexStorage2DMultisample, "glTexStorage2DMultisample"));
        DAWN_TRY(LoadProc(getProc, &GetMultisamplefv, "glGetMultisamplefv"));
        DAWN_TRY(LoadProc(getProc, &SampleMaski, "glSampleMaski"));
        DAWN_TRY(LoadProc(getProc, &GetTexLevelParameteriv, "glGetTexLevelParameteriv"));
        DAWN_TRY(LoadProc(getProc, &GetTexLevelParameterfv, "glGetTexLevelParameterfv"));
        DAWN_TRY(LoadProc(getProc, &BindVertexBuffer, "glBindVertexBuffer"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribFormat, "glVertexAttribFormat"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribIFormat, "glVertexAttribIFormat"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribBinding, "glVertexAttribBinding"));
        DAWN_TRY(LoadProc(getProc, &VertexBindingDivisor, "glVertexBindingDivisor"));
    }

    // OpenGL ES 3.2
    if (majorVersion > 3 || (majorVersion == 3 && minorVersion >= 2)) {
        DAWN_TRY(LoadProc(getProc, &BlendBarrier, "glBlendBarrier"));
        DAWN_TRY(LoadProc(getProc, &CopyImageSubData, "glCopyImageSubData"));
        DAWN_TRY(LoadProc(getProc, &DebugMessageControl, "glDebugMessageControl"));
        DAWN_TRY(LoadProc(getProc, &DebugMessageInsert, "glDebugMessageInsert"));
        DAWN_TRY(LoadProc(getProc, &DebugMessageCallback, "glDebugMessageCallback"));
        DAWN_TRY(LoadProc(getProc, &GetDebugMessageLog, "glGetDebugMessageLog"));
        DAWN_TRY(LoadProc(getProc, &PushDebugGroup, "glPushDebugGroup"));
        DAWN_TRY(LoadProc(getProc, &PopDebugGroup, "glPopDebugGroup"));
        DAWN_TRY(LoadProc(getProc, &ObjectLabel, "glObjectLabel"));
        DAWN_TRY(LoadProc(getProc, &GetObjectLabel, "glGetObjectLabel"));
        DAWN_TRY(LoadProc(getProc, &ObjectPtrLabel, "glObjectPtrLabel"));
        DAWN_TRY(LoadProc(getProc, &GetObjectPtrLabel, "glGetObjectPtrLabel"));
        DAWN_TRY(LoadProc(getProc, &GetPointerv, "glGetPointerv"));
        DAWN_TRY(LoadProc(getProc, &Enablei, "glEnablei"));
        DAWN_TRY(LoadProc(getProc, &Disablei, "glDisablei"));
        DAWN_TRY(LoadProc(getProc, &BlendEquationi, "glBlendEquationi"));
        DAWN_TRY(LoadProc(getProc, &BlendEquationSeparatei, "glBlendEquationSeparatei"));
        DAWN_TRY(LoadProc(getProc, &BlendFunci, "glBlendFunci"));
        DAWN_TRY(LoadProc(getProc, &BlendFuncSeparatei, "glBlendFuncSeparatei"));
        DAWN_TRY(LoadProc(getProc, &ColorMaski, "glColorMaski"));
        DAWN_TRY(LoadProc(getProc, &IsEnabledi, "glIsEnabledi"));
        DAWN_TRY(LoadProc(getProc, &DrawElementsBaseVertex, "glDrawElementsBaseVertex"));
        DAWN_TRY(LoadProc(getProc, &DrawRangeElementsBaseVertex, "glDrawRangeElementsBaseVertex"));
        DAWN_TRY(LoadProc(getProc, &DrawElementsInstancedBaseVertex, "glDrawElementsInstancedBaseVertex"));
        DAWN_TRY(LoadProc(getProc, &FramebufferTexture, "glFramebufferTexture"));
        DAWN_TRY(LoadProc(getProc, &PrimitiveBoundingBox, "glPrimitiveBoundingBox"));
        DAWN_TRY(LoadProc(getProc, &GetGraphicsResetStatus, "glGetGraphicsResetStatus"));
        DAWN_TRY(LoadProc(getProc, &ReadnPixels, "glReadnPixels"));
        DAWN_TRY(LoadProc(getProc, &GetnUniformfv, "glGetnUniformfv"));
        DAWN_TRY(LoadProc(getProc, &GetnUniformiv, "glGetnUniformiv"));
        DAWN_TRY(LoadProc(getProc, &GetnUniformuiv, "glGetnUniformuiv"));
        DAWN_TRY(LoadProc(getProc, &MinSampleShading, "glMinSampleShading"));
        DAWN_TRY(LoadProc(getProc, &PatchParameteri, "glPatchParameteri"));
        DAWN_TRY(LoadProc(getProc, &TexParameterIiv, "glTexParameterIiv"));
        DAWN_TRY(LoadProc(getProc, &TexParameterIuiv, "glTexParameterIuiv"));
        DAWN_TRY(LoadProc(getProc, &GetTexParameterIiv, "glGetTexParameterIiv"));
        DAWN_TRY(LoadProc(getProc, &GetTexParameterIuiv, "glGetTexParameterIuiv"));
        DAWN_TRY(LoadProc(getProc, &SamplerParameterIiv, "glSamplerParameterIiv"));
        DAWN_TRY(LoadProc(getProc, &SamplerParameterIuiv, "glSamplerParameterIuiv"));
        DAWN_TRY(LoadProc(getProc, &GetSamplerParameterIiv, "glGetSamplerParameterIiv"));
        DAWN_TRY(LoadProc(getProc, &GetSamplerParameterIuiv, "glGetSamplerParameterIuiv"));
        DAWN_TRY(LoadProc(getProc, &TexBuffer, "glTexBuffer"));
        DAWN_TRY(LoadProc(getProc, &TexBufferRange, "glTexBufferRange"));
        DAWN_TRY(LoadProc(getProc, &TexStorage3DMultisample, "glTexStorage3DMultisample"));
    }


    InitializeSupportedGLExtensions();

    // GL_EXT_texture_compression_s3tc
    if (IsGLExtensionSupported("GL_EXT_texture_compression_s3tc")) {
    }
    // GL_EXT_texture_compression_s3tc_srgb
    if (IsGLExtensionSupported("GL_EXT_texture_compression_s3tc_srgb")) {
    }
    // GL_OES_EGL_image
    if (IsGLExtensionSupported("GL_OES_EGL_image")) {
        DAWN_TRY(LoadProc(getProc, &EGLImageTargetTexture2DOES, "glEGLImageTargetTexture2DOES"));
        DAWN_TRY(LoadProc(getProc, &EGLImageTargetRenderbufferStorageOES, "glEGLImageTargetRenderbufferStorageOES"));
    }
    // GL_EXT_texture_format_BGRA8888
    if (IsGLExtensionSupported("GL_EXT_texture_format_BGRA8888")) {
    }
    // GL_APPLE_texture_format_BGRA8888
    if (IsGLExtensionSupported("GL_APPLE_texture_format_BGRA8888")) {
    }

    // GL_ANGLE_base_vertex_base_instance
    // See crbug.com/dawn/1715 for why this is embedded
    if (IsGLExtensionSupported("GL_ANGLE_base_vertex_base_instance")) {
        DAWN_TRY(LoadProc(getProc, &DrawArraysInstancedBaseInstanceANGLE, "glDrawArraysInstancedBaseInstanceANGLE"));
        DAWN_TRY(LoadProc(getProc, &DrawElementsInstancedBaseVertexBaseInstanceANGLE, "glDrawElementsInstancedBaseVertexBaseInstanceANGLE"));
        DAWN_TRY(LoadProc(getProc, &MultiDrawArraysInstancedBaseInstanceANGLE, "glMultiDrawArraysInstancedBaseInstanceANGLE"));
        DAWN_TRY(LoadProc(getProc, &MultiDrawElementsInstancedBaseVertexBaseInstanceANGLE, "glMultiDrawElementsInstancedBaseVertexBaseInstanceANGLE"));
    }

    return {};
}

MaybeError OpenGLFunctionsBase::LoadDesktopGLProcs(GetProcAddress getProc, int majorVersion, int minorVersion) {
    // Desktop OpenGL 1.0
    if (majorVersion > 1 || (majorVersion == 1 && minorVersion >= 0)) {
        DAWN_TRY(LoadProc(getProc, &CullFace, "glCullFace"));
        DAWN_TRY(LoadProc(getProc, &FrontFace, "glFrontFace"));
        DAWN_TRY(LoadProc(getProc, &Hint, "glHint"));
        DAWN_TRY(LoadProc(getProc, &LineWidth, "glLineWidth"));
        DAWN_TRY(LoadProc(getProc, &PointSize, "glPointSize"));
        DAWN_TRY(LoadProc(getProc, &PolygonMode, "glPolygonMode"));
        DAWN_TRY(LoadProc(getProc, &Scissor, "glScissor"));
        DAWN_TRY(LoadProc(getProc, &TexParameterf, "glTexParameterf"));
        DAWN_TRY(LoadProc(getProc, &TexParameterfv, "glTexParameterfv"));
        DAWN_TRY(LoadProc(getProc, &TexParameteri, "glTexParameteri"));
        DAWN_TRY(LoadProc(getProc, &TexParameteriv, "glTexParameteriv"));
        DAWN_TRY(LoadProc(getProc, &TexImage1D, "glTexImage1D"));
        DAWN_TRY(LoadProc(getProc, &TexImage2D, "glTexImage2D"));
        DAWN_TRY(LoadProc(getProc, &DrawBuffer, "glDrawBuffer"));
        DAWN_TRY(LoadProc(getProc, &Clear, "glClear"));
        DAWN_TRY(LoadProc(getProc, &ClearColor, "glClearColor"));
        DAWN_TRY(LoadProc(getProc, &ClearStencil, "glClearStencil"));
        DAWN_TRY(LoadProc(getProc, &ClearDepth, "glClearDepth"));
        DAWN_TRY(LoadProc(getProc, &StencilMask, "glStencilMask"));
        DAWN_TRY(LoadProc(getProc, &ColorMask, "glColorMask"));
        DAWN_TRY(LoadProc(getProc, &DepthMask, "glDepthMask"));
        DAWN_TRY(LoadProc(getProc, &Disable, "glDisable"));
        DAWN_TRY(LoadProc(getProc, &Enable, "glEnable"));
        DAWN_TRY(LoadProc(getProc, &Finish, "glFinish"));
        DAWN_TRY(LoadProc(getProc, &Flush, "glFlush"));
        DAWN_TRY(LoadProc(getProc, &BlendFunc, "glBlendFunc"));
        DAWN_TRY(LoadProc(getProc, &LogicOp, "glLogicOp"));
        DAWN_TRY(LoadProc(getProc, &StencilFunc, "glStencilFunc"));
        DAWN_TRY(LoadProc(getProc, &StencilOp, "glStencilOp"));
        DAWN_TRY(LoadProc(getProc, &DepthFunc, "glDepthFunc"));
        DAWN_TRY(LoadProc(getProc, &PixelStoref, "glPixelStoref"));
        DAWN_TRY(LoadProc(getProc, &PixelStorei, "glPixelStorei"));
        DAWN_TRY(LoadProc(getProc, &ReadBuffer, "glReadBuffer"));
        DAWN_TRY(LoadProc(getProc, &ReadPixels, "glReadPixels"));
        DAWN_TRY(LoadProc(getProc, &GetBooleanv, "glGetBooleanv"));
        DAWN_TRY(LoadProc(getProc, &GetDoublev, "glGetDoublev"));
        DAWN_TRY(LoadProc(getProc, &GetError, "glGetError"));
        DAWN_TRY(LoadProc(getProc, &GetFloatv, "glGetFloatv"));
        DAWN_TRY(LoadProc(getProc, &GetIntegerv, "glGetIntegerv"));
        DAWN_TRY(LoadProc(getProc, &GetString, "glGetString"));
        DAWN_TRY(LoadProc(getProc, &GetTexImage, "glGetTexImage"));
        DAWN_TRY(LoadProc(getProc, &GetTexParameterfv, "glGetTexParameterfv"));
        DAWN_TRY(LoadProc(getProc, &GetTexParameteriv, "glGetTexParameteriv"));
        DAWN_TRY(LoadProc(getProc, &GetTexLevelParameterfv, "glGetTexLevelParameterfv"));
        DAWN_TRY(LoadProc(getProc, &GetTexLevelParameteriv, "glGetTexLevelParameteriv"));
        DAWN_TRY(LoadProc(getProc, &IsEnabled, "glIsEnabled"));
        DAWN_TRY(LoadProc(getProc, &DepthRange, "glDepthRange"));
        DAWN_TRY(LoadProc(getProc, &Viewport, "glViewport"));
    }

    // Desktop OpenGL 1.1
    if (majorVersion > 1 || (majorVersion == 1 && minorVersion >= 1)) {
        DAWN_TRY(LoadProc(getProc, &DrawArrays, "glDrawArrays"));
        DAWN_TRY(LoadProc(getProc, &DrawElements, "glDrawElements"));
        DAWN_TRY(LoadProc(getProc, &PolygonOffset, "glPolygonOffset"));
        DAWN_TRY(LoadProc(getProc, &CopyTexImage1D, "glCopyTexImage1D"));
        DAWN_TRY(LoadProc(getProc, &CopyTexImage2D, "glCopyTexImage2D"));
        DAWN_TRY(LoadProc(getProc, &CopyTexSubImage1D, "glCopyTexSubImage1D"));
        DAWN_TRY(LoadProc(getProc, &CopyTexSubImage2D, "glCopyTexSubImage2D"));
        DAWN_TRY(LoadProc(getProc, &TexSubImage1D, "glTexSubImage1D"));
        DAWN_TRY(LoadProc(getProc, &TexSubImage2D, "glTexSubImage2D"));
        DAWN_TRY(LoadProc(getProc, &BindTexture, "glBindTexture"));
        DAWN_TRY(LoadProc(getProc, &DeleteTextures, "glDeleteTextures"));
        DAWN_TRY(LoadProc(getProc, &GenTextures, "glGenTextures"));
        DAWN_TRY(LoadProc(getProc, &IsTexture, "glIsTexture"));
    }

    // Desktop OpenGL 1.2
    if (majorVersion > 1 || (majorVersion == 1 && minorVersion >= 2)) {
        DAWN_TRY(LoadProc(getProc, &DrawRangeElements, "glDrawRangeElements"));
        DAWN_TRY(LoadProc(getProc, &TexImage3D, "glTexImage3D"));
        DAWN_TRY(LoadProc(getProc, &TexSubImage3D, "glTexSubImage3D"));
        DAWN_TRY(LoadProc(getProc, &CopyTexSubImage3D, "glCopyTexSubImage3D"));
    }

    // Desktop OpenGL 1.3
    if (majorVersion > 1 || (majorVersion == 1 && minorVersion >= 3)) {
        DAWN_TRY(LoadProc(getProc, &ActiveTexture, "glActiveTexture"));
        DAWN_TRY(LoadProc(getProc, &SampleCoverage, "glSampleCoverage"));
        DAWN_TRY(LoadProc(getProc, &CompressedTexImage3D, "glCompressedTexImage3D"));
        DAWN_TRY(LoadProc(getProc, &CompressedTexImage2D, "glCompressedTexImage2D"));
        DAWN_TRY(LoadProc(getProc, &CompressedTexImage1D, "glCompressedTexImage1D"));
        DAWN_TRY(LoadProc(getProc, &CompressedTexSubImage3D, "glCompressedTexSubImage3D"));
        DAWN_TRY(LoadProc(getProc, &CompressedTexSubImage2D, "glCompressedTexSubImage2D"));
        DAWN_TRY(LoadProc(getProc, &CompressedTexSubImage1D, "glCompressedTexSubImage1D"));
        DAWN_TRY(LoadProc(getProc, &GetCompressedTexImage, "glGetCompressedTexImage"));
    }

    // Desktop OpenGL 1.4
    if (majorVersion > 1 || (majorVersion == 1 && minorVersion >= 4)) {
        DAWN_TRY(LoadProc(getProc, &BlendFuncSeparate, "glBlendFuncSeparate"));
        DAWN_TRY(LoadProc(getProc, &MultiDrawArrays, "glMultiDrawArrays"));
        DAWN_TRY(LoadProc(getProc, &MultiDrawElements, "glMultiDrawElements"));
        DAWN_TRY(LoadProc(getProc, &PointParameterf, "glPointParameterf"));
        DAWN_TRY(LoadProc(getProc, &PointParameterfv, "glPointParameterfv"));
        DAWN_TRY(LoadProc(getProc, &PointParameteri, "glPointParameteri"));
        DAWN_TRY(LoadProc(getProc, &PointParameteriv, "glPointParameteriv"));
        DAWN_TRY(LoadProc(getProc, &BlendColor, "glBlendColor"));
        DAWN_TRY(LoadProc(getProc, &BlendEquation, "glBlendEquation"));
    }

    // Desktop OpenGL 1.5
    if (majorVersion > 1 || (majorVersion == 1 && minorVersion >= 5)) {
        DAWN_TRY(LoadProc(getProc, &GenQueries, "glGenQueries"));
        DAWN_TRY(LoadProc(getProc, &DeleteQueries, "glDeleteQueries"));
        DAWN_TRY(LoadProc(getProc, &IsQuery, "glIsQuery"));
        DAWN_TRY(LoadProc(getProc, &BeginQuery, "glBeginQuery"));
        DAWN_TRY(LoadProc(getProc, &EndQuery, "glEndQuery"));
        DAWN_TRY(LoadProc(getProc, &GetQueryiv, "glGetQueryiv"));
        DAWN_TRY(LoadProc(getProc, &GetQueryObjectiv, "glGetQueryObjectiv"));
        DAWN_TRY(LoadProc(getProc, &GetQueryObjectuiv, "glGetQueryObjectuiv"));
        DAWN_TRY(LoadProc(getProc, &BindBuffer, "glBindBuffer"));
        DAWN_TRY(LoadProc(getProc, &DeleteBuffers, "glDeleteBuffers"));
        DAWN_TRY(LoadProc(getProc, &GenBuffers, "glGenBuffers"));
        DAWN_TRY(LoadProc(getProc, &IsBuffer, "glIsBuffer"));
        DAWN_TRY(LoadProc(getProc, &BufferData, "glBufferData"));
        DAWN_TRY(LoadProc(getProc, &BufferSubData, "glBufferSubData"));
        DAWN_TRY(LoadProc(getProc, &GetBufferSubData, "glGetBufferSubData"));
        DAWN_TRY(LoadProc(getProc, &MapBuffer, "glMapBuffer"));
        DAWN_TRY(LoadProc(getProc, &UnmapBuffer, "glUnmapBuffer"));
        DAWN_TRY(LoadProc(getProc, &GetBufferParameteriv, "glGetBufferParameteriv"));
        DAWN_TRY(LoadProc(getProc, &GetBufferPointerv, "glGetBufferPointerv"));
    }

    // Desktop OpenGL 2.0
    if (majorVersion > 2 || (majorVersion == 2 && minorVersion >= 0)) {
        DAWN_TRY(LoadProc(getProc, &BlendEquationSeparate, "glBlendEquationSeparate"));
        DAWN_TRY(LoadProc(getProc, &DrawBuffers, "glDrawBuffers"));
        DAWN_TRY(LoadProc(getProc, &StencilOpSeparate, "glStencilOpSeparate"));
        DAWN_TRY(LoadProc(getProc, &StencilFuncSeparate, "glStencilFuncSeparate"));
        DAWN_TRY(LoadProc(getProc, &StencilMaskSeparate, "glStencilMaskSeparate"));
        DAWN_TRY(LoadProc(getProc, &AttachShader, "glAttachShader"));
        DAWN_TRY(LoadProc(getProc, &BindAttribLocation, "glBindAttribLocation"));
        DAWN_TRY(LoadProc(getProc, &CompileShader, "glCompileShader"));
        DAWN_TRY(LoadProc(getProc, &CreateProgram, "glCreateProgram"));
        DAWN_TRY(LoadProc(getProc, &CreateShader, "glCreateShader"));
        DAWN_TRY(LoadProc(getProc, &DeleteProgram, "glDeleteProgram"));
        DAWN_TRY(LoadProc(getProc, &DeleteShader, "glDeleteShader"));
        DAWN_TRY(LoadProc(getProc, &DetachShader, "glDetachShader"));
        DAWN_TRY(LoadProc(getProc, &DisableVertexAttribArray, "glDisableVertexAttribArray"));
        DAWN_TRY(LoadProc(getProc, &EnableVertexAttribArray, "glEnableVertexAttribArray"));
        DAWN_TRY(LoadProc(getProc, &GetActiveAttrib, "glGetActiveAttrib"));
        DAWN_TRY(LoadProc(getProc, &GetActiveUniform, "glGetActiveUniform"));
        DAWN_TRY(LoadProc(getProc, &GetAttachedShaders, "glGetAttachedShaders"));
        DAWN_TRY(LoadProc(getProc, &GetAttribLocation, "glGetAttribLocation"));
        DAWN_TRY(LoadProc(getProc, &GetProgramiv, "glGetProgramiv"));
        DAWN_TRY(LoadProc(getProc, &GetProgramInfoLog, "glGetProgramInfoLog"));
        DAWN_TRY(LoadProc(getProc, &GetShaderiv, "glGetShaderiv"));
        DAWN_TRY(LoadProc(getProc, &GetShaderInfoLog, "glGetShaderInfoLog"));
        DAWN_TRY(LoadProc(getProc, &GetShaderSource, "glGetShaderSource"));
        DAWN_TRY(LoadProc(getProc, &GetUniformLocation, "glGetUniformLocation"));
        DAWN_TRY(LoadProc(getProc, &GetUniformfv, "glGetUniformfv"));
        DAWN_TRY(LoadProc(getProc, &GetUniformiv, "glGetUniformiv"));
        DAWN_TRY(LoadProc(getProc, &GetVertexAttribdv, "glGetVertexAttribdv"));
        DAWN_TRY(LoadProc(getProc, &GetVertexAttribfv, "glGetVertexAttribfv"));
        DAWN_TRY(LoadProc(getProc, &GetVertexAttribiv, "glGetVertexAttribiv"));
        DAWN_TRY(LoadProc(getProc, &GetVertexAttribPointerv, "glGetVertexAttribPointerv"));
        DAWN_TRY(LoadProc(getProc, &IsProgram, "glIsProgram"));
        DAWN_TRY(LoadProc(getProc, &IsShader, "glIsShader"));
        DAWN_TRY(LoadProc(getProc, &LinkProgram, "glLinkProgram"));
        DAWN_TRY(LoadProc(getProc, &ShaderSource, "glShaderSource"));
        DAWN_TRY(LoadProc(getProc, &UseProgram, "glUseProgram"));
        DAWN_TRY(LoadProc(getProc, &Uniform1f, "glUniform1f"));
        DAWN_TRY(LoadProc(getProc, &Uniform2f, "glUniform2f"));
        DAWN_TRY(LoadProc(getProc, &Uniform3f, "glUniform3f"));
        DAWN_TRY(LoadProc(getProc, &Uniform4f, "glUniform4f"));
        DAWN_TRY(LoadProc(getProc, &Uniform1i, "glUniform1i"));
        DAWN_TRY(LoadProc(getProc, &Uniform2i, "glUniform2i"));
        DAWN_TRY(LoadProc(getProc, &Uniform3i, "glUniform3i"));
        DAWN_TRY(LoadProc(getProc, &Uniform4i, "glUniform4i"));
        DAWN_TRY(LoadProc(getProc, &Uniform1fv, "glUniform1fv"));
        DAWN_TRY(LoadProc(getProc, &Uniform2fv, "glUniform2fv"));
        DAWN_TRY(LoadProc(getProc, &Uniform3fv, "glUniform3fv"));
        DAWN_TRY(LoadProc(getProc, &Uniform4fv, "glUniform4fv"));
        DAWN_TRY(LoadProc(getProc, &Uniform1iv, "glUniform1iv"));
        DAWN_TRY(LoadProc(getProc, &Uniform2iv, "glUniform2iv"));
        DAWN_TRY(LoadProc(getProc, &Uniform3iv, "glUniform3iv"));
        DAWN_TRY(LoadProc(getProc, &Uniform4iv, "glUniform4iv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix2fv, "glUniformMatrix2fv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix3fv, "glUniformMatrix3fv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix4fv, "glUniformMatrix4fv"));
        DAWN_TRY(LoadProc(getProc, &ValidateProgram, "glValidateProgram"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib1d, "glVertexAttrib1d"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib1dv, "glVertexAttrib1dv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib1f, "glVertexAttrib1f"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib1fv, "glVertexAttrib1fv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib1s, "glVertexAttrib1s"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib1sv, "glVertexAttrib1sv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib2d, "glVertexAttrib2d"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib2dv, "glVertexAttrib2dv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib2f, "glVertexAttrib2f"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib2fv, "glVertexAttrib2fv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib2s, "glVertexAttrib2s"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib2sv, "glVertexAttrib2sv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib3d, "glVertexAttrib3d"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib3dv, "glVertexAttrib3dv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib3f, "glVertexAttrib3f"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib3fv, "glVertexAttrib3fv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib3s, "glVertexAttrib3s"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib3sv, "glVertexAttrib3sv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib4Nbv, "glVertexAttrib4Nbv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib4Niv, "glVertexAttrib4Niv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib4Nsv, "glVertexAttrib4Nsv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib4Nub, "glVertexAttrib4Nub"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib4Nubv, "glVertexAttrib4Nubv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib4Nuiv, "glVertexAttrib4Nuiv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib4Nusv, "glVertexAttrib4Nusv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib4bv, "glVertexAttrib4bv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib4d, "glVertexAttrib4d"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib4dv, "glVertexAttrib4dv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib4f, "glVertexAttrib4f"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib4fv, "glVertexAttrib4fv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib4iv, "glVertexAttrib4iv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib4s, "glVertexAttrib4s"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib4sv, "glVertexAttrib4sv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib4ubv, "glVertexAttrib4ubv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib4uiv, "glVertexAttrib4uiv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttrib4usv, "glVertexAttrib4usv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribPointer, "glVertexAttribPointer"));
    }

    // Desktop OpenGL 2.1
    if (majorVersion > 2 || (majorVersion == 2 && minorVersion >= 1)) {
        DAWN_TRY(LoadProc(getProc, &UniformMatrix2x3fv, "glUniformMatrix2x3fv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix3x2fv, "glUniformMatrix3x2fv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix2x4fv, "glUniformMatrix2x4fv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix4x2fv, "glUniformMatrix4x2fv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix3x4fv, "glUniformMatrix3x4fv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix4x3fv, "glUniformMatrix4x3fv"));
    }

    // Desktop OpenGL 3.0
    if (majorVersion > 3 || (majorVersion == 3 && minorVersion >= 0)) {
        DAWN_TRY(LoadProc(getProc, &ColorMaski, "glColorMaski"));
        DAWN_TRY(LoadProc(getProc, &GetBooleani_v, "glGetBooleani_v"));
        DAWN_TRY(LoadProc(getProc, &GetIntegeri_v, "glGetIntegeri_v"));
        DAWN_TRY(LoadProc(getProc, &Enablei, "glEnablei"));
        DAWN_TRY(LoadProc(getProc, &Disablei, "glDisablei"));
        DAWN_TRY(LoadProc(getProc, &IsEnabledi, "glIsEnabledi"));
        DAWN_TRY(LoadProc(getProc, &BeginTransformFeedback, "glBeginTransformFeedback"));
        DAWN_TRY(LoadProc(getProc, &EndTransformFeedback, "glEndTransformFeedback"));
        DAWN_TRY(LoadProc(getProc, &BindBufferRange, "glBindBufferRange"));
        DAWN_TRY(LoadProc(getProc, &BindBufferBase, "glBindBufferBase"));
        DAWN_TRY(LoadProc(getProc, &TransformFeedbackVaryings, "glTransformFeedbackVaryings"));
        DAWN_TRY(LoadProc(getProc, &GetTransformFeedbackVarying, "glGetTransformFeedbackVarying"));
        DAWN_TRY(LoadProc(getProc, &ClampColor, "glClampColor"));
        DAWN_TRY(LoadProc(getProc, &BeginConditionalRender, "glBeginConditionalRender"));
        DAWN_TRY(LoadProc(getProc, &EndConditionalRender, "glEndConditionalRender"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribIPointer, "glVertexAttribIPointer"));
        DAWN_TRY(LoadProc(getProc, &GetVertexAttribIiv, "glGetVertexAttribIiv"));
        DAWN_TRY(LoadProc(getProc, &GetVertexAttribIuiv, "glGetVertexAttribIuiv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI1i, "glVertexAttribI1i"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI2i, "glVertexAttribI2i"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI3i, "glVertexAttribI3i"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI4i, "glVertexAttribI4i"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI1ui, "glVertexAttribI1ui"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI2ui, "glVertexAttribI2ui"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI3ui, "glVertexAttribI3ui"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI4ui, "glVertexAttribI4ui"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI1iv, "glVertexAttribI1iv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI2iv, "glVertexAttribI2iv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI3iv, "glVertexAttribI3iv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI4iv, "glVertexAttribI4iv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI1uiv, "glVertexAttribI1uiv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI2uiv, "glVertexAttribI2uiv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI3uiv, "glVertexAttribI3uiv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI4uiv, "glVertexAttribI4uiv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI4bv, "glVertexAttribI4bv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI4sv, "glVertexAttribI4sv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI4ubv, "glVertexAttribI4ubv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribI4usv, "glVertexAttribI4usv"));
        DAWN_TRY(LoadProc(getProc, &GetUniformuiv, "glGetUniformuiv"));
        DAWN_TRY(LoadProc(getProc, &BindFragDataLocation, "glBindFragDataLocation"));
        DAWN_TRY(LoadProc(getProc, &GetFragDataLocation, "glGetFragDataLocation"));
        DAWN_TRY(LoadProc(getProc, &Uniform1ui, "glUniform1ui"));
        DAWN_TRY(LoadProc(getProc, &Uniform2ui, "glUniform2ui"));
        DAWN_TRY(LoadProc(getProc, &Uniform3ui, "glUniform3ui"));
        DAWN_TRY(LoadProc(getProc, &Uniform4ui, "glUniform4ui"));
        DAWN_TRY(LoadProc(getProc, &Uniform1uiv, "glUniform1uiv"));
        DAWN_TRY(LoadProc(getProc, &Uniform2uiv, "glUniform2uiv"));
        DAWN_TRY(LoadProc(getProc, &Uniform3uiv, "glUniform3uiv"));
        DAWN_TRY(LoadProc(getProc, &Uniform4uiv, "glUniform4uiv"));
        DAWN_TRY(LoadProc(getProc, &TexParameterIiv, "glTexParameterIiv"));
        DAWN_TRY(LoadProc(getProc, &TexParameterIuiv, "glTexParameterIuiv"));
        DAWN_TRY(LoadProc(getProc, &GetTexParameterIiv, "glGetTexParameterIiv"));
        DAWN_TRY(LoadProc(getProc, &GetTexParameterIuiv, "glGetTexParameterIuiv"));
        DAWN_TRY(LoadProc(getProc, &ClearBufferiv, "glClearBufferiv"));
        DAWN_TRY(LoadProc(getProc, &ClearBufferuiv, "glClearBufferuiv"));
        DAWN_TRY(LoadProc(getProc, &ClearBufferfv, "glClearBufferfv"));
        DAWN_TRY(LoadProc(getProc, &ClearBufferfi, "glClearBufferfi"));
        DAWN_TRY(LoadProc(getProc, &GetStringi, "glGetStringi"));
        DAWN_TRY(LoadProc(getProc, &IsRenderbuffer, "glIsRenderbuffer"));
        DAWN_TRY(LoadProc(getProc, &BindRenderbuffer, "glBindRenderbuffer"));
        DAWN_TRY(LoadProc(getProc, &DeleteRenderbuffers, "glDeleteRenderbuffers"));
        DAWN_TRY(LoadProc(getProc, &GenRenderbuffers, "glGenRenderbuffers"));
        DAWN_TRY(LoadProc(getProc, &RenderbufferStorage, "glRenderbufferStorage"));
        DAWN_TRY(LoadProc(getProc, &GetRenderbufferParameteriv, "glGetRenderbufferParameteriv"));
        DAWN_TRY(LoadProc(getProc, &IsFramebuffer, "glIsFramebuffer"));
        DAWN_TRY(LoadProc(getProc, &BindFramebuffer, "glBindFramebuffer"));
        DAWN_TRY(LoadProc(getProc, &DeleteFramebuffers, "glDeleteFramebuffers"));
        DAWN_TRY(LoadProc(getProc, &GenFramebuffers, "glGenFramebuffers"));
        DAWN_TRY(LoadProc(getProc, &CheckFramebufferStatus, "glCheckFramebufferStatus"));
        DAWN_TRY(LoadProc(getProc, &FramebufferTexture1D, "glFramebufferTexture1D"));
        DAWN_TRY(LoadProc(getProc, &FramebufferTexture2D, "glFramebufferTexture2D"));
        DAWN_TRY(LoadProc(getProc, &FramebufferTexture3D, "glFramebufferTexture3D"));
        DAWN_TRY(LoadProc(getProc, &FramebufferRenderbuffer, "glFramebufferRenderbuffer"));
        DAWN_TRY(LoadProc(getProc, &GetFramebufferAttachmentParameteriv, "glGetFramebufferAttachmentParameteriv"));
        DAWN_TRY(LoadProc(getProc, &GenerateMipmap, "glGenerateMipmap"));
        DAWN_TRY(LoadProc(getProc, &BlitFramebuffer, "glBlitFramebuffer"));
        DAWN_TRY(LoadProc(getProc, &RenderbufferStorageMultisample, "glRenderbufferStorageMultisample"));
        DAWN_TRY(LoadProc(getProc, &FramebufferTextureLayer, "glFramebufferTextureLayer"));
        DAWN_TRY(LoadProc(getProc, &MapBufferRange, "glMapBufferRange"));
        DAWN_TRY(LoadProc(getProc, &FlushMappedBufferRange, "glFlushMappedBufferRange"));
        DAWN_TRY(LoadProc(getProc, &BindVertexArray, "glBindVertexArray"));
        DAWN_TRY(LoadProc(getProc, &DeleteVertexArrays, "glDeleteVertexArrays"));
        DAWN_TRY(LoadProc(getProc, &GenVertexArrays, "glGenVertexArrays"));
        DAWN_TRY(LoadProc(getProc, &IsVertexArray, "glIsVertexArray"));
    }

    // Desktop OpenGL 3.1
    if (majorVersion > 3 || (majorVersion == 3 && minorVersion >= 1)) {
        DAWN_TRY(LoadProc(getProc, &DrawArraysInstanced, "glDrawArraysInstanced"));
        DAWN_TRY(LoadProc(getProc, &DrawElementsInstanced, "glDrawElementsInstanced"));
        DAWN_TRY(LoadProc(getProc, &TexBuffer, "glTexBuffer"));
        DAWN_TRY(LoadProc(getProc, &PrimitiveRestartIndex, "glPrimitiveRestartIndex"));
        DAWN_TRY(LoadProc(getProc, &CopyBufferSubData, "glCopyBufferSubData"));
        DAWN_TRY(LoadProc(getProc, &GetUniformIndices, "glGetUniformIndices"));
        DAWN_TRY(LoadProc(getProc, &GetActiveUniformsiv, "glGetActiveUniformsiv"));
        DAWN_TRY(LoadProc(getProc, &GetActiveUniformName, "glGetActiveUniformName"));
        DAWN_TRY(LoadProc(getProc, &GetUniformBlockIndex, "glGetUniformBlockIndex"));
        DAWN_TRY(LoadProc(getProc, &GetActiveUniformBlockiv, "glGetActiveUniformBlockiv"));
        DAWN_TRY(LoadProc(getProc, &GetActiveUniformBlockName, "glGetActiveUniformBlockName"));
        DAWN_TRY(LoadProc(getProc, &UniformBlockBinding, "glUniformBlockBinding"));
        DAWN_TRY(LoadProc(getProc, &BindBufferRange, "glBindBufferRange"));
        DAWN_TRY(LoadProc(getProc, &BindBufferBase, "glBindBufferBase"));
        DAWN_TRY(LoadProc(getProc, &GetIntegeri_v, "glGetIntegeri_v"));
    }

    // Desktop OpenGL 3.2
    if (majorVersion > 3 || (majorVersion == 3 && minorVersion >= 2)) {
        DAWN_TRY(LoadProc(getProc, &DrawElementsBaseVertex, "glDrawElementsBaseVertex"));
        DAWN_TRY(LoadProc(getProc, &DrawRangeElementsBaseVertex, "glDrawRangeElementsBaseVertex"));
        DAWN_TRY(LoadProc(getProc, &DrawElementsInstancedBaseVertex, "glDrawElementsInstancedBaseVertex"));
        DAWN_TRY(LoadProc(getProc, &MultiDrawElementsBaseVertex, "glMultiDrawElementsBaseVertex"));
        DAWN_TRY(LoadProc(getProc, &ProvokingVertex, "glProvokingVertex"));
        DAWN_TRY(LoadProc(getProc, &FenceSync, "glFenceSync"));
        DAWN_TRY(LoadProc(getProc, &IsSync, "glIsSync"));
        DAWN_TRY(LoadProc(getProc, &DeleteSync, "glDeleteSync"));
        DAWN_TRY(LoadProc(getProc, &ClientWaitSync, "glClientWaitSync"));
        DAWN_TRY(LoadProc(getProc, &WaitSync, "glWaitSync"));
        DAWN_TRY(LoadProc(getProc, &GetInteger64v, "glGetInteger64v"));
        DAWN_TRY(LoadProc(getProc, &GetSynciv, "glGetSynciv"));
        DAWN_TRY(LoadProc(getProc, &GetInteger64i_v, "glGetInteger64i_v"));
        DAWN_TRY(LoadProc(getProc, &GetBufferParameteri64v, "glGetBufferParameteri64v"));
        DAWN_TRY(LoadProc(getProc, &FramebufferTexture, "glFramebufferTexture"));
        DAWN_TRY(LoadProc(getProc, &TexImage2DMultisample, "glTexImage2DMultisample"));
        DAWN_TRY(LoadProc(getProc, &TexImage3DMultisample, "glTexImage3DMultisample"));
        DAWN_TRY(LoadProc(getProc, &GetMultisamplefv, "glGetMultisamplefv"));
        DAWN_TRY(LoadProc(getProc, &SampleMaski, "glSampleMaski"));
    }

    // Desktop OpenGL 3.3
    if (majorVersion > 3 || (majorVersion == 3 && minorVersion >= 3)) {
        DAWN_TRY(LoadProc(getProc, &BindFragDataLocationIndexed, "glBindFragDataLocationIndexed"));
        DAWN_TRY(LoadProc(getProc, &GetFragDataIndex, "glGetFragDataIndex"));
        DAWN_TRY(LoadProc(getProc, &GenSamplers, "glGenSamplers"));
        DAWN_TRY(LoadProc(getProc, &DeleteSamplers, "glDeleteSamplers"));
        DAWN_TRY(LoadProc(getProc, &IsSampler, "glIsSampler"));
        DAWN_TRY(LoadProc(getProc, &BindSampler, "glBindSampler"));
        DAWN_TRY(LoadProc(getProc, &SamplerParameteri, "glSamplerParameteri"));
        DAWN_TRY(LoadProc(getProc, &SamplerParameteriv, "glSamplerParameteriv"));
        DAWN_TRY(LoadProc(getProc, &SamplerParameterf, "glSamplerParameterf"));
        DAWN_TRY(LoadProc(getProc, &SamplerParameterfv, "glSamplerParameterfv"));
        DAWN_TRY(LoadProc(getProc, &SamplerParameterIiv, "glSamplerParameterIiv"));
        DAWN_TRY(LoadProc(getProc, &SamplerParameterIuiv, "glSamplerParameterIuiv"));
        DAWN_TRY(LoadProc(getProc, &GetSamplerParameteriv, "glGetSamplerParameteriv"));
        DAWN_TRY(LoadProc(getProc, &GetSamplerParameterIiv, "glGetSamplerParameterIiv"));
        DAWN_TRY(LoadProc(getProc, &GetSamplerParameterfv, "glGetSamplerParameterfv"));
        DAWN_TRY(LoadProc(getProc, &GetSamplerParameterIuiv, "glGetSamplerParameterIuiv"));
        DAWN_TRY(LoadProc(getProc, &QueryCounter, "glQueryCounter"));
        DAWN_TRY(LoadProc(getProc, &GetQueryObjecti64v, "glGetQueryObjecti64v"));
        DAWN_TRY(LoadProc(getProc, &GetQueryObjectui64v, "glGetQueryObjectui64v"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribDivisor, "glVertexAttribDivisor"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribP1ui, "glVertexAttribP1ui"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribP1uiv, "glVertexAttribP1uiv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribP2ui, "glVertexAttribP2ui"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribP2uiv, "glVertexAttribP2uiv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribP3ui, "glVertexAttribP3ui"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribP3uiv, "glVertexAttribP3uiv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribP4ui, "glVertexAttribP4ui"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribP4uiv, "glVertexAttribP4uiv"));
        DAWN_TRY(LoadProc(getProc, &VertexP2ui, "glVertexP2ui"));
        DAWN_TRY(LoadProc(getProc, &VertexP2uiv, "glVertexP2uiv"));
        DAWN_TRY(LoadProc(getProc, &VertexP3ui, "glVertexP3ui"));
        DAWN_TRY(LoadProc(getProc, &VertexP3uiv, "glVertexP3uiv"));
        DAWN_TRY(LoadProc(getProc, &VertexP4ui, "glVertexP4ui"));
        DAWN_TRY(LoadProc(getProc, &VertexP4uiv, "glVertexP4uiv"));
        DAWN_TRY(LoadProc(getProc, &TexCoordP1ui, "glTexCoordP1ui"));
        DAWN_TRY(LoadProc(getProc, &TexCoordP1uiv, "glTexCoordP1uiv"));
        DAWN_TRY(LoadProc(getProc, &TexCoordP2ui, "glTexCoordP2ui"));
        DAWN_TRY(LoadProc(getProc, &TexCoordP2uiv, "glTexCoordP2uiv"));
        DAWN_TRY(LoadProc(getProc, &TexCoordP3ui, "glTexCoordP3ui"));
        DAWN_TRY(LoadProc(getProc, &TexCoordP3uiv, "glTexCoordP3uiv"));
        DAWN_TRY(LoadProc(getProc, &TexCoordP4ui, "glTexCoordP4ui"));
        DAWN_TRY(LoadProc(getProc, &TexCoordP4uiv, "glTexCoordP4uiv"));
        DAWN_TRY(LoadProc(getProc, &MultiTexCoordP1ui, "glMultiTexCoordP1ui"));
        DAWN_TRY(LoadProc(getProc, &MultiTexCoordP1uiv, "glMultiTexCoordP1uiv"));
        DAWN_TRY(LoadProc(getProc, &MultiTexCoordP2ui, "glMultiTexCoordP2ui"));
        DAWN_TRY(LoadProc(getProc, &MultiTexCoordP2uiv, "glMultiTexCoordP2uiv"));
        DAWN_TRY(LoadProc(getProc, &MultiTexCoordP3ui, "glMultiTexCoordP3ui"));
        DAWN_TRY(LoadProc(getProc, &MultiTexCoordP3uiv, "glMultiTexCoordP3uiv"));
        DAWN_TRY(LoadProc(getProc, &MultiTexCoordP4ui, "glMultiTexCoordP4ui"));
        DAWN_TRY(LoadProc(getProc, &MultiTexCoordP4uiv, "glMultiTexCoordP4uiv"));
        DAWN_TRY(LoadProc(getProc, &NormalP3ui, "glNormalP3ui"));
        DAWN_TRY(LoadProc(getProc, &NormalP3uiv, "glNormalP3uiv"));
        DAWN_TRY(LoadProc(getProc, &ColorP3ui, "glColorP3ui"));
        DAWN_TRY(LoadProc(getProc, &ColorP3uiv, "glColorP3uiv"));
        DAWN_TRY(LoadProc(getProc, &ColorP4ui, "glColorP4ui"));
        DAWN_TRY(LoadProc(getProc, &ColorP4uiv, "glColorP4uiv"));
        DAWN_TRY(LoadProc(getProc, &SecondaryColorP3ui, "glSecondaryColorP3ui"));
        DAWN_TRY(LoadProc(getProc, &SecondaryColorP3uiv, "glSecondaryColorP3uiv"));
    }

    // Desktop OpenGL 4.0
    if (majorVersion > 4 || (majorVersion == 4 && minorVersion >= 0)) {
        DAWN_TRY(LoadProc(getProc, &MinSampleShading, "glMinSampleShading"));
        DAWN_TRY(LoadProc(getProc, &BlendEquationi, "glBlendEquationi"));
        DAWN_TRY(LoadProc(getProc, &BlendEquationSeparatei, "glBlendEquationSeparatei"));
        DAWN_TRY(LoadProc(getProc, &BlendFunci, "glBlendFunci"));
        DAWN_TRY(LoadProc(getProc, &BlendFuncSeparatei, "glBlendFuncSeparatei"));
        DAWN_TRY(LoadProc(getProc, &DrawArraysIndirect, "glDrawArraysIndirect"));
        DAWN_TRY(LoadProc(getProc, &DrawElementsIndirect, "glDrawElementsIndirect"));
        DAWN_TRY(LoadProc(getProc, &Uniform1d, "glUniform1d"));
        DAWN_TRY(LoadProc(getProc, &Uniform2d, "glUniform2d"));
        DAWN_TRY(LoadProc(getProc, &Uniform3d, "glUniform3d"));
        DAWN_TRY(LoadProc(getProc, &Uniform4d, "glUniform4d"));
        DAWN_TRY(LoadProc(getProc, &Uniform1dv, "glUniform1dv"));
        DAWN_TRY(LoadProc(getProc, &Uniform2dv, "glUniform2dv"));
        DAWN_TRY(LoadProc(getProc, &Uniform3dv, "glUniform3dv"));
        DAWN_TRY(LoadProc(getProc, &Uniform4dv, "glUniform4dv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix2dv, "glUniformMatrix2dv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix3dv, "glUniformMatrix3dv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix4dv, "glUniformMatrix4dv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix2x3dv, "glUniformMatrix2x3dv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix2x4dv, "glUniformMatrix2x4dv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix3x2dv, "glUniformMatrix3x2dv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix3x4dv, "glUniformMatrix3x4dv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix4x2dv, "glUniformMatrix4x2dv"));
        DAWN_TRY(LoadProc(getProc, &UniformMatrix4x3dv, "glUniformMatrix4x3dv"));
        DAWN_TRY(LoadProc(getProc, &GetUniformdv, "glGetUniformdv"));
        DAWN_TRY(LoadProc(getProc, &GetSubroutineUniformLocation, "glGetSubroutineUniformLocation"));
        DAWN_TRY(LoadProc(getProc, &GetSubroutineIndex, "glGetSubroutineIndex"));
        DAWN_TRY(LoadProc(getProc, &GetActiveSubroutineUniformiv, "glGetActiveSubroutineUniformiv"));
        DAWN_TRY(LoadProc(getProc, &GetActiveSubroutineUniformName, "glGetActiveSubroutineUniformName"));
        DAWN_TRY(LoadProc(getProc, &GetActiveSubroutineName, "glGetActiveSubroutineName"));
        DAWN_TRY(LoadProc(getProc, &UniformSubroutinesuiv, "glUniformSubroutinesuiv"));
        DAWN_TRY(LoadProc(getProc, &GetUniformSubroutineuiv, "glGetUniformSubroutineuiv"));
        DAWN_TRY(LoadProc(getProc, &GetProgramStageiv, "glGetProgramStageiv"));
        DAWN_TRY(LoadProc(getProc, &PatchParameteri, "glPatchParameteri"));
        DAWN_TRY(LoadProc(getProc, &PatchParameterfv, "glPatchParameterfv"));
        DAWN_TRY(LoadProc(getProc, &BindTransformFeedback, "glBindTransformFeedback"));
        DAWN_TRY(LoadProc(getProc, &DeleteTransformFeedbacks, "glDeleteTransformFeedbacks"));
        DAWN_TRY(LoadProc(getProc, &GenTransformFeedbacks, "glGenTransformFeedbacks"));
        DAWN_TRY(LoadProc(getProc, &IsTransformFeedback, "glIsTransformFeedback"));
        DAWN_TRY(LoadProc(getProc, &PauseTransformFeedback, "glPauseTransformFeedback"));
        DAWN_TRY(LoadProc(getProc, &ResumeTransformFeedback, "glResumeTransformFeedback"));
        DAWN_TRY(LoadProc(getProc, &DrawTransformFeedback, "glDrawTransformFeedback"));
        DAWN_TRY(LoadProc(getProc, &DrawTransformFeedbackStream, "glDrawTransformFeedbackStream"));
        DAWN_TRY(LoadProc(getProc, &BeginQueryIndexed, "glBeginQueryIndexed"));
        DAWN_TRY(LoadProc(getProc, &EndQueryIndexed, "glEndQueryIndexed"));
        DAWN_TRY(LoadProc(getProc, &GetQueryIndexediv, "glGetQueryIndexediv"));
    }

    // Desktop OpenGL 4.1
    if (majorVersion > 4 || (majorVersion == 4 && minorVersion >= 1)) {
        DAWN_TRY(LoadProc(getProc, &ReleaseShaderCompiler, "glReleaseShaderCompiler"));
        DAWN_TRY(LoadProc(getProc, &ShaderBinary, "glShaderBinary"));
        DAWN_TRY(LoadProc(getProc, &GetShaderPrecisionFormat, "glGetShaderPrecisionFormat"));
        DAWN_TRY(LoadProc(getProc, &DepthRangef, "glDepthRangef"));
        DAWN_TRY(LoadProc(getProc, &ClearDepthf, "glClearDepthf"));
        DAWN_TRY(LoadProc(getProc, &GetProgramBinary, "glGetProgramBinary"));
        DAWN_TRY(LoadProc(getProc, &ProgramBinary, "glProgramBinary"));
        DAWN_TRY(LoadProc(getProc, &ProgramParameteri, "glProgramParameteri"));
        DAWN_TRY(LoadProc(getProc, &UseProgramStages, "glUseProgramStages"));
        DAWN_TRY(LoadProc(getProc, &ActiveShaderProgram, "glActiveShaderProgram"));
        DAWN_TRY(LoadProc(getProc, &CreateShaderProgramv, "glCreateShaderProgramv"));
        DAWN_TRY(LoadProc(getProc, &BindProgramPipeline, "glBindProgramPipeline"));
        DAWN_TRY(LoadProc(getProc, &DeleteProgramPipelines, "glDeleteProgramPipelines"));
        DAWN_TRY(LoadProc(getProc, &GenProgramPipelines, "glGenProgramPipelines"));
        DAWN_TRY(LoadProc(getProc, &IsProgramPipeline, "glIsProgramPipeline"));
        DAWN_TRY(LoadProc(getProc, &GetProgramPipelineiv, "glGetProgramPipelineiv"));
        DAWN_TRY(LoadProc(getProc, &ProgramParameteri, "glProgramParameteri"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform1i, "glProgramUniform1i"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform1iv, "glProgramUniform1iv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform1f, "glProgramUniform1f"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform1fv, "glProgramUniform1fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform1d, "glProgramUniform1d"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform1dv, "glProgramUniform1dv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform1ui, "glProgramUniform1ui"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform1uiv, "glProgramUniform1uiv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform2i, "glProgramUniform2i"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform2iv, "glProgramUniform2iv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform2f, "glProgramUniform2f"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform2fv, "glProgramUniform2fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform2d, "glProgramUniform2d"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform2dv, "glProgramUniform2dv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform2ui, "glProgramUniform2ui"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform2uiv, "glProgramUniform2uiv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform3i, "glProgramUniform3i"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform3iv, "glProgramUniform3iv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform3f, "glProgramUniform3f"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform3fv, "glProgramUniform3fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform3d, "glProgramUniform3d"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform3dv, "glProgramUniform3dv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform3ui, "glProgramUniform3ui"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform3uiv, "glProgramUniform3uiv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform4i, "glProgramUniform4i"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform4iv, "glProgramUniform4iv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform4f, "glProgramUniform4f"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform4fv, "glProgramUniform4fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform4d, "glProgramUniform4d"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform4dv, "glProgramUniform4dv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform4ui, "glProgramUniform4ui"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniform4uiv, "glProgramUniform4uiv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix2fv, "glProgramUniformMatrix2fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix3fv, "glProgramUniformMatrix3fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix4fv, "glProgramUniformMatrix4fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix2dv, "glProgramUniformMatrix2dv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix3dv, "glProgramUniformMatrix3dv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix4dv, "glProgramUniformMatrix4dv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix2x3fv, "glProgramUniformMatrix2x3fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix3x2fv, "glProgramUniformMatrix3x2fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix2x4fv, "glProgramUniformMatrix2x4fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix4x2fv, "glProgramUniformMatrix4x2fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix3x4fv, "glProgramUniformMatrix3x4fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix4x3fv, "glProgramUniformMatrix4x3fv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix2x3dv, "glProgramUniformMatrix2x3dv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix3x2dv, "glProgramUniformMatrix3x2dv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix2x4dv, "glProgramUniformMatrix2x4dv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix4x2dv, "glProgramUniformMatrix4x2dv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix3x4dv, "glProgramUniformMatrix3x4dv"));
        DAWN_TRY(LoadProc(getProc, &ProgramUniformMatrix4x3dv, "glProgramUniformMatrix4x3dv"));
        DAWN_TRY(LoadProc(getProc, &ValidateProgramPipeline, "glValidateProgramPipeline"));
        DAWN_TRY(LoadProc(getProc, &GetProgramPipelineInfoLog, "glGetProgramPipelineInfoLog"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribL1d, "glVertexAttribL1d"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribL2d, "glVertexAttribL2d"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribL3d, "glVertexAttribL3d"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribL4d, "glVertexAttribL4d"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribL1dv, "glVertexAttribL1dv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribL2dv, "glVertexAttribL2dv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribL3dv, "glVertexAttribL3dv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribL4dv, "glVertexAttribL4dv"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribLPointer, "glVertexAttribLPointer"));
        DAWN_TRY(LoadProc(getProc, &GetVertexAttribLdv, "glGetVertexAttribLdv"));
        DAWN_TRY(LoadProc(getProc, &ViewportArrayv, "glViewportArrayv"));
        DAWN_TRY(LoadProc(getProc, &ViewportIndexedf, "glViewportIndexedf"));
        DAWN_TRY(LoadProc(getProc, &ViewportIndexedfv, "glViewportIndexedfv"));
        DAWN_TRY(LoadProc(getProc, &ScissorArrayv, "glScissorArrayv"));
        DAWN_TRY(LoadProc(getProc, &ScissorIndexed, "glScissorIndexed"));
        DAWN_TRY(LoadProc(getProc, &ScissorIndexedv, "glScissorIndexedv"));
        DAWN_TRY(LoadProc(getProc, &DepthRangeArrayv, "glDepthRangeArrayv"));
        DAWN_TRY(LoadProc(getProc, &DepthRangeIndexed, "glDepthRangeIndexed"));
        DAWN_TRY(LoadProc(getProc, &GetFloati_v, "glGetFloati_v"));
        DAWN_TRY(LoadProc(getProc, &GetDoublei_v, "glGetDoublei_v"));
    }

    // Desktop OpenGL 4.2
    if (majorVersion > 4 || (majorVersion == 4 && minorVersion >= 2)) {
        DAWN_TRY(LoadProc(getProc, &DrawArraysInstancedBaseInstance, "glDrawArraysInstancedBaseInstance"));
        DAWN_TRY(LoadProc(getProc, &DrawElementsInstancedBaseInstance, "glDrawElementsInstancedBaseInstance"));
        DAWN_TRY(LoadProc(getProc, &DrawElementsInstancedBaseVertexBaseInstance, "glDrawElementsInstancedBaseVertexBaseInstance"));
        DAWN_TRY(LoadProc(getProc, &GetInternalformativ, "glGetInternalformativ"));
        DAWN_TRY(LoadProc(getProc, &GetActiveAtomicCounterBufferiv, "glGetActiveAtomicCounterBufferiv"));
        DAWN_TRY(LoadProc(getProc, &BindImageTexture, "glBindImageTexture"));
        DAWN_TRY(LoadProc(getProc, &MemoryBarrier, "glMemoryBarrier"));
        DAWN_TRY(LoadProc(getProc, &TexStorage1D, "glTexStorage1D"));
        DAWN_TRY(LoadProc(getProc, &TexStorage2D, "glTexStorage2D"));
        DAWN_TRY(LoadProc(getProc, &TexStorage3D, "glTexStorage3D"));
        DAWN_TRY(LoadProc(getProc, &DrawTransformFeedbackInstanced, "glDrawTransformFeedbackInstanced"));
        DAWN_TRY(LoadProc(getProc, &DrawTransformFeedbackStreamInstanced, "glDrawTransformFeedbackStreamInstanced"));
    }

    // Desktop OpenGL 4.3
    if (majorVersion > 4 || (majorVersion == 4 && minorVersion >= 3)) {
        DAWN_TRY(LoadProc(getProc, &ClearBufferData, "glClearBufferData"));
        DAWN_TRY(LoadProc(getProc, &ClearBufferSubData, "glClearBufferSubData"));
        DAWN_TRY(LoadProc(getProc, &DispatchCompute, "glDispatchCompute"));
        DAWN_TRY(LoadProc(getProc, &DispatchComputeIndirect, "glDispatchComputeIndirect"));
        DAWN_TRY(LoadProc(getProc, &CopyImageSubData, "glCopyImageSubData"));
        DAWN_TRY(LoadProc(getProc, &FramebufferParameteri, "glFramebufferParameteri"));
        DAWN_TRY(LoadProc(getProc, &GetFramebufferParameteriv, "glGetFramebufferParameteriv"));
        DAWN_TRY(LoadProc(getProc, &GetInternalformati64v, "glGetInternalformati64v"));
        DAWN_TRY(LoadProc(getProc, &InvalidateTexSubImage, "glInvalidateTexSubImage"));
        DAWN_TRY(LoadProc(getProc, &InvalidateTexImage, "glInvalidateTexImage"));
        DAWN_TRY(LoadProc(getProc, &InvalidateBufferSubData, "glInvalidateBufferSubData"));
        DAWN_TRY(LoadProc(getProc, &InvalidateBufferData, "glInvalidateBufferData"));
        DAWN_TRY(LoadProc(getProc, &InvalidateFramebuffer, "glInvalidateFramebuffer"));
        DAWN_TRY(LoadProc(getProc, &InvalidateSubFramebuffer, "glInvalidateSubFramebuffer"));
        DAWN_TRY(LoadProc(getProc, &MultiDrawArraysIndirect, "glMultiDrawArraysIndirect"));
        DAWN_TRY(LoadProc(getProc, &MultiDrawElementsIndirect, "glMultiDrawElementsIndirect"));
        DAWN_TRY(LoadProc(getProc, &GetProgramInterfaceiv, "glGetProgramInterfaceiv"));
        DAWN_TRY(LoadProc(getProc, &GetProgramResourceIndex, "glGetProgramResourceIndex"));
        DAWN_TRY(LoadProc(getProc, &GetProgramResourceName, "glGetProgramResourceName"));
        DAWN_TRY(LoadProc(getProc, &GetProgramResourceiv, "glGetProgramResourceiv"));
        DAWN_TRY(LoadProc(getProc, &GetProgramResourceLocation, "glGetProgramResourceLocation"));
        DAWN_TRY(LoadProc(getProc, &GetProgramResourceLocationIndex, "glGetProgramResourceLocationIndex"));
        DAWN_TRY(LoadProc(getProc, &ShaderStorageBlockBinding, "glShaderStorageBlockBinding"));
        DAWN_TRY(LoadProc(getProc, &TexBufferRange, "glTexBufferRange"));
        DAWN_TRY(LoadProc(getProc, &TexStorage2DMultisample, "glTexStorage2DMultisample"));
        DAWN_TRY(LoadProc(getProc, &TexStorage3DMultisample, "glTexStorage3DMultisample"));
        DAWN_TRY(LoadProc(getProc, &TextureView, "glTextureView"));
        DAWN_TRY(LoadProc(getProc, &BindVertexBuffer, "glBindVertexBuffer"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribFormat, "glVertexAttribFormat"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribIFormat, "glVertexAttribIFormat"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribLFormat, "glVertexAttribLFormat"));
        DAWN_TRY(LoadProc(getProc, &VertexAttribBinding, "glVertexAttribBinding"));
        DAWN_TRY(LoadProc(getProc, &VertexBindingDivisor, "glVertexBindingDivisor"));
        DAWN_TRY(LoadProc(getProc, &DebugMessageControl, "glDebugMessageControl"));
        DAWN_TRY(LoadProc(getProc, &DebugMessageInsert, "glDebugMessageInsert"));
        DAWN_TRY(LoadProc(getProc, &DebugMessageCallback, "glDebugMessageCallback"));
        DAWN_TRY(LoadProc(getProc, &GetDebugMessageLog, "glGetDebugMessageLog"));
        DAWN_TRY(LoadProc(getProc, &PushDebugGroup, "glPushDebugGroup"));
        DAWN_TRY(LoadProc(getProc, &PopDebugGroup, "glPopDebugGroup"));
        DAWN_TRY(LoadProc(getProc, &ObjectLabel, "glObjectLabel"));
        DAWN_TRY(LoadProc(getProc, &GetObjectLabel, "glGetObjectLabel"));
        DAWN_TRY(LoadProc(getProc, &ObjectPtrLabel, "glObjectPtrLabel"));
        DAWN_TRY(LoadProc(getProc, &GetObjectPtrLabel, "glGetObjectPtrLabel"));
    }

    // Desktop OpenGL 4.4
    if (majorVersion > 4 || (majorVersion == 4 && minorVersion >= 4)) {
        DAWN_TRY(LoadProc(getProc, &BufferStorage, "glBufferStorage"));
        DAWN_TRY(LoadProc(getProc, &ClearTexImage, "glClearTexImage"));
        DAWN_TRY(LoadProc(getProc, &ClearTexSubImage, "glClearTexSubImage"));
        DAWN_TRY(LoadProc(getProc, &BindBuffersBase, "glBindBuffersBase"));
        DAWN_TRY(LoadProc(getProc, &BindBuffersRange, "glBindBuffersRange"));
        DAWN_TRY(LoadProc(getProc, &BindTextures, "glBindTextures"));
        DAWN_TRY(LoadProc(getProc, &BindSamplers, "glBindSamplers"));
        DAWN_TRY(LoadProc(getProc, &BindImageTextures, "glBindImageTextures"));
        DAWN_TRY(LoadProc(getProc, &BindVertexBuffers, "glBindVertexBuffers"));
    }

    // Desktop OpenGL 4.5
    if (majorVersion > 4 || (majorVersion == 4 && minorVersion >= 5)) {
        DAWN_TRY(LoadProc(getProc, &ClipControl, "glClipControl"));
        DAWN_TRY(LoadProc(getProc, &CreateTransformFeedbacks, "glCreateTransformFeedbacks"));
        DAWN_TRY(LoadProc(getProc, &TransformFeedbackBufferBase, "glTransformFeedbackBufferBase"));
        DAWN_TRY(LoadProc(getProc, &TransformFeedbackBufferRange, "glTransformFeedbackBufferRange"));
        DAWN_TRY(LoadProc(getProc, &GetTransformFeedbackiv, "glGetTransformFeedbackiv"));
        DAWN_TRY(LoadProc(getProc, &GetTransformFeedbacki_v, "glGetTransformFeedbacki_v"));
        DAWN_TRY(LoadProc(getProc, &GetTransformFeedbacki64_v, "glGetTransformFeedbacki64_v"));
        DAWN_TRY(LoadProc(getProc, &CreateBuffers, "glCreateBuffers"));
        DAWN_TRY(LoadProc(getProc, &NamedBufferStorage, "glNamedBufferStorage"));
        DAWN_TRY(LoadProc(getProc, &NamedBufferData, "glNamedBufferData"));
        DAWN_TRY(LoadProc(getProc, &NamedBufferSubData, "glNamedBufferSubData"));
        DAWN_TRY(LoadProc(getProc, &CopyNamedBufferSubData, "glCopyNamedBufferSubData"));
        DAWN_TRY(LoadProc(getProc, &ClearNamedBufferData, "glClearNamedBufferData"));
        DAWN_TRY(LoadProc(getProc, &ClearNamedBufferSubData, "glClearNamedBufferSubData"));
        DAWN_TRY(LoadProc(getProc, &MapNamedBuffer, "glMapNamedBuffer"));
        DAWN_TRY(LoadProc(getProc, &MapNamedBufferRange, "glMapNamedBufferRange"));
        DAWN_TRY(LoadProc(getProc, &UnmapNamedBuffer, "glUnmapNamedBuffer"));
        DAWN_TRY(LoadProc(getProc, &FlushMappedNamedBufferRange, "glFlushMappedNamedBufferRange"));
        DAWN_TRY(LoadProc(getProc, &GetNamedBufferParameteriv, "glGetNamedBufferParameteriv"));
        DAWN_TRY(LoadProc(getProc, &GetNamedBufferParameteri64v, "glGetNamedBufferParameteri64v"));
        DAWN_TRY(LoadProc(getProc, &GetNamedBufferPointerv, "glGetNamedBufferPointerv"));
        DAWN_TRY(LoadProc(getProc, &GetNamedBufferSubData, "glGetNamedBufferSubData"));
        DAWN_TRY(LoadProc(getProc, &CreateFramebuffers, "glCreateFramebuffers"));
        DAWN_TRY(LoadProc(getProc, &NamedFramebufferRenderbuffer, "glNamedFramebufferRenderbuffer"));
        DAWN_TRY(LoadProc(getProc, &NamedFramebufferParameteri, "glNamedFramebufferParameteri"));
        DAWN_TRY(LoadProc(getProc, &NamedFramebufferTexture, "glNamedFramebufferTexture"));
        DAWN_TRY(LoadProc(getProc, &NamedFramebufferTextureLayer, "glNamedFramebufferTextureLayer"));
        DAWN_TRY(LoadProc(getProc, &NamedFramebufferDrawBuffer, "glNamedFramebufferDrawBuffer"));
        DAWN_TRY(LoadProc(getProc, &NamedFramebufferDrawBuffers, "glNamedFramebufferDrawBuffers"));
        DAWN_TRY(LoadProc(getProc, &NamedFramebufferReadBuffer, "glNamedFramebufferReadBuffer"));
        DAWN_TRY(LoadProc(getProc, &InvalidateNamedFramebufferData, "glInvalidateNamedFramebufferData"));
        DAWN_TRY(LoadProc(getProc, &InvalidateNamedFramebufferSubData, "glInvalidateNamedFramebufferSubData"));
        DAWN_TRY(LoadProc(getProc, &ClearNamedFramebufferiv, "glClearNamedFramebufferiv"));
        DAWN_TRY(LoadProc(getProc, &ClearNamedFramebufferuiv, "glClearNamedFramebufferuiv"));
        DAWN_TRY(LoadProc(getProc, &ClearNamedFramebufferfv, "glClearNamedFramebufferfv"));
        DAWN_TRY(LoadProc(getProc, &ClearNamedFramebufferfi, "glClearNamedFramebufferfi"));
        DAWN_TRY(LoadProc(getProc, &BlitNamedFramebuffer, "glBlitNamedFramebuffer"));
        DAWN_TRY(LoadProc(getProc, &CheckNamedFramebufferStatus, "glCheckNamedFramebufferStatus"));
        DAWN_TRY(LoadProc(getProc, &GetNamedFramebufferParameteriv, "glGetNamedFramebufferParameteriv"));
        DAWN_TRY(LoadProc(getProc, &GetNamedFramebufferAttachmentParameteriv, "glGetNamedFramebufferAttachmentParameteriv"));
        DAWN_TRY(LoadProc(getProc, &CreateRenderbuffers, "glCreateRenderbuffers"));
        DAWN_TRY(LoadProc(getProc, &NamedRenderbufferStorage, "glNamedRenderbufferStorage"));
        DAWN_TRY(LoadProc(getProc, &NamedRenderbufferStorageMultisample, "glNamedRenderbufferStorageMultisample"));
        DAWN_TRY(LoadProc(getProc, &GetNamedRenderbufferParameteriv, "glGetNamedRenderbufferParameteriv"));
        DAWN_TRY(LoadProc(getProc, &CreateTextures, "glCreateTextures"));
        DAWN_TRY(LoadProc(getProc, &TextureBuffer, "glTextureBuffer"));
        DAWN_TRY(LoadProc(getProc, &TextureBufferRange, "glTextureBufferRange"));
        DAWN_TRY(LoadProc(getProc, &TextureStorage1D, "glTextureStorage1D"));
        DAWN_TRY(LoadProc(getProc, &TextureStorage2D, "glTextureStorage2D"));
        DAWN_TRY(LoadProc(getProc, &TextureStorage3D, "glTextureStorage3D"));
        DAWN_TRY(LoadProc(getProc, &TextureStorage2DMultisample, "glTextureStorage2DMultisample"));
        DAWN_TRY(LoadProc(getProc, &TextureStorage3DMultisample, "glTextureStorage3DMultisample"));
        DAWN_TRY(LoadProc(getProc, &TextureSubImage1D, "glTextureSubImage1D"));
        DAWN_TRY(LoadProc(getProc, &TextureSubImage2D, "glTextureSubImage2D"));
        DAWN_TRY(LoadProc(getProc, &TextureSubImage3D, "glTextureSubImage3D"));
        DAWN_TRY(LoadProc(getProc, &CompressedTextureSubImage1D, "glCompressedTextureSubImage1D"));
        DAWN_TRY(LoadProc(getProc, &CompressedTextureSubImage2D, "glCompressedTextureSubImage2D"));
        DAWN_TRY(LoadProc(getProc, &CompressedTextureSubImage3D, "glCompressedTextureSubImage3D"));
        DAWN_TRY(LoadProc(getProc, &CopyTextureSubImage1D, "glCopyTextureSubImage1D"));
        DAWN_TRY(LoadProc(getProc, &CopyTextureSubImage2D, "glCopyTextureSubImage2D"));
        DAWN_TRY(LoadProc(getProc, &CopyTextureSubImage3D, "glCopyTextureSubImage3D"));
        DAWN_TRY(LoadProc(getProc, &TextureParameterf, "glTextureParameterf"));
        DAWN_TRY(LoadProc(getProc, &TextureParameterfv, "glTextureParameterfv"));
        DAWN_TRY(LoadProc(getProc, &TextureParameteri, "glTextureParameteri"));
        DAWN_TRY(LoadProc(getProc, &TextureParameterIiv, "glTextureParameterIiv"));
        DAWN_TRY(LoadProc(getProc, &TextureParameterIuiv, "glTextureParameterIuiv"));
        DAWN_TRY(LoadProc(getProc, &TextureParameteriv, "glTextureParameteriv"));
        DAWN_TRY(LoadProc(getProc, &GenerateTextureMipmap, "glGenerateTextureMipmap"));
        DAWN_TRY(LoadProc(getProc, &BindTextureUnit, "glBindTextureUnit"));
        DAWN_TRY(LoadProc(getProc, &GetTextureImage, "glGetTextureImage"));
        DAWN_TRY(LoadProc(getProc, &GetCompressedTextureImage, "glGetCompressedTextureImage"));
        DAWN_TRY(LoadProc(getProc, &GetTextureLevelParameterfv, "glGetTextureLevelParameterfv"));
        DAWN_TRY(LoadProc(getProc, &GetTextureLevelParameteriv, "glGetTextureLevelParameteriv"));
        DAWN_TRY(LoadProc(getProc, &GetTextureParameterfv, "glGetTextureParameterfv"));
        DAWN_TRY(LoadProc(getProc, &GetTextureParameterIiv, "glGetTextureParameterIiv"));
        DAWN_TRY(LoadProc(getProc, &GetTextureParameterIuiv, "glGetTextureParameterIuiv"));
        DAWN_TRY(LoadProc(getProc, &GetTextureParameteriv, "glGetTextureParameteriv"));
        DAWN_TRY(LoadProc(getProc, &CreateVertexArrays, "glCreateVertexArrays"));
        DAWN_TRY(LoadProc(getProc, &DisableVertexArrayAttrib, "glDisableVertexArrayAttrib"));
        DAWN_TRY(LoadProc(getProc, &EnableVertexArrayAttrib, "glEnableVertexArrayAttrib"));
        DAWN_TRY(LoadProc(getProc, &VertexArrayElementBuffer, "glVertexArrayElementBuffer"));
        DAWN_TRY(LoadProc(getProc, &VertexArrayVertexBuffer, "glVertexArrayVertexBuffer"));
        DAWN_TRY(LoadProc(getProc, &VertexArrayVertexBuffers, "glVertexArrayVertexBuffers"));
        DAWN_TRY(LoadProc(getProc, &VertexArrayAttribBinding, "glVertexArrayAttribBinding"));
        DAWN_TRY(LoadProc(getProc, &VertexArrayAttribFormat, "glVertexArrayAttribFormat"));
        DAWN_TRY(LoadProc(getProc, &VertexArrayAttribIFormat, "glVertexArrayAttribIFormat"));
        DAWN_TRY(LoadProc(getProc, &VertexArrayAttribLFormat, "glVertexArrayAttribLFormat"));
        DAWN_TRY(LoadProc(getProc, &VertexArrayBindingDivisor, "glVertexArrayBindingDivisor"));
        DAWN_TRY(LoadProc(getProc, &GetVertexArrayiv, "glGetVertexArrayiv"));
        DAWN_TRY(LoadProc(getProc, &GetVertexArrayIndexediv, "glGetVertexArrayIndexediv"));
        DAWN_TRY(LoadProc(getProc, &GetVertexArrayIndexed64iv, "glGetVertexArrayIndexed64iv"));
        DAWN_TRY(LoadProc(getProc, &CreateSamplers, "glCreateSamplers"));
        DAWN_TRY(LoadProc(getProc, &CreateProgramPipelines, "glCreateProgramPipelines"));
        DAWN_TRY(LoadProc(getProc, &CreateQueries, "glCreateQueries"));
        DAWN_TRY(LoadProc(getProc, &GetQueryBufferObjecti64v, "glGetQueryBufferObjecti64v"));
        DAWN_TRY(LoadProc(getProc, &GetQueryBufferObjectiv, "glGetQueryBufferObjectiv"));
        DAWN_TRY(LoadProc(getProc, &GetQueryBufferObjectui64v, "glGetQueryBufferObjectui64v"));
        DAWN_TRY(LoadProc(getProc, &GetQueryBufferObjectuiv, "glGetQueryBufferObjectuiv"));
        DAWN_TRY(LoadProc(getProc, &MemoryBarrierByRegion, "glMemoryBarrierByRegion"));
        DAWN_TRY(LoadProc(getProc, &GetTextureSubImage, "glGetTextureSubImage"));
        DAWN_TRY(LoadProc(getProc, &GetCompressedTextureSubImage, "glGetCompressedTextureSubImage"));
        DAWN_TRY(LoadProc(getProc, &GetGraphicsResetStatus, "glGetGraphicsResetStatus"));
        DAWN_TRY(LoadProc(getProc, &GetnCompressedTexImage, "glGetnCompressedTexImage"));
        DAWN_TRY(LoadProc(getProc, &GetnTexImage, "glGetnTexImage"));
        DAWN_TRY(LoadProc(getProc, &GetnUniformdv, "glGetnUniformdv"));
        DAWN_TRY(LoadProc(getProc, &GetnUniformfv, "glGetnUniformfv"));
        DAWN_TRY(LoadProc(getProc, &GetnUniformiv, "glGetnUniformiv"));
        DAWN_TRY(LoadProc(getProc, &GetnUniformuiv, "glGetnUniformuiv"));
        DAWN_TRY(LoadProc(getProc, &ReadnPixels, "glReadnPixels"));
        DAWN_TRY(LoadProc(getProc, &GetnMapdv, "glGetnMapdv"));
        DAWN_TRY(LoadProc(getProc, &GetnMapfv, "glGetnMapfv"));
        DAWN_TRY(LoadProc(getProc, &GetnMapiv, "glGetnMapiv"));
        DAWN_TRY(LoadProc(getProc, &GetnPixelMapfv, "glGetnPixelMapfv"));
        DAWN_TRY(LoadProc(getProc, &GetnPixelMapuiv, "glGetnPixelMapuiv"));
        DAWN_TRY(LoadProc(getProc, &GetnPixelMapusv, "glGetnPixelMapusv"));
        DAWN_TRY(LoadProc(getProc, &GetnPolygonStipple, "glGetnPolygonStipple"));
        DAWN_TRY(LoadProc(getProc, &GetnColorTable, "glGetnColorTable"));
        DAWN_TRY(LoadProc(getProc, &GetnConvolutionFilter, "glGetnConvolutionFilter"));
        DAWN_TRY(LoadProc(getProc, &GetnSeparableFilter, "glGetnSeparableFilter"));
        DAWN_TRY(LoadProc(getProc, &GetnHistogram, "glGetnHistogram"));
        DAWN_TRY(LoadProc(getProc, &GetnMinmax, "glGetnMinmax"));
        DAWN_TRY(LoadProc(getProc, &TextureBarrier, "glTextureBarrier"));
    }

    // Desktop OpenGL 4.6
    if (majorVersion > 4 || (majorVersion == 4 && minorVersion >= 6)) {
        DAWN_TRY(LoadProc(getProc, &SpecializeShader, "glSpecializeShader"));
        DAWN_TRY(LoadProc(getProc, &MultiDrawArraysIndirectCount, "glMultiDrawArraysIndirectCount"));
        DAWN_TRY(LoadProc(getProc, &MultiDrawElementsIndirectCount, "glMultiDrawElementsIndirectCount"));
        DAWN_TRY(LoadProc(getProc, &PolygonOffsetClamp, "glPolygonOffsetClamp"));
    }


    InitializeSupportedGLExtensions();

    // GL_EXT_texture_compression_s3tc
    if (IsGLExtensionSupported("GL_EXT_texture_compression_s3tc")) {
    }

    return {};
}

void OpenGLFunctionsBase::InitializeSupportedGLExtensions() {
    int32_t numExtensions;
    GetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);

    for (int32_t i = 0; i < numExtensions; ++i) {
        const char* extensionName = reinterpret_cast<const char*>(GetStringi(GL_EXTENSIONS, i));
        mSupportedGLExtensionsSet.insert(extensionName);
    }
}

bool OpenGLFunctionsBase::IsGLExtensionSupported(const char* extension) const {
    ASSERT(extension != nullptr);
    return mSupportedGLExtensionsSet.count(extension) != 0;
}

}  // namespace dawn::native::opengl
