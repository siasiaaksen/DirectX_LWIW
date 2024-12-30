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
		StarRenderer->SetRelativeScale3D({ 4991, 1061, 1.0f });
		StarRenderer->SetWorldLocation({ 3, 187, 0.0f });
		StarRenderer->CreateAnimation("TwinkleStar", "Title_Train_Star.png", 0, 4, 0.3f);
		StarRenderer->ChangeAnimation("TwinkleStar");
		StarRenderer->SetupAttachment(RootComponent);
	}

	{
		StarRenderer = CreateDefaultSubObject<USpriteRenderer>();
		StarRenderer->SetSprite("Title_Train_Star.png", 5);
		StarRenderer->SetRelativeScale3D({ 4991, 1061, 1.0f });
		StarRenderer->SetWorldLocation({ 3, 187, 0.0f });
		StarRenderer->CreateAnimation("FallingStar", "Title_Train_Star.png", 5, 10, 0.3f);
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

