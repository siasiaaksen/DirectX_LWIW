#include "PreCompile.h"
#include "TitleBridge.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>


ATitleBridge::ATitleBridge()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	BridgeRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BridgeRenderer->SetSprite("Title_Train_Bridge.png", 0);
	BridgeRenderer->SetRelativeScale3D({ 1407, 219, 1.0f });
	BridgeRenderer->SetWorldLocation({ 1, -251, 0.0f });
	BridgeRenderer->SetupAttachment(RootComponent);
}

ATitleBridge::~ATitleBridge()
{
}

void ATitleBridge::BeginPlay()
{
	AActor::BeginPlay();
}

void ATitleBridge::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

