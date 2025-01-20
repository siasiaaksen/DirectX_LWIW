#pragma once
#include <EngineCore/Actor.h>


enum class ECreatureType
{
	TREE,
};


class ACreature : public AActor
{
public:
	ACreature();
	~ACreature();

	ACreature(const ACreature& _Other) = delete;
	ACreature(ACreature&& _Other) noexcept = delete;
	ACreature& operator=(const ACreature& _Other) = delete;
	ACreature& operator=(ACreature&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	ECreatureType CreatureTypeValue;

protected:

private:

};

