#include "PreCompile.h"
#include "TitleStar.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>


ATitleStar::ATitleStar()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	{
		StarRenderer = CreateDefaultSubObject<USpriteRenderer>();
		StarRenderer->SetSprite("Title_Train_Star.png", 0);
		StarRenderer->SetAutoScaleRatio(1.0f);
		StarRenderer->SetWorldLocation({ 3.0f, 187.0f, 9.0f });
		StarRenderer->CreateAnimation("TwinkleStar", "Title_Train_Star.png", 0, 4, 0.3f);
		StarRenderer->ChangeAnimation("TwinkleStar");
		StarRenderer->SetupAttachment(RootComponent);
	}

	{
		StarRenderer = CreateDefaultSubObject<USpriteRenderer>();
		StarRenderer->SetSprite("Title_Train_ShootingStar.png", 0);
		StarRenderer->SetAutoScaleRatio(1.0f);
		StarRenderer->SetWorldLocation({ 0.0f, 195.0f, 8.0f });
		StarRenderer->CreateAnimation("FallingStar", "Title_Train_ShootingStar.png", 0, 3, 0.5f);
		StarRenderer->ChangeAnimation("FallingStar");
		StarRenderer->SetupAttachment(RootComponent);
	}

}

ATitleStar::~ATitleStar()
{
}

void ATitleStar::BeginPlay()
{
	AActor::BeginPlay();
}

void ATitleStar::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

