#pragma once
#include "EngineShaderResources.h"
#include "Mesh.h"
#include "EngineMaterial.h"


class URenderUnit
{
public:
	URenderUnit();
	~URenderUnit();

	URenderUnit(const URenderUnit& _Other) = delete;
	URenderUnit(URenderUnit&& _Other) noexcept = delete;
	URenderUnit& operator=(const URenderUnit& _Other) = delete;
	URenderUnit& operator=(URenderUnit&& _Other) noexcept = delete;

	// 매쉬(육체) 
	std::shared_ptr<UMesh> Mesh;
	// 머티리얼(피부)
	std::shared_ptr<UEngineMaterial> Material;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayOut;

	ENGINEAPI void SetMesh(std::string_view _Name);
	ENGINEAPI void SetMaterial(std::string_view _Name);

	ENGINEAPI virtual void Render(class UEngineCamera* _Camera, float _DeltaTime);

protected:

private:
	UEngineConstantBufferRes Res;

	void InputLayOutCreate();
};

