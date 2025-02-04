#pragma once
#include <EngineCore/ImageWidget.h>
#include "Item.h"


class USlotCursor : public UImageWidget
{
public:
	bool IsSelect = false;
};


class UInvenSlot : public UImageWidget
{
public:
	FVector Pos;
	FVector Scale;
	FIntPoint CurIndex;
	
	bool IsEmpty = true;

	std::shared_ptr<UItem> Item;
	std::shared_ptr<ItemInfo> Info;
};


class UInventory : public UImageWidget
{
public:
	UInventory();
	~UInventory();

	UInventory(const UInventory& _Other) = delete;
	UInventory(UInventory&& _Other) noexcept = delete;
	UInventory& operator=(const UInventory& _Other) = delete;
	UInventory& operator=(UInventory&& _Other) noexcept = delete;

	void BeginPlay();
	void Tick(float _DeltaTime);

	void InvenInit();

	void AllSlotSetActive(bool _Value);

	void InvenSetActiveSwitch();

	void IndexCheck();

	void KeyInput();

	void AddItem(std::string_view _SpriteName);

protected:

private:
	std::vector<std::vector<std::shared_ptr<UInvenSlot>>> InvenSlot;
	std::shared_ptr<UInvenSlot> Slot;
	std::shared_ptr<USlotCursor> Cursor;

	bool IsSlotsActive = false;

	FVector Pos = { -350.0f, 90.0f };
	FVector Scale = { 330.0f, 390.0f };
};

