#include "PreCompile.h"
#include "InteractObject.h"
#include <EngineCore/DefaultSceneComponent.h>


AInteractObject::AInteractObject()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Sprite = CreateDefaultSubObject<USpriteRenderer>();
	Sprite->SpriteData.Pivot = { 0.5f, 0.25f };
	Sprite->SetupAttachment(RootComponent);

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetCollisionProfileName("InteractObject");
	Collision->SetActive(false);
	Collision->SetupAttachment(RootComponent);
}

AInteractObject::~AInteractObject()
{
}

void AInteractObject::BeginPlay()
{
	AActor::BeginPlay();
}

void AInteractObject::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	FVector Pos = GetActorLocation();
	Pos.Z = Pos.Y - (Sprite->GetWorldScale3D().Y * 0.25f);

	SetActorLocation(Pos);
}

void AInteractObject::Serialize(UEngineSerializer& _Ser)
{
	_Ser << GetActorLocation();
	_Ser << SpriteIndex;
	_Ser << Sprite->SpriteData.Pivot;
	_Ser << IsColActive;
	_Ser << ColPos;
	_Ser << ColScale;
	_Ser << ObjectName;
}

void AInteractObject::DeSerialize(UEngineSerializer& _Ser)
{
	FVector SavePos;
	_Ser >> SavePos;
	SetActorLocation(SavePos);

	_Ser >> SpriteIndex;
	Sprite->SetSprite("InteractObject", SpriteIndex);
	Sprite->SetAutoScale(true);

	float4 Pivot;
	_Ser >> Pivot;
	Sprite->SpriteData.Pivot = Pivot;

	_Ser >> IsColActive;
	Collision->SetActive(IsColActive);

	_Ser >> ColPos;
	Collision->SetWorldLocation(ColPos);

	_Ser >> ColScale;
	Collision->SetScale3D(ColScale);

	_Ser >> ObjectName;
	SetName(ObjectName);
}

