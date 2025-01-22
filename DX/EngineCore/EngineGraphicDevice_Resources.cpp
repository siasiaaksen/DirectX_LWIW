#include "PreCompile.h"
#include "EngineGraphicDevice.h"
#include "EngineVertex.h"
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "Mesh.h"
#include "EngineBlend.h"
#include "EngineShader.h"
#include "EngineMaterial.h"
#include "EngineTexture.h"
#include "EngineFont.h"
#include "EngineDepthStencilState.h"


void UEngineGraphicDevice::DefaultResourcesInit()
{
	DepthStencilInit();
	TextureInit();
	MeshInit();
	BlendInit();
	RasterizerStateInit();
	ShaderInit();
	MaterialInit();

	// ��Ʈ �ε�
	UEngineFont::Load("SDSamliphopangcheTTFBasic", "SDSamliphopangcheTTFBasic");
}

void UEngineGraphicDevice::DepthStencilInit()
{
	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
		Desc.DepthEnable = true;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		// ���̰��� �� ������ ���
		Desc.DepthFunc = D3D11_COMPARISON_LESS;
		Desc.StencilEnable = false;

		UEngineDepthStencilState::Create("BaseDepth", Desc);
	}

	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
		Desc.DepthEnable = false;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_LESS;
		Desc.StencilEnable = false;

		UEngineDepthStencilState::Create("UIDepth", Desc);
	}

	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
		Desc.DepthEnable = true;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
		Desc.StencilEnable = false;

		UEngineDepthStencilState::Create("CollisionDebugDepth", Desc);
	}

	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
		Desc.DepthEnable = true;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
		Desc.StencilEnable = false;

		UEngineDepthStencilState::Create("TargetMerge", Desc);
	}
}

void UEngineGraphicDevice::TextureInit()
{

	D3D11_SAMPLER_DESC SampInfo = { D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT };
	SampInfo.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	SampInfo.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	SampInfo.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;

	SampInfo.BorderColor[0] = 0.0f;
	SampInfo.BorderColor[1] = 0.0f;
	SampInfo.BorderColor[2] = 0.0f;
	SampInfo.BorderColor[3] = 0.0f;

	UEngineSampler::Create("WRAPSampler", SampInfo);

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("EngineShader"))
		{
			MSGASSERT("EngineShader ������ ã�� ���߽��ϴ�.");
			return;
		}
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}
	}
}

void UEngineGraphicDevice::ShaderInit()
{
	UEngineDirectory CurDir;
	CurDir.MoveParentToDirectory("EngineShader");

	std::vector<UEngineFile> ShaderFiles = CurDir.GetAllFile(true, { ".fx", ".hlsl" });

	for (size_t i = 0; i < ShaderFiles.size(); i++)
	{
		UEngineShader::ReflectionCompile(ShaderFiles[i]);
	}
}

