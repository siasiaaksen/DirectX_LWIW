#include "PreCompile.h"
#include "Ellie.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/Collision.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/CameraActor.h>
#include "Room.h"
#include "Mongsiri.h"
#include "Tree.h"


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
			EllieRenderer->CreateAnimation("Ellie_Walk_FLeft", "Ellie_Walk.png", 28, 35, AnimSpeed);
			EllieRenderer->CreateAnimation("Ellie_Walk_Front", "Ellie_Walk.png", 12, 19, AnimSpeed);
			EllieRenderer->CreateAnimation("Ellie_Walk_FRight", "Ellie_Walk.png", 44, 51, AnimSpeed);
			EllieRenderer->CreateAnimation("Ellie_Walk_BLeft", "Ellie_Walk.png", 60, 67, AnimSpeed);
			EllieRenderer->CreateAnimation("Ellie_Walk_Back", "Ellie_Walk.png", 68, 75, AnimSpeed);
			EllieRenderer->CreateAnimation("Ellie_Walk_BRight", "Ellie_Walk.png", 80, 87, AnimSpeed);
		}

		// EllieIdle
		{
			EllieRenderer->SetSprite("Ellie_Idle.png");
			//EllieRenderer->SetRelativeScale3D({ 76, 96, 1.0f });
			EllieRenderer->CreateAnimation("Ellie_Idle_FLeft", "Ellie_Idle.png", 0, 3, AnimSpeed);
			EllieRenderer->CreateAnimation("Ellie_Idle_Front", "Ellie_Idle.png", 4, 7, AnimSpeed);
			EllieRenderer->CreateAnimation("Ellie_Idle_FRight", "Ellie_Idle.png", 8, 11, AnimSpeed);
			EllieRenderer->CreateAnimation("Ellie_Idle_BLeft", "Ellie_Idle.png", 12, 15, AnimSpeed);
			EllieRenderer->CreateAnimation("Ellie_Idle_Back", "Ellie_Idle.png", 16, 19, AnimSpeed);
			EllieRenderer->CreateAnimation("Ellie_Idle_BRight", "Ellie_Idle.png", 20, 23, AnimSpeed);
		}

		// EllieCollectingMongsiri
		{
			EllieRenderer->SetSprite("Ellie_Collection_Mongsiri.png");
			EllieRenderer->CreateAnimation("Ellie_Collecting_FLeft_M", "Ellie_Collection_Mongsiri.png", 0, 4, 0.4f, false);
			EllieRenderer->CreateAnimation("Ellie_Collecting_FRight_M", "Ellie_Collection_Mongsiri.png", 5, 9, 0.4f, false);
		}

		// EllieCollectingWitchFlower
		{
			EllieRenderer->SetSprite("Ellie_Collection_WitchFlower.png");
			EllieRenderer->CreateAnimation("Ellie_Collecting_FLeft_F", "Ellie_Collection_WitchFlower.png", 0, 8, 0.4f, false);
			EllieRenderer->CreateAnimation("Ellie_Collecting_FRight_F", "Ellie_Collection_WitchFlower.png", 9, 17, 0.4f, false);
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

	SetColImage("Map_Col.png", "Map");
}

AEllie::~AEllie()
{
}

void AEllie::BeginPlay()
{
	APawn::BeginPlay();
}

void AEllie::EllieSpeedUpDown()
{
	if (true == UEngineInput::IsDown(VK_INSERT))
	{
		Speed += 100.0f;
	}

	if (true == UEngineInput::IsDown(VK_DELETE))
	{
		Speed -= 100.0f;
	}
}

void AEllie::Tick(float _DeltaTime)
{
	APawn::Tick(_DeltaTime);

	EllieSpeedUpDown();

	switch (State)
	{
	case EEllieState::IDLE:
		Idle(_DeltaTime);
		CollectItem(_DeltaTime);
		break;
	case EEllieState::MOVE:
		Move(_DeltaTime);
		break;
	case EEllieState::COLLECTING:
		Collecting(_DeltaTime);
		break;
	default:
		break;
	}
	
	// Sorting
	{
		FVector Pos = GetActorLocation();
		Pos.Z = Pos.Y;

		SetActorLocation(Pos);
	}
}

void AEllie::Idle(float _DeltaTime)
{
	DirCheck();

	EllieRenderer->ChangeAnimation("Ellie_Idle" + DirName);

	if (true == UEngineInput::IsPress(VK_UP) || true == UEngineInput::IsPress(VK_DOWN) ||
		true == UEngineInput::IsPress(VK_LEFT) || true == UEngineInput::IsPress(VK_RIGHT))
	{
		State = EEllieState::MOVE;
	}
}

