#pragma once
#include <EngineCore/Actor.h>


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

protected:

private:

};

