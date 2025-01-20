#pragma once
#include "EngineResources.h"
#include "EngineDeviceBuffer.h"
#include "EngineEnums.h"


class UEngineStructuredBuffer
{
public:
	UEngineStructuredBuffer();
	~UEngineStructuredBuffer();

	UEngineStructuredBuffer(const UEngineStructuredBuffer& _Other) = delete;
	UEngineStructuredBuffer(UEngineStructuredBuffer&& _Other) noexcept = delete;
	UEngineStructuredBuffer& operator=(const UEngineStructuredBuffer& _Other) = delete;
	UEngineStructuredBuffer& operator=(UEngineStructuredBuffer&& _Other) noexcept = delete;

protected:

private:
};

