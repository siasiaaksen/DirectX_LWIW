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
		Camera->SetActorLocation({ 0.0f, 0.0f, -624.0f, 1.0f});
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
	FVector ElliePos = Ellie->GetActorLocation();
	FVector WindowSize = UEngineCore::GetMainWindow().GetWindowSize();

	float X1 = -RoomSize.Half().X + WindowSize.Half().X;
	float X2 = RoomSize.Half().X - WindowSize.Half().X > ElliePos.X;
	float ElliePosX = ElliePos.X;
	float ElliePosY = ElliePos.Y;

	int a = 0;

	if (-RoomSize.Half().X <= ElliePos.X - WindowSize.Half().X)
	{
		return true;
	}

	if (RoomSize.Half().X >= ElliePos.X + WindowSize.Half().X)
	{
		return true;
	}

	return false;
}

void APlayGameMode::CameraMove()
{
	FVector RoomSize = Room->GetRoomSize();
	FVector WindowSize = UEngineCore::GetScreenScale();
	FVector ElliePos = Ellie->GetActorLocation();
	FVector CameraPos = Camera->GetActorLocation();;
	FVector CurCameraPos = { 0.0f, 0.0f, 0.0f };

	if (-RoomSize.Half().X + WindowSize.Half().X >= CameraPos.X)
	{
		CurCameraPos.X = -RoomSize.Half().X + WindowSize.Half().X;
	}
	else if (RoomSize.Half().X - WindowSize.Half().X <= CameraPos.X)
	{
		CurCameraPos.X = RoomSize.Half().X - WindowSize.Half().X;
	}
	else
	{
		CurCameraPos.X = ElliePos.X;
	}

	if (-RoomSize.Half().Y + WindowSize.Half().Y >= CameraPos.Y)
	{
		CurCameraPos.Y = -RoomSize.Half().Y + WindowSize.Half().Y;
	}
	else if (RoomSize.Half().Y - WindowSize.Half().Y <= CameraPos.Y)
	{
		CurCameraPos.Y = RoomSize.Half().Y - WindowSize.Half().Y;
	}
	else
	{
		CurCameraPos.Y = ElliePos.Y;
	}

	Camera->SetActorLocation({ CurCameraPos.X, CurCameraPos.Y, -624.0f });
}

