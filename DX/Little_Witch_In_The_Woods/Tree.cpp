#include "PreCompile.h"
#include "Tree.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>


ATree::ATree()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	TreeSprite = CreateDefaultSubObject<USpriteRenderer>();
	TreeSprite->SetupAttachment(RootComponent);

	TreeCollision = CreateDefaultSubObject<UCollision>();
	TreeCollision->SetupAttachment(RootComponent);
}

ATree::~ATree()
{
}



