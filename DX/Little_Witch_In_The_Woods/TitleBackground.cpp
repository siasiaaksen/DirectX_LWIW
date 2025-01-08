#include "PreCompile.h"
#include "TitleBackground.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/Collision.h>


ATitleBackground::ATitleBackground()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	{
		BGRenderer = CreateDefaultSubObject<USpriteRenderer>();
		BGRenderer->SetSprite("Title_Train_Sky.png", 0);
		BGRenderer->SetAutoScaleRatio(1.0f);
		BGRenderer->SetWorldLocation({ 0.0f, 0.0f, 15.0f });
		BGRenderer->SetupAttachment(RootComponent);
	}

	{
		BGCollision = CreateDefaultSubObject<UCollision>();
		BGCollision->SetCollisionProfileName("BG");
		BGCollision->SetScale3D({ 1450.0f, 720.0f });
		BGCollision->SetWorldLocation({ 100.0f, 0.0f });
		BGCollision->SetupAttachment(RootComponent);
	}
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