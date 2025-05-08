float4x4	matWorld;
float4x4	matView;
float4x4	matProjection;
float4x4	matViewProjection;

float4		vColor;
float4		vScale;

Texture		InputTexture;

const	float3		LightDirection = float3(0, 1, -1);

sampler TextureSampler = sampler_state
{
    Texture = <InputTexture>;
    MinFilter = LINEAR;  
    MagFilter = LINEAR;
    MipFilter = LINEAR;
    
    AddressU = Wrap;
    AddressV = Wrap;
};

void	Vertex_Parse(
in	float4	inPosition	:	POSITION,
in	float3	inNormal	:	NORMAL,
in	float2	inTexCoord	:	TEXCOORD0,

out	float4	outPosition	:	POSITION,
out	float2	outTexCoord	:	TEXCOORD0,
out	float3	outNormal	:	TEXCOORD1)
{
	outPosition = mul(inPosition * vScale, matWorld);
	outPosition = mul(outPosition, mul(matView, matProjection));
	
	outNormal = normalize(mul(inNormal, matWorld));
	outTexCoord = inTexCoord;
}

void Pixel_Parse(
in	float2	inTexCoord	:	TEXCOORD0,
in	float3	inNormal	:	TEXCOORD1,

out	float4	outColor	:	COLOR)
{
	float	LightDotNormal = max(0.4f, dot(inNormal, LightDirection));
	outColor = vColor * tex2D(TextureSampler, inTexCoord);
	outColor.xyz *= LightDotNormal;
}

technique
{
	pass P0
	{
		VertexShader = compile vs_2_0	Vertex_Parse();
		PixelShader = compile ps_2_0	Pixel_Parse();
	}
}