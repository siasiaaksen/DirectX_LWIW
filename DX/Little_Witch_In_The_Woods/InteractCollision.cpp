#include "PreCompile.h"
#include "InteractCollision.h"
#include <EngineCore/Collision.h>
#include <EngineCore/DefaultSceneComponent.h>


AInteractCollision::AInteractCollision()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	InterCol = CreateDefaultSubObject<UCollision>();
	InterCol->SetCollisionProfileName("InterCol");
	InterCol->SetupAttachment(RootComponent);
}

AInteractCollision::~AInteractCollision()
{
}

void AInteractCollision::BeginPlay()
{
	AActor::BeginPlay();
}

void AInteractCollision::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

void AInteractCollision::Serialize(UEngineSerializer& _Ser)
{
	_Ser << GetActorLocation();
	_Ser << InterColSize;
	_Ser << InterColName;
}

void AInteractCollision::DeSerialize(UEngineSerializer& _Ser)
{
	FVector SavePos;
	_Ser >> SavePos;
	SetActorLocation(SavePos);

	_Ser >> InterColSize;
	SetActorRelativeScale3D(InterColSize);

	_Ser >> InterColName;
	SetName(InterColName);
}