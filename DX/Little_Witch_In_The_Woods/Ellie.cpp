#include "PreCompile.h"
#include "Ellie.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineSprite.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/CameraActor.h>


AEllie::AEllie()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	EllieRenderer = CreateDefaultSubObject<USpriteRenderer>();

	// EllieWalk
	{
		EllieRenderer->SetSprite("Ellie_Walk.png");
		//EllieRenderer->SetRelativeScale3D({ 73, 92, 1.0f });
		EllieRenderer->CreateAnimation("Ellie_Walk_FLeft", "Ellie_Walk.png", 28, 35, 0.1f);
		{
			USpriteRenderer::FrameAnimation* Animation = EllieRenderer->FindAnimation("Ellie_Walk_FLeft");
			Animation->IsAutoScale = true;
			Animation->AutoScaleRatio = 1.0f;
		}
		EllieRenderer->CreateAnimation("Ellie_Walk_Front", "Ellie_Walk.png", 12, 19, 0.1f);
				{
			USpriteRenderer::FrameAnimation* Animation = EllieRenderer->FindAnimation("Ellie_Walk_Front");
			Animation->IsAutoScale = true;
			Animation->AutoScaleRatio = 1.0f;
		}
		EllieRenderer->CreateAnimation("Ellie_Walk_FRight", "Ellie_Walk.png", 44, 51, 0.1f);
		{
			USpriteRenderer::FrameAnimation* Animation = EllieRenderer->FindAnimation("Ellie_Walk_FRight");
			Animation->IsAutoScale = true;
			Animation->AutoScaleRatio = 1.0f;
		}
		EllieRenderer->CreateAnimation("Ellie_Walk_BLeft", "Ellie_Walk.png", 60, 67, 0.1f);
		{
			USpriteRenderer::FrameAnimation* Animation = EllieRenderer->FindAnimation("Ellie_Walk_BLeft");
			Animation->IsAutoScale = true;
			Animation->AutoScaleRatio = 1.0f;
		}
		EllieRenderer->CreateAnimation("Ellie_Walk_Back", "Ellie_Walk.png", 68, 75, 0.1f);
		{
			USpriteRenderer::FrameAnimation* Animation = EllieRenderer->FindAnimation("Ellie_Walk_Back");
			Animation->IsAutoScale = true;
			Animation->AutoScaleRatio = 1.0f;
		}
		EllieRenderer->CreateAnimation("Ellie_Walk_BRight", "Ellie_Walk.png", 80, 87, 0.1f);
		{
			USpriteRenderer::FrameAnimation* Animation = EllieRenderer->FindAnimation("Ellie_Walk_BRight");
			Animation->IsAutoScale = true;
			Animation->AutoScaleRatio = 1.0f;
		}
	}

	// EllieIdle
	{
		EllieRenderer->SetSprite("Ellie_Idle.png");
		//EllieRenderer->SetRelativeScale3D({ 76, 96, 1.0f });
		EllieRenderer->CreateAnimation("Ellie_Idle_FLeft", "Ellie_Idle.png", 0, 3, 0.1f);
		{
			USpriteRenderer::FrameAnimation* Animation = EllieRenderer->FindAnimation("Ellie_Idle_FLeft");
			Animation->IsAutoScale = true;
			Animation->AutoScaleRatio = 1.0f;
		}
		EllieRenderer->CreateAnimation("Ellie_Idle_Front", "Ellie_Idle.png", 4, 7, 0.1f);
		{
			USpriteRenderer::FrameAnimation* Animation = EllieRenderer->FindAnimation("Ellie_Idle_Front");
			Animation->IsAutoScale = true;
			Animation->AutoScaleRatio = 1.0f;
		}
		EllieRenderer->CreateAnimation("Ellie_Idle_FRight", "Ellie_Idle.png", 8, 11, 0.1f);
		{
			USpriteRenderer::FrameAnimation* Animation = EllieRenderer->FindAnimation("Ellie_Idle_FRight");
			Animation->IsAutoScale = true;
			Animation->AutoScaleRatio = 1.0f;
		}
		EllieRenderer->CreateAnimation("Ellie_Idle_BLeft", "Ellie_Idle.png", 12, 15, 0.1f);
		{
			USpriteRenderer::FrameAnimation* Animation = EllieRenderer->FindAnimation("Ellie_Idle_BLeft");
			Animation->IsAutoScale = true;
			Animation->AutoScaleRatio = 1.0f;
		}
		EllieRenderer->CreateAnimation("Ellie_Idle_Back", "Ellie_Idle.png", 16, 19, 0.1f);
		{
			USpriteRenderer::FrameAnimation* Animation = EllieRenderer->FindAnimation("Ellie_Idle_Back");
			Animation->IsAutoScale = true;
			Animation->AutoScaleRatio = 1.0f;
		}
		EllieRenderer->CreateAnimation("Ellie_Idle_BRight", "Ellie_Idle.png", 20, 23, 0.1f);
		{
			USpriteRenderer::FrameAnimation* Animation = EllieRenderer->FindAnimation("Ellie_Idle_BRight");
			Animation->IsAutoScale = true;
			Animation->AutoScaleRatio = 1.0f;
		}
	}

	//EllieRenderer->SetRelativeScale3D({ 76, 96, 1.0f });
	EllieRenderer->ChangeAnimation("Ellie_Idle_Front");
	EllieRenderer->SetupAttachment(RootComponent);

	// 카메라가 엘리를 따라다니게
	Camera = GetWorld()->GetMainCamera();
	Camera->AttachToActor(this);

	State = EEllieState::IDLE;
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
	switch (PosValue)
	{
	case 0:
		EllieRenderer->ChangeAnimation("Ellie_Idle_Front");
		break;
	case 1:
		EllieRenderer->ChangeAnimation("Ellie_Idle_Back");
		break;
	case 2:
		EllieRenderer->ChangeAnimation("Ellie_Idle_FLeft");
		break;
	case 3:
		EllieRenderer->ChangeAnimation("Ellie_Idle_FRight");
		break;
	case 4:
		EllieRenderer->ChangeAnimation("Ellie_Idle_BLeft");
		break;
	case 5:
		EllieRenderer->ChangeAnimation("Ellie_Idle_BRight");
		break;
	default:
		break;
	}

	if (true == UEngineInput::IsPress('W') || true == UEngineInput::IsPress('S') ||
		true == UEngineInput::IsPress('A') || true == UEngineInput::IsPress('D'))
	{
		State = EEllieState::MOVE;
	}
}

