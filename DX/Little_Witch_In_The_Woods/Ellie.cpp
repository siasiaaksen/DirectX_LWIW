#include "PreCompile.h"
#include "Ellie.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/Collision.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/CameraActor.h>
#include "Room.h"


AEllie::AEllie()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	{
		EllieRenderer = CreateDefaultSubObject<USpriteRenderer>();
		EllieRenderer->SetupAttachment(RootComponent);
		EllieRenderer->SetAutoScaleRatio(1.0f);

		// EllieWalk
		{
			EllieRenderer->SetSprite("Ellie_Walk.png");
			//EllieRenderer->SetRelativeScale3D({ 73, 92, 1.0f });
			EllieRenderer->CreateAnimation("Ellie_Walk_FLeft", "Ellie_Walk.png", 28, 35, 0.1f);
			EllieRenderer->CreateAnimation("Ellie_Walk_Front", "Ellie_Walk.png", 12, 19, 0.1f);
			EllieRenderer->CreateAnimation("Ellie_Walk_FRight", "Ellie_Walk.png", 44, 51, 0.1f);
			EllieRenderer->CreateAnimation("Ellie_Walk_BLeft", "Ellie_Walk.png", 60, 67, 0.1f);
			EllieRenderer->CreateAnimation("Ellie_Walk_Back", "Ellie_Walk.png", 68, 75, 0.1f);
			EllieRenderer->CreateAnimation("Ellie_Walk_BRight", "Ellie_Walk.png", 80, 87, 0.1f);
		}

		// EllieIdle
		{
			EllieRenderer->SetSprite("Ellie_Idle.png");
			//EllieRenderer->SetRelativeScale3D({ 76, 96, 1.0f });
			EllieRenderer->CreateAnimation("Ellie_Idle_FLeft", "Ellie_Idle.png", 0, 3, 0.1f);
			EllieRenderer->CreateAnimation("Ellie_Idle_Front", "Ellie_Idle.png", 4, 7, 0.1f);
			EllieRenderer->CreateAnimation("Ellie_Idle_FRight", "Ellie_Idle.png", 8, 11, 0.1f);
			EllieRenderer->CreateAnimation("Ellie_Idle_BLeft", "Ellie_Idle.png", 12, 15, 0.1f);
			EllieRenderer->CreateAnimation("Ellie_Idle_Back", "Ellie_Idle.png", 16, 19, 0.1f);
			EllieRenderer->CreateAnimation("Ellie_Idle_BRight", "Ellie_Idle.png", 20, 23, 0.1f);
		}

		//EllieRenderer->SetRelativeScale3D({ 76, 96, 1.0f });
		EllieRenderer->ChangeAnimation("Ellie_Idle_Front");
	}

	State = EEllieState::IDLE;

	{
		EllieCollision = CreateDefaultSubObject<UCollision>();
		EllieCollision->SetCollisionProfileName("Ellie");
		EllieCollision->SetScale3D(EllieSize);
		FVector CollisionCenter;
		CollisionCenter.Y = EllieSize.Y - EllieSize.Half().Y;
		EllieCollision->SetWorldLocation(CollisionCenter);
		EllieCollision->SetupAttachment(RootComponent);
	}

	SetColImage("TestBaseMap_Col.png", "Play");
}

AEllie::~AEllie()
{
}

void AEllie::BeginPlay()
{
	APawn::BeginPlay();
}

void AEllie::Tick(float _DeltaTime)
{
	APawn::Tick(_DeltaTime);

	switch (State)
	{
	case EEllieState::IDLE:
		Idle();
		break;
	case EEllieState::MOVE:
		Move(_DeltaTime);
		break;
	default:
		break;
	}
}

void AEllie::Idle()
{
	DirCheck();

	EllieRenderer->ChangeAnimation("Ellie_Idle" + DirString);

	if (true == UEngineInput::IsPress('W') || true == UEngineInput::IsPress('S') ||
		true == UEngineInput::IsPress('A') || true == UEngineInput::IsPress('D'))
	{
		State = EEllieState::MOVE;
	}
}

void AEllie::Move(float _DeltaTime)
{
	DirCheck();

	FVector Pos = FVector::ZERO;

	if (true == UEngineInput::IsPress('W'))
	{
		Pos += FVector::UP;
	}
	if (true == UEngineInput::IsPress('S'))
	{
		Pos += FVector::DOWN;
	}
	if (true == UEngineInput::IsPress('A'))
	{
		Pos += FVector::LEFT;
	}
	if (true == UEngineInput::IsPress('D'))
	{
		Pos += FVector::RIGHT;
	}

	if (IsMoveCheck(Pos.NormalizeReturn() * _DeltaTime * Speed))
	{
		AddActorLocation(Pos.NormalizeReturn() * _DeltaTime * Speed);	
	}
	
	EllieRenderer->ChangeAnimation("Ellie_Walk" + DirString);

	if (true == UEngineInput::IsUp('W') || true == UEngineInput::IsUp('S') ||
		true == UEngineInput::IsUp('A') || true == UEngineInput::IsUp('D'))
	{
		State = EEllieState::IDLE;
	}
}

bool AEllie::IsMoveCheck(FVector _Dir)
{
	std::vector<UCollision*> Result;
	if (false == EllieCollision->CollisionCheck("Room", _Dir, Result))
	{
		return false;
	}

	FVector EllieHalf = EllieSize.Half();
	FVector ElliePos = GetActorLocation();

	if (_Dir.X < 0)
	{
		EllieHalf.X *= -1.01f;
	}
	if (_Dir.Y < 0)
	{
		EllieHalf.Y *= -0.01f;
	}

	//                        RoomSize
	FVector NextPoint = FVector(250.0f, -250.0f) + GetActorLocation() + EllieHalf;
	NextPoint.Y *= -1.0f;

	UColor Color = ColImage.GetColor(NextPoint, UColor::WHITE);
	if (Color == UColor::MAGENTA) 
	{
		return false;
	}

	return true;
}

void AEllie::DirCheck()
{
	if (true == UEngineInput::IsPress('W'))
	{
		if (true == UEngineInput::IsPress('A'))
		{
			DirString = "_BLeft";
			return;
		}
		if (true == UEngineInput::IsPress('D'))
		{
			DirString = "_BRight";
			return;
		}

		DirString = "_Back";
	}
	if (true == UEngineInput::IsPress('S'))
	{
		if (true == UEngineInput::IsPress('A'))
		{
			DirString = "_FLeft";
			return;
		}
		if (true == UEngineInput::IsPress('D'))
		{
			DirString = "_FRight";
			return;
		}

		DirString = "_Front";
	}
	if (true == UEngineInput::IsPress('A'))
	{
		DirString = "_FLeft";
	}
	if (true == UEngineInput::IsPress('D'))
	{
		DirString = "_FRight";
	}
}

void AEllie::SetColImage(std::string_view _ColImageName, std::string_view _FolderName)
{
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("LWIWResources\\Image"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}

		Dir.Append(_FolderName);
		UEngineFile ImageFiles = Dir.GetFile(_ColImageName);

		ColImage.Load(nullptr, ImageFiles.GetPathToString());
	}
}

