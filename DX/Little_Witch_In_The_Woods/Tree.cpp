#include "PreCompile.h"
#include "Tree.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>
#include "Ellie.h"


ATree::ATree()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	TreeSprite = CreateDefaultSubObject<USpriteRenderer>();
	TreeSprite->SetupAttachment(RootComponent);
	TreeSprite->SetTexture("Tree_0.png", true, 1.0f);
	TreeSprite->SpriteData.Pivot = { 0.5f, 0.25f };

	TreeCollision = CreateDefaultSubObject<UCollision>();
	TreeCollision->SetupAttachment(RootComponent);
	TreeCollision->SetCollisionProfileName("Tree");
	TreeCollision->SetScale3D({ 5.0f, 0.5f });
	TreeCollision->SetWorldLocation({ GetActorLocation().X, GetActorLocation().Y - 30.0f});

	//SetActorLocation({ 100.0f, 100.0f });
}

ATree::~ATree()
{
}

void ATree::BeginPlay()
{
	AActor::BeginPlay();
}

void ATree::Tick(float _DeltaTime)
{
	FVector Pos = GetActorLocation();
	Pos.Z = Pos.Y - 80.0f;

	SetActorLocation(Pos);
}



