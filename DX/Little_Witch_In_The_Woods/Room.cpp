#include "PreCompile.h"
#include "Room.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EnginePlatform/EngineInput.h>
#include "Ellie.h"

ARoom::ARoom()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	{
		BaseSprite = CreateDefaultSubObject<USpriteRenderer>();
		BaseSprite->SetTexture("Map.png");
		BaseSprite->SetScale3D(RoomSize);
		BaseSprite->SetWorldLocation({ 0.0f, 0.0f, 1000.0f });
		BaseSprite->SetupAttachment(RootComponent);
	}

	{
		BaseColSprite = CreateDefaultSubObject<USpriteRenderer>();
		BaseColSprite->SetTexture("Map_Col.png", true, 1.0f);
		BaseColSprite->SetWorldLocation({ 0.0f, 0.0f, 800.0f });
		BaseColSprite->SetupAttachment(RootComponent);
	}

	{
		BaseCollision = CreateDefaultSubObject<UCollision>();
		BaseCollision->SetCollisionProfileName("Room");
		BaseCollision->SetScale3D(CollisionSize);
		BaseCollision->SetupAttachment(RootComponent);
	}

}

ARoom::~ARoom()
{
}

void ARoom::BeginPlay()
{
	AActor::BeginPlay();
}

void ARoom::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (true == UEngineInput::IsDown(VK_F2))
	{
		BaseColSprite->SetActiveSwitch();
	}
}

void ARoom::SetColImage(std::string_view _ColImageName, std::string_view _FolderName)
{
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("LWIWResources\\Image\\Play"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}

		Dir.Append(_FolderName);
		UEngineFile ImageFiles = Dir.GetFile(_ColImageName);

		ColImage.Load(nullptr, ImageFiles.GetPathToString());
	}
}