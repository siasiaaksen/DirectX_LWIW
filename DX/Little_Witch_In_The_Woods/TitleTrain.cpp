#include "PreCompile.h"
#include "TitleTrain.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>


ATitleTrain::ATitleTrain()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	{
		TrainRenderer = CreateDefaultSubObject<USpriteRenderer>();
		TrainRenderer->SetSprite("Title_Train_Train.png", 0);
		TrainRenderer->SetRelativeScale3D({ 1149, 72, 1.0f });
		TrainRenderer->SetWorldLocation({ -341, -107, 0.0f });
		TrainRenderer->SetupAttachment(RootComponent);
	}

	{
		TrainRenderer = CreateDefaultSubObject<USpriteRenderer>();
		TrainRenderer->SetSprite("Title_Train_TrainBlur.png", 0);
		TrainRenderer->SetRelativeScale3D({ 870, 60, 1.0f });
		TrainRenderer->SetWorldLocation({ -205, -328, 0.0f });
		TrainRenderer->SetupAttachment(RootComponent);
	}
}

ATitleTrain::~ATitleTrain()
{
}

void ATitleTrain::BeginPlay()
{
	AActor::BeginPlay();
}

void ATitleTrain::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

