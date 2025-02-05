#pragma once
#include <EngineCore/ImageWidget.h>


class ItemInfo
{
public:
	std::string ItemName;
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

	void SetItem(std::string_view _ItemName, FIntPoint _ItemIndex, int _ItemCount);

	ItemInfo& GetInfo()
	{
		return Info;
	}

protected:

private:
	ItemInfo Info;
};

