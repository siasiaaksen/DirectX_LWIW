#include "PreCompile.h"
#include "MapEditorMode.h"
#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineWindow.h>
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
#include "MapObject.h"
#include "InteractObject.h"
#include "InteractCollision.h"


class UEditorGUIWindow : public UEngineGUIWindow
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


enum class ESpawnList
{
	MapObject,
};


enum class EEDITMode
{
	MapGround,
	MapObject,
	InteractObject,
};


enum class EActorList
{
	EntColList = 1,
	MapObejctList = 2,
	InteractObjectList = 4,
};


class UMapEditorWindow : public UEngineGUIWindow
{
public:
	int SelectItem = 0;
	int ObjectItem = -1;
	int InterColItem = -1;
	int InteractObjItem = -1;
	UTileMapRenderer* TileMapRenderer = nullptr;
	EEDITMode Mode = EEDITMode::MapGround;

	FVector InterColPos;
	FVector InterColScale;

	float SpritePosX = 0.0f;
	float SpritePosY = 0.0f;
	float ZSort = 0.0f;

	char Buf[255]{};

	std::string SpriteName;

	FVector MousePos;

	void SelectGroundMap()
	{
		ImGui::Text("=== Select Map Ground ===");

		if (ImGui::Button("MapGround"))
		{
			{
				std::list<std::shared_ptr<ARoom>> AllRoomList = GetWorld()->GetAllActorListByClass<ARoom>();
				for (std::shared_ptr<ARoom> Rooms : AllRoomList)
				{
					Rooms->Destroy();
				}

				std::list<std::shared_ptr<AInteractCollision>> AllEntColList = GetWorld()->GetAllActorListByClass<AInteractCollision>();
				for (std::shared_ptr<AInteractCollision> EntCol : AllEntColList)
				{
					EntCol->Destroy();
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

				std::list<std::shared_ptr<AInteractCollision>> AllEntColList = GetWorld()->GetAllActorListByClass<AInteractCollision>();
				for (std::shared_ptr<AInteractCollision> EntCol : AllEntColList)
				{
					EntCol->Destroy();
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

			std::shared_ptr<ARoom> Room = GetWorld()->SpawnActor<ARoom>();
			Room->SetColImage("WitchHouse_Outside_Col.png", "Map");

			FVector RoomSize = Room->GetColImage().GetImageScale();
			Room->SetRoomSprite("WitchHouse_Outside.png", RoomSize);
			Room->SetRoomColSprite("WitchHouse_Outside_Col.png");

			FVector ColSize = RoomSize - FVector(70.0f, 100.0f);
			Room->SetCollisionSize(ColSize);
			Room->SetActorLocation({ 0.0f, 0.0f, 1000.0f });
		}

		if (ImGui::Button("WitchHouse"))
		{
			{
				std::list<std::shared_ptr<ARoom>> AllRoomList = GetWorld()->GetAllActorListByClass<ARoom>();
				for (std::shared_ptr<ARoom> Rooms : AllRoomList)
				{
					Rooms->Destroy();
				}

				std::list<std::shared_ptr<AInteractCollision>> AllEntColList = GetWorld()->GetAllActorListByClass<AInteractCollision>();
				for (std::shared_ptr<AInteractCollision> EntCol : AllEntColList)
				{
					EntCol->Destroy();
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

			std::shared_ptr<ARoom> Room = GetWorld()->SpawnActor<ARoom>();
			Room->SetColImage("WitchHouse1F_Col.png", "Map");

			FVector RoomSize = Room->GetColImage().GetImageScale();
			Room->SetRoomSprite("WitchHouse1F.png", RoomSize);
			Room->SetRoomColSprite("WitchHouse1F_Col.png");

			FVector ColSize = RoomSize - FVector(70.0f, 100.0f);
			Room->SetCollisionSize(ColSize);
			Room->SetActorLocation({ 0.0f, 0.0f, 1000.0f });
		}

		if (ImGui::Button("Basement"))
		{
			{
				std::list<std::shared_ptr<ARoom>> AllRoomList = GetWorld()->GetAllActorListByClass<ARoom>();
				for (std::shared_ptr<ARoom> Rooms : AllRoomList)
				{
					Rooms->Destroy();
				}

				std::list<std::shared_ptr<AInteractCollision>> AllEntColList = GetWorld()->GetAllActorListByClass<AInteractCollision>();
				for (std::shared_ptr<AInteractCollision> EntCol : AllEntColList)
				{
					EntCol->Destroy();
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

			std::shared_ptr<ARoom> Room = GetWorld()->SpawnActor<ARoom>();
			Room->SetColImage("Basement_Col.png", "Map");

			FVector RoomSize = Room->GetColImage().GetImageScale();
			Room->SetRoomSprite("Basement.png", RoomSize);
			Room->SetRoomColSprite("Basement_Col.png");

			FVector ColSize = RoomSize - FVector(70.0f, 100.0f);
			Room->SetCollisionSize(ColSize);
			Room->SetActorLocation({ 0.0f, 0.0f, 1000.0f });
		}

		ImGui::Text("=== Create Entrance Collision ===");

		// EntranceCollision
		{
			std::string InterColName;
			strncpy_s(Buf, InterColName.c_str(), sizeof(Buf) - 1);
			ImGui::InputText("InterColName", Buf, sizeof(Buf));

			if (true == UEngineInput::IsDown(VK_LBUTTON))
			{
				if (false == GEngine->GetMainWindow().IsMouseScreenOut())
				{
					std::shared_ptr<AInteractCollision> InterCol = GetWorld()->SpawnActor<AInteractCollision>("InterCol");
					MousePos = GetWorld()->GetMainCamera()->ScreenMousePosToWorldPos();
					InterCol->SetActorLocation(MousePos);
					InterCol->SetInterColName(Buf);
					InterCol->SetName(InterCol->GetInterColName());
				}
			}

			std::vector<std::shared_ptr<AInteractCollision>> AllInterColList = GetWorld()->GetAllActorArrayByClass<AInteractCollision>();
			std::vector<std::string> ArrString;
			for (std::shared_ptr<class AActor> Actor : AllInterColList)
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
				ImGui::ListBox("AllInterColList", &InterColItem, &Arr[0], static_cast<int>(Arr.size()));

				if (InterColItem != -1)
				{
					ImGui::Text(AllInterColList[InterColItem]->GetInterColName().c_str());

					InterColPos = AllInterColList[InterColItem]->GetActorLocation();
					InterColScale = AllInterColList[InterColItem]->GetActorTransform().WorldScale;

					ImGui::InputFloat("InterColPosX", &InterColPos.X);
					ImGui::InputFloat("InterColPosY", &InterColPos.Y);
					ImGui::InputFloat("InterColScaleX", &InterColScale.X);
					ImGui::InputFloat("InterColScaleY", &InterColScale.Y);

					AllInterColList[InterColItem]->SetActorLocation(InterColPos);
					AllInterColList[InterColItem]->SetInterColSize(InterColScale);
					AllInterColList[InterColItem]->SetActorRelativeScale3D(AllInterColList[InterColItem]->GetInterColSize());

					if (true == ImGui::Button("Delete"))
					{
						AllInterColList[InterColItem]->Destroy();
						InterColItem = -1;
					}

					if (true == ImGui::Button("InterColDelete"))
					{
						std::list<std::shared_ptr<AInteractCollision>> AllInterColList = GetWorld()->GetAllActorListByClass<AInteractCollision>();
						for (std::shared_ptr<AInteractCollision> InterCol : AllInterColList)
						{
							InterCol->Destroy();
						}
					}
				}
			}
		}
	}

	int SelectObject = 0;
	void ObjectMode()
	{
		ImGui::Text("=== Select Object Sprite ===");

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
					if (0 != (i % 5))
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

			if (true == UEngineInput::IsDown(VK_LBUTTON))
			{
				if (false == GEngine->GetMainWindow().IsMouseScreenOut())
				{
					std::shared_ptr<AMapObject> NewObject = GetWorld()->SpawnActor<AMapObject>("MapObject");
					MousePos = GetWorld()->GetMainCamera()->ScreenMousePosToWorldPos();
					NewObject->SetActorLocation(MousePos);
					NewObject->GetSprite()->SetSprite("Map_Object", SelectObject);
					NewObject->SetSpriteIndex(SelectObject);
					NewObject->GetSprite()->SpriteData.Pivot = { 0.5f, 0.25f };	// YSorting 때 필요
					SpriteName = NewObject->GetSprite()->GetSprite()->GetTexture(SelectObject)->GetName();
					NewObject->SetSpriteName(SpriteName);
					NewObject->SetName(NewObject->GetSpriteName());
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
				ImGui::ListBox("AllObjectList", &ObjectItem, &Arr[0], static_cast<int>(Arr.size()));

				if (ObjectItem != -1)
				{
					ImGui::Text("=== Object Sprite Option ===");

					// MapObjectSprite
					{
						SpritePosX = AllMapObjectList[ObjectItem]->GetActorLocation().X;
						SpritePosY = AllMapObjectList[ObjectItem]->GetActorLocation().Y;

						ImGui::InputFloat("SpritePosX", &SpritePosX);
						ImGui::InputFloat("SpritePosY", &SpritePosY);

						FVector SpritePos = FVector(SpritePosX, SpritePosY);

						ZSort = AllMapObjectList[ObjectItem]->GetActorLocation().Z;

						AllMapObjectList[ObjectItem]->SetActorLocation({ SpritePos.X, SpritePos.Y, ZSort });

						ImGui::Text("ZValue");
						ImGui::Text(std::to_string(ZSort).c_str());
					}

					ImGui::Text("=== Object Collision Option ===");

					// MapObjectCollision
					{
						bool IsColActive = AllMapObjectList[ObjectItem]->GetColActive();

						ImGui::Checkbox("IsColActive", &IsColActive);

						if (true == IsColActive)
						{
							AllMapObjectList[ObjectItem]->SetColActive(true);

							{
								FVector ColPos = AllMapObjectList[ObjectItem]->GetCollision()->GetRelativeLocation();

								ImGui::InputFloat("ColPosX", &ColPos.X);
								ImGui::InputFloat("ColPosY", &ColPos.Y);

								AllMapObjectList[ObjectItem]->SetColPos(ColPos);
								AllMapObjectList[ObjectItem]->GetCollision()->SetWorldLocation(ColPos);
							}

							{
								FVector ColScale = AllMapObjectList[ObjectItem]->GetCollision()->GetWorldScale3D();

								ImGui::InputFloat("ColScaleX", &ColScale.X);
								ImGui::InputFloat("ColScaleY", &ColScale.Y);

								AllMapObjectList[ObjectItem]->SetColScale(ColScale);
								AllMapObjectList[ObjectItem]->GetCollision()->SetScale3D(ColScale);
							}
						}
						else
						{
							AllMapObjectList[ObjectItem]->SetColActive(false);
						}
					}
				}

				if (true == ImGui::Button("Delete"))
				{
					AllMapObjectList[ObjectItem]->Destroy();
					ObjectItem = -1;
				}

				if (ImGui::Button("EditObjectDelete"))
				{
					std::list<std::shared_ptr<AMapObject>> AllMapObjectList = GetWorld()->GetAllActorListByClass<AMapObject>();
					for (std::shared_ptr<AMapObject> MapObject : AllMapObjectList)
					{
						MapObject->Destroy();
					}
				}
			}
		}
	}

	int SelectInteract = 0;
	void InteractMode()
	{
		ImGui::Text("=== Select InteractObj Sprite ===");

		{
			std::shared_ptr<UEngineSprite> Sprite = UEngineSprite::Find<UEngineSprite>("InteractObject");
			for (size_t i = 0; i < Sprite->GetSpriteCount(); i++)
			{
				UEngineTexture* Texture = Sprite->GetTexture(i);
				FSpriteData Data = Sprite->GetSpriteData(i);

				ImTextureID SRV = reinterpret_cast<ImTextureID>(Texture->GetSRV());

				std::string Text = std::to_string(i);

				if (i != 0)
				{
					if (0 != (i % 5))
					{
						ImGui::SameLine();
					}
				}

				ImVec2 Pos = { Data.CuttingPos.X, Data.CuttingPos.Y };
				ImVec2 Size = { Data.CuttingPos.X + Data.CuttingSize.X, Data.CuttingPos.Y + Data.CuttingSize.Y };

				if (ImGui::ImageButton(Text.c_str(), SRV, { 60, 60 }, Pos, Size))
				{
					SelectInteract = static_cast<int>(i);
				}
			}

			std::string InteractObjName;
			strncpy_s(Buf, InteractObjName.c_str(), sizeof(Buf) - 1);
			if (ImGui::InputText("InteractObjName", Buf, sizeof(Buf)))
			{
				if (true == UEngineInput::IsDown(VK_LBUTTON))
				{
					if (false == GEngine->GetMainWindow().IsMouseScreenOut())
					{
						std::shared_ptr<AInteractObject> NewObject = GetWorld()->SpawnActor<AInteractObject>("InteractObject");
						MousePos = GetWorld()->GetMainCamera()->ScreenMousePosToWorldPos();
						NewObject->SetActorLocation(MousePos);
						NewObject->GetSprite()->SetSprite("InteractObject", SelectInteract);
						NewObject->SetSpriteIndex(SelectInteract);
						NewObject->GetSprite()->SpriteData.Pivot = { 0.5f, 0.25f };	// YSorting 때 필요
						NewObject->SetObjectName(Buf);
						NewObject->SetName(NewObject->GetObjectName());
					}
				}
			}
		}

		{
			std::vector<std::shared_ptr<AInteractObject>> AllInteractObjectList = GetWorld()->GetAllActorArrayByClass<AInteractObject>();
			std::vector<std::string> ArrString;
			for (std::shared_ptr<class AActor> Actor : AllInteractObjectList)
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
				ImGui::ListBox("AllObjectList", &InteractObjItem, &Arr[0], static_cast<int>(Arr.size()));

				if (InteractObjItem != -1)
				{
					ImGui::Text("=== Object Sprite Option ===");

					// InteractObjectSprite
					{
						SpritePosX = AllInteractObjectList[InteractObjItem]->GetActorLocation().X;
						SpritePosY = AllInteractObjectList[InteractObjItem]->GetActorLocation().Y;

						ImGui::InputFloat("SpritePosX", &SpritePosX);
						ImGui::InputFloat("SpritePosY", &SpritePosY);

						FVector SpritePos = FVector(SpritePosX, SpritePosY);

						ZSort = AllInteractObjectList[InteractObjItem]->GetActorLocation().Z;

						AllInteractObjectList[InteractObjItem]->SetActorLocation({ SpritePos.X, SpritePos.Y, ZSort });

						ImGui::Text("ZValue");
						ImGui::Text(std::to_string(ZSort).c_str());
					}

					ImGui::Text("=== Object Collision Option ===");

					// InteractObjectCollision
					{
						bool IsColActive = AllInteractObjectList[InteractObjItem]->GetColActive();

						ImGui::Checkbox("IsColActive", &IsColActive);

						if (true == IsColActive)
						{
							AllInteractObjectList[InteractObjItem]->SetColActive(true);

							{
								FVector ColPos = AllInteractObjectList[InteractObjItem]->GetCollision()->GetRelativeLocation();

								ImGui::InputFloat("ColPosX", &ColPos.X);
								ImGui::InputFloat("ColPosY", &ColPos.Y);

								AllInteractObjectList[InteractObjItem]->SetColPos(ColPos);
								AllInteractObjectList[InteractObjItem]->GetCollision()->SetWorldLocation(ColPos);
							}

							{
								FVector ColScale = AllInteractObjectList[InteractObjItem]->GetCollision()->GetWorldScale3D();

								ImGui::InputFloat("ColScaleX", &ColScale.X);
								ImGui::InputFloat("ColScaleY", &ColScale.Y);

								AllInteractObjectList[InteractObjItem]->SetColScale(ColScale);
								AllInteractObjectList[InteractObjItem]->GetCollision()->SetScale3D(ColScale);
							}
						}
						else
						{
							AllInteractObjectList[InteractObjItem]->SetColActive(false);
						}
					}
				}

				if (true == ImGui::Button("Delete"))
				{
					AllInteractObjectList[InteractObjItem]->Destroy();
					InteractObjItem = -1;
				}

				if (ImGui::Button("EditObjectDelete"))
				{
					std::list<std::shared_ptr<AInteractObject>> AllInteractObjectList = GetWorld()->GetAllActorListByClass<AInteractObject>();
					for (std::shared_ptr<AInteractObject> InteractObject : AllInteractObjectList)
					{
						InteractObject->Destroy();
					}
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
				std::list<std::shared_ptr<AInteractCollision>> AllInterColList = GetWorld()->GetAllActorListByClass<AInteractCollision>();
				std::list<std::shared_ptr<AMapObject>> AllMapObjectList = GetWorld()->GetAllActorListByClass<AMapObject>();
				std::list<std::shared_ptr<AInteractObject>> AllInteractObjectList = GetWorld()->GetAllActorListByClass<AInteractObject>();

				UEngineSerializer Ser;

				{
					int ListNum = 0;

					if (0 != static_cast<int>(AllInterColList.size()))
					{
						ListNum += static_cast<int>(EActorList::EntColList);
					}

					if (0 != static_cast<int>(AllMapObjectList.size()))
					{
						ListNum += static_cast<int>(EActorList::MapObejctList);
					}

					if (0 != static_cast<int>(AllInteractObjectList.size()))
					{
						ListNum += static_cast<int>(EActorList::InteractObjectList);
					}

					Ser << ListNum;
				}

				{
					if (0 != static_cast<int>(AllInterColList.size()))
					{
						Ser << static_cast<int>(AllInterColList.size());
						for (std::shared_ptr<AInteractCollision> InterCol : AllInterColList)
						{
							InterCol->Serialize(Ser);
						}
					}

					if (0 != static_cast<int>(AllMapObjectList.size()))
					{
						Ser << static_cast<int>(AllMapObjectList.size());
						for (std::shared_ptr<AMapObject> Actor : AllMapObjectList)
						{
							Actor->Serialize(Ser);
						}
					}

					if (0 != static_cast<int>(AllInteractObjectList.size()))
					{
						Ser << static_cast<int>(AllInteractObjectList.size());
						for (std::shared_ptr<AInteractObject> Actor : AllInteractObjectList)
						{
							Actor->Serialize(Ser);
						}
					}
				}

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

				int ListNum;
				Ser >> ListNum;

				switch (ListNum)
				{
				case 1:
				{
					int InterColCount = 0;
					Ser >> InterColCount;
					for (size_t i = 0; i < InterColCount; i++)
					{
						std::shared_ptr<AInteractCollision> NewInterCol = GetWorld()->SpawnActor<AInteractCollision>();

						NewInterCol->DeSerialize(Ser);
					}
					break;
				}
				case 2:
				{
					int MapObjectCount = 0;
					Ser >> MapObjectCount;
					for (size_t i = 0; i < MapObjectCount; i++)
					{
						std::shared_ptr<AMapObject> NewMapObject = GetWorld()->SpawnActor<AMapObject>();

						NewMapObject->DeSerialize(Ser);
					}
					break;
				}
				case 3:
				{
					int InterColCount = 0;
					Ser >> InterColCount;
					for (size_t i = 0; i < InterColCount; i++)
					{
						std::shared_ptr<AInteractCollision> NewInterCol = GetWorld()->SpawnActor<AInteractCollision>();

						NewInterCol->DeSerialize(Ser);
					}

					int MapObjectCount = 0;
					Ser >> MapObjectCount;
					for (size_t i = 0; i < MapObjectCount; i++)
					{
						std::shared_ptr<AMapObject> NewMapObject = GetWorld()->SpawnActor<AMapObject>();

						NewMapObject->DeSerialize(Ser);
					}
					break;
				}
				case 4:
				{
					int InteractObjCount = 0;
					Ser >> InteractObjCount;
					for (size_t i = 0; i < InteractObjCount; i++)
					{
						std::shared_ptr<AInteractObject> NewInteractObj = GetWorld()->SpawnActor<AInteractObject>();

						NewInteractObj->DeSerialize(Ser);
					}
					break;
				}
				case 5:
				{
					int InterColCount = 0;
					Ser >> InterColCount;
					for (size_t i = 0; i < InterColCount; i++)
					{
						std::shared_ptr<AInteractCollision> NewInterCol = GetWorld()->SpawnActor<AInteractCollision>();

						NewInterCol->DeSerialize(Ser);
					}

					int InteractObjCount = 0;
					Ser >> InteractObjCount;
					for (size_t i = 0; i < InteractObjCount; i++)
					{
						std::shared_ptr<AInteractObject> NewInteractObj = GetWorld()->SpawnActor<AInteractObject>();

						NewInteractObj->DeSerialize(Ser);
					}
					break;
				}
				case 6:
				{
					int MapObjectCount = 0;
					Ser >> MapObjectCount;
					for (size_t i = 0; i < MapObjectCount; i++)
					{
						std::shared_ptr<AMapObject> NewMapObject = GetWorld()->SpawnActor<AMapObject>();

						NewMapObject->DeSerialize(Ser);
					}

					int InteractObjCount = 0;
					Ser >> InteractObjCount;
					for (size_t i = 0; i < InteractObjCount; i++)
					{
						std::shared_ptr<AInteractObject> NewInteractObj = GetWorld()->SpawnActor<AInteractObject>();

						NewInteractObj->DeSerialize(Ser);
					}
					break;
				}
				case 7:
				{
					int InterColCount = 0;
					Ser >> InterColCount;
					for (size_t i = 0; i < InterColCount; i++)
					{
						std::shared_ptr<AInteractCollision> NewInterCol = GetWorld()->SpawnActor<AInteractCollision>();

						NewInterCol->DeSerialize(Ser);
					}

					int MapObjectCount = 0;
					Ser >> MapObjectCount;
					for (size_t i = 0; i < MapObjectCount; i++)
					{
						std::shared_ptr<AMapObject> NewMapObject = GetWorld()->SpawnActor<AMapObject>();

						NewMapObject->DeSerialize(Ser);
					}

					int InteractObjCount = 0;
					Ser >> InteractObjCount;
					for (size_t i = 0; i < InteractObjCount; i++)
					{
						std::shared_ptr<AInteractObject> NewInteractObj = GetWorld()->SpawnActor<AInteractObject>();

						NewInteractObj->DeSerialize(Ser);
					}
					break;
				}
				default:
					break;
				}
			}
		}
	}

	// MapEditModeSwitch
	void OnGUI() override
	{
		{
			if (Mode == EEDITMode::MapObject)
			{
				if (ImGui::Button("ObjectMode"))
				{
					Mode = EEDITMode::InteractObject;
				}
			}
			else if (Mode == EEDITMode::InteractObject)
			{
				if (ImGui::Button("InteractObject"))
				{
					Mode = EEDITMode::MapGround;
				}
			}
			else
			{
				if (ImGui::Button("MapGroundMode"))
				{
					Mode = EEDITMode::MapObject;
				}
			}
		}

		switch (Mode)
		{
		case EEDITMode::MapGround:
			SelectGroundMap();
			break;
		case EEDITMode::MapObject:
			ObjectMode();
			break;
		case EEDITMode::InteractObject:
			InteractMode();
			break;
		default:
			break;
		}
		
		SaveAndLoad();
	}
};


AMapEditorMode::AMapEditorMode()
{
	GetWorld()->CreateCollisionProfile("Room");
	GetWorld()->CreateCollisionProfile("MapObject");
	GetWorld()->CreateCollisionProfile("InterCol");
	GetWorld()->CreateCollisionProfile("InteractObject");

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	// 카메라
	{
		Camera = GetWorld()->GetMainCamera();
		Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
		Camera->GetCameraComponent()->SetProjectionType(EProjectionType::Orthographic);
		Camera->GetCameraComponent()->SetZSort(0, true);
	}

	// 중심 확인 랜더러
	PivotSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	PivotSpriteRenderer->SetupAttachment(RootComponent);
	PivotSpriteRenderer->SetRelativeScale3D({ 50.0f, 50.0f, 1.0f });
}

AMapEditorMode::~AMapEditorMode()
{
}

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
	if (true == UEngineInput::IsDown(VK_F2))
	{
		std::list<std::shared_ptr<ARoom>> AllRoomList = GetWorld()->GetAllActorListByClass<ARoom>();
		for (std::shared_ptr<ARoom> Rooms : AllRoomList)
		{
			Rooms->GetRoomColSprite()->SetActiveSwitch();
		}
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
		std::shared_ptr<UEditorGUIWindow> Window = UEngineGUI::FindGUIWindow<UEditorGUIWindow>("UEditorGUIWindow");

		if (nullptr == Window)
		{
			Window = UEngineGUI::CreateGUIWindow<UEditorGUIWindow>("UEditorGUIWindow");
		}

		Window->SetActive(true);
	}

	{
		MapEditWindow = UEngineGUI::FindGUIWindow<UMapEditorWindow>("MapEditorWindow");

		if (nullptr == MapEditWindow)
		{
			MapEditWindow = UEngineGUI::CreateGUIWindow<UMapEditorWindow>("MapEditorWindow");
		}

		MapEditWindow->SetActive(true);
	}
}


