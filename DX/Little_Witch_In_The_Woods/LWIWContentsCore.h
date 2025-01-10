#pragma once
#include <EngineCore/IContentsCore.h>


class ULWIWContentsCore : public IContentsCore
{
public:
	ULWIWContentsCore();
	~ULWIWContentsCore();

	ULWIWContentsCore(const ULWIWContentsCore& _Other) = delete;
	ULWIWContentsCore(ULWIWContentsCore&& _Other) noexcept = delete;
	ULWIWContentsCore& operator=(const ULWIWContentsCore& _Other) = delete;
	ULWIWContentsCore& operator=(ULWIWContentsCore&& _Other) noexcept = delete;

protected:
	void EngineStart(UEngineInitData& _Data);
	void EngineTick(float _DeltaTime);
	void EngineEnd();

private:
	void LWIWResourcesSetting();
};

