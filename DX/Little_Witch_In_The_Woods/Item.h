#pragma once
#include <EngineCore/ImageWidget.h>


class ItemInfo
{
public:
	FIntPoint ItemIndex;
	int ItemCount;
};


class UItem : public UImageWidget
{
public:
	UItem();
	~UItem();

	UItem(const UItem& _Other) = delete;
	UItem(UItem&& _Other) noexcept = delete;
	UItem& operator=(const UItem& _Other) = delete;
	UItem& operator=(UItem&& _Other) noexcept = delete;

	void SetItem(std::string_view _SpriteName);

protected:

private:
	ItemInfo Info;
};

