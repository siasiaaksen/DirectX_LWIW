#include "PreCompile.h"
#include "TitleTree.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>


ATitleTree::ATitleTree()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	TreeRenderer = CreateDefaultSubObject<USpriteRenderer>();
	TreeRenderer->SetSprite("Title_Train_Tree.png", 0);
	TreeRenderer->SetAutoScaleRatio(1.0f);
	TreeRenderer->SetWorldLocation({ -74.0f, -190.0f, 3.0f });
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
}

