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
		LogoRenderer->SetWorldLocation({ 380, 134.0f, 1.0f });
		LogoRenderer->SetupAttachment(RootComponent);
	}

	{
		TextRenderer = CreateDefaultSubObject<USpriteRenderer>();
		TextRenderer->SetTexture("Title_StartText.png", true, 1.0f);
		TextRenderer->SetWorldLocation({ 402 , 0 , 2.0f });
		TextRenderer->SetupAttachment(RootComponent);
	}

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