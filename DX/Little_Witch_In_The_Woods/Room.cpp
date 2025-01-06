#include "PreCompile.h"
#include "Room.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>


ARoom::ARoom()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	{
		BaseSprite = CreateDefaultSubObject<USpriteRenderer>();
		BaseSprite->SetTexture("TestBaseMap.png", true, 1.0f);
		BaseSprite->SetScale3D({ RoomSize.X, RoomSize.Y });
		BaseSprite->SetWorldLocation({ 0.0f, 0.0f, 100.0f });
		BaseSprite->SetupAttachment(RootComponent);
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
}