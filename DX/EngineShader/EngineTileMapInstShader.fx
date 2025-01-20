
struct EngineVertex
{
    //                 시맨틱
    float4 POSITION : POSITION;
	float4 UV : TEXCOORD;
    float4 COLOR : COLOR;
	uint iInstance : SV_InstanceID;
};

struct VertexShaderOutPut
{
    float4 SVPOSITION : SV_POSITION;
    float4 UV : TEXCOORD;
    float4 COLOR : COLOR;
};

struct FTransform
{
	// 변환용 벨류
    float4 Scale;
    float4 Rotation;
    float4 Quat;
    float4 Location;

	// 릴레이티브 로컬
    float4 RelativeScale;
    float4 RelativeRotation;
    float4 RelativeQuat;
    float4 RelativeLocation;

	// 월드
    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldQuat;
    float4 WorldLocation;

    float4x4 ScaleMat;
    float4x4 RotationMat;
    float4x4 LocationMat;
    float4x4 RevolveMat;
    float4x4 ParentMat;
    float4x4 LocalWorld;
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
    float4x4 WVP;
};

struct FSpriteData
{
    float4 CuttingPos;
    float4 CuttingSize;
	float4 Pivot;
};

StructuredBuffer<FTransform> TileMapInstTransformBuffer : register(t0);

StructuredBuffer<FSpriteData> TileMapInstSpriteBuffer : register(t1);

VertexShaderOutPut TileMapInst_VS(EngineVertex _Vertex)
{
    VertexShaderOutPut OutPut;
    
    int Index = _Vertex.iInstance;
	
    _Vertex.POSITION.x += (1.0f - TileMapInstSpriteBuffer[Index].Pivot.x) - 0.5f;
    _Vertex.POSITION.y += (1.0f - TileMapInstSpriteBuffer[Index].Pivot.y) - 0.5f;
	
    OutPut.SVPOSITION = mul(_Vertex.POSITION, TileMapInstTransformBuffer[Index].WVP);
	
    OutPut.UV = _Vertex.UV;
    OutPut.UV.x = (_Vertex.UV.x * TileMapInstSpriteBuffer[Index].CuttingSize.x) + TileMapInstSpriteBuffer[Index].CuttingPos.x;
    OutPut.UV.y = (_Vertex.UV.y * TileMapInstSpriteBuffer[Index].CuttingSize.y) + TileMapInstSpriteBuffer[Index].CuttingPos.y;
	
    OutPut.COLOR = _Vertex.COLOR;
    
    return OutPut;
}

Texture2D TileMapTex : register(t0);

SamplerState ImageSampler : register(s0);

cbuffer ResultColor : register(b0)
{
    float4 PlusColor;
    float4 MulColor;
};

float4 TileMapInst_PS(VertexShaderOutPut _Vertex) : SV_Target0
{
    float4 Color = TileMapTex.Sample(ImageSampler, _Vertex.UV.xy);

    if (0.0f >= Color.a)
    {
		// 픽셀쉐이더에서 아웃풋 머저로 넘기지 않음
        clip(-1);
    }
    
    Color += PlusColor;
    Color *= MulColor;
    return Color;
}