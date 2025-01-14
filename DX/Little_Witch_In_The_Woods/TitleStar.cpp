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
		StarRenderer->SetWorldLocation({ 3.0f, 187.0f, 14.0f });
		StarRenderer->CreateAnimation("TwinkleStar", "Title_Train_Star.png", 0, 4, 0.3f);
		StarRenderer->ChangeAnimation("TwinkleStar");
		StarRenderer->SetupAttachment(RootComponent);
	}

	{
		ShootingStarRenderer = CreateDefaultSubObject<USpriteRenderer>();
		ShootingStarRenderer->SetSprite("Title_Train_ShootingStar.png", 0);
		ShootingStarRenderer->SetAutoScaleRatio(1.0f);
		ShootingStarRenderer->SetWorldLocation({ 0.0f, 195.0f, 13.0f });
		ShootingStarRenderer->CreateAnimation("FallingStar", "Title_Train_ShootingStar.png", 0, 3, 0.5f);
		ShootingStarRenderer->ChangeAnimation("FallingStar");
		ShootingStarRenderer->SetupAttachment(RootComponent);
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