void AEllie::Move(float _DeltaTime)
{
	if (true == UEngineInput::IsPress('W'))
	{
		if (true == UEngineInput::IsPress('A'))
		{
			EllieRenderer->ChangeAnimation("Ellie_Walk_BLeft");
			AddActorLocation(FVector({ -1.0f, 1.0f }).NormalizeReturn() * _DeltaTime * 80.0f);
			PosValue = 4;
			return;
		}
		if (true == UEngineInput::IsPress('D'))
		{
			EllieRenderer->ChangeAnimation("Ellie_Walk_BRight");
			AddActorLocation(FVector({ 1.0f, 1.0f }).NormalizeReturn() * _DeltaTime * 80.0f);
			PosValue = 5;
			return;
		}

		EllieRenderer->ChangeAnimation("Ellie_Walk_Back");
		AddActorLocation(FVector({ 0.0f, 1.0f }) * _DeltaTime * 80.0f);
		PosValue = 1;
	}
	if (true == UEngineInput::IsPress('S'))
	{
		if (true == UEngineInput::IsPress('A'))
		{
			EllieRenderer->ChangeAnimation("Ellie_Walk_FLeft");
			AddActorLocation(FVector({ -1.0f, -1.0f }).NormalizeReturn() * _DeltaTime * 80.0f);
			PosValue = 2;
			return;
		}
		if (true == UEngineInput::IsPress('D'))
		{
			EllieRenderer->ChangeAnimation("Ellie_Walk_FRight");
			AddActorLocation(FVector({ 1.0f, -1.0f }).NormalizeReturn() * _DeltaTime * 80.0f);
			PosValue = 3;
			return;
		}

		EllieRenderer->ChangeAnimation("Ellie_Walk_Front");
		AddActorLocation(FVector({ 0.0f, -1.0f }) * _DeltaTime * 80.0f);
		PosValue = 0;
	}
	if (true == UEngineInput::IsPress('A'))
	{
		EllieRenderer->ChangeAnimation("Ellie_Walk_FLeft");
		AddActorLocation(FVector({ -1.0f, 0.0f }) * _DeltaTime * 80.0f);
		PosValue = 2;
	}
	if (true == UEngineInput::IsPress('D'))
	{
		EllieRenderer->ChangeAnimation("Ellie_Walk_FRight");
		AddActorLocation(FVector({ 1.0f, 0.0f }) * _DeltaTime * 80.0f);
		PosValue = 3;
	}

	if (true == UEngineInput::IsUp('W') || true == UEngineInput::IsUp('S') ||
		true == UEngineInput::IsUp('A') || true == UEngineInput::IsUp('D'))
	{
		State = EEllieState::IDLE;
	}
}




