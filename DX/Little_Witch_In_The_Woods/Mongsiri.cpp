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
		MongsiriRenderer = CreateDefaultSubObject<USpriteRenderer>();
		MongsiriRenderer->SetupAttachment(RootComponent);
		MongsiriRenderer->SetAutoScaleRatio(3.0f);

		{
			MongsiriRenderer->SetSprite("Mongsiri_Idle.png");
			MongsiriRenderer->CreateAnimation("Mongsiri_Idle_Front", "Mongsiri_Idle.png", { 0, 1, 2, 1 }, AnimSpeed);
			MongsiriRenderer->CreateAnimation("Mongsiri_Idle_Back", "Mongsiri_Idle.png", { 3, 4, 5, 4 }, AnimSpeed);
		}

		{
			MongsiriRenderer->SetSprite("Mongsiri_Jump.png");
			MongsiriRenderer->CreateAnimation("Mongsiri_Jump_Front", "Mongsiri_Jump.png", 0, 9, AnimSpeed);
			MongsiriRenderer->CreateAnimation("Mongsiri_Jump_Back", "Mongsiri_Jump.png", 10, 19, AnimSpeed);
		}

		MongsiriRenderer->ChangeAnimation("Mongsiri_Idle_Front");
	}

	{
		{
			MongsiriOuterCol = CreateDefaultSubObject<UCollision>();
			MongsiriOuterCol->SetCollisionProfileName("MongsiriOuter");
			MongsiriOuterCol->SetScale3D(MongsiriSize * 10);
			FVector CollisionCenter;
			CollisionCenter.Y = MongsiriSize.Y - MongsiriSize.Half().Y;
			MongsiriOuterCol->SetWorldLocation(CollisionCenter);
			MongsiriOuterCol->SetupAttachment(RootComponent);
		}

		{
			MongsiriInnerCol = CreateDefaultSubObject<UCollision>();
			MongsiriInnerCol->SetCollisionProfileName("MongsiriInner");
			MongsiriInnerCol->SetScale3D(MongsiriSize * 5);
			FVector CollisionCenter;
			CollisionCenter.Y = MongsiriSize.Y - MongsiriSize.Half().Y;
			MongsiriInnerCol->SetWorldLocation(CollisionCenter);
			MongsiriInnerCol->SetupAttachment(RootComponent);
		}
	}

	{
		FindMark = CreateDefaultSubObject<USpriteRenderer>();
		FindMark->SetupAttachment(MongsiriRenderer);
		FindMark->SetTexture("Exclamation.png", true, 0.05f);
		FindMark->SetRelativeLocation({ 0.0f, 1.3f, 0.0f });
		FindMark->SetActive(false);
	}

	State = EMongsiriState::IDLE;
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

	switch (State)
	{
	case EMongsiriState::IDLE:
		Idle(_DeltaTime);
		break;
	case EMongsiriState::JUMP:
		Jump(_DeltaTime);
		break;
	case EMongsiriState::COLLECTED:
		break;
	case EMongsiriState::ESCAPE:
		break;
	case EMongsiriState::DISAPPEAR:
		break;
	case EMongsiriState::MAX:
		break;
	default:
		break;
	}

	// Sorting
	FVector Pos = GetActorLocation();
	Pos.Z = Pos.Y;

	SetActorLocation(Pos);

	SwitchAnim();
}

void AMongsiri::Idle(float _DeltaTime)
{
	FindCheck(_DeltaTime);
	ChaseCheck(_DeltaTime);
}

void AMongsiri::Jump(float _DeltaTime)
{
	MoveToEllie(_DeltaTime);
}

void AMongsiri::FindCheck(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (true == MongsiriOuterCol->CollisionCheck("Ellie", Result))
	{
		FindMark->SetActive(true);
	}
	else
	{
		FindMark->SetActive(false);
	}
}

void AMongsiri::ChaseCheck(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (true == MongsiriInnerCol->CollisionCheck("Ellie", Result))
	{
		State = EMongsiriState::JUMP;
		MongsiriRenderer->ChangeAnimation("Mongsiri_Jump" + DirName);
	}
	else
	{
		State = EMongsiriState::IDLE;
		MongsiriRenderer->ChangeAnimation("Mongsiri_Idle" + DirName);
	}
}

void AMongsiri::MoveToEllie(float _DeltaTime)
{
	FVector StartPos = GetActorLocation();
	FVector EndPos = GetWorld()->GetMainPawn()->GetActorLocation() - FVector(0.0f, 50.0f);

	FVector CurPos = FVector::Lerp(StartPos, EndPos, _DeltaTime * MoveSpeed);

	SetActorLocation(CurPos);

	State = EMongsiriState::IDLE;
}

void AMongsiri::SwitchAnim()
{
	AEllie* Ellie = dynamic_cast<AEllie*>(GetWorld()->GetMainPawn());
	FVector ElliePos = Ellie->GetActorLocation();
	FVector MongsiriPos = GetActorLocation();

	if (MongsiriPos.Y - ElliePos.Y < 0)
	{
		DirName = "_Back";
	}
	else
	{
		DirName = "_Front";
	}
}
