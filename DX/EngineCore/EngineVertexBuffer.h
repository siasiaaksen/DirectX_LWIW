#pragma once
#include "EngineResources.h"
#include "EngineDeviceBuffer.h"


class UEngineVertexBuffer : public UEngineResources, public UEngineDeviceBuffer
{
public:
	UEngineVertexBuffer();
	~UEngineVertexBuffer();

	UEngineVertexBuffer(const UEngineVertexBuffer& _Other) = delete;
	UEngineVertexBuffer(UEngineVertexBuffer&& _Other) noexcept = delete;
	UEngineVertexBuffer& operator=(const UEngineVertexBuffer& _Other) = delete;
	UEngineVertexBuffer& operator=(UEngineVertexBuffer&& _Other) noexcept = delete;

	template<typename VertexType>
	static std::shared_ptr<UEngineVertexBuffer> Create(std::string_view _Name, const std::vector<VertexType>& _VertexData)
	{
		return Create(_Name, reinterpret_cast<const void*>(&_VertexData[0]), sizeof(VertexType), _VertexData.size());
	}

	static std::shared_ptr<UEngineVertexBuffer> Create(std::string_view _Name, const void* _InitData, size_t _VertexSize, size_t _VertexCount);

	void Setting();

protected:
	void ResCreate(const void* _InitData, size_t _VertexSize, size_t _VertexCount);

private:
	UINT VertexSize = 0;
	UINT VertexCount = 0;
};

