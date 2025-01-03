#include "PreCompile.h"
#include "RenderUnit.h"


URenderUnit::URenderUnit()
{
}

URenderUnit::~URenderUnit()
{
}

void URenderUnit::SetMesh(std::string_view _Name)
{
	Mesh = UMesh::Find<UMesh>(_Name);

	if (nullptr == Mesh)
	{
		MSGASSERT("존재하지 않는 매쉬를 세팅하려고 했습니다.");
	}

	if (nullptr != Material)
	{
		InputLayOutCreate();
	}
}

void URenderUnit::SetMaterial(std::string_view _Name)
{
	Material = UEngineMaterial::Find<UEngineMaterial>(_Name);

	if (nullptr == Material)
	{
		MSGASSERT("존재하지 않는 머티리얼을를 세팅하려고 했습니다.");
	}

	if (nullptr != Mesh)
	{
		InputLayOutCreate();
	}
}

void URenderUnit::Render(class UEngineCamera* _Camera, float _DeltaTime)
{
	//	InputAssembler1Setting();
	Mesh->GetVertexBuffer()->Setting();

	//	VertexShaderSetting();
	Material->GetVertexShader()->Setting();

	//	InputAssembler2Setting();
	Mesh->GetIndexBuffer()->Setting();
	Material->PrimitiveTopologySetting();

	UEngineCore::GetDevice().GetContext()->IASetInputLayout(InputLayOut.Get());

	//	RasterizerSetting();
	Material->GetRasterizerState()->Setting();

	//	PixelShaderSetting();
	Material->GetPixelShader()->Setting();

	//	OutPutMergeSetting();
	Material->GetBlend()->Setting();
	ID3D11RenderTargetView* RTV = UEngineCore::GetDevice().GetRTV();
	ID3D11RenderTargetView* ArrRtv[16] = { 0 };
	ArrRtv[0] = RTV; 
	UEngineCore::GetDevice().GetContext()->OMSetRenderTargets(1, &ArrRtv[0], nullptr);
}

void URenderUnit::InputLayOutCreate()
{
	Microsoft::WRL::ComPtr<ID3DBlob> Blob = Material->GetVertexShader()->GetShaderCodeBlob();

	UEngineInputLayOutInfo* InfoPtr = Mesh->GetVertexBuffer()->GetInfoPtr();

	HRESULT Result = UEngineCore::GetDevice().GetDevice()->CreateInputLayout(
		&InfoPtr->InputLayOutData[0],
		static_cast<unsigned int>(InfoPtr->InputLayOutData.size()),
		Blob->GetBufferPointer(),
		Blob->GetBufferSize(),
		&InputLayOut);
}
