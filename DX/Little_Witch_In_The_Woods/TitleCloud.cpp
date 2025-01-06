#include "PreCompile.h"
#include "TitleCloud.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/TimeEventComponent.h>


ATitleCloud::ATitleCloud()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	{
		CloudRenderer = CreateDefaultSubObject<USpriteRenderer>();
		CloudRenderer->SetTexture("Title_Train_Cloud_0.png", true, 1.0f);
		CloudRenderer->SetWorldLocation({ -588.0f, 211.0f, 11.0f });
		CloudRenderer->SetupAttachment(RootComponent);
	}

	{
		CloudRenderer = CreateDefaultSubObject<USpriteRenderer>();
		CloudRenderer->SetTexture("Title_Train_Cloud_1.png", true, 1.0f);
		CloudRenderer->SetWorldLocation({ -517.0f, 55.0f, 10.0f });
		CloudRenderer->SetupAttachment(RootComponent);
	}

	{
		CloudRenderer = CreateDefaultSubObject<USpriteRenderer>();
		CloudRenderer->SetTexture("Title_Train_Cloud_2.png", true, 1.0f);
		CloudRenderer->SetWorldLocation({ 245.0f, 22.0f, 9.0f });
		CloudRenderer->SetupAttachment(RootComponent);
	}

	{
		CloudRenderer = CreateDefaultSubObject<USpriteRenderer>();
		CloudRenderer->SetTexture("Title_Train_Cloud_3.png", true, 1.0f);
		CloudRenderer->SetWorldLocation({ 63.0f, 134.0f, 8.0f });
		CloudRenderer->SetupAttachment(RootComponent);
	}

	{
		CloudRenderer = CreateDefaultSubObject<USpriteRenderer>();
		CloudRenderer->SetTexture("Title_Train_Cloud_3.png", true, 1.0f);
		CloudRenderer->SetWorldLocation({ 357.0f, 228.0f, 7.0f });
		CloudRenderer->SetupAttachment(RootComponent);
	}

	TimeEvent = CreateDefaultSubObject<UTimeEventComponent>();

	//TimeEvent->AddEvent(1.0f,
	//	[this](float _DeltaTime, float _A)
	//	{
	//		CloudMove(_DeltaTime);
	//	},
	//	[this]()
	//	{
	//		CloudRenderer->SetWorldLocation({ -588.0f, 211.0f, 11.0f });
	//	},
	//	true);
}

ATitleCloud::~ATitleCloud()
{
}

void ATitleCloud::BeginPlay()
{
	AActor::BeginPlay();
}

void ATitleCloud::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	CloudMove(_DeltaTime);
}

void ATitleCloud::CloudMove(float _DeltaTime)
{
	CloudRenderer->AddRelativeLocation({ -15.0f * _DeltaTime, 0.0f, 0.0f, 1.0f });
}

void ATitleCloud::SetCloud(std::string_view _SpriteName, FVector& _Location)
{

}

