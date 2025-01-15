#include "PreCompile.h"
#include "PlayHUD.h"
#include <EngineCore/Widget.h>


APlayHUD::APlayHUD()
{
}

APlayHUD::~APlayHUD()
{
}

void APlayHUD::BeginPlay()
{
	AHUD::BeginPlay();

	std::shared_ptr<UWidget> Button = CreateWidget<UWidget>(-1);

	//Button->SetScale3D({ 100, 100, 1 });
	//Button->SetWorldLocation({ -200, 300 });
	//Button->SetTexture("BackGround.png");
	//Button->SetDownEvent([]()
	//	{
	//		UEngineDebug::OutPutString("Click~~~~~~~~~");
	//	});
}

void APlayHUD::Tick(float _DeltaTime)
{
	AHUD::Tick(_DeltaTime);
}