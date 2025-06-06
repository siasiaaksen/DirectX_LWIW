#include "PreCompile.h"
#include "Inventory.h"
#include <EngineBase/EngineString.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/HUD.h>
#include <EnginePlatform/EngineInput.h>


UInventory::UInventory()
{
	InvenInit();

}

UInventory::~UInventory()
{
}

void UInventory::InvenInit()
{
	// InventoryBase
	{
		SetTexture("Inventory_Base.png");
		SetWorldLocation(Pos);
		SetScale3D(Scale);
	}

	// InvenSlot
	{
		InvenSlot.resize(6);
		for (size_t x = 0; x < InvenSlot.size(); x++)
		{
			for (size_t y = 0; y < 5; y++)
			{
				Slot = GetHUD()->CreateWidget<UInvenSlot>(2);

				Slot->SetTexture("Inventory_SlotBase.png");
				Slot->SetScale3D({ 50.0f, 50.0f });

				float4 SlotScale = Slot->GetWorldScale3D();

				float SlotXPos = (Pos.X + 20.0f) - Scale.X / 2 + SlotScale.X / 2 + (10.0f + SlotScale.X) * y;
				float SlotYPos = (Pos.Y - 20.0f) + Scale.Y / 2 - SlotScale.Y / 2 - (10.0f + SlotScale.Y) * x;
				Slot->SetWorldLocation({ SlotXPos, SlotYPos });

				Slot->Pos = Slot->GetWorldLocation();
				Slot->Scale = SlotScale;
				Slot->CurIndex = { 0, 0 };

				InvenSlot[x].push_back(Slot);
			}
		}
	}

	// InvenCursor
	{
		Cursor = GetHUD()->CreateWidget<USlotCursor>(4);

		Cursor->SetSprite("Inventory_Cursor.png");
		Cursor->CreateAnimation("Cursor", "Inventory_Cursor.png", 0, 1, 0.5f, true);
		Cursor->ChangeAnimation("Cursor");
		Cursor->SetWorldLocation(InvenSlot[Slot->CurIndex.X][Slot->CurIndex.Y].get()->Pos);
	}

	AllSlotSetActive(false);
	SetActive(false);
	Cursor->SetActive(false);
}

void UInventory::BeginPlay()
{
	UImageWidget::BeginPlay();
}

void UInventory::Tick(float _DeltaTime)
{
	UImageWidget::Tick(_DeltaTime);

	KeyInput();
	IndexCheck();

	Cursor->SetWorldLocation(InvenSlot[Slot->CurIndex.X][Slot->CurIndex.Y].get()->Pos);
}

void UInventory::AddItem(std::string_view _SpriteName, std::string_view _ItemName)
{
	std::string UpperName = UEngineString::ToUpper(_ItemName);
	for (int x = 0; x < InvenSlot.size(); x++)
	{
		for (int y = 0; y < InvenSlot[x].size(); y++)
		{
			std::shared_ptr<UInvenSlot> CurSlot = InvenSlot[x][y];
			if (true == CurSlot->IsEmpty)
			{
				CurSlot->Item = GetHUD()->CreateWidget<UItem>(8);
				CurSlot->Item->SetItem(_ItemName, {x, y}, 1);
				CurSlot->Item->SetTexture(_SpriteName);
				CurSlot->Item->SetWorldLocation(CurSlot->Pos);
				CurSlot->Item->SetScale3D({ 50.0f, 50.0f });
				CurSlot->Item->SetActive(false);
				CurSlot->IsEmpty = false;
				return;
			}
			else if (false == CurSlot->IsEmpty && UpperName == CurSlot->Item->GetInfo().ItemName)
			{
				CurSlot->Item->GetInfo().ItemCount += 1;
				return;
			}
			else if (false == CurSlot->IsEmpty && UpperName != CurSlot->Item->GetInfo().ItemName)
			{
				continue;
			}
		}
	}
}

void UInventory::KeyInput()
{
	if (true == UEngineInput::IsDown(VK_UP))
	{
		Slot->CurIndex.X -= 1;
	}
	if (true == UEngineInput::IsDown(VK_DOWN))
	{
		Slot->CurIndex.X += 1;
	}
	if (true == UEngineInput::IsDown(VK_LEFT))
	{
		Slot->CurIndex.Y -= 1;
	}
	if (true == UEngineInput::IsDown(VK_RIGHT))
	{
		Slot->CurIndex.Y += 1;
	}
	if (true == UEngineInput::IsDown(VK_SPACE))
	{
		int a = 0;
	}
}

void UInventory::IndexCheck()
{
	if (Slot->CurIndex.X < 0)
	{
		Slot->CurIndex.X = 5;
	}
	if (Slot->CurIndex.X > 5)
	{
		Slot->CurIndex.X = 0;
	}
	if (Slot->CurIndex.Y < 0)
	{
		Slot->CurIndex.Y = 4;
	}
	if (Slot->CurIndex.Y > 4)
	{
		Slot->CurIndex.Y = 0;
	}
}

void UInventory::AllSlotSetActive(bool _Value)
{
	for (size_t x = 0; x < InvenSlot.size(); x++)
	{
		for (size_t y = 0; y < InvenSlot[x].size(); y++)
		{
			if (nullptr != InvenSlot[x][y]->Item)
			{
				InvenSlot[x][y]->Item->SetActive(_Value);
			}

			InvenSlot[x][y]->SetActive(_Value);
			IsSlotsActive = _Value;
		}
	}
}

void UInventory::InvenSetActiveSwitch()
{
	SetActiveSwitch();
	IsSlotsActive = !IsSlotsActive;
	AllSlotSetActive(IsSlotsActive);
	Cursor->SetActive(IsSlotsActive);
}

