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
#include "WitchFlower.h"
#include "InteractCollision.h"
#include "MapObject.h"
#include "InteractObject.h"


class UPlayGUIWindow : public UEngineGUIWindow
{
public:
	void OnGUI() override
	{
		if (true == ImGui::Button("FreeCameraOn"))
		{
			GetWorld()->GetMainCamera()->FreeCameraSwitch();
		}

		ImGui::SameLine();
	}
};


APlayGameMode::APlayGameMode()
{
	GetWorld()->CreateCollisionProfile("Room");
	GetWorld()->CreateCollisionProfile("Ellie");
	GetWorld()->CreateCollisionProfile("EllieInner");
	GetWorld()->CreateCollisionProfile("MongsiriOuter");
	GetWorld()->CreateCollisionProfile("MongsiriInner");
	GetWorld()->CreateCollisionProfile("MongsiriEscape");
	GetWorld()->CreateCollisionProfile("WitchFlower");
	GetWorld()->CreateCollisionProfile("InterCol");
	GetWorld()->CreateCollisionProfile("MapObject");
	GetWorld()->CreateCollisionProfile("InteractObject");

	GetWorld()->LinkCollisionProfile("Room", "Ellie");
	GetWorld()->LinkCollisionProfile("Ellie", "MongsiriOuter");
	GetWorld()->LinkCollisionProfile("Ellie", "MongsiriInner");
	GetWorld()->LinkCollisionProfile("Ellie", "WitchFlower");
	GetWorld()->LinkCollisionProfile("MongsiriEscape", "InterCol");
	GetWorld()->LinkCollisionProfile("Ellie", "InterCol");
	GetWorld()->LinkCollisionProfile("EllieInner", "MapObject");

	// 카메라
	{
		Camera = GetWorld()->GetMainCamera();
		Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
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
	//Ellie->SetActorLocation({ 0.0f, 0.0f, 10.0f });
	// WitchHouseEntrance
	Ellie->SetActorLocation({ 1000.0f, 1200.0f, 10.0f });

	Room = GetWorld()->SpawnActor<ARoom>();

	{
		Ellie->SetColImage("WitchHouse_Outside_Col.png", "Map");
		Room->SetColImage("WitchHouse_Outside_Col.png", "Map");
		FVector RoomSize = Room->GetColImage().GetImageScale();

		Room->SetRoomSprite("WitchHouse_Outside.png", RoomSize);
		Room->SetRoomColSprite("WitchHouse_Outside_Col.png");

		FVector ColSize = RoomSize - (Ellie->GetEllieSize());
		Room->SetCollisionSize(RoomSize - (Ellie->GetEllieSize()));
		Room->SetActorLocation({ 0.0f, 0.0f, 1000.0f });

		Ellie->SetActorLocation({ -50.0f, -500.0f, 10.0f });

		{
			const std::string Path = ".\\..\\LWIWResources\\Data\\WitchHouse_Outside.MapData";
			UEngineFile FIle = Path;
			FIle.FileOpen("rb");

			UEngineSerializer Ser;
			FIle.Read(Ser);

			int ListNum;
			Ser >> ListNum;

			LoadData(Ser, ListNum);
		}

		Camera->SetActorLocation({ Ellie->GetActorLocation().X, Ellie->GetActorLocation().Y, -624.0f, 1.0f });
	}
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
	if (true == UEngineInput::IsDown(VK_F2))
	{
		std::list<std::shared_ptr<UCollision>> AllColList = GetWorld()->GetAllActorListByClass<UCollision>();
		for (std::shared_ptr<UCollision> Collision : AllColList)
		{
			Collision->DebugRenderSwitch();
		}

		Room->GetRoomColSprite()->SetActiveSwitch();
	}
}

void APlayGameMode::CameraMove()
{
	RoomSize = Room->GetRoomSize();
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
	std::list<std::shared_ptr<AInteractCollision>> AllInterColList = GetWorld()->GetAllActorListByClass<AInteractCollision>();
	for (std::shared_ptr<AInteractCollision> InterCol : AllInterColList)
	{
		std::vector<UCollision*> Result;
		if (true == InterCol->GetInterCol()->CollisionCheck("Ellie", Result))
		{
			std::string InterColName = InterCol->GetInterColName();
			if (InterCol->GetInterColName() == "WitchHouseYard")
			{
				{
					std::list<std::shared_ptr<AInteractCollision>> AllInterColList = GetWorld()->GetAllActorListByClass<AInteractCollision>();
					for (std::shared_ptr<AInteractCollision> InterCol : AllInterColList)
					{
						InterCol->Destroy();
					}

					std::list<std::shared_ptr<AMapObject>> AllMapObjectList = GetWorld()->GetAllActorListByClass<AMapObject>();
					for (std::shared_ptr<AMapObject> MapObject : AllMapObjectList)
					{
						MapObject->Destroy();
					}

					std::list<std::shared_ptr<AInteractObject>> AllInteractObjectList = GetWorld()->GetAllActorListByClass<AInteractObject>();
					for (std::shared_ptr<AInteractObject> InteractObject : AllInteractObjectList)
					{
						InteractObject->Destroy();
					}
				}

				{
					Ellie->SetColImage("Map_Col.png", "Map");
					Room->SetColImage("Map_Col.png", "Map");
					FVector RoomSize = Room->GetColImage().GetImageScale();

					Room->SetRoomSprite("Map.png", RoomSize);
					Room->SetRoomColSprite("Map_Col.png");

					FVector ColSize = RoomSize - (Ellie->GetEllieSize());
					Room->SetCollisionSize(RoomSize - (Ellie->GetEllieSize()));
					Room->SetActorLocation({ 0.0f, 0.0f, 1000.0f });

					Ellie->SetActorLocation({ 450.0f, 1200.0f, 10.0f });

					// Creature
					{
						Mongsiri = GetWorld()->SpawnActor<AMongsiri>();
						Mongsiri->SetActorLocation({ 1100.0f, 1000.0f, 100.0f });

						WitchFlower = GetWorld()->SpawnActor<AWitchFlower>();
						WitchFlower->SetActorLocation({ 800.0f, 900.0f, 100.0f });
					}

					{
						const std::string Path = ".\\..\\LWIWResources\\Data\\MainMap.MapData";
						UEngineFile FIle = Path;
						FIle.FileOpen("rb");

						UEngineSerializer Ser;
						FIle.Read(Ser);

						int ListNum;
						Ser >> ListNum;

						LoadData(Ser, ListNum);
					}
				}
			}

			if (InterCol->GetInterColName() == "MainMap")
			{
				{
					std::list<std::shared_ptr<AInteractCollision>> AllInterColList = GetWorld()->GetAllActorListByClass<AInteractCollision>();
					for (std::shared_ptr<AInteractCollision> InterCol : AllInterColList)
					{
						InterCol->Destroy();
					}

					std::list<std::shared_ptr<AMapObject>> AllMapObjectList = GetWorld()->GetAllActorListByClass<AMapObject>();
					for (std::shared_ptr<AMapObject> MapObject : AllMapObjectList)
					{
						MapObject->Destroy();
					}

					std::list<std::shared_ptr<AInteractObject>> AllInteractObjectList = GetWorld()->GetAllActorListByClass<AInteractObject>();
					for (std::shared_ptr<AInteractObject> InteractObject : AllInteractObjectList)
					{
						InteractObject->Destroy();
					}
				}

				{
					Ellie->SetColImage("WitchHouse_Outside_Col.png", "Map");
					Room->SetColImage("WitchHouse_Outside_Col.png", "Map");
					FVector RoomSize = Room->GetColImage().GetImageScale();

					Room->SetRoomSprite("WitchHouse_Outside.png", RoomSize);
					Room->SetRoomColSprite("WitchHouse_Outside_Col.png");

					FVector ColSize = RoomSize - (Ellie->GetEllieSize());
					Room->SetCollisionSize(RoomSize - (Ellie->GetEllieSize()));
					Room->SetActorLocation({ 0.0f, 0.0f, 1000.0f });

					Ellie->SetActorLocation({ -50.0f, -500.0f, 10.0f });

					{
						const std::string Path = ".\\..\\LWIWResources\\Data\\WitchHouse_Outside.MapData";
						UEngineFile FIle = Path;
						FIle.FileOpen("rb");

						UEngineSerializer Ser;
						FIle.Read(Ser);

						int ListNum;
						Ser >> ListNum;

						LoadData(Ser, ListNum);
					}
				}
			}

			{
				/*if (InterCol->GetInterColName() == "WitchHouse")
				{
					{
						std::list<std::shared_ptr<AInteractCollision>> AllInterColList = GetWorld()->GetAllActorListByClass<AInteractCollision>();
						for (std::shared_ptr<AInteractCollision> InterCol : AllInterColList)
						{
							InterCol->Destroy();
						}

						std::list<std::shared_ptr<AMapObject>> AllMapObjectList = GetWorld()->GetAllActorListByClass<AMapObject>();
						for (std::shared_ptr<AMapObject> MapObject : AllMapObjectList)
						{
							MapObject->Destroy();
						}

						std::list<std::shared_ptr<AInteractObject>> AllInteractObjectList = GetWorld()->GetAllActorListByClass<AInteractObject>();
						for (std::shared_ptr<AInteractObject> InteractObject : AllInteractObjectList)
						{
							InteractObject->Destroy();
						}
					}

					{
						Ellie->SetColImage("WitchHouse1F_Col.png", "Map");
						Room->SetColImage("WitchHouse1F_Col.png", "Map");
						FVector RoomSize = Room->GetColImage().GetImageScale();

						Room->SetRoomSprite("WitchHouse1F.png", RoomSize);
						Room->SetRoomColSprite("WitchHouse1F_Col.png");

						FVector ColSize = RoomSize - (Ellie->GetEllieSize());
						Room->SetCollisionSize(RoomSize - (Ellie->GetEllieSize()));
						Room->SetActorLocation({ 0.0f, 0.0f, 1000.0f });

						Ellie->SetActorLocation({ 0.0f, -110.0f, 10.0f });

						Camera->SetActorLocation({ 0.0f, 0.0f, -624.0f, 1.0f });

						{
							const std::string Path = ".\\..\\LWIWResources\\Data\\WitchHouseF1.MapData";
							UEngineFile FIle = Path;
							FIle.FileOpen("rb");

							UEngineSerializer Ser;
							FIle.Read(Ser);

							int ListNum;
							Ser >> ListNum;

							LoadData(Ser, ListNum);
						}
					}
				}*/
			}

			if (InterCol->GetInterColName() == "WitchHouse")
			{
				{
					std::list<std::shared_ptr<AInteractCollision>> AllInterColList = GetWorld()->GetAllActorListByClass<AInteractCollision>();
					for (std::shared_ptr<AInteractCollision> InterCol : AllInterColList)
					{
						InterCol->Destroy();
					}

					std::list<std::shared_ptr<AMapObject>> AllMapObjectList = GetWorld()->GetAllActorListByClass<AMapObject>();
					for (std::shared_ptr<AMapObject> MapObject : AllMapObjectList)
					{
						MapObject->Destroy();
					}

					std::list<std::shared_ptr<AInteractObject>> AllInteractObjectList = GetWorld()->GetAllActorListByClass<AInteractObject>();
					for (std::shared_ptr<AInteractObject> InteractObject : AllInteractObjectList)
					{
						InteractObject->Destroy();
					}
				}

				{
					Ellie->SetColImage("Basement_Col.png", "Map");
					Room->SetColImage("Basement_Col.png", "Map");
					FVector RoomSize = Room->GetColImage().GetImageScale();

					Room->SetRoomSprite("Basement.png", RoomSize);
					Room->SetRoomColSprite("Basement_Col.png");

					FVector ColSize = RoomSize - (Ellie->GetEllieSize());
					Room->SetCollisionSize(RoomSize - (Ellie->GetEllieSize()));
					Room->SetActorLocation({ 0.0f, 0.0f, 1000.0f });

					Ellie->SetActorLocation({ 20.0f, 20.0f, 10.0f });

					Camera->SetActorLocation({ 0.0f, 0.0f, -624.0f, 1.0f });

					{
						const std::string Path = ".\\..\\LWIWResources\\Data\\Basement.MapData";
						UEngineFile FIle = Path;
						FIle.FileOpen("rb");

						UEngineSerializer Ser;
						FIle.Read(Ser);

						int ListNum;
						Ser >> ListNum;

						LoadData(Ser, ListNum);
					}
				}
			}

			if (InterCol->GetInterColName() == "Basement")
			{
				{
					std::list<std::shared_ptr<AInteractCollision>> AllInterColList = GetWorld()->GetAllActorListByClass<AInteractCollision>();
					for (std::shared_ptr<AInteractCollision> InterCol : AllInterColList)
					{
						InterCol->Destroy();
					}

					std::list<std::shared_ptr<AMapObject>> AllMapObjectList = GetWorld()->GetAllActorListByClass<AMapObject>();
					for (std::shared_ptr<AMapObject> MapObject : AllMapObjectList)
					{
						MapObject->Destroy();
					}

					std::list<std::shared_ptr<AInteractObject>> AllInteractObjectList = GetWorld()->GetAllActorListByClass<AInteractObject>();
					for (std::shared_ptr<AInteractObject> InteractObject : AllInteractObjectList)
					{
						InteractObject->Destroy();
					}
				}

				{
					Ellie->SetColImage("WitchHouse_Outside_Col.png", "Map");
					Room->SetColImage("WitchHouse_Outside_Col.png", "Map");
					FVector RoomSize = Room->GetColImage().GetImageScale();

					Room->SetRoomSprite("WitchHouse_Outside.png", RoomSize);
					Room->SetRoomColSprite("WitchHouse_Outside_Col.png");

					FVector ColSize = RoomSize - (Ellie->GetEllieSize());
					Room->SetCollisionSize(RoomSize - (Ellie->GetEllieSize()));
					Room->SetActorLocation({ 0.0f, 0.0f, 1000.0f });

					Ellie->SetActorLocation({ -40.0f, -110.0f, 10.0f });

					Camera->SetActorLocation({ 0.0f, 0.0f, -624.0f, 1.0f });

					{
						const std::string Path = ".\\..\\LWIWResources\\Data\\WitchHouse_Outside.MapData";
						UEngineFile FIle = Path;
						FIle.FileOpen("rb");

						UEngineSerializer Ser;
						FIle.Read(Ser);

						int ListNum;
						Ser >> ListNum;

						LoadData(Ser, ListNum);

						std::list<std::shared_ptr<AMapObject>> AllMapObjectList = GetWorld()->GetAllActorListByClass<AMapObject>();
						std::list<std::shared_ptr<AInteractObject>> AllInteractObjectList = GetWorld()->GetAllActorListByClass<AInteractObject>();

						if (0 != static_cast<int>(AllMapObjectList.size()))
						{
							for (std::shared_ptr<AMapObject> MapObject : AllMapObjectList)
							{
								FVector ObjectPos = MapObject->GetActorLocation();
								MapObject->SetActorLocation({ ObjectPos.X, ObjectPos.Y, ObjectPos.Z + -300.0f });
							}
						}

						if (0 != static_cast<int>(AllInteractObjectList.size()))
						{
							for (std::shared_ptr<AInteractObject> InteractObj : AllInteractObjectList)
							{
								FVector ObjectPos = InteractObj->GetActorLocation();
								InteractObj->SetActorLocation({ ObjectPos.X, ObjectPos.Y, ObjectPos.Z + -300.0f });
							}
						}
					}
				}
			}
		}
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

void APlayGameMode::LoadData(UEngineSerializer _Ser, int _ListNum)
{
	switch (_ListNum)
	{
	case 1:
	{
		int InterColCount = 0;
		_Ser >> InterColCount;
		for (size_t i = 0; i < InterColCount; i++)
		{
			std::shared_ptr<AInteractCollision> NewInterCol = GetWorld()->SpawnActor<AInteractCollision>();

			NewInterCol->DeSerialize(_Ser);
		}
		break;
	}
	case 2:
	{
		int MapObjectCount = 0;
		_Ser >> MapObjectCount;
		for (size_t i = 0; i < MapObjectCount; i++)
		{
			std::shared_ptr<AMapObject> NewMapObject = GetWorld()->SpawnActor<AMapObject>();

			NewMapObject->DeSerialize(_Ser);
		}
		break;
	}
	case 3:
	{
		int InterColCount = 0;
		_Ser >> InterColCount;
		for (size_t i = 0; i < InterColCount; i++)
		{
			std::shared_ptr<AInteractCollision> NewInterCol = GetWorld()->SpawnActor<AInteractCollision>();

			NewInterCol->DeSerialize(_Ser);
		}

		int MapObjectCount = 0;
		_Ser >> MapObjectCount;
		for (size_t i = 0; i < MapObjectCount; i++)
		{
			std::shared_ptr<AMapObject> NewMapObject = GetWorld()->SpawnActor<AMapObject>();

			NewMapObject->DeSerialize(_Ser);
		}
		break;
	}
	case 4:
	{
		int InteractObjCount = 0;
		_Ser >> InteractObjCount;
		for (size_t i = 0; i < InteractObjCount; i++)
		{
			std::shared_ptr<AInteractObject> NewInteractObj = GetWorld()->SpawnActor<AInteractObject>();

			NewInteractObj->DeSerialize(_Ser);
		}
		break;
	}
	case 5:
	{
		int InterColCount = 0;
		_Ser >> InterColCount;
		for (size_t i = 0; i < InterColCount; i++)
		{
			std::shared_ptr<AInteractCollision> NewInterCol = GetWorld()->SpawnActor<AInteractCollision>();

			NewInterCol->DeSerialize(_Ser);
		}

		int InteractObjCount = 0;
		_Ser >> InteractObjCount;
		for (size_t i = 0; i < InteractObjCount; i++)
		{
			std::shared_ptr<AInteractObject> NewInteractObj = GetWorld()->SpawnActor<AInteractObject>();

			NewInteractObj->DeSerialize(_Ser);
		}
		break;
	}
	case 6:
	{
		int MapObjectCount = 0;
		_Ser >> MapObjectCount;
		for (size_t i = 0; i < MapObjectCount; i++)
		{
			std::shared_ptr<AMapObject> NewMapObject = GetWorld()->SpawnActor<AMapObject>();

			NewMapObject->DeSerialize(_Ser);
		}

		int InteractObjCount = 0;
		_Ser >> InteractObjCount;
		for (size_t i = 0; i < InteractObjCount; i++)
		{
			std::shared_ptr<AInteractObject> NewInteractObj = GetWorld()->SpawnActor<AInteractObject>();

			NewInteractObj->DeSerialize(_Ser);
		}
		break;
	}
	case 7:
	{
		int InterColCount = 0;
		_Ser >> InterColCount;
		for (size_t i = 0; i < InterColCount; i++)
		{
			std::shared_ptr<AInteractCollision> NewInterCol = GetWorld()->SpawnActor<AInteractCollision>();

			NewInterCol->DeSerialize(_Ser);
		}

		int MapObjectCount = 0;
		_Ser >> MapObjectCount;
		for (size_t i = 0; i < MapObjectCount; i++)
		{
			std::shared_ptr<AMapObject> NewMapObject = GetWorld()->SpawnActor<AMapObject>();

			NewMapObject->DeSerialize(_Ser);
		}

		int InteractObjCount = 0;
		_Ser >> InteractObjCount;
		for (size_t i = 0; i < InteractObjCount; i++)
		{
			std::shared_ptr<AInteractObject> NewInteractObj = GetWorld()->SpawnActor<AInteractObject>();

			NewInteractObj->DeSerialize(_Ser);
		}
		break;
	}
	default:
		break;
	}
}
