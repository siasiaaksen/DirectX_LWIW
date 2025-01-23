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

void AMapObject::Serialize(UEngineSerializer& _Ser)
{
	_Ser << GetActorLocation();
	_Ser << SpriteIndex;
	_Ser << SpriteName;
	_Ser << SpritePivot;
}


void AMapObject::DeSerialize(UEngineSerializer& _Ser)
{
	FVector SavePos;
	_Ser >> SavePos;
	SetActorLocation(SavePos);

	_Ser >> SpriteIndex;
	_Ser >> SpriteName;

	GetSprite()->SetSprite("Map_Object", SpriteIndex);
	Sprite->SetAutoScale(true);
	SetName(SpriteName);

	_Ser >> SpritePivot;
	GetSprite()->SpriteData.Pivot = SpritePivot;
}

