#include "PreCompile.h"
#include "PlayGameMode.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCamera.h>
#include "Ellie.h"
#include "Room.h"


APlayGameMode::APlayGameMode()
{
	// 카메라
	{
		Camera = GetWorld()->GetMainCamera();
		Camera->SetActorLocation({ 0.0f, 0.0f, -624.0f, 1.0f });
		Camera->GetCameraComponent()->SetProjectionType(EProjectionType::Orthographic);
		Camera->GetCameraComponent()->SetZSort(0, true);
	}

	Ellie = GetWorld()->SpawnActor<AEllie>();
	Room = GetWorld()->SpawnActor<ARoom>();
	Room->SetRoomSize({ 1920.0f, 720.0f });
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
	// 부모 호출
	AActor::Tick(_DeltaTime);

	CameraMove();

	if (true == UEngineInput::IsDown(VK_HOME))
	{
		UEngineCore::OpenLevel("TitleLevel");
	}
}

bool APlayGameMode::IsCameraMove()
{
	FVector RoomSize = Room->GetRoomSize();
	FVector ElliePos = Ellie->GetActorTransform().Location;
	FVector EllieSize = Ellie->GetActorTransform().Scale;
	FVector WindowSize = UEngineCore::GetMainWindow().GetWindowSize();
	FVector CameraPos = Camera->GetActorTransform().Location;

	if (-RoomSize.Half().X + WindowSize.Half().X < ElliePos.X)
	{
		return true;
	}

	if (-RoomSize.Half().Y + WindowSize.Half().Y < ElliePos.Y)
	{
		return true;
	}

	if (RoomSize.Half().X - WindowSize.Half().X > ElliePos.X)
	{
		return true;
	}

	if (RoomSize.Half().Y - WindowSize.Half().Y > ElliePos.Y)
	{
		return true;
	}

	return false;
}

void APlayGameMode::CameraMove()
{
	if (true == IsCameraMove())
	{
		Camera->SetActorLocation(Ellie->GetActorTransform().Location);
	}
}

