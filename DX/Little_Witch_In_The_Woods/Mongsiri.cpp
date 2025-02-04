#include "PreCompile.h"
#include "Mongsiri.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/Collision.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/CameraActor.h>
#include "Ellie.h"
#include "InteractObject.h"
#include "InteractCollision.h"


AMongsiri::AMongsiri()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	{
		MongsiriRenderer = CreateDefaultSubObject<USpriteRenderer>();
		MongsiriRenderer->SetupAttachment(RootComponent);
		MongsiriRenderer->SetAutoScaleRatio(2.5f);

		{
			MongsiriRenderer->SetSprite("Mongsiri_Idle.png");
			MongsiriRenderer->CreateAnimation("Mongsiri_Idle_FLeft", "Mongsiri_Idle.png", { 0, 1, 2, 1 }, AnimSpeed);
			MongsiriRenderer->CreateAnimation("Mongsiri_Idle_BLeft", "Mongsiri_Idle.png", { 3, 4, 5, 4 }, AnimSpeed);
			MongsiriRenderer->CreateAnimation("Mongsiri_Idle_FRight", "Mongsiri_Idle.png", { 6, 7, 8, 7 }, AnimSpeed);
			MongsiriRenderer->CreateAnimation("Mongsiri_Idle_BRight", "Mongsiri_Idle.png", { 9, 10, 11, 10 }, AnimSpeed);
		}

		{
			MongsiriRenderer->SetSprite("Mongsiri_Jump.png");
			MongsiriRenderer->CreateAnimation("Mongsiri_Jump_FLeft", "Mongsiri_Jump.png", 0, 9, AnimSpeed);
			MongsiriRenderer->CreateAnimation("Mongsiri_Jump_BLeft", "Mongsiri_Jump.png", 10, 19, AnimSpeed);
			MongsiriRenderer->CreateAnimation("Mongsiri_Jump_FRight", "Mongsiri_Jump.png", 20, 29, AnimSpeed);
			MongsiriRenderer->CreateAnimation("Mongsiri_Jump_BRight", "Mongsiri_Jump.png", 30, 39, AnimSpeed);
		}

		{
			MongsiriRenderer->SetSprite("Mongsiri_Collected.png");
			MongsiriRenderer->CreateAnimation("Mongsiri_Collected_FLeft", "Mongsiri_Collected.png", 0, 6, AnimSpeed, false);
			MongsiriRenderer->CreateAnimation("Mongsiri_Collected_FRight", "Mongsiri_Collected.png", { 13, 12, 11, 10, 9, 8, 7 }, AnimSpeed, false);
		}

		{
			MongsiriRenderer->SetSprite("Mongsiri_Escape.png");
			MongsiriRenderer->CreateAnimation("Mongsiri_Escape_FLeft", "Mongsiri_Escape.png", 0, 23, AnimSpeed, false);
		}

		MongsiriRenderer->ChangeAnimation("Mongsiri_Idle_FLeft");
	}

	{
		{
			MongsiriOuterCol = CreateDefaultSubObject<UCollision>();
			MongsiriOuterCol->SetCollisionProfileName("MongsiriOuter");
			MongsiriOuterCol->SetScale3D(MongsiriSize * 8);
			FVector CollisionCenter;
			CollisionCenter.Y = MongsiriSize.Y - MongsiriSize.Half().Y;
			MongsiriOuterCol->SetWorldLocation(CollisionCenter);
			MongsiriOuterCol->SetupAttachment(RootComponent);
		}

		{
			MongsiriInnerCol = CreateDefaultSubObject<UCollision>();
			MongsiriInnerCol->SetCollisionProfileName("MongsiriInner");
			MongsiriInnerCol->SetScale3D(MongsiriSize * 0.8f);
			FVector CollisionCenter;
			CollisionCenter.Y = MongsiriSize.Y - MongsiriSize.Half().Y;
			MongsiriInnerCol->SetWorldLocation(CollisionCenter);
			MongsiriInnerCol->SetupAttachment(RootComponent);
		}

		{
			MongsiriEscapeCol = CreateDefaultSubObject<UCollision>();
			MongsiriEscapeCol->SetCollisionProfileName("MongsiriEscape");
			MongsiriEscapeCol->SetScale3D(MongsiriSize * 0.1f);
			FVector CollisionCenter;
			CollisionCenter.Y = MongsiriSize.Y - (MongsiriSize.Half().Y * 1.5f);
			MongsiriEscapeCol->SetWorldLocation(CollisionCenter);
			MongsiriEscapeCol->SetupAttachment(RootComponent);
		}
	}

	{
		FindMark = CreateDefaultSubObject<USpriteRenderer>();
		FindMark->SetupAttachment(MongsiriRenderer);
		FindMark->SetTexture("Question.png", true, 0.05f);
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
	AInteractObject::BeginPlay();
}

void AMongsiri::Tick(float _DeltaTime)
{
	AInteractObject::Tick(_DeltaTime);

	switch (State)
	{
	case EMongsiriState::IDLE:
		Idle(_DeltaTime);
		break;
	case EMongsiriState::MOVE:
		Move(_DeltaTime);
		break;
	case EMongsiriState::COLLECTED:
		Collected(_DeltaTime);
		break;
	case EMongsiriState::ESCAPE:
		Escape(_DeltaTime);
		break;
	case EMongsiriState::DISAPPEAR:
		Disappear(_DeltaTime);
		break;
	default:
		break;
	}

	// Sorting
	if (true == IsSort)
	{
		YSorting();
	}
}

