#include "PreCompile.h"
#include "MapObject.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>


AMapObject::AMapObject()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Sprite = CreateDefaultSubObject<USpriteRenderer>();
	Sprite->SetupAttachment(RootComponent);
}

AMapObject::~AMapObject()
{
}

void AMapObject::BeginPlay()
{
	AActor::BeginPlay();
}

void AMapObject::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	FVector Pos = GetActorLocation();
	Pos.Z = Pos.Y;

	SetActorLocation(Pos);
}