void UEngineGraphicDevice::MeshInit()
{
	{
		std::vector<FEngineVertex> Vertexs;
		Vertexs.resize(4);
		Vertexs[0] = FEngineVertex{ FVector(-0.5f, 0.5f, 0.0f), {0.0f , 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f} };
		Vertexs[1] = FEngineVertex{ FVector(0.5f, 0.5f, 0.0f), {1.0f , 0.0f } , {0.0f, 1.0f, 0.0f, 1.0f} };
		Vertexs[2] = FEngineVertex{ FVector(-0.5f, -0.5f, 0.0f), {0.0f , 1.0f } , {0.0f, 0.0f, 1.0f, 1.0f} };
		Vertexs[3] = FEngineVertex{ FVector(0.5f, -0.5f, 0.0f), {1.0f , 1.0f } , {1.0f, 1.0f, 1.0f, 1.0f} };

		UEngineVertexBuffer::Create("Rect", Vertexs);
	}

	{
		std::vector<unsigned int> Indexs;

		Indexs.push_back(0);
		Indexs.push_back(1);
		Indexs.push_back(2);

		Indexs.push_back(1);
		Indexs.push_back(3);
		Indexs.push_back(2);

		UEngineIndexBuffer::Create("Rect", Indexs);
	}

	{
		std::vector<FEngineVertex> Vertexs;
		Vertexs.resize(4);
		Vertexs[0] = FEngineVertex{ FVector(-1.0f, 1.0f, 0.0f), {0.0f , 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f} };
		Vertexs[1] = FEngineVertex{ FVector(1.0f, 1.0f, 0.0f), {1.0f , 0.0f } , {0.0f, 1.0f, 0.0f, 1.0f} };
		Vertexs[2] = FEngineVertex{ FVector(-1.0f, -1.0f, 0.0f), {0.0f , 1.0f } , {0.0f, 0.0f, 1.0f, 1.0f} };
		Vertexs[3] = FEngineVertex{ FVector(1.0f, -1.0f, 0.0f), {1.0f , 1.0f } , {1.0f, 1.0f, 1.0f, 1.0f} };

		UEngineVertexBuffer::Create("FullRect", Vertexs);
	}

	{
		UMesh::Create("Rect");

		UMesh::Create("FullRect", "FullRect", "Rect");
	}

	{
		std::vector<FEngineVertex> Vertex;
		Vertex.resize(24);
		// �ո�
		Vertex[0] = { float4(-0.5f, 0.5f, 0.5f) , float4(0.0f, 0.0f), float4::RED, float4(0.0f, 0.0f, 1.0f) };
		Vertex[1] = { float4(0.5f, 0.5f, 0.5f)  , float4(1.0f, 0.0f), float4::RED, float4(0.0f, 0.0f, 1.0f) };
		Vertex[2] = { float4(0.5f, -0.5f, 0.5f) , float4(1.0f, 1.0f), float4::RED, float4(0.0f, 0.0f, 1.0f) };
		Vertex[3] = { float4(-0.5f, -0.5f, 0.5f), float4(0.0f, 1.0f), float4::RED, float4(0.0f, 0.0f, 1.0f) };

		// �޸�
		Vertex[4] = { float4(-0.5f, 0.5f, 0.5f).RotationXDegReturn(180) , float4(0.0f, 0.0f), float4::RED, float4(0.0f, 0.0f, -1.0f) };
		Vertex[5] = { float4(0.5f, 0.5f, 0.5f).RotationXDegReturn(180)  , float4(1.0f, 0.0f), float4::RED, float4(0.0f, 0.0f, -1.0f) };
		Vertex[6] = { float4(0.5f, -0.5f, 0.5f).RotationXDegReturn(180) , float4(1.0f, 1.0f), float4::RED, float4(0.0f, 0.0f, -1.0f) };
		Vertex[7] = { float4(-0.5f, -0.5f, 0.5f).RotationXDegReturn(180), float4(0.0f, 1.0f), float4::RED, float4(0.0f, 0.0f, -1.0f) };

		// ����
		Vertex[8] = { float4(-0.5f, 0.5f, 0.5f).RotationYDegReturn(-90) , float4(0.0f, 0.0f), float4::RED, float4(1.0f, 0.0f, 0.0f) };
		Vertex[9] = { float4(0.5f, 0.5f, 0.5f).RotationYDegReturn(-90)  , float4(1.0f, 0.0f), float4::RED, float4(1.0f, 0.0f, 0.0f) };
		Vertex[10] = { float4(0.5f, -0.5f, 0.5f).RotationYDegReturn(-90) , float4(1.0f, 1.0f), float4::RED, float4(1.0f, 0.0f, 0.0f) };
		Vertex[11] = { float4(-0.5f, -0.5f, 0.5f).RotationYDegReturn(-90), float4(0.0f, 1.0f), float4::RED, float4(1.0f, 0.0f, 0.0f) };

		// ������
		Vertex[12] = { float4(-0.5f, 0.5f, 0.5f).RotationYDegReturn(90) , float4(0.0f, 0.0f), float4::RED, float4(-1.0f, 0.0f, 0.0f) };
		Vertex[13] = { float4(0.5f, 0.5f, 0.5f).RotationYDegReturn(90)  , float4(1.0f, 0.0f), float4::RED, float4(-1.0f, 0.0f, 0.0f) };
		Vertex[14] = { float4(0.5f, -0.5f, 0.5f).RotationYDegReturn(90) , float4(1.0f, 1.0f), float4::RED, float4(-1.0f, 0.0f, 0.0f) };
		Vertex[15] = { float4(-0.5f, -0.5f, 0.5f).RotationYDegReturn(90), float4(0.0f, 1.0f), float4::RED, float4(-1.0f, 0.0f, 0.0f) };


		// ��
		Vertex[16] = { float4(-0.5f, 0.5f, 0.5f).RotationXDegReturn(-90) , float4(0.0f, 0.0f), float4::RED, float4(0.0f, 1.0f, 0.0f) };
		Vertex[17] = { float4(0.5f, 0.5f, 0.5f).RotationXDegReturn(-90)  , float4(1.0f, 0.0f), float4::RED, float4(0.0f, 1.0f, 0.0f) };
		Vertex[18] = { float4(0.5f, -0.5f, 0.5f).RotationXDegReturn(-90) , float4(1.0f, 1.0f), float4::RED, float4(0.0f, 1.0f, 0.0f) };
		Vertex[19] = { float4(-0.5f, -0.5f, 0.5f).RotationXDegReturn(-90), float4(0.0f, 1.0f), float4::RED, float4(0.0f, 1.0f, 0.0f) };

		// �Ʒ�
		Vertex[20] = { float4(-0.5f, 0.5f, 0.5f).RotationXDegReturn(90) , float4(0.0f, 0.0f), float4::RED, float4(1.0f, -1.0f, 0.0f) };
		Vertex[21] = { float4(0.5f, 0.5f, 0.5f).RotationXDegReturn(90)  , float4(1.0f, 0.0f), float4::RED, float4(1.0f, -1.0f, 0.0f) };
		Vertex[22] = { float4(0.5f, -0.5f, 0.5f).RotationXDegReturn(90) , float4(1.0f, 1.0f), float4::RED, float4(1.0f, -1.0f, 0.0f) };
		Vertex[23] = { float4(-0.5f, -0.5f, 0.5f).RotationXDegReturn(90), float4(0.0f, 1.0f), float4::RED, float4(1.0f, -1.0f, 0.0f) };


		UEngineVertexBuffer::Create("Box", Vertex);
	}

	{
		std::vector<int> Index;
		for (int i = 0; i < 6; i++)
		{
			Index.push_back(i * 4 + 2);
			Index.push_back(i * 4 + 1);
			Index.push_back(i * 4 + 0);

			Index.push_back(i * 4 + 3);
			Index.push_back(i * 4 + 2);
			Index.push_back(i * 4 + 0);
		}


		UEngineIndexBuffer::Create("Box", Index);
		UMesh::Create("Box", "Box", "Box");
	}


	// Sphere
	{
		FEngineVertex V;
		std::vector<FEngineVertex> VBVector;
		std::vector<UINT> IBVector;

		float Radius = 0.5f;
		// �ϱ���
		V.POSITION = float4(0.0f, Radius, 0.0f, 1.0f);
		V.TEXCOORD = float4(0.5f, 0.0f);
		V.NORMAL = float4(0.0f, Radius, 0.0f, 1.0f);
		V.NORMAL.Normalize();
		V.NORMAL.W = 0.0f;
		V.TANGENT = float4(1.0f, 0.0f, 0.0f, 0.0f);
		V.BINORMAL = float4(0.0f, 0.0f, 1.0f, 0.0f);

		VBVector.push_back(V);

		UINT iStackCount = 16; 
		UINT iSliceCount = 16; 

		float yRotAngle = UEngineMath::PI / (float)iStackCount;
		float zRotAngle = UEngineMath::PI2 / (float)iSliceCount;

		float yUvRatio = 1.0f / (float)iStackCount;
		float zUvRatio = 1.0f / (float)iStackCount;

		for (UINT y = 1; y < iStackCount; ++y)
		{
			float phi = y * yRotAngle;
			for (UINT z = 0; z < iSliceCount + 1; ++z)
			{
				float theta = z * zRotAngle;
				V.POSITION = float4{
					Radius * sinf(y * yRotAngle) * cosf(z * zRotAngle),
					Radius * cosf(y * yRotAngle),
					Radius * sinf(y * yRotAngle) * sinf(z * zRotAngle),
					1.0f 
				};

				V.TEXCOORD = float4(yUvRatio * z, zUvRatio * y);
				V.NORMAL = V.POSITION.NormalizeReturn();
				V.NORMAL.W = 0.0f;

				V.TANGENT.X = -Radius * sinf(phi) * sinf(theta);
				V.TANGENT.Y = 0.0f;
				V.TANGENT.Z = Radius * sinf(phi) * cosf(theta);
				V.TANGENT = V.TANGENT.NormalizeReturn();
				V.TANGENT.W = 0.0f;

				V.BINORMAL = float4::Cross(V.TANGENT, V.NORMAL);
				V.BINORMAL = V.BINORMAL.NormalizeReturn();
				V.BINORMAL.W = 0.0f;

				VBVector.push_back(V);
			}
		}

		// ������
		V.POSITION = float4(0.0f, -Radius, 0.0f, 1.0f);
		V.TEXCOORD = float4(0.5f, 1.0f);
		V.NORMAL = float4(0.0f, -Radius, 0.0f, 1.0f);
		V.NORMAL.Normalize();
		V.NORMAL.W = 0.0f;
		V.TANGENT = float4(-1.0f, 0.0f, 0.0f, 0.0f);
		V.BINORMAL = float4(0.0f, 0.0f, -1.0f, 0.0f);
		VBVector.push_back(V);

		IBVector.clear();

		// �ϱ����� �̷�� ���� �����
		for (UINT i = 0; i < iSliceCount; i++)
		{
			// ������ ������ �ϱ���
			IBVector.push_back(0);
			IBVector.push_back(i + 2);
			IBVector.push_back(i + 1);
		}

		for (UINT y = 0; y < iStackCount - 2; y++)
		{
			for (UINT z = 0; z < iSliceCount; z++)
			{
				IBVector.push_back((iSliceCount + 1) * y + z + 1);
				IBVector.push_back((iSliceCount + 1) * (y + 1) + (z + 1) + 1);
				IBVector.push_back((iSliceCount + 1) * (y + 1) + z + 1);

				IBVector.push_back((iSliceCount + 1) * y + z + 1);
				IBVector.push_back((iSliceCount + 1) * y + (z + 1) + 1);
				IBVector.push_back((iSliceCount + 1) * (y + 1) + (z + 1) + 1);
			}
		}

		// ���������� ������ �ε���
		UINT iBotIndex = (UINT)VBVector.size() - 1;
		for (UINT i = 0; i < iSliceCount; i++)
		{
			// ������ ������ �ϱ���
			IBVector.push_back(iBotIndex);
			IBVector.push_back(iBotIndex - (i + 2));
			IBVector.push_back(iBotIndex - (i + 1));
		}

		UEngineVertexBuffer::Create("Sphere", VBVector);
		UEngineIndexBuffer::Create("Sphere", IBVector);

		UMesh::Create("Sphere");
	}
}

