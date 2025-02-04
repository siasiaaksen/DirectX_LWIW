#include "PreCompile.h"
#include "PlayHUD.h"
#include <EngineCore/ImageWidget.h>
#include <EngineCore/FontWidget.h>
#include <EnginePlatform/EngineInput.h>
#include "Ellie.h"
#include "Inventory.h"


APlayHUD::APlayHUD()
{
}

APlayHUD::~APlayHUD()
{
}

void APlayHUD::BeginPlay()
{
	AHUD::BeginPlay();

	Inventory = CreateWidget<UInventory>(-1);
}

void APlayHUD::Tick(float _DeltaTime)
{
	AHUD::Tick(_DeltaTime);

	AEllie* Ellie = dynamic_cast<AEllie*>(GetWorld()->GetMainPawn());
	
	if (true == UEngineInput::IsDown('I'))
	{

		Inventory->InvenSetActiveSwitch();

		if (true == Ellie->IsEllieMove)
		{
			Ellie->IsEllieMove = false;
		}
		else
		{
			Ellie->IsEllieMove = true;
		}
	}

	int CollectItemNum = static_cast<int>(AEllie::EllieCollectItem);
	std::string_view ItemName;

	switch (CollectItemNum)
	{
	case 0:
		ItemName = "Mongsiri_Collect.png";
		Inventory->AddItem(ItemName);
		break;
	case 1:
	default:
		break;
	}
}