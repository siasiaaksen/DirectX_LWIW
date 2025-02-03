#include "PreCompile.h"
#include "Inventory.h"
#include <EngineCore/SpriteRenderer.h>


UInventory::UInventory()
{
	InvenInit();
}

UInventory::~UInventory()
{
}

void UInventory::InvenInit()
{
	SetTexture("Inventory_Base.png");
	SetWorldLocation(Pos);
	SetScale3D(Scale);

	InvenSlot.resize(3);
	for (size_t x = 0; x < InvenSlot.size(); x++)
	{
		for (size_t y = 0; y < 5; y++)
		{
			//InvenSlot[y].resize(5);

			std::shared_ptr<UInvenSlot> Slot = GetWorld()->SpawnActor<UInvenSlot>();
			Slot->SlotSprite = Slot->CreateDefaultSubObject<USpriteRenderer>();
			Slot->SlotSprite->SetupAttachment(this);
			Slot->SlotSprite->SetSprite("Inventory_SlotBase.png");
			float4 SlotScale = Slot->SlotSprite->GetWorldScale3D();
			float SlotXPos = Pos.X - Scale.X / 2 + SlotScale.X / 2 + 10.0f + SlotScale.X * y;
			float SlotYPos = Pos.Y + Scale.Y / 2 + SlotScale.Y / 2 + 10.0f + SlotScale.Y * x;
			Slot->SlotSprite->SetWorldLocation({ SlotXPos, SlotYPos, 1000.0f });
			InvenSlot[y].push_back(Slot);
		}
	}

	SetActive(true);
}

void UInventory::BeginPlay()
{
	UImageWidget::BeginPlay();
}

void UInventory::Tick(float _DeltaTime)
{
	UImageWidget::Tick(_DeltaTime);
}