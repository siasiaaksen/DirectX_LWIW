#include "PreCompile.h"
#include "ULWIWContentsCore.h"
#include <EngineCore/Level.h>
#include "TitleGameMode.h"


CreateContentsCoreDefine(ULWIWContentsCore);

ULWIWContentsCore::ULWIWContentsCore()
{
}

ULWIWContentsCore::~ULWIWContentsCore()
{
}

void ULWIWContentsCore::EngineStart(UEngineInitData& _Data)
{
	_Data.WindowPos = { 360, 100 };
	_Data.WindowSize = { 1280, 720 };

	UEngineCore::CreateLevel<ATitleGameMode, APawn>("Titlelevel");
	UEngineCore::OpenLevel("Titlelevel");
}

void ULWIWContentsCore::EngineTick(float _DeltaTime)
{
}

void ULWIWContentsCore::EngineEnd()
{
}