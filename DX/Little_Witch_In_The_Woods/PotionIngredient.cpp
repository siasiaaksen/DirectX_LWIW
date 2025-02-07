#include "PreCompile.h"
#include "PotionIngredient.h"


APotionIngredient::APotionIngredient()
{
}

APotionIngredient::~APotionIngredient()
{
}

void APotionIngredient::BeginPlay()
{
	AInteractObject::BeginPlay();
}

void APotionIngredient::Tick(float _DeltaTime)
{
	AInteractObject::Tick(_DeltaTime);
}