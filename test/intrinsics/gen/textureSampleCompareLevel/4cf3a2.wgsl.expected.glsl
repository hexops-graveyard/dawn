SKIP: FAILED

#version 310 es
precision mediump float;

uniform highp samplerCubeArrayShadow arg_0_arg_1;

void textureSampleCompareLevel_4cf3a2() {
  float res = texture(arg_0_arg_1, vec4(0.0f, 0.0f, 0.0f, float(1)), 1.0f);
}

vec4 vertex_main() {
  textureSampleCompareLevel_4cf3a2();
  return vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

void main() {
  vec4 inner_result = vertex_main();
  gl_Position = inner_result;
  gl_Position.y = -(gl_Position.y);
  gl_Position.z = ((2.0f * gl_Position.z) - gl_Position.w);
  return;
}
Error parsing GLSL shader:
ERROR: 0:4: 'samplerCubeArrayShadow' : Reserved word. 
ERROR: 0:4: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



#version 310 es
precision mediump float;

uniform highp samplerCubeArrayShadow arg_0_arg_1;

void textureSampleCompareLevel_4cf3a2() {
  float res = texture(arg_0_arg_1, vec4(0.0f, 0.0f, 0.0f, float(1)), 1.0f);
}

void fragment_main() {
  textureSampleCompareLevel_4cf3a2();
}

void main() {
  fragment_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:4: 'samplerCubeArrayShadow' : Reserved word. 
ERROR: 0:4: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



#version 310 es
precision mediump float;

uniform highp samplerCubeArrayShadow arg_0_arg_1;

void textureSampleCompareLevel_4cf3a2() {
  float res = texture(arg_0_arg_1, vec4(0.0f, 0.0f, 0.0f, float(1)), 1.0f);
}

void compute_main() {
  textureSampleCompareLevel_4cf3a2();
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  compute_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:4: 'samplerCubeArrayShadow' : Reserved word. 
ERROR: 0:4: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



