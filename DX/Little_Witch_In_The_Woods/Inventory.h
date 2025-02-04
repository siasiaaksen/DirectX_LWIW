#pragma once
#include <EngineCore/ImageWidget.h>


class USlotCursor : public UImageWidget
{
public:

protected:

private:

};


class UInvenSlot : public UImageWidget
{
public:
	FVector Pos;
	FVector Scale;
	FIntPoint CurIndex;
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

protected:

private:
	std::vector<std::vector<std::shared_ptr<UInvenSlot>>> InvenSlot;
	std::shared_ptr<UInvenSlot> Slot;
	std::shared_ptr<USlotCursor> Cursor;

	bool IsSlotsActive = false;

	FVector Pos = { -350.0f, 90.0f };
	FVector Scale = { 330.0f, 390.0f };
};

