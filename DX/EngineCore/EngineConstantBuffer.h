#pragma once
#include "EngineResources.h"
#include "EngineDeviceBuffer.h"


class UEngineConstantBuffer : public UEngineResources, public UEngineDeviceBuffer
{
public:
	UEngineConstantBuffer();
	~UEngineConstantBuffer();

	UEngineConstantBuffer(const UEngineConstantBuffer& _Other) = delete;
	UEngineConstantBuffer(UEngineConstantBuffer&& _Other) noexcept = delete;
	UEngineConstantBuffer& operator=(const UEngineConstantBuffer& _Other) = delete;
	UEngineConstantBuffer& operator=(UEngineConstantBuffer&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineConstantBuffer> CreateOrFind(int _Byte, const std::string_view& _Name);

protected:

private:
	static std::map<int, std::map<std::string, std::shared_ptr<UEngineConstantBuffer>>> BufferMap;

	void ResCreate();
};

