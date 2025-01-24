#include "PreCompile.h"
#include "MapObject.h"
#include <EngineCore/DefaultSceneComponent.h>


AMapObject::AMapObject()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Sprite = CreateDefaultSubObject<USpriteRenderer>();
	Sprite->SpriteData.Pivot = { 0.5f, 0.25f };
	Sprite->SetupAttachment(RootComponent);

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetCollisionProfileName("MapObject");
	Collision->SetActive(false);
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
	Pos.Z = Pos.Y - (Sprite->GetWorldScale3D().Y * 0.25f);

	SetActorLocation(Pos);
}

void AMapObject::Serialize(UEngineSerializer& _Ser)
{
	_Ser << GetActorLocation();
	_Ser << SpriteIndex;
	_Ser << SpriteName;
	_Ser << Sprite->SpriteData.Pivot;
	_Ser << IsColActive;
	_Ser << ColPos;
	_Ser << ColScale;
}

void AMapObject::DeSerialize(UEngineSerializer& _Ser)
{
	FVector SavePos;
	_Ser >> SavePos;
	SetActorLocation(SavePos);

	_Ser >> SpriteIndex;
	_Ser >> SpriteName;

	Sprite->SetSprite("Map_Object", SpriteIndex);
	Sprite->SetAutoScale(true);
	SetName(SpriteName);

	float4 Pivot;
	_Ser >> Pivot;
	Sprite->SpriteData.Pivot = Pivot;

	_Ser >> IsColActive;
	Collision->SetActive(IsColActive);

	_Ser >> ColPos;
	Collision->SetWorldLocation(ColPos);

	_Ser >> ColScale;
	Collision->SetScale3D(ColScale);
}

