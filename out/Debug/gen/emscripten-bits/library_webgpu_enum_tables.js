    AddressMode: [
      'repeat',
      'mirror-repeat',
      'clamp-to-edge',
    ],
    BlendFactor: [
      'zero',
      'one',
      'src',
      'one-minus-src',
      'src-alpha',
      'one-minus-src-alpha',
      'dst',
      'one-minus-dst',
      'dst-alpha',
      'one-minus-dst-alpha',
      'src-alpha-saturated',
      'constant',
      'one-minus-constant',
    ],
    BlendOperation: [
      'add',
      'subtract',
      'reverse-subtract',
      'min',
      'max',
    ],
    BufferBindingType: [
      undefined,
      'uniform',
      'storage',
      'read-only-storage',
    ],
    BufferMapState: [
      'unmapped',
      'pending',
      'mapped',
    ],
    CompareFunction: [
      undefined,
      'never',
      'less',
      'less-equal',
      'greater',
      'greater-equal',
      'equal',
      'not-equal',
      'always',
    ],
    CompilationInfoRequestStatus: [
      'success',
      'error',
      'device-lost',
      'unknown',
    ],
    ComputePassTimestampLocation: [
      'beginning',
      'end',
    ],
    CullMode: [
      'none',
      'front',
      'back',
    ],
    ErrorFilter: [
      'validation',
      'out-of-memory',
      'internal',
    ],
    FeatureName: [
      undefined,
      'depth-clip-control',
      'depth32float-stencil8',
      'timestamp-query',
      'pipeline-statistics-query',
      'texture-compression-bc',
      'texture-compression-etc2',
      'texture-compression-astc',
      'indirect-first-instance',
      'shader-f16',
      'rg11b10ufloat-renderable',
      'bgra8unorm-storage',
      'float32filterable',
    ],
    FilterMode: [
      'nearest',
      'linear',
    ],
    FrontFace: [
      'ccw',
      'cw',
    ],
    IndexFormat: [
      undefined,
      'uint16',
      'uint32',
    ],
    LoadOp: [
      undefined,
      'clear',
      'load',
    ],
    MipmapFilterMode: [
      'nearest',
      'linear',
    ],
    PipelineStatisticName: [
      'vertex-shader-invocations',
      'clipper-invocations',
      'clipper-primitives-out',
      'fragment-shader-invocations',
      'compute-shader-invocations',
    ],
    PowerPreference: [
      undefined,
      'low-power',
      'high-performance',
    ],
    PrimitiveTopology: [
      'point-list',
      'line-list',
      'line-strip',
      'triangle-list',
      'triangle-strip',
    ],
    QueryType: [
      'occlusion',
      'pipeline-statistics',
      'timestamp',
    ],
    RenderPassTimestampLocation: [
      'beginning',
      'end',
    ],
    SamplerBindingType: [
      undefined,
      'filtering',
      'non-filtering',
      'comparison',
    ],
    StencilOperation: [
      'keep',
      'zero',
      'replace',
      'invert',
      'increment-clamp',
      'decrement-clamp',
      'increment-wrap',
      'decrement-wrap',
    ],
    StorageTextureAccess: [
      undefined,
      'write-only',
    ],
    StoreOp: [
      undefined,
      'store',
      'discard',
    ],
    TextureAspect: [
      'all',
      'stencil-only',
      'depth-only',
    ],
    TextureDimension: [
      '1d',
      '2d',
      '3d',
    ],
    TextureFormat: [
      undefined,
      'r8unorm',
      'r8snorm',
      'r8uint',
      'r8sint',
      'r16uint',
      'r16sint',
      'r16float',
      'rg8unorm',
      'rg8snorm',
      'rg8uint',
      'rg8sint',
      'r32float',
      'r32uint',
      'r32sint',
      'rg16uint',
      'rg16sint',
      'rg16float',
      'rgba8unorm',
      'rgba8unorm-srgb',
      'rgba8snorm',
      'rgba8uint',
      'rgba8sint',
      'bgra8unorm',
      'bgra8unorm-srgb',
      'rgb10a2unorm',
      'rg11b10ufloat',
      'rgb9e5ufloat',
      'rg32float',
      'rg32uint',
      'rg32sint',
      'rgba16uint',
      'rgba16sint',
      'rgba16float',
      'rgba32float',
      'rgba32uint',
      'rgba32sint',
      'stencil8',
      'depth16unorm',
      'depth24plus',
      'depth24plus-stencil8',
      'depth32float',
      'depth32float-stencil8',
      'bc1-rgba-unorm',
      'bc1-rgba-unorm-srgb',
      'bc2-rgba-unorm',
      'bc2-rgba-unorm-srgb',
      'bc3-rgba-unorm',
      'bc3-rgba-unorm-srgb',
      'bc4-r-unorm',
      'bc4-r-snorm',
      'bc5-rg-unorm',
      'bc5-rg-snorm',
      'bc6h-rgb-ufloat',
      'bc6h-rgb-float',
      'bc7-rgba-unorm',
      'bc7-rgba-unorm-srgb',
      'etc2-rgb8unorm',
      'etc2-rgb8unorm-srgb',
      'etc2-rgb8a1unorm',
      'etc2-rgb8a1unorm-srgb',
      'etc2-rgba8unorm',
      'etc2-rgba8unorm-srgb',
      'eac-r11unorm',
      'eac-r11snorm',
      'eac-rg11unorm',
      'eac-rg11snorm',
      'astc-4x4-unorm',
      'astc-4x4-unorm-srgb',
      'astc-5x4-unorm',
      'astc-5x4-unorm-srgb',
      'astc-5x5-unorm',
      'astc-5x5-unorm-srgb',
      'astc-6x5-unorm',
      'astc-6x5-unorm-srgb',
      'astc-6x6-unorm',
      'astc-6x6-unorm-srgb',
      'astc-8x5-unorm',
      'astc-8x5-unorm-srgb',
      'astc-8x6-unorm',
      'astc-8x6-unorm-srgb',
      'astc-8x8-unorm',
      'astc-8x8-unorm-srgb',
      'astc-10x5-unorm',
      'astc-10x5-unorm-srgb',
      'astc-10x6-unorm',
      'astc-10x6-unorm-srgb',
      'astc-10x8-unorm',
      'astc-10x8-unorm-srgb',
      'astc-10x10-unorm',
      'astc-10x10-unorm-srgb',
      'astc-12x10-unorm',
      'astc-12x10-unorm-srgb',
      'astc-12x12-unorm',
      'astc-12x12-unorm-srgb',
    ],
    TextureSampleType: [
      undefined,
      'float',
      'unfilterable-float',
      'depth',
      'sint',
      'uint',
    ],
    TextureViewDimension: [
      undefined,
      '1d',
      '2d',
      '2d-array',
      'cube',
      'cube-array',
      '3d',
    ],
    VertexFormat: [
      undefined,
      'uint8x2',
      'uint8x4',
      'sint8x2',
      'sint8x4',
      'unorm8x2',
      'unorm8x4',
      'snorm8x2',
      'snorm8x4',
      'uint16x2',
      'uint16x4',
      'sint16x2',
      'sint16x4',
      'unorm16x2',
      'unorm16x4',
      'snorm16x2',
      'snorm16x4',
      'float16x2',
      'float16x4',
      'float32',
      'float32x2',
      'float32x3',
      'float32x4',
      'uint32',
      'uint32x2',
      'uint32x3',
      'uint32x4',
      'sint32',
      'sint32x2',
      'sint32x3',
      'sint32x4',
    ],
    VertexStepMode: [
      'vertex',
      'instance',
      undefined,
    ],
