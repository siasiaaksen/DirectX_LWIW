#include "PreCompile.h"
#include "Creature.h"


ACreature::ACreature()
{
}

ACreature::~ACreature()
{
}

void ACreature::BeginPlay()
{
	AActor::BeginPlay();
}

void ACreature::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
