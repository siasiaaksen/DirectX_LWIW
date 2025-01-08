#include "PreCompile.h"
#include "TitleCloud.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/Collision.h>


ATitleCloud::ATitleCloud()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	{
		CloudRenderer = CreateDefaultSubObject<USpriteRenderer>();
		CloudRenderer->SetTexture("Title_Train_Cloud_0.png", true, 1.0f);
		CloudRenderer->SetWorldLocation({ -588.0f, 211.0f, 11.0f });
		CloudRenderer->ColorData.MulColor = float4(1.0f, 1.0f, 1.0f, CloudAlpha);
		CloudRenderer->SetupAttachment(RootComponent);
		CloudRendV.push_back(CloudRenderer);

		CloudCollision = CreateDefaultSubObject<UCollision>();
		CloudCollision->SetCollisionProfileName("Cloud");
		CloudCollision->SetScale3D(CloudRenderer->GetWorldScale3D());
		CloudCollision->SetWorldLocation(CloudRenderer->GetTransformRef().WorldLocation);
		CloudCollision->SetupAttachment(RootComponent);
		CloudColV.push_back(CloudCollision);

		CloudSpeed.push_back(1.0f);
	}

	{
		CloudRenderer = CreateDefaultSubObject<USpriteRenderer>();
		CloudRenderer->SetTexture("Title_Train_Cloud_1.png", true, 1.0f);
		CloudRenderer->SetWorldLocation({ -517.0f, 55.0f, 10.0f });
		CloudRenderer->ColorData.MulColor = float4(1.0f, 1.0f, 1.0f, CloudAlpha);
		CloudRenderer->SetupAttachment(RootComponent);
		CloudRendV.push_back(CloudRenderer);

		CloudCollision = CreateDefaultSubObject<UCollision>();
		CloudCollision->SetCollisionProfileName("Cloud");
		CloudCollision->SetScale3D(CloudRenderer->GetWorldScale3D());
		CloudCollision->SetWorldLocation(CloudRenderer->GetTransformRef().WorldLocation);
		CloudCollision->SetupAttachment(RootComponent);
		CloudColV.push_back(CloudCollision);

		CloudSpeed.push_back(1.5f);
	}

	{
		CloudRenderer = CreateDefaultSubObject<USpriteRenderer>();
		CloudRenderer->SetTexture("Title_Train_Cloud_2.png", true, 1.0f);
		CloudRenderer->SetWorldLocation({ 245.0f, 22.0f, 9.0f });
		CloudRenderer->ColorData.MulColor = float4(1.0f, 1.0f, 1.0f, CloudAlpha);
		CloudRenderer->SetupAttachment(RootComponent);
		CloudRendV.push_back(CloudRenderer);

		CloudCollision = CreateDefaultSubObject<UCollision>();
		CloudCollision->SetCollisionProfileName("Cloud");
		CloudCollision->SetScale3D(CloudRenderer->GetWorldScale3D());
		CloudCollision->SetWorldLocation(CloudRenderer->GetTransformRef().WorldLocation);
		CloudCollision->SetupAttachment(RootComponent);
		CloudColV.push_back(CloudCollision);

		CloudSpeed.push_back(1.3f);
	}

	{
		CloudRenderer = CreateDefaultSubObject<USpriteRenderer>();
		CloudRenderer->SetTexture("Title_Train_Cloud_3.png", true, 1.0f);
		CloudRenderer->SetWorldLocation({ 63.0f, 134.0f, 8.0f });
		CloudRenderer->ColorData.MulColor = float4(1.0f, 1.0f, 1.0f, CloudAlpha);
		CloudRenderer->SetupAttachment(RootComponent);
		CloudRendV.push_back(CloudRenderer);

		CloudCollision = CreateDefaultSubObject<UCollision>();
		CloudCollision->SetCollisionProfileName("Cloud");
		CloudCollision->SetScale3D(CloudRenderer->GetWorldScale3D());
		CloudCollision->SetWorldLocation(CloudRenderer->GetTransformRef().WorldLocation);
		CloudCollision->SetupAttachment(RootComponent);
		CloudColV.push_back(CloudCollision);

		CloudSpeed.push_back(1.4f);
	}

	{
		CloudRenderer = CreateDefaultSubObject<USpriteRenderer>();
		CloudRenderer->SetTexture("Title_Train_Cloud_3.png", true, 1.0f);
		CloudRenderer->SetWorldLocation({ 357.0f, 228.0f, 7.0f });
		CloudRenderer->ColorData.MulColor = float4(1.0f, 1.0f, 1.0f, CloudAlpha);
		CloudRenderer->SetupAttachment(RootComponent);
		CloudRendV.push_back(CloudRenderer);

		CloudCollision = CreateDefaultSubObject<UCollision>();
		CloudCollision->SetCollisionProfileName("Cloud");
		CloudCollision->SetScale3D(CloudRenderer->GetWorldScale3D());
		CloudCollision->SetWorldLocation(CloudRenderer->GetTransformRef().WorldLocation);
		CloudCollision->SetupAttachment(RootComponent);
		CloudColV.push_back(CloudCollision);

		CloudSpeed.push_back(1.2f);
	}
}

ATitleCloud::~ATitleCloud()
{
}

void ATitleCloud::BeginPlay()
{
	AActor::BeginPlay();

	Random.SetSeed(100);
}

void ATitleCloud::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	CloudMove(_DeltaTime);
}

void ATitleCloud::CloudMove(float _DeltaTime)
{
	FVector Dir = { -15.0f * _DeltaTime, 0.0f, 0.0f, 1.0f};

	CloudCheck(Dir);

	for (int i = 0; i < CloudRendV.size(); i++)
	{
		int RandomIndex = Random.RandomInt(0, (CloudSpeed.size() - 1));
		Speed = CloudSpeed[RandomIndex];

		Dir.X *= Speed;
		CloudRendV[i]->AddRelativeLocation(Dir);
		CloudColV[i]->AddRelativeLocation(Dir);
	}
}

void ATitleCloud::CloudCheck(FVector _Dir)
{
	for (int i = 0; i < CloudColV.size(); i++)
	{
		std::vector<UCollision*> Result;
		if (false == CloudColV[i]->CollisionCheck("BG", _Dir, Result))
		{
			FVector NewCloudColPos = CloudColV[i]->GetTransformRef().WorldLocation;
			NewCloudColPos.X = UEngineCore::GetScreenScale().Half().X + CloudColV[i]->GetWorldScale3D().Half().X;
			CloudColV[i]->SetWorldLocation(NewCloudColPos);
			CloudRendV[i]->SetWorldLocation(NewCloudColPos);
		}
	}
}

