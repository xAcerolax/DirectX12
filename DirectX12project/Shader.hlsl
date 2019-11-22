/RootSignature�̒�`
//���[�g����
#define RS "RootFlags(ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT),"\
							"DescriptorTable(CBV(b0, numDescriptors = 1, space = 0, offset = 0, offset = DESCRIPTOR_RANGE_OFFSET_APPEND),"\
							"visibility = SHADER_VISIBILITY_ALL),"\
							"DescriptorTable(CBV(b1, numDescriptors = 1, space = 0, offset = 0, offset = DESCRIPTOR_RANGE_OFFSET_APPEND),"\
							"visibility = SHADER_VISIBILITY_ALL),"\
							"DescriptorTable(SRV(t0, numDescriptors = 1, space = 0, offset = 0, offset = DESCRIPTOR_RANGE_OFFSET_APPEND),"\
							"visibility = SHADER_VISIBILITY_ALL),"\
							"StaticSampler(s0,"\
											  "filter = FILTER_MIN_MAG_MIP_LINEAR,"\
											  "addressU = TEXTURE_ADDRESS_WRAP,"\
											  "addressV = TEXTURE_ADDRESS_WRAP,"\
											  "addressW = TEXTURE_ADDRESS_WRAP,"\
											  "mipLodBias = 0.0f,"\
											  "maxAnisotropy = 0,"\
											  "comparisonFunc = COMPARISON_NEVER,"\
											  "borderColor = STATIC_BODER_COLOR_TRANSPARENT_BLACK,"\
											  "minLOD = 0.0f,"\
											  "maxLOD = 3.402823466+38f,"\
											  "space  = 0,"\
											  "visibility = SHADER_VISIBILITY_ALL,"\
											  ")"\
//��`�͂����܂�


//ConstantBuffer (b0)
cbuffer Window : register(b0)
{
	float2 windowSize;
}

//ConstantBuffer (b1)
cbuffer Info : register(b1)
{
	float2 size;
	float2 reverse;
	float angle;
	float alpha;
}


//Texture(t0)
Texture2D<float4> tex: register(t0);

//Static Sampler (s0)
SamplerState smp : register(s0);


//����
struct Input
{
	float4 pos : POSITION;
	float2 uv : TEXCOORD;
};

//�o��
struct Out
{
	float4 svpos : SV_POSITION;
	float4 pos : POSITION;
	float2 uv : TEXCOORD;
};
