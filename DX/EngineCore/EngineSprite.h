#pragma once
#include "EngineTexture.h"
#include <EngineBase/EngineMath.h>
#include "EngineResources.h"


struct FSpriteData
{
	float4 CuttingPos = { 0.0f, 0.0f };
	float4 CuttingSize = { 1.0f, 1.0f };
	float4 Pivot = { 0.5f, 0.5f };
};


class UEngineSprite : public UEngineResources
{
public:
	UEngineSprite();
	~UEngineSprite();

	UEngineSprite(const UEngineSprite& _Other) = delete;
	UEngineSprite(UEngineSprite&& _Other) noexcept = delete;
	UEngineSprite& operator=(const UEngineSprite& _Other) = delete;
	UEngineSprite& operator=(UEngineSprite&& _Other) noexcept = delete;

	ENGINEAPI static std::shared_ptr<UEngineSprite> CreateSpriteToMeta(std::string_view _Name, std::string_view _DataFileExt);

	ENGINEAPI ID3D11ShaderResourceView* GetSRV();

	ENGINEAPI FSpriteData GetSpriteData(size_t _Index)
	{
		if (SpriteDatas.size() <= _Index)
		{
			MSGASSERT("��������Ʈ�� �ε����� �ʰ��Ͽ� ����Ϸ��� �߽��ϴ�.");
		}

		return SpriteDatas[_Index];
	}

	ENGINEAPI FVector GetSpriteScaleToReal(size_t _Index);

protected:

private:
	UEngineTexture* Texture;
	std::vector<FSpriteData> SpriteDatas;
};

