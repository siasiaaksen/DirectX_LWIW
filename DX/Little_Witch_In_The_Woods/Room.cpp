#include "PreCompile.h"
#include "Room.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EnginePlatform/EngineInput.h>


ARoom::ARoom()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	{
		BaseSprite = CreateDefaultSubObject<USpriteRenderer>();
		BaseSprite->SetTexture("TestBaseMap.png");
		BaseSprite->SetScale3D(RoomSize);
		BaseSprite->SetWorldLocation({ 0.0f, 0.0f, 100.0f });
		BaseSprite->SetupAttachment(RootComponent);
	}

	{
		BaseColSprite = CreateDefaultSubObject<USpriteRenderer>();
		BaseColSprite->SetTexture("TestBaseMap_Col.png", true, 1.0f);
		BaseColSprite->SetWorldLocation({ 0.0f, 0.0f, 80.0f });
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