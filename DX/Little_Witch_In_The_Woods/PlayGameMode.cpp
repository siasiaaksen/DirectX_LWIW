#include "PreCompile.h"
#include "PlayGameMode.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCamera.h>
#include "Ellie.h"
#include "Room.h"


APlayGameMode::APlayGameMode()
{
	GetWorld()->CreateCollisionProfile("Room");
	GetWorld()->CreateCollisionProfile("Ellie");
	GetWorld()->LinkCollisionProfile("Room", "Ellie");

	// ī�޶�
	{
		Camera = GetWorld()->GetMainCamera();
		Camera->SetActorLocation({ 0.0f, 0.0f, -624.0f, 1.0f});
		Camera->GetCameraComponent()->SetProjectionType(EProjectionType::Orthographic);
		Camera->GetCameraComponent()->SetZSort(0, true);
	}

	Ellie = GetWorld()->SpawnActor<AEllie>();
	Room = GetWorld()->SpawnActor<ARoom>();
	Room->SetRoomSize({ 1920.0f, 720.0f });
	Room->SetCollisionSize(FVector(1920.0f, 720.0f) - (Ellie->GetEllieSize() * 2.0f));
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	AActor::BeginPlay();
}

void APlayGameMode::Tick(float _DeltaTime)
{
	// �θ� ȣ��
	AActor::Tick(_DeltaTime);

	CameraMove();

	if (true == UEngineInput::IsDown(VK_HOME))
	{
		UEngineCore::OpenLevel("TitleLevel");
	}
}

void APlayGameMode::CameraMove()
{
	FVector RoomSize = Room->GetRoomSize();
	FVector WindowSize = UEngineCore::GetScreenScale();
	FVector ElliePos = Ellie->GetActorLocation();
	FVector CurCameraPos = { 0.0f, 0.0f, 0.0f };

	if (-RoomSize.Half().X + WindowSize.Half().X >= ElliePos.X)
	{
		CurCameraPos.X = -RoomSize.Half().X + WindowSize.Half().X;
	}
	else if (RoomSize.Half().X - WindowSize.Half().X <= ElliePos.X)
	{
		CurCameraPos.X = RoomSize.Half().X - WindowSize.Half().X;
	}
	else
	{
		CurCameraPos.X = ElliePos.X;
	}

	if (-RoomSize.Half().Y + WindowSize.Half().Y >= ElliePos.Y)
	{
		CurCameraPos.Y = -RoomSize.Half().Y + WindowSize.Half().Y;
	}
	else if (RoomSize.Half().Y - WindowSize.Half().Y <= ElliePos.Y)
	{
		CurCameraPos.Y = RoomSize.Half().Y - WindowSize.Half().Y;
	}
	else
	{
		CurCameraPos.Y = ElliePos.Y;
	}

	Camera->SetActorLocation({ CurCameraPos.X, CurCameraPos.Y, -624.0f });
}

