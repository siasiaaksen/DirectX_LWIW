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
	BridgeRenderer->SetAutoScaleRatio(1.0f);
	BridgeRenderer->SetWorldLocation({ 1.0f, -251.0f, 4.0f });
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

	BridgeRenderer->UVValue.PlusUVValue += float4(0.5f * _DeltaTime, 0.0f, 0.0f, 1.0f);
}

