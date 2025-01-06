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

	if (true == UEngineInput::IsDown(VK_HOME))
	{
		UEngineCore::OpenLevel("TitleLevel");
	}

	FVector RoomSize = Room->GetRoomSize();
	FVector ElliePos = Ellie->GetActorTransform().Location;
	FVector WindowSize = UEngineCore::GetMainWindow().GetWindowSize();

	FVector Pos = ElliePos - WindowSize;


	int a = 0;

	// 엘리 따라다니게, 범위 밖으로 못 나가게
	{
		if (ElliePos.X - WindowSize.X > 0 &&
			ElliePos.X - WindowSize.X < RoomSize.X &&
			ElliePos.Y - WindowSize.Y > 0 &&
			ElliePos.Y - WindowSize.Y < RoomSize.Y)
		{
			Camera->SetActorLocation(Ellie->GetActorTransform().Location);
		}

		//Camera->SetActorLocation(Ellie->GetActorTransform().Location);
	}
}

