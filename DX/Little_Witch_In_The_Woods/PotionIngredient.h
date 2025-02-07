#pragma once
#include "InteractObject.h"


class APotionIngredient : public AInteractObject
{
public:
	APotionIngredient();
	~APotionIngredient();

	APotionIngredient(const APotionIngredient& _Other) = delete;
	APotionIngredient(APotionIngredient&& _Other) noexcept = delete;
	APotionIngredient& operator=(const APotionIngredient& _Other) = delete;
	APotionIngredient& operator=(APotionIngredient&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:

};

