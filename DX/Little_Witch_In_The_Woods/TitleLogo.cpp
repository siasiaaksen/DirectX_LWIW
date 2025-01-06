#include "PreCompile.h"
#include "TitleLogo.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>


ATitleLogo::ATitleLogo()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	{
		LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();
		LogoRenderer->SetSprite("Logo.png", 0);
		LogoRenderer->SetAutoScaleRatio(0.7f);
		LogoRenderer->SetWorldLocation({ 402 , 134 , 0.0f });
	}

	{
		//LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();
		//LogoRenderer->SetSprite("Title_StartText.png");
		//LogoRenderer->SetRelativeScale3D({ 276, 30, 1.0f });
		//LogoRenderer->SetWorldLocation({ 402 , 0 , 0.0f });
	}

	LogoRenderer->SetupAttachment(RootComponent);
}

ATitleLogo::~ATitleLogo()
{
}

void ATitleLogo::BeginPlay()
{
	AActor::BeginPlay();
}

void ATitleLogo::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}