void UEngineGraphicDevice::BlendInit()
{
	D3D11_BLEND_DESC Desc = { 0 };

	Desc.AlphaToCoverageEnable = false;

	// 0�� �������� 8���� �� ������
	Desc.IndependentBlendEnable = true;
	Desc.RenderTarget[0].BlendEnable = true;
	Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	// �������
	// �˺����÷� = SrcColor (�ɼ�) SrcFactor (BlendOp) DestColor (�ɼ�) DestFactor  
	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	// SrcColor 1.0, 0.0f, 0.0f, 0.8f; * 0.8f 0.8f 0.8f 0.8f
	// DestColor 0.0, 0.0f, 1.0f, 1.0f; * 1 - 0.8f,  1 - 0.8f, 1 - 0.8f, 1 - 0.8f

	// ���� = SrcColor (�ɼ�) SrcFactor (BlendOp) DestColor (�ɼ�) DestFactor  
	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;
	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

	UEngineBlend::Create("AlphaBlend", Desc);
}

void UEngineGraphicDevice::RasterizerStateInit()
{
	{
		D3D11_RASTERIZER_DESC Desc = {};
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;

		UEngineRasterizerState::Create("EngineBase", Desc);
	}

	{
		D3D11_RASTERIZER_DESC Desc = {};
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;

		UEngineRasterizerState::Create("CollisionDebugRas", Desc);
	}
}

