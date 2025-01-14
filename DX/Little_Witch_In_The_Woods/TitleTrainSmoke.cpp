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
		BigSmokeRenderer = CreateDefaultSubObject<USpriteRenderer>();
		BigSmokeRenderer->SetSprite("Title_Train_SmokeB.png", 0);
		BigSmokeRenderer->SetAutoScaleRatio(1.0f);
		BigSmokeRenderer->SetWorldLocation({ -50.0f, -15.0f, 4.0f });
		BigSmokeRenderer->ColorData.MulColor = float4(1.0f, 1.0f, 1.0f, SmokeAlpha);
		BigSmokeRenderer->CreateAnimation("BigSmoke", "Title_Train_SmokeB.png", 0, 3, 0.1f);
		BigSmokeRenderer->ChangeAnimation("BigSmoke");
		BigSmokeRenderer->SetupAttachment(RootComponent);
	}

	// Mid
	{
		MidSmokeRenderer = CreateDefaultSubObject<USpriteRenderer>();
		MidSmokeRenderer->SetSprite("Title_Train_SmokeM.png", 0);
		MidSmokeRenderer->SetAutoScaleRatio(1.0f);
		MidSmokeRenderer->SetWorldLocation({ 12.0f, -25.0f, 3.0f });
		MidSmokeRenderer->ColorData.MulColor = float4(1.0f, 1.0f, 1.0f, SmokeAlpha);
		MidSmokeRenderer->CreateAnimation("MidSmoke", "Title_Train_SmokeM.png", 0, 4, 0.1f);
		MidSmokeRenderer->ChangeAnimation("MidSmoke");
		MidSmokeRenderer->SetupAttachment(RootComponent);
	}

	//Small
	{
		SmallSmokeRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SmallSmokeRenderer->SetSprite("Title_Train_SmokeS.png", 0);
		SmallSmokeRenderer->SetAutoScaleRatio(1.0f);
		SmallSmokeRenderer->SetWorldLocation({ 108.0f, -35.0f, 2.0f });
		SmallSmokeRenderer->ColorData.MulColor = float4(1.0f, 1.0f, 1.0f, SmokeAlpha);
		SmallSmokeRenderer->CreateAnimation("SmallSmoke", "Title_Train_SmokeS.png", 0, 3, 0.1f);
		SmallSmokeRenderer->ChangeAnimation("SmallSmoke");
		SmallSmokeRenderer->SetupAttachment(RootComponent);
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

