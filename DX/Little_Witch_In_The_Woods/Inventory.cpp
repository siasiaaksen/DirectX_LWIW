#include "PreCompile.h"
#include "Inventory.h"

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
	SetWorldLocation({ -350.0f, 150.0f });
	SetScale3D({ 400.0f, 300.0f });

	InvenSlot.resize(3);
	for (size_t y = 0; y < InvenSlot.size(); y++)
	{
		InvenSlot[y].resize(5);

		//InvenSlot[y]->SetTexture("Inventory_SlotBase.png", true, 1.0f);
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