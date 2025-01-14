#include "PreCompile.h"
#include "LWIWContentsCore.h"
#include <EngineCore/EngineGraphicDevice.h>
#include <EngineCore/EngineVertex.h>
#include <EngineCore/EngineIndexBuffer.h>
#include <EngineCore/Mesh.h>
#include <EngineCore/EngineBlend.h>
#include <EngineCore/EngineShader.h>
#include <EngineCore/EngineMaterial.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>


void ULWIWContentsCore::LWIWResourcesSetting()
{
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
		//UEngineSprite::CreateSpriteToMeta("Title_Train_Tree.png", ".SData");
		UEngineSprite::CreateSpriteToMeta("Title_Train_Star.png", ".SData");
		UEngineSprite::CreateSpriteToMeta("Title_Train_ShootingStar.png", ".SData");
		UEngineSprite::CreateSpriteToMeta("Title_Train_SmokeB.png", ".SData");
		UEngineSprite::CreateSpriteToMeta("Title_Train_SmokeM.png", ".SData");
		UEngineSprite::CreateSpriteToMeta("Title_Train_SmokeS.png", ".SData");
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

		UEngineSprite::CreateSpriteToMeta("Mongsiri_Idle.png", ".SData");
		UEngineSprite::CreateSpriteToMeta("Mongsiri_Jump.png", ".SData");
		UEngineSprite::CreateSpriteToMeta("Mongsiri_Collected.png", ".SData");
		UEngineSprite::CreateSpriteToMeta("Ellie_Walk.png", ".SData");
		UEngineSprite::CreateSpriteToMeta("Ellie_Idle.png", ".SData");
		UEngineSprite::CreateSpriteToMeta("Ellie_Collection_Mongsiri.png", ".SData");
		UEngineSprite::CreateSpriteToMeta("Mongsiri_Escape.png", ".SData");
	}

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("LWIWResources\\Image"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}

		Dir.Append("Tiles");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}

		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
	}
}

