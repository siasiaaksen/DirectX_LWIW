#include "PreCompile.h"
#include "LWIWContentsCore.h"
#include <EngineCore/Level.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/HUD.h>
#include "ContentsEditorGUI.h"
#include "TitleGameMode.h"
#include "PlayGameMode.h"
#include "MapEditorMode.h"
#include "Ellie.h"


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

	LWIWResourcesSetting();

	UEngineCore::CreateLevel<ATitleGameMode, APawn, AHUD>("TitleLevel");
	UEngineCore::CreateLevel<APlayGameMode, AEllie, AHUD>("PlayLevel");
	UEngineCore::CreateLevel<AMapEditorMode, APawn, AHUD>("MapEditorLevel");
	UEngineCore::OpenLevel("PlayLevel");

	UEngineGUI::AllWindowOff();

	UEngineGUI::CreateGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");
	std::shared_ptr<UContentsEditorGUI> Window = UEngineGUI::FindGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");
	Window->SetActive(true);
}

void ULWIWContentsCore::EngineTick(float _DeltaTime)
{
}

void ULWIWContentsCore::EngineEnd()
{
}