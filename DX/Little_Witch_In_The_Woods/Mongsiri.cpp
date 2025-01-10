#include "PreCompile.h"
#include "Mongsiri.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/Collision.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/CameraActor.h>
#include "Ellie.h"


AMongsiri::AMongsiri()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	{
		{
			MongsiriRenderer = CreateDefaultSubObject<USpriteRenderer>();
			MongsiriRenderer->SetupAttachment(RootComponent);
			MongsiriRenderer->SetAutoScaleRatio(3.0f);

			MongsiriRenderer->SetSprite("Mongsiri_Idle.png");
			MongsiriRenderer->CreateAnimation("Mongsiri_Idle_Front", "Mongsiri_Idle.png", { 0, 1, 2, 1 }, 0.2f);
			MongsiriRenderer->CreateAnimation("Mongsiri_Idle_Back", "Mongsiri_Idle.png", { 3, 4, 5, 4 }, 0.2f);
			MongsiriRenderer->ChangeAnimation("Mongsiri_Idle_Front");
		}

		{
			MongsiriCollision = CreateDefaultSubObject<UCollision>();
			MongsiriCollision->SetCollisionProfileName("Mongsiri");
			MongsiriCollision->SetScale3D(MongsiriSize * 5);
			FVector CollisionCenter;
			CollisionCenter.Y = MongsiriSize.Y - MongsiriSize.Half().Y;
			MongsiriCollision->SetWorldLocation(CollisionCenter);
			MongsiriCollision->SetupAttachment(RootComponent);
		}
	}
}

AMongsiri::~AMongsiri()
{
}

void AMongsiri::BeginPlay()
{
	AActor::BeginPlay();
}

void AMongsiri::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	ChaseCheck(_DeltaTime);
}

void AMongsiri::ChaseCheck(float _DeltaTime)
{
	//FVector StartPos = GetActorLocation();
	////FVector EndPos = /* ¿¤¸® À§Ä¡ */ ;

	//FVector CurPos = FVector::Lerp(StartPos, EndPos, _DeltaTime);

	std::vector<UCollision*> Result;
	if (true == MongsiriCollision->CollisionCheck("Ellie", Result))
	{
		//SetActorLocation(CurPos);

		int a = 0;
	}
}