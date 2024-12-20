
struct EngineVertex
{
    float4 POSITION : POSITION;
    float4 COLOR : COLOR;
};

struct VertexShaderOutPut
{
    float4 SVPOSITION : SV_POSITION;
    float4 NEWPOSITION : POSITION;
    float4 COLOR : COLOR;
};

VertexShaderOutPut VertexToWorld(EngineVertex _Vertex)
{
    VertexShaderOutPut OutPut;

    OutPut.SVPOSITION = _Vertex.POSITION;
	OutPut.NEWPOSITION = _Vertex.POSITION;
    OutPut.COLOR = _Vertex.COLOR;
    
	return OutPut;
}

float4 PixelToWorld(VertexShaderOutPut _Vertex) : SV_Target0
{
    if (_Vertex.NEWPOSITION.x < 0)
    {
        return float4(0.9f, 0.5f, 0.1f, 1.0f);
    }
    else
    {
        return float4(0.1f, 0.5f, 0.9f, 1.0f);
    }

    return _Vertex.COLOR;
}