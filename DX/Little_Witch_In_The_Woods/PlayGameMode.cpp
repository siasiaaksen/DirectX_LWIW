#include "PreCompile.h"
#include "PlayGameMode.h"
#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineWinImage.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCamera.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include "ContentsEditorGUI.h"
#include "Ellie.h"
#include "Room.h"
#include "Mongsiri.h"
#include "MongsiriHole.h"
#include "EntranceCollision.h"


class UPlayGUIWindow : public UEngineGUIWindow
{
public:
	void OnGUI() override
	{
		//if (true == ImGui::Button("WindowButton"))
		//{
		//}

		if (true == ImGui::Button("FreeCameraOn"))
		{
			GetWorld()->GetMainCamera()->FreeCameraSwitch();
		}

		ImGui::SameLine();
		//ImGui::Text("test");
	}
};


APlayGameMode::APlayGameMode()
{
	GetWorld()->CreateCollisionProfile("Room");
	GetWorld()->CreateCollisionProfile("Ellie");
	GetWorld()->CreateCollisionProfile("MongsiriOuter");
	GetWorld()->CreateCollisionProfile("MongsiriInner");
	GetWorld()->CreateCollisionProfile("MongsiriHole");
	GetWorld()->CreateCollisionProfile("Entrance");
	GetWorld()->LinkCollisionProfile("Room", "Ellie");
	GetWorld()->LinkCollisionProfile("Ellie", "MongsiriOuter");
	GetWorld()->LinkCollisionProfile("Ellie", "MongsiriInner");
	GetWorld()->LinkCollisionProfile("MongsiriInner", "MongsiriHole");
	GetWorld()->LinkCollisionProfile("Ellie", "Entrance");

	// 카메라
	{
		Camera = GetWorld()->GetMainCamera();
		Camera->SetActorLocation({ 0.0f, 0.0f, -624.0f, 1.0f});
		Camera->GetCameraComponent()->SetProjectionType(EProjectionType::Orthographic);
		Camera->GetCameraComponent()->SetZSort(0, true);
	}
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	AActor::BeginPlay();

	Ellie = dynamic_cast<AEllie*>(GetWorld()->GetMainPawn());
	
	// Mid
	//Ellie->SetActorLocation({ 0.0f, -100.0f, 10.0f });
	// WitchHouseEntrance
	Ellie->SetActorLocation({ 1200.0f, 1000.0f, 10.0f });

	Room = GetWorld()->SpawnActor<ARoom>();

	Room->SetColImage("Map_Col.png", "Map");
	FVector RoomSize = Room->GetColImage().GetImageScale();

	Room->SetRoomSize(RoomSize);
	Room->SetCollisionSize(RoomSize - (Ellie->GetEllieSize()));
	Room->SetActorLocation({ 0.0f, 0.0f, 1000.0f });

	Mongsiri = GetWorld()->SpawnActor<AMongsiri>();
	Mongsiri->SetActorLocation({ 0.0f, -300.0f, 100.0f });

	std::shared_ptr<AMongsiriHole> MongsiriHole = GetWorld()->SpawnActor<AMongsiriHole>();
	MongsiriHole->SetActorLocation({ 0.0f, 0.0f, 10.0f });

	EntranceCol = GetWorld()->SpawnActor<AEntranceCollision>();
}

void APlayGameMode::Tick(float _DeltaTime)
{
	// 부모 호출
	AActor::Tick(_DeltaTime);

	CameraMove();

	RoomChange();

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

	if ((RoomSize.X > WindowSize.X) && (RoomSize.Y > WindowSize.Y))
	{
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
}

void APlayGameMode::RoomChange()
{
	if (true == UEngineInput::IsPress('Q'))
	{
		//Camera->SetActorLocation({ 0.0f, 0.0f, -624.0f, 1.0f });
		Room->SetRoomSize({ 2000.0f, 800.0f });
		Room->SetCollisionSize(Room->GetRoomSize() - (Ellie->GetEllieSize()/* * 2.0f*/));
	}
}

void APlayGameMode::LevelChangeStart()
{
	UEngineGUI::AllWindowOff();

	{
		std::shared_ptr<UContentsEditorGUI> Window = UEngineGUI::FindGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");

		if (nullptr == Window)
		{
			Window = UEngineGUI::CreateGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");
		}

		Window->SetActive(true);
	}

	{
		std::shared_ptr<UPlayGUIWindow> Window = UEngineGUI::FindGUIWindow<UPlayGUIWindow>("UPlayGUIWindow");

		if (nullptr == Window)
		{
			Window = UEngineGUI::CreateGUIWindow<UPlayGUIWindow>("UPlayGUIWindow");
		}

		Window->SetActive(true);
	}
}
