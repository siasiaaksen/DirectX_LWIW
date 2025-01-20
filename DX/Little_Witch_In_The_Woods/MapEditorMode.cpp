#include "PreCompile.h"
#include "MapEditorMode.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCamera.h>
#include <EngineCore/TileMapRenderer.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "ContentsEditorGUI.h"
#include "Creature.h"
#include "Room.h"
#include "Ellie.h"
#include "Tree.h"


enum class ESpawnList
{
	Tree,
};


enum class EEDITMode
{
	TileMap,
	Object,
};


class UMapEditorWindow : public UEngineGUIWindow
{
public:
	int SelectItem = 0;
	int ObjectItem = -1;
	UTileMapRenderer* TileMapRenderer = nullptr;
	EEDITMode Mode = EEDITMode::Object;

	int TileCountX = 10;
	int TileCountY = 10;
	int SelectTileIndex = 0;

	float PosX = 0.0f;
	float PosY = 0.0f;

	//void TileMapMode()
	//{
	//	{
	//		UEngineSprite* Sprite = TileMapRenderer->GetSprite();

	//		for (size_t i = 0; i < Sprite->GetSpriteCount(); i++)
	//		{
	//			UEngineTexture* Texture = Sprite->GetTexture(i);
	//			FSpriteData Data = Sprite->GetSpriteData(i);

	//			ImTextureID SRV = reinterpret_cast<ImTextureID>(Texture->GetSRV());

	//			std::string Text = std::to_string(i);

	//			if (i != 0)
	//			{
	//				if (0 != (i % 10))
	//				{
	//					// 엔터를 치지 않는
	//					ImGui::SameLine();
	//				}
	//			}

	//			ImVec2 Pos = { Data.CuttingPos.X, Data.CuttingPos.Y };
	//			ImVec2 Size = { Data.CuttingPos.X + Data.CuttingSize.X, Data.CuttingPos.Y + Data.CuttingSize.Y };
	//			if (ImGui::ImageButton(Text.c_str(), SRV, { 60, 60 }, Pos, Size))
	//			{
	//				SelectTileIndex = static_cast<int>(i);
	//			}
	//		}

	//		//ImGui::InputInt("TileMapX", &TileCountX);
	//		//ImGui::InputInt("TileMapY", &TileCountY);

	//		//if (ImGui::Button("TileMap Create"))
	//		//{
	//		//	for (int y = 0; y < TileCountY; y++)
	//		//	{
	//		//		for (int x = 0; x < TileCountX; x++)
	//		//		{
	//		//			TileMapRenderer->SetTile(x, y, SelectTileIndex);
	//		//		}
	//		//	}
	//		//}

	//		if (true == UEngineInput::IsPress(VK_LBUTTON))
	//		{
	//			FVector ScreenPos = GetWorld()->GetMainCamera()->ScreenMousePosToWorldPos();
	//			
	//			TileMapRenderer->SetTile(ScreenPos, SelectTileIndex);
	//		}

	//		if (true == UEngineInput::IsPress(VK_RBUTTON))
	//		{
	//			FVector ScreenPos = GetWorld()->GetMainCamera()->ScreenMousePosToWorldPos();

	//			TileMapRenderer->RemoveTile(ScreenPos);
	//		}
	//	}
	//}

	void SelectGroundMap()
	{
		if (ImGui::Button("MapGround"))
		{
			{
				std::list<std::shared_ptr<ARoom>> AllRoomList = GetWorld()->GetAllActorListByClass<ARoom>();
				for (std::shared_ptr<ARoom> Rooms : AllRoomList)
				{
					Rooms->Destroy();
				}

				std::list<std::shared_ptr<AMapObject>> AllMapObjectList = GetWorld()->GetAllActorListByClass<AMapObject>();
				for (std::shared_ptr<AMapObject> MapObject : AllMapObjectList)
				{
					MapObject->Destroy();
				}
			}

			std::shared_ptr<ARoom> Room = GetWorld()->SpawnActor<ARoom>();
			Room->SetColImage("Map_Col.png", "Map");

			FVector RoomSize = Room->GetColImage().GetImageScale();
			Room->SetRoomSprite("Map.png", RoomSize);
			Room->SetRoomColSprite("Map_Col.png");

			FVector ColSize = RoomSize - FVector(70.0f, 100.0f);
			Room->SetCollisionSize(ColSize);
			Room->SetActorLocation({ 0.0f, 0.0f, 1000.0f });
		}

		if (ImGui::Button("WitchHouseYard"))
		{
			{
				std::list<std::shared_ptr<ARoom>> AllRoomList = GetWorld()->GetAllActorListByClass<ARoom>();
				for (std::shared_ptr<ARoom> Rooms : AllRoomList)
				{
					Rooms->Destroy();
				}

				std::list<std::shared_ptr<AMapObject>> AllMapObjectList = GetWorld()->GetAllActorListByClass<AMapObject>();
				for (std::shared_ptr<AMapObject> MapObject : AllMapObjectList)
				{
					MapObject->Destroy();
				}
			}

			std::shared_ptr<ARoom> Room = GetWorld()->SpawnActor<ARoom>();
			Room->SetColImage("WitchHouse_Outside_Col.png", "Map");

			FVector RoomSize = Room->GetColImage().GetImageScale();
			Room->SetRoomSprite("WitchHouse_Outside.png", RoomSize);
			Room->SetRoomColSprite("WitchHouse_Outside_Col.png");

			FVector ColSize = RoomSize - FVector(70.0f, 100.0f);
			Room->SetCollisionSize(ColSize);
			Room->SetActorLocation({ 0.0f, 0.0f, 1000.0f });
		}
	}

