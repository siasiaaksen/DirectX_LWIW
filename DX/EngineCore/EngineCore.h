#pragma once
#include <EngineBase/EngineDefine.h>


class EngineCore
{
public:
	ENGINEAPI EngineCore();
	ENGINEAPI ~EngineCore();

	EngineCore(const EngineCore& _Other) = delete;
	EngineCore(EngineCore&& _Other) noexcept = delete;
	EngineCore& operator=(const EngineCore& _Other) = delete;
	EngineCore& operator=(EngineCore&& _Other) noexcept = delete;

protected:

private:

};

