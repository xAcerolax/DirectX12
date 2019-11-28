#include "Header.hlsli"

//シェーダに使用するRootSignatureをバインド
[RootSignature(RS)]
Out main(Input input)
{
	input.pos.xy = float2(-1.0f, 1.0f) + (input.pos.xy / float2((windowSize.x / 2.0f), -(windowSize.y / 2.0f)));

	
	Out o;
	o.svpos = input.pos;
	o.pos = input.pos;
	o.uv = input.uv;
	
	return o;
}
