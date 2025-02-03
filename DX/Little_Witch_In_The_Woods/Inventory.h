#pragma once
#include <EngineCore/ImageWidget.h>


class UInvenSlot : public AActor
{
public:
	FIntPoint Index;
	std::shared_ptr<class USpriteRenderer> SlotSprite;
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

protected:

private:
	std::vector<std::vector<std::shared_ptr<UInvenSlot>>> InvenSlot;

	FVector Pos = { -350.0f, 150.0f };
	FVector Scale = { 400.0f, 300.0f };
};

