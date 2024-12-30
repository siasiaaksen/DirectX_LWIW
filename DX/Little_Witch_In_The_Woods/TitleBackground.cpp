#include "PreCompile.h"
#include "TitleBackground.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>


ATitleBackground::ATitleBackground()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	BGRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BGRenderer->SetSprite("Logo.png");
	BGRenderer->SetRelativeScale3D({ 679, 330, 1.0f });
	BGRenderer->SetupAttachment(RootComponent);
}

ATitleBackground::~ATitleBackground()
{
}

void ATitleBackground::BeginPlay()
{
	AActor::BeginPlay();
}

void ATitleBackground::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}