void AEllie::Move(float _DeltaTime)
{
	DirCheck();

	FVector Pos = FVector::ZERO;

	if (true == UEngineInput::IsPress(VK_UP))
	{
		Pos += FVector::UP;
	}
	if (true == UEngineInput::IsPress(VK_DOWN))
	{
		Pos += FVector::DOWN;
	}
	if (true == UEngineInput::IsPress(VK_LEFT))
	{
		Pos += FVector::LEFT;
	}
	if (true == UEngineInput::IsPress(VK_RIGHT))
	{
		Pos += FVector::RIGHT;
	}

	if (IsMoveCheck(Pos.NormalizeReturn() * _DeltaTime * Speed))
	{
		AddActorLocation(Pos.NormalizeReturn() * _DeltaTime * Speed);	
	}
	
	EllieRenderer->ChangeAnimation("Ellie_Walk" + DirName);

	if (true == UEngineInput::IsUp(VK_UP) || true == UEngineInput::IsUp(VK_DOWN) ||
		true == UEngineInput::IsUp(VK_LEFT) || true == UEngineInput::IsUp(VK_RIGHT))
	{
		State = EEllieState::IDLE;
	}
}

void AEllie::Collecting(float _DeltaTime)
{
	int Frame = 0;

	if (Mongsiri->GetActorLocation().X - GetActorLocation().X <= 0)
	{
		DirName = "_FLeft";
		Frame = 4;
	}
	else
	{
		DirName = "_FRight";
		Frame = 9;
	}

	EllieRenderer->ChangeAnimation("Ellie_Collecting" + DirName + "_M");
	EllieRenderer->SetAnimationEvent("Ellie_Collecting" + DirName + "_M", Frame, [this]() { State = EEllieState::IDLE; });
}

bool AEllie::IsMoveCheck(FVector _Dir)
{
	std::vector<UCollision*> Result;
	if (false == EllieCollision->CollisionCheck("Room", _Dir, Result))
	{
		return false;
	}

	//std::vector<UCollision*> Result2;
	//if (true == EllieCollision->CollisionCheck("Tree", _Dir, Result2))
	//{
	//	ATree* Tree = dynamic_cast<ATree*>(Result2[0]->GetActor());

	//	//if (GetActorLocation().Z <= Tree->GetActorLocation().Z)
	//	//{
	//	//}
	//	//	return false;
	//}

	FVector EllieHalf = EllieSize.Half();

	if (_Dir.X < 0)
	{
		EllieHalf.X -= EllieHalf.X * 2.0f;
	}
	if (_Dir.X >= 0)
	{
		EllieHalf.X *= 0.1f;
	}
	if (_Dir.Y < 0)
	{
		EllieHalf.Y -= EllieHalf.Y * 1.0f;
	}
	if (_Dir.Y >= 0)
	{
		EllieHalf.Y -= EllieHalf.Y * 0.5f;
	}

	FVector ColImageSize = FVector(ColImage.GetImageScale().Half().X, -ColImage.GetImageScale().Half().Y);

	//                    RoomSize
	FVector NextPoint = ColImageSize + GetActorLocation() + EllieHalf;
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
	if (true == UEngineInput::IsPress(VK_UP))
	{
		if (true == UEngineInput::IsPress(VK_LEFT))
		{
			DirName = "_BLeft";
			return;
		}
		if (true == UEngineInput::IsPress(VK_RIGHT))
		{
			DirName = "_BRight";
			return;
		}

		DirName = "_Back";
	}
	if (true == UEngineInput::IsPress(VK_DOWN))
	{
		if (true == UEngineInput::IsPress(VK_LEFT))
		{
			DirName = "_FLeft";
			return;
		}
		if (true == UEngineInput::IsPress(VK_RIGHT))
		{
			DirName = "_FRight";
			return;
		}

		DirName = "_Front";
	}
	if (true == UEngineInput::IsPress(VK_LEFT))
	{
		DirName = "_FLeft";
	}
	if (true == UEngineInput::IsPress(VK_RIGHT))
	{
		DirName = "_FRight";
	}
}

void AEllie::SetColImage(std::string_view _ColImageName, std::string_view _FolderName)
{
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("LWIWResources\\Image\\Play"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}

		Dir.Append(_FolderName);
		UEngineFile ImageFiles = Dir.GetFile(_ColImageName);

		ColImage.Load(nullptr, ImageFiles.GetPathToString());
	}
}

void AEllie::CollectItem(float _DeltaTime)
{
	// 엘리 위치 이동 및 크리쳐의 콜랙트 관련 함수 호출

	std::vector<UCollision*> Result;
	if (true == EllieCollision->CollisionCheck("MongsiriInner", Result))
	{
		if (true == UEngineInput::IsDown('Z'))
		{
			Mongsiri = dynamic_cast<AMongsiri*>(Result[0]->GetActor());

			FVector StartPos = GetActorLocation();
			FVector EndPos = Mongsiri->GetActorLocation();

			FVector CurPos = FVector::Lerp(StartPos, EndPos, _DeltaTime * 2.0f);

			SetActorLocation(CurPos);
			
			State = EEllieState::COLLECTING;
			Mongsiri->SetSort(false);
			Mongsiri->SetState(EMongsiriState::COLLECTED);
		}
	}
}
