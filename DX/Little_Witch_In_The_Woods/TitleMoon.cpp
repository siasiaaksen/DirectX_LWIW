#include "PreCompile.h"
#include "TitleMoon.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>


ATitleMoon::ATitleMoon()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	MoonRenderer = CreateDefaultSubObject<USpriteRenderer>();
	MoonRenderer->SetSprite("Title_Train_Moon.png", 0);
	MoonRenderer->SetAutoScaleRatio(2.6f);
	MoonRenderer->SetWorldLocation({ -326.0f, 209.0f, 12.0f });
	MoonRenderer->SetupAttachment(RootComponent);
}

ATitleMoon::~ATitleMoon()
{
}

void ATitleMoon::BeginPlay()
{
	AActor::BeginPlay();
}

void ATitleMoon::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}