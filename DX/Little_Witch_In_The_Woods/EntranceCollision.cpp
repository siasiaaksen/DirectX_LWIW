#include "PreCompile.h"
#include "EntranceCollision.h"
#include <EngineCore/Collision.h>
#include <EngineCore/DefaultSceneComponent.h>


AEntranceCollision::AEntranceCollision()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	EntranceCol = CreateDefaultSubObject<UCollision>();
	EntranceCol->SetCollisionProfileName("Entrance");
	EntranceCol->SetupAttachment(RootComponent);
	//EntranceCol->SetScale3D(EntranceSize);
	//EntranceCol->SetWorldLocation(EntrancePos);
}

AEntranceCollision::~AEntranceCollision()
{
}

void AEntranceCollision::BeginPlay()
{
	AActor::BeginPlay();
}

void AEntranceCollision::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

void AEntranceCollision::Serialize(UEngineSerializer& _Ser)
{
	_Ser << GetActorLocation();
	_Ser << EntranceSize;
	_Ser << EntranceName;
}

void AEntranceCollision::DeSerialize(UEngineSerializer& _Ser)
{
	FVector SavePos;
	_Ser >> SavePos;
	SetActorLocation(SavePos);

	_Ser >> EntranceSize;
	SetActorRelativeScale3D(EntranceSize);

	_Ser >> EntranceName;
	SetName(EntranceName);
}