void AMongsiri::Idle(float _DeltaTime)
{
	FindCheck(_DeltaTime);
	SwitchAnim();
}

void AMongsiri::Move(float _DeltaTime)
{
	MoveToEllie(_DeltaTime);
	SwitchAnim();
}

void AMongsiri::Collected(float _DeltaTime)
{
	int Frame = 0;
	AEllie* Ellie = dynamic_cast<AEllie*>(GetWorld()->GetMainPawn());

	SetActorLocation(Ellie->GetActorLocation() + FVector(-2.0f, 10.0f));

	if (GetActorLocation().X - Ellie->GetActorLocation().X <= 0)
	{
		DirName = "_FLeft";
		Frame = 6;
	}
	else
	{
		DirName = "_FRight";
		Frame = 7;
	}

	FindMark->SetActive(false);
	MongsiriRenderer->ChangeAnimation("Mongsiri_Collected" + DirName);
	MongsiriRenderer->SetAnimationEvent("Mongsiri_Collected" + DirName, Frame, 
		[this, Ellie]() 
		{ 
			FVector CollectPos = Ellie->GetActorLocation() - FVector(5.0f, 20.0f);
			SetActorLocation(CollectPos);
			IsSort = true;

			// Escape Part
			State = EMongsiriState::ESCAPE;
			IsEscape = true;
		});
	
}

void AMongsiri::Escape(float _DeltaTime)
{
	std::list<std::shared_ptr<AInteractCollision>> AllInterColList = GetWorld()->GetAllActorListByClass<AInteractCollision>();
	for (std::shared_ptr<AInteractCollision> InterCol : AllInterColList)
	{
		std::string InterColName = InterCol->GetInterColName();
		if (InterColName == "MongsiriHole")
		{
			FVector StartPos = GetActorLocation();
			FVector EndPos = InterCol->GetActorLocation();
			FVector CurPos = FVector::Lerp(StartPos, EndPos, _DeltaTime * 0.2f);

			if (CurPos != EndPos)
			{
				FindMark->SetActive(true);
				FindMark->SetTexture("Exclamation.png", true, 0.05f);
				MongsiriRenderer->ChangeAnimation("Mongsiri_Jump_FRight");
				SetActorLocation(CurPos);
			}

			std::vector<UCollision*> Result;
			if (true == MongsiriEscapeCol->CollisionCheck("InterCol", Result))
			{
				SetActorLocation({ InterCol->GetActorLocation().X, InterCol->GetActorLocation().Y - 12.0f });
				SetActorRotation({ 0.0f, 180.0f, 0.0f });
				State = EMongsiriState::DISAPPEAR;
			}
		}
	}
}

void AMongsiri::Disappear(float _DeltaTime)
{
	FindMark->SetActive(false);
	MongsiriRenderer->ChangeAnimation("Mongsiri_Escape_FLeft");
	MongsiriRenderer->SetAnimationEvent("Mongsiri_Escape_FLeft", 23,
		[this]()
		{
			MongsiriRenderer->SetActive(false);
		});
}

void AMongsiri::YSorting()
{
	FVector Pos = GetActorLocation();
	Pos.Z = Pos.Y;

	SetActorLocation(Pos);
}

void AMongsiri::FindCheck(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (true == MongsiriOuterCol->CollisionCheck("Ellie", Result))
	{
		if (false == IsEscape)
		{
			FindMark->SetActive(true);
			State = EMongsiriState::MOVE;
			MongsiriRenderer->ChangeAnimation("Mongsiri_Jump" + DirName);
		}
		//else
		//{
		//	// Escape Part
		//	FindMark->SetActive(false);
		//	State = EMongsiriState::IDLE;
		//	MongsiriRenderer->ChangeAnimation("Mongsiri_Idle_FLeft");
		//}
	}
	else
	{
		FindMark->SetActive(false);
		State = EMongsiriState::IDLE;
		MongsiriRenderer->ChangeAnimation("Mongsiri_Idle" + DirName);
	}
}

void AMongsiri::MoveToEllie(float _DeltaTime)
{
	FVector StartPos = GetActorLocation();
	FVector EndPos = GetWorld()->GetMainPawn()->GetActorLocation();

	FVector CurPos = FVector::Lerp(StartPos, EndPos, _DeltaTime * MoveSpeed);

	SetActorLocation(CurPos);

	State = EMongsiriState::IDLE;
}

void AMongsiri::SwitchAnim()
{
	AEllie* Ellie = dynamic_cast<AEllie*>(GetWorld()->GetMainPawn());
	FVector ElliePos = Ellie->GetActorLocation();
	FVector MongsiriPos = GetActorLocation();

	if (MongsiriPos.Y - ElliePos.Y <= 0)
	{
		if (MongsiriPos.X - ElliePos.X <= 0)
		{
			DirName = "_BRight";
		}
		else
		{
			DirName = "_BLeft";
		}
	}
	else
	{
		if (MongsiriPos.X - ElliePos.X <= 0)
		{
			DirName = "_FRight";
		}
		else
		{
			DirName = "_FLeft";
		}
	}
}
