#include "PreCompile.h"
#include "Renderer.h"
#include <EngineBase/EngineString.h>


URenderer::URenderer()
{
}

URenderer::~URenderer()
{
	VertexBuffer = nullptr;
	ShaderCodeBlob = nullptr;
	ErrorCodeBlob = nullptr;
}

void URenderer::SetOrder(int _Order)
{
	int PrevOrder = GetOrder();

	UObject::SetOrder(_Order);

	ULevel* Level = GetActor()->GetWorld();

	std::shared_ptr<URenderer> RendererPtr = GetThis<URenderer>();

	Level->ChangeRenderGroup(PrevOrder, RendererPtr);
}

ENGINEAPI void URenderer::BeginPlay()
{
	SetOrder(0);

	InputAssembler1Init();
	VertexShaderInit();
}

void URenderer::Render(float _DeltaTime)
{
	InputAssembler1Setting();
	VertexShaderSetting();
}

void URenderer::InputAssembler1Init()
{
	std::vector<EngineVertex> Vertexs;
	Vertexs.resize(6);

	Vertexs[0] = EngineVertex{ FVector(-0.5f, 0.5f, -0.5f), {} };
	Vertexs[1] = EngineVertex{ FVector(0.5f, 0.5f, -0.5f), {} };
	Vertexs[2] = EngineVertex{ FVector(-0.5f, -0.5f, -0.5f), {} };
	Vertexs[3] = EngineVertex{ FVector(0.5f, 0.5f, -0.5f), {} };
	Vertexs[4] = EngineVertex{ FVector(0.5f, -0.5f, -0.5f), {} };
	Vertexs[5] = EngineVertex{ FVector(-0.5f, -0.5f, -0.5f), {} };

	D3D11_BUFFER_DESC BufferInfo = { 0 };

	BufferInfo.ByteWidth = sizeof(EngineVertex) * static_cast<int>(Vertexs.size());
	// 용도는 버텍스 버퍼
	BufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// CPU에서 수정할수 있는지
	BufferInfo.CPUAccessFlags = 0;
	// 메모리 위치를 그래픽카드로 할거냐 cpu로 할건지
	BufferInfo.Usage = D3D11_USAGE_DEFAULT;

	// 초기값
	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = &Vertexs[0];

	if (S_OK != UEngineCore::Device.GetDevice()->CreateBuffer(&BufferInfo, &Data, &VertexBuffer))
	{
		MSGASSERT("버텍스 버퍼 생성에 실패했습니다.");
		return;
	}
}

void URenderer::InputAssembler1Setting()
{
	UINT VertexSize = sizeof(EngineVertex);
	UINT Offset = 0;

	UEngineCore::Device.GetContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &VertexSize, &Offset);
	UEngineCore::Device.GetContext()->IASetInputLayout(InputLayOut.Get());
}

void URenderer::InputAssembler1LayOut()
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> InputLayOutData;

	{
		D3D11_INPUT_ELEMENT_DESC Desc;
		Desc.SemanticName = "POSITION";
		Desc.InputSlot = 0;
		Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		Desc.AlignedByteOffset = 0;
		Desc.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
		Desc.SemanticIndex = 0;
		Desc.InstanceDataStepRate = 0;
		InputLayOutData.push_back(Desc);
	}

	{
		D3D11_INPUT_ELEMENT_DESC Desc;
		Desc.SemanticName = "COLOR";
		Desc.InputSlot = 0;
		Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		Desc.AlignedByteOffset = 16;
		Desc.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
		Desc.SemanticIndex = 0;
		Desc.InstanceDataStepRate = 0;
		InputLayOutData.push_back(Desc);
	}

	HRESULT Result = UEngineCore::Device.GetDevice()->CreateInputLayout(
		&InputLayOutData[0],
		InputLayOutData.size(),
		ShaderCodeBlob->GetBufferPointer(),
		ShaderCodeBlob->GetBufferSize(),
		&InputLayOut);

	if (S_OK != Result)
	{
		MSGASSERT("인풋 레이아웃 생성에 실패했습니다");
	}
}

void URenderer::VertexShaderInit()
{
	UEngineDirectory CurDir;
	CurDir.MoveParentToDirectory("EngineShader");
	UEngineFile File = CurDir.GetFile("EngineSpriteShader.fx");

	std::string Path = File.GetPathToString();

	std::wstring WPath = UEngineString::AnsiToUnicode(Path);

	std::string version = "vs_5_0";

	int Flag0 = 0;
	int Flag1 = 0;

#ifdef _DEBUG
	Flag0 = D3D10_SHADER_DEBUG;
#endif
	Flag0 |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	D3DCompileFromFile(
		WPath.c_str(),
		nullptr,
		nullptr,
		"VertexToWorld",
		version.c_str(),
		Flag0,
		Flag1,
		&ShaderCodeBlob,
		&ErrorCodeBlob
	);

	if (nullptr == ShaderCodeBlob)
	{
		std::string ErrString = reinterpret_cast<char*>(ErrorCodeBlob->GetBufferPointer());
		MSGASSERT("쉐이더 코드 중간빌드에서 실패했습니다\n" + ErrString);
		return;
	}

	HRESULT Result = UEngineCore::Device.GetDevice()->CreateVertexShader(
		ShaderCodeBlob->GetBufferPointer(),
		ShaderCodeBlob->GetBufferSize(),
		nullptr,
		&VertexShader
	);

	if (S_OK != Result)
	{
		MSGASSERT("버텍스 쉐이더 생성에 실패했습니다.");
	}

	InputAssembler1LayOut();
}

void URenderer::VertexShaderSetting()
{
	UEngineCore::Device.GetContext()->VSSetShader(VertexShader.Get(), nullptr, 0);
}

void URenderer::InputAssembler2Init()
{
}
void URenderer::InputAssembler2Setting()
{
}