void UEngineGraphicDevice::MaterialInit()
{
	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("SpriteMaterial");
		Mat->SetVertexShader("EngineSpriteShader.fx");
		Mat->SetPixelShader("EngineSpriteShader.fx");
	}

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("WidgetMaterial");
		Mat->SetVertexShader("EngineSpriteShader.fx");
		Mat->SetPixelShader("EngineSpriteShader.fx");
		Mat->SetDepthStencilState("UIDepth");
	}

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("CollisionDebugMaterial");
		Mat->SetVertexShader("EngineDebugCollisionShader.fx");
		Mat->SetPixelShader("EngineDebugCollisionShader.fx");
		Mat->SetDepthStencilState("CollisionDebugDepth");
		Mat->SetRasterizerState("CollisionDebugRas");
	}

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("TileMap");
		Mat->SetVertexShader("EngineTileMapShader.fx");
		Mat->SetPixelShader("EngineTileMapShader.fx");
	}

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("TileMapInst");
		Mat->SetVertexShader("EngineTileMapInstShader.fx");
		Mat->SetPixelShader("EngineTileMapInstShader.fx");
	}

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("TargetMerge");
		Mat->SetVertexShader("EngineTargetMergeShader.fx");
		Mat->SetPixelShader("EngineTargetMergeShader.fx");
		Mat->SetDepthStencilState("TargetMerge");
	}
}