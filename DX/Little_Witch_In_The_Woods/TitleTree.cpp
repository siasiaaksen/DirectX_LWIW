#include "PreCompile.h"
#include "TitleTree.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>


ATitleTree::ATitleTree()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	TreeRenderer = CreateDefaultSubObject<USpriteRenderer>();
	TreeRenderer->SetTexture("Title_Train_Tree.png", true, 1.0f);
	TreeRenderer->SetWorldLocation({ -74.0f, -190.0f, 2.0f });
	TreeRenderer->SetupAttachment(RootComponent);
}

ATitleTree::~ATitleTree()
{
}

void ATitleTree::BeginPlay()
{
	AActor::BeginPlay();
}

void ATitleTree::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	TreeRenderer->UVValue.PlusUVValue += float4(0.5f * _DeltaTime, 0.0f, 0.0f, 1.0f);
}



