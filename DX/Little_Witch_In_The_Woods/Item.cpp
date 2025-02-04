#include "PreCompile.h"
#include "Item.h"


UItem::UItem()
{
}

UItem::~UItem()
{
}

void UItem::SetItem(std::string_view _SpriteName)
{
	SetTexture(_SpriteName);
}

