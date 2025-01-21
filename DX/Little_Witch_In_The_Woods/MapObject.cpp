#include "PreCompile.h"
#include "MapObject.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>


AMapObject::AMapObject()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Sprite = CreateDefaultSubObject<USpriteRenderer>();
	Sprite->SetupAttachment(RootComponent);

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("MapObject");
}

AMapObject::~AMapObject()
{
}

void AMapObject::SetColActive(bool _Value)
{
	Collision->SetActive(_Value);
}

bool AMapObject::GetColActive()
{
	return Collision->GetIsActiveValueRef();
}

void AMapObject::BeginPlay()
{
	AActor::BeginPlay();
}

void AMapObject::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

