#include "PreCompile.h"
#include "TitleTrainSmoke.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>


ATitleTrainSmoke::ATitleTrainSmoke()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	//Big
	{
		SmokeRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SmokeRenderer->SetSprite("Title_Train_SmokeB.png", 0);
		SmokeRenderer->SetAutoScaleRatio(1.0f);
		SmokeRenderer->SetWorldLocation({ -50.0f, -15.0f, 4.0f });
		SmokeRenderer->CreateAnimation("BigSmoke", "Title_Train_SmokeB.png", 0, 3, 0.1f);
		SmokeRenderer->ChangeAnimation("BigSmoke");
		SmokeRenderer->SetupAttachment(RootComponent);
	}

	// Mid
	{
		SmokeRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SmokeRenderer->SetSprite("Title_Train_SmokeM.png", 0);
		SmokeRenderer->SetAutoScaleRatio(1.0f);
		SmokeRenderer->SetWorldLocation({ 12.0f, -25.0f, 3.0f });
		SmokeRenderer->CreateAnimation("MidSmoke", "Title_Train_SmokeM.png", 0, 4, 0.1f);
		SmokeRenderer->ChangeAnimation("MidSmoke");
		SmokeRenderer->SetupAttachment(RootComponent);
	}

	//Small
	{
		SmokeRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SmokeRenderer->SetSprite("Title_Train_SmokeS.png", 0);
		SmokeRenderer->SetAutoScaleRatio(1.0f);
		SmokeRenderer->SetWorldLocation({ 108.0f, -35.0f, 2.0f });
		SmokeRenderer->CreateAnimation("SmallSmoke", "Title_Train_SmokeS.png", 0, 3, 0.1f);
		SmokeRenderer->ChangeAnimation("SmallSmoke");
		SmokeRenderer->SetupAttachment(RootComponent);
	}
}

ATitleTrainSmoke::~ATitleTrainSmoke()
{
}

void ATitleTrainSmoke::BeginPlay()
{
	AActor::BeginPlay();
}

void ATitleTrainSmoke::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

