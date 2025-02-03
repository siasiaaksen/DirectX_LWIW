#pragma once
#include <EngineCore/ImageWidget.h>
#include <EngineCore/SpriteRenderer.h>


class UInvenSlot : public UImageWidget
{
public:
	FIntPoint Index;
	//USpriteRenderer SlotSprite;
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
	std::vector<std::vector<UInvenSlot*>> InvenSlot;
};