	int SelectObject = 0;

	void ObjectMode()
	{
		{
			std::shared_ptr<UEngineSprite> Sprite = UEngineSprite::Find<UEngineSprite>("Map_Object");
			for (size_t i = 0; i < Sprite->GetSpriteCount(); i++)
			{
				UEngineTexture* Texture = Sprite->GetTexture(i);
				FSpriteData Data = Sprite->GetSpriteData(i);

				ImTextureID SRV = reinterpret_cast<ImTextureID>(Texture->GetSRV());

				std::string Text = std::to_string(i);

				if (i != 0)
				{
					if (0 != (i % 10))
					{
						ImGui::SameLine();
					}
				}

				ImVec2 Pos = { Data.CuttingPos.X, Data.CuttingPos.Y };
				ImVec2 Size = { Data.CuttingPos.X + Data.CuttingSize.X, Data.CuttingPos.Y + Data.CuttingSize.Y };

				if (ImGui::ImageButton(Text.c_str(), SRV, { 60, 60 }, Pos, Size))
				{
					SelectObject = static_cast<int>(i);
				}
			}

			ImGui::InputFloat("PosX", &PosX);
			ImGui::InputFloat("PosY", &PosY);

			FVector SpritePos = FVector(PosX, PosY);

			if (true == UEngineInput::IsDown(VK_LBUTTON))
			{
				std::shared_ptr<AMapObject> NewObject = GetWorld()->SpawnActor<AMapObject>("Tree_0");
				FVector Pos = GetWorld()->GetMainCamera()->ScreenMousePosToWorldPos();
				NewObject->SetActorLocation(SpritePos);
				NewObject->Sprite->SetSprite("Map_Object", SelectObject);
			}
		}

		{
			if (ImGui::Button("EditObjectDelete"))
			{
				std::list<std::shared_ptr<AMapObject>> AllMapObjectList = GetWorld()->GetAllActorListByClass<AMapObject>();
				for (std::shared_ptr<AMapObject> MapObject : AllMapObjectList)
				{
					MapObject->Destroy();
				}
			}
		}

		{
			std::vector<std::shared_ptr<AMapObject>> AllMapObjectList = GetWorld()->GetAllActorArrayByClass<AMapObject>();

			std::vector<std::string> ArrString;
			for (std::shared_ptr<class AActor> Actor : AllMapObjectList)
			{
				ArrString.push_back(Actor->GetName());
			}

			std::vector<const char*> Arr;
			for (size_t i = 0; i < ArrString.size(); i++)
			{
				Arr.push_back(ArrString[i].c_str());
			}

			if (0 < Arr.size())
			{
				ImGui::ListBox("AllActorList", &ObjectItem, &Arr[0], static_cast<int>(Arr.size()));

				if (ObjectItem != -1)
				{
				}

				if (true == ImGui::Button("Delete"))
				{
					AllMapObjectList[ObjectItem]->Destroy();
					ObjectItem = -1;
				}
			}
		}
	}

	void SaveAndLoad()
	{
		if (true == ImGui::Button("Save"))
		{
			UEngineDirectory Dir;
			if (false == Dir.MoveParentToDirectory("LWIWResources"))
			{
				MSGASSERT("리소스 폴더를 찾지 못했습니다.");
				return;
			}

			Dir.Append("Data");
			std::string InitPath = Dir.GetPathToString();

			OPENFILENAME ofn;       // common dialog box structure
			char szFile[260] = { 0 };       // if using TCHAR macros
			// Initialize OPENFILENAME
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = nullptr;
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = ("All\0*.*\0");
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrDefExt = "MapData";
			ofn.lpstrInitialDir = InitPath.c_str();
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if (GetSaveFileNameA(&ofn) == TRUE)
			{
				std::list<std::shared_ptr<ACreature>> AllCreatureList = GetWorld()->GetAllActorListByClass<ACreature>();

				UEngineSerializer Ser;

				Ser << static_cast<int>(AllCreatureList.size());

				for (std::shared_ptr<ACreature> Actor : AllCreatureList)
				{
					Ser << static_cast<int>(Actor->CreatureTypeValue);
					Actor->Serialize(Ser);
				}

				//TileMapRenderer->Serialize(Ser);

				UEngineFile NewFile = Dir.GetFile(ofn.lpstrFile);

				NewFile.FileOpen("wb");
				NewFile.Write(Ser);
			}
		}

		if (true == ImGui::Button("Load"))
		{
			UEngineDirectory Dir;
			if (false == Dir.MoveParentToDirectory("LWIWResources"))
			{
				MSGASSERT("리소스 폴더를 찾지 못했습니다.");
				return;
			}

			Dir.Append("Data");
			std::string InitPath = Dir.GetPathToString();

			OPENFILENAME ofn;       // common dialog box structure
			char szFile[260] = { 0 };       // if using TCHAR macros
			// Initialize OPENFILENAME
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = nullptr;
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = ("All\0*.*\0Text\0*.MapData\0");
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = InitPath.c_str();
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if (GetOpenFileNameA(&ofn) == TRUE)
			{
				UEngineFile NewFile = Dir.GetFile(ofn.lpstrFile);
				UEngineSerializer Ser;

				NewFile.FileOpen("rb");
				NewFile.Read(Ser);

				int CreatureCount = 0;

				Ser >> CreatureCount;

				for (size_t i = 0; i < CreatureCount; i++)
				{
					int CreatureTypeValue = 0;
					Ser >> CreatureTypeValue;

					ECreatureType CreatureType = static_cast<ECreatureType>(CreatureTypeValue);

					std::shared_ptr<ACreature> NewCreature = nullptr;

					switch (CreatureType)
					{
					case ECreatureType::Tree:
						//NewCreature = GetWorld()->SpawnActor<ATree>();
						break;
					default:
						break;
					}

					NewCreature->DeSerialize(Ser);
				}

				//TileMapRenderer->DeSerialize(Ser);
			}
		}
	}

	void OnGUI() override
	{
		//{
		//	if (Mode == EEDITMode::Object)
		//	{
		//		if (ImGui::Button("ObjectMode"))
		//		{
		//			Mode = EEDITMode::TileMap;
		//		}
		//	}
		//	else
		//	{
		//		if (ImGui::Button("TileMapMode"))
		//		{
		//			Mode = EEDITMode::Object;
		//		}
		//	}
		//}

		//switch (Mode)
		//{
		//case EEDITMode::TileMap:
		//	TileMapMode();
		//	break;
		//case EEDITMode::Object:
		//	ObjectMode();
		//	break;
		//default:
		//	break;
		//}
		
		SelectGroundMap();
		ObjectMode();
		SaveAndLoad();
	}
};


AMapEditorMode::AMapEditorMode()
{
	GetWorld()->CreateCollisionProfile("Room");
	//GetWorld()->CreateCollisionProfile("Tree");

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	// 카메라
	{
		Camera = GetWorld()->GetMainCamera();
		Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
		Camera->GetCameraComponent()->SetZSort(0, true);
	}

	//PivotSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//PivotSpriteRenderer->SetupAttachment(RootComponent);
	//PivotSpriteRenderer->SetRelativeScale3D({ 50.0f, 50.0f, 1.0f });

	//TileMapRenderer = CreateDefaultSubObject<UTileMapRenderer>();
	//TileMapRenderer->SetupAttachment(RootComponent);
	//TileSize = { 336.0f, 384.0f };
	//TileMapRenderer->SetTileSetting(ETileMapType::Rect, "Tree", TileSize, TileSize, { 0.0f, 0.0f });
}

AMapEditorMode::~AMapEditorMode()
{
}

//void AMapEditorMode::BeginPlay()
//{
//	AActor::BeginPlay();
//}

void AMapEditorMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (true == UEngineInput::IsDown(VK_HOME))
	{
		UEngineCore::OpenLevel("TitleLevel");
	}

	if (true == UEngineInput::IsPress('W'))
	{
		Camera->AddActorLocation({ 0.0f, 300.0f * _DeltaTime, 0.0f });
	}
	if (true == UEngineInput::IsPress('S'))
	{
		Camera->AddActorLocation({ 0.0f, -300.0f * _DeltaTime, 0.0f });
	}
	if (true == UEngineInput::IsPress('A'))
	{
		Camera->AddActorLocation({ -300.0f * _DeltaTime, 0.0f, 0.0f });
	}
	if (true == UEngineInput::IsPress('D'))
	{
		Camera->AddActorLocation({ 300.0f * _DeltaTime, 0.0f, 0.0f });
	}
	if (true == UEngineInput::IsPress(VK_F3))
	{
		Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
	}
}

void AMapEditorMode::LevelChangeStart()
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
		TileMapWindow = UEngineGUI::FindGUIWindow<UMapEditorWindow>("MapEditorWindow");

		if (nullptr == TileMapWindow)
		{
			TileMapWindow = UEngineGUI::CreateGUIWindow<UMapEditorWindow>("MapEditorWindow");
		}

		TileMapWindow->SetActive(true);
		TileMapWindow->TileMapRenderer = TileMapRenderer.get();
	}
}

