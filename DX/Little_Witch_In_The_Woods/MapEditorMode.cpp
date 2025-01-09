#include "PreCompile.h"
#include "MapEditorMode.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCamera.h>
#include "ContentsEditorGUI.h"


class UMapEditorWindow : public UEngineGUIWindow
{
public:
	int SelectItem = 0;

	void OnGUI() override
	{
		std::vector<const char*> Arr;
		//Arr.push_back("Monster");

		//ImGui::ListBox("SpawnList", &SelectItem, &Arr[0], 2);

		if (true == UEngineInput::IsDown(VK_LBUTTON))
		{
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
			int ValueX = 10;
			ImGui::InputInt("TileMapX", &ValueX);
			int ValueY = 10;
			ImGui::InputInt("TileMapY", &ValueY);

			if (ImGui::Button("TileMap Create"))
			{
				int a = 0;
			}
		}

		if (true == ImGui::Button("Save"))
		{
			UEngineDirectory Dir;
			if (false == Dir.MoveParentToDirectory("ContentsResources"))
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
				UEngineSerializer Ser;

				//Ser << static_cast<int>(AllMonsterList.size());

				//for (std::shared_ptr<AMon> Actor : AllMonsterList)
				//{

				//	Ser << static_cast<int>(Actor->MonsterTypeValue);
				//	// 여기 저장된다는 이야기
				//	Actor->Serialize(Ser);
				//}

				UEngineFile NewFile = Dir.GetFile(ofn.lpstrFile);

				NewFile.FileOpen("wb");
				NewFile.Write(Ser);
			}
		}

		if (true == ImGui::Button("Load"))
		{
			UEngineDirectory Dir;
			if (false == Dir.MoveParentToDirectory("ContentsResources"))
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
			}
		}
	}
};


AMapEditorMode::AMapEditorMode()
{
	// 카메라
	{
		std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
		Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
		Camera->GetCameraComponent()->SetZSort(0, true);
	}

	// imgui
	{
		UEngineGUI::CreateGUIWindow<UMapEditorWindow>("MapEditorWindow");
	}
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
	}

}

