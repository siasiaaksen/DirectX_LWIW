#include "PreCompile.h"
#include "Item.h"
#include <EngineBase/EngineString.h>
#include <EngineCore/HUD.h>


UItem::UItem()
{
}

UItem::~UItem()
{
}

void UItem::SetItem(std::string_view _ItemName, FIntPoint _ItemIndex, int _ItemCount)
{
	std::string UpperName = UEngineString::ToUpper(_ItemName);
	Info.ItemName = UpperName;
	Info.ItemIndex = _ItemIndex;
	Info.ItemCount = _ItemCount;
}

