#include "PreCompile.h"
#include "ULWIWContentsCore.h"
#include <EngineCore/Level.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>
#include "TitleGameMode.h"
#include "PlayGameMode.h"
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

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("LWIWResources\\Image"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}

		Dir.Append("Title");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}

		UEngineSprite::CreateSpriteToMeta("Title_Train_Sky.png", ".SData");
		UEngineSprite::CreateSpriteToMeta("Logo.png", ".SData");
		UEngineSprite::CreateSpriteToMeta("Title_Train_Moon.png", ".SData");
		UEngineSprite::CreateSpriteToMeta("Title_Train_Mountain.png", ".SData");
		UEngineSprite::CreateSpriteToMeta("Title_Train_Bridge.png", ".SData");
		UEngineSprite::CreateSpriteToMeta("Title_Train_Train.png", ".SData");
		UEngineSprite::CreateSpriteToMeta("Title_Train_TrainBlur.png", ".SData");
		UEngineSprite::CreateSpriteToMeta("Title_Train_Tree.png", ".SData");
		UEngineSprite::CreateSpriteToMeta("Title_Train_Star.png", ".SData");
		UEngineSprite::CreateSpriteToMeta("Title_Train_ShootingStar.png", ".SData");
	}

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("LWIWResources\\Image"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}

		Dir.Append("Play");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}

		UEngineSprite::CreateSpriteToMeta("Ellie_Walk.png", ".SData");
		UEngineSprite::CreateSpriteToMeta("Ellie_Idle.png", ".SData");
	}

	UEngineCore::CreateLevel<ATitleGameMode, APawn>("TitleLevel");
	UEngineCore::CreateLevel<APlayGameMode, AEllie>("PlayLevel");
	UEngineCore::OpenLevel("TitleLevel");
}

void ULWIWContentsCore::EngineTick(float _DeltaTime)
{
}

void ULWIWContentsCore::EngineEnd()
{
}