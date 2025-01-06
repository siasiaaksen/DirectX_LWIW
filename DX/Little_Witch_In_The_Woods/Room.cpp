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
		BaseSprite->SetScale3D({ 1280.0f, 720.0f });
		BaseSprite->SetWorldLocation({ -588.0f, 211.0f, 11.0f });
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