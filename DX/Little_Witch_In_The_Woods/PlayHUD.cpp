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

	if (ECollectItem::MONGSIRI == Ellie->ItemType)
	{
		Inventory->AddItem("Mongsiri_Collect.png", "MongsiriFur");
		Ellie->ItemType = ECollectItem::MAX;
	}
}