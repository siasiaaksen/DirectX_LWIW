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


//enum class ESpawnList
//{
//	Monster,
//	Monster2,
//};


enum class EEditMode
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
	EEditMode Mode = EEditMode::TileMap;

	int TileCountX = 10;
	int TileCountY = 10;
	int SelectTileIndex = 0;

	void TileMapMode()
	{
		{
			UEngineSprite* Sprite = TileMapRenderer->GetSprite();

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
						// ���͸� ġ�� �ʴ�
						ImGui::SameLine();
					}
				}

				ImVec2 Pos = { Data.CuttingPos.X, Data.CuttingPos.Y };
				ImVec2 Size = { Data.CuttingPos.X + Data.CuttingSize.X, Data.CuttingPos.Y + Data.CuttingSize.Y };
				if (ImGui::ImageButton(Text.c_str(), SRV, { 60, 60 }, Pos, Size))
				{
					SelectTileIndex = static_cast<int>(i);
				}
			}

			ImGui::InputInt("TileMapX", &TileCountX);
			ImGui::InputInt("TileMapY", &TileCountY);

			if (ImGui::Button("TileMap Create"))
			{
				for (int y = 0; y < TileCountY; y++)
				{
					for (int x = 0; x < TileCountX; x++)
					{
						TileMapRenderer->SetTile(x, y, SelectTileIndex);
					}
				}
			}

			if (true == UEngineInput::IsPress(VK_LBUTTON))
			{
				FVector ScreenPos = GetWorld()->GetMainCamera()->ScreenMousePosToWorldPos();
				
				TileMapRenderer->SetTile(ScreenPos, SelectTileIndex);
			}

			if (true == UEngineInput::IsPress(VK_RBUTTON))
			{
				FVector ScreenPos = GetWorld()->GetMainCamera()->ScreenMousePosToWorldPos();

				TileMapRenderer->RemoveTile(ScreenPos);
			}
		}
	}

	void ObjectMode()
	{
		{
			std::vector<const char*> Arr;
			//Arr.push_back("Monster");
			//Arr.push_back("Monster2");

			//ImGui::ListBox("SpawnList", &SelectItem, &Arr[0], 2);

			 //GetMainWindow()->IsScreenOut();

			if (true == UEngineInput::IsDown(VK_LBUTTON))
			{
				//ESpawnList SelectMonster = static_cast<ESpawnList>(SelectItem);
				//std::shared_ptr<class ACameraActor> Camera = GetWorld()->GetMainCamera();
				//FVector Pos = Camera->ScreenMousePosToWorldPos();
				//Pos.Z = 0.0f;

				//std::shared_ptr<AMon> NewMonster;

				//switch (SelectMonster)
				//{
				//case ESpawnList::Monster:
				//	NewMonster = GetWorld()->SpawnActor<AMonster>("Monster");
				//	break;
				//case ESpawnList::Monster2:
				//	NewMonster = GetWorld()->SpawnActor<AMonster2>("Monster2");
				//	break;
				//default:
				//	break;
				//}

				//NewMonster->SetActorLocation(Pos);
			}
		}

		{
			if (ImGui::Button("EditObjectDelete"))
			{
				//std::list<std::shared_ptr<AMon>> AllMonsterList = GetWorld()->GetAllActorListByClass<AMon>();
				//for (std::shared_ptr<AMon> Mon : AllMonsterList)
				//{
				//	Mon->Destroy();
				//}
			}
		}

		{
			//std::vector<std::shared_ptr<AMon>> AllMonsterList = GetWorld()->GetAllActorArrayByClass<AMon>();

			//std::vector<std::string> ArrString;
			//for (std::shared_ptr<class AActor> Actor : AllMonsterList)
			//{
			//	ArrString.push_back(Actor->GetName());
			//}

			//std::vector<const char*> Arr;
			//for (size_t i = 0; i < ArrString.size(); i++)
			//{
			//	Arr.push_back(ArrString[i].c_str());
			//}

			//if (0 < Arr.size())
			//{
			//	ImGui::ListBox("AllActorList", &ObjectItem, &Arr[0], static_cast<int>(Arr.size()));

			//	if (ObjectItem != -1)
			//	{
			//	}

			//	if (true == ImGui::Button("Delete"))
			//	{
			//		AllMonsterList[ObjectItem]->Destroy();
			//		ObjectItem = -1;
			//	}
			//}
		}
	}

	void SaveAndLoad()
	{
		if (true == ImGui::Button("Save"))
		{
			UEngineDirectory Dir;
			if (false == Dir.MoveParentToDirectory("LWIWResources"))
			{
				MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
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
				//std::list<std::shared_ptr<AMon>> AllMonsterList = GetWorld()->GetAllActorListByClass<AMon>();

				UEngineSerializer Ser;

				//Ser << static_cast<int>(AllMonsterList.size());

				//for (std::shared_ptr<AMon> Actor : AllMonsterList)
				//{
				//	Ser << static_cast<int>(Actor->MonsterTypeValue);
				//	Actor->Serialize(Ser);
				//}

				TileMapRenderer->Serialize(Ser);

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
				MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
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

				//int MonsterCount = 0;

				//Ser >> MonsterCount;

				//for (size_t i = 0; i < MonsterCount; i++)
				//{
				//	int MonsterTypeValue = 0;
				//	Ser >> MonsterTypeValue;

				//	EMonsterType MonsterType = static_cast<EMonsterType>(MonsterTypeValue);

				//	std::shared_ptr<AMon> NewMon = nullptr;

				//	switch (MonsterType)
				//	{
				//	case Monster:
				//		NewMon = GetWorld()->SpawnActor<AMonster>();
				//		break;
				//	case Monster2:
				//		NewMon = GetWorld()->SpawnActor<AMonster2>();
				//		break;
				//	default:
				//		break;
				//	}

				//	NewMon->DeSerialize(Ser);
				//}

				TileMapRenderer->DeSerialize(Ser);
			}
		}
	}

	void OnGUI() override
	{
		{
			if (Mode == EEditMode::Object)
			{
				if (ImGui::Button("ObjectMode"))
				{
					Mode = EEditMode::TileMap;
				}
			}
			else
			{
				if (ImGui::Button("TileMapMode"))
				{
					Mode = EEditMode::Object;
				}
			}
		}

		switch (Mode)
		{
		case EEditMode::TileMap:
			TileMapMode();
			break;
		case EEditMode::Object:
			ObjectMode();
			break;
		default:
			break;
		}

		SaveAndLoad();
	}
};


AMapEditorMode::AMapEditorMode()
{
	//GetWorld()->CreateCollisionProfile("Monster");

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	// ī�޶�
	{
		std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
		Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
		Camera->GetCameraComponent()->SetZSort(0, true);
	}

	PivotSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	PivotSpriteRenderer->SetupAttachment(RootComponent);
	PivotSpriteRenderer->SetRelativeScale3D({ 50.0f, 50.0f, 1.0f });

	TileMapRenderer = CreateDefaultSubObject<UTileMapRenderer>();
	TileMapRenderer->SetupAttachment(RootComponent);
	TileMapRenderer->SetTileSetting(ETileMapType::Rect, "Tiles", TileSize, TileSize, { 0.0f, 0.0f });
}

AMapEditorMode::~AMapEditorMode()
{
}

void AMapEditorMode::BeginPlay()
{
	AActor::BeginPlay();
}

void AMapEditorMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (true == UEngineInput::IsDown(VK_HOME))
	{
		UEngineCore::OpenLevel("TitleLevel");
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

