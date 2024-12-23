#pragma once
#include "EngineResources.h"

#include "ThirdParty/DirectxTex/Inc/DirectXTex.h"


class UEngineTexture : public UEngineResources<UEngineTexture>
{
public:
	ENGINEAPI UEngineTexture();
	ENGINEAPI ~UEngineTexture();

	UEngineTexture(const UEngineTexture& _Other) = delete;
	UEngineTexture(UEngineTexture&& _Other) noexcept = delete;
	UEngineTexture& operator=(const UEngineTexture& _Other) = delete;
	UEngineTexture& operator=(UEngineTexture&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineTexture> Load(std::string_view _Path)
	{
		UEnginePath EnginePath = UEnginePath(_Path);

		std::string FileName = EnginePath.GetFileName();

		return Load(FileName, _Path);
	}

	static std::shared_ptr<UEngineTexture> Load(std::string_view _Name, std::string_view _Path)
	{
		std::string UpperName = ToUpperName(_Name);

		if (true == Contains(UpperName))
		{
			MSGASSERT("�̹� �ε��� �ؽ�ó�� �� �ε��Ϸ��� �߽��ϴ�." + UpperName);
			return nullptr;
		}

		std::shared_ptr<UEngineTexture> NewTexture = MakeRes(_Name, _Path);
		NewTexture->ResLoad();
		return NewTexture;
	}

	ID3D11ShaderResourceView* GetSRV()
	{
		return SRV.Get();
	}

protected:

private:
	ENGINEAPI void ResLoad();

	Microsoft::WRL::ComPtr<ID3D11Texture2D> Texture2D = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> SRV = nullptr;
};

