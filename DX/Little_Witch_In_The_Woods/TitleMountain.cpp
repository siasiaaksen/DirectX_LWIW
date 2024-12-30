#include "PreCompile.h"
#include "TitleMountain.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>


ATitleMountain::ATitleMountain()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	MountainRenderer = CreateDefaultSubObject<USpriteRenderer>();
	MountainRenderer->SetSprite("Title_Train_Mountain.png", 0);
	MountainRenderer->SetRelativeScale3D({ 1315, 526, 1.0f });
	MountainRenderer->SetWorldLocation({ 17, -119, 0.0f });
	MountainRenderer->SetupAttachment(RootComponent);
}

ATitleMountain::~ATitleMountain()
{
}

void ATitleMountain::BeginPlay()
{
	AActor::BeginPlay();
}

void ATitleMountain::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
