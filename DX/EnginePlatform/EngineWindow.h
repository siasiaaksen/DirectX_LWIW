#pragma once
#include <EngineBase/EngineDefine.h>


class EngineWindow
{
public:
	ENGINEAPI EngineWindow();
	ENGINEAPI ~EngineWindow();

	EngineWindow(const EngineWindow& _Other) = delete;
	EngineWindow(EngineWindow&& _Other) noexcept = delete;
	EngineWindow& operator=(const EngineWindow& _Other) = delete;
	EngineWindow& operator=(EngineWindow&& _Other) noexcept = delete;

protected:

private:

};

