#pragma once
#include "EngineConstantBuffer.h"


class UEngineConstantBufferRes
{
public:
	void* Data;
	UINT BufferSize;
	std::shared_ptr<UEngineConstantBuffer> Res;
};


class UEngineShaderResources
{
public:
	UEngineShaderResources();
	~UEngineShaderResources();

	UEngineShaderResources(const UEngineShaderResources& _Other) = delete;
	UEngineShaderResources(UEngineShaderResources&& _Other) noexcept = delete;
	UEngineShaderResources& operator=(const UEngineShaderResources& _Other) = delete;
	UEngineShaderResources& operator=(UEngineShaderResources&& _Other) noexcept = delete;

	void CreateConstantBufferRes(std::string_view Name, UEngineConstantBufferRes Res);

protected:

private:
	std::map<std::string, UEngineConstantBufferRes> ConstantBufferRess;
};

