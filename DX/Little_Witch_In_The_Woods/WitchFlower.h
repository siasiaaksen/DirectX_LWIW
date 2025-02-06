#pragma once
#include "InteractObject.h"


enum class EWitchFlowerState
{
	IDLE,
	COLLECTED,
	DISAPPEAR,
	MAX,
};


class AWitchFlower : public AInteractObject
{
public:
	AWitchFlower();
	~AWitchFlower();

	AWitchFlower(const AWitchFlower& _Other) = delete;
	AWitchFlower(AWitchFlower&& _Other) noexcept = delete;
	AWitchFlower& operator=(const AWitchFlower& _Other) = delete;
	AWitchFlower& operator=(AWitchFlower&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Collected();
	void Disappear();

	void SetState(EWitchFlowerState _State)
	{
		State = _State;
	}

	bool CollectedState()
	{
		return IsCollected;
	}

protected:

private:
	std::shared_ptr<class USpriteRenderer> WitchFlowerRenderer;
	std::shared_ptr<class UCollision> WitchFlowerCol;
	std::shared_ptr<class ACameraActor> Camera;

	FVector WitchFlowerSize = { 50.0f, 50.0f };
	float AnimSpeed = 0.3f;

	EWitchFlowerState State;

	bool IsCollected = false;
};

