#pragma once
#include <EngineCore/Actor.h>


class AMongsiri : public AActor
{
public:
	AMongsiri();
	~AMongsiri();

	AMongsiri(const AMongsiri& _Other) = delete;
	AMongsiri(AMongsiri&& _Other) noexcept = delete;
	AMongsiri& operator=(const AMongsiri& _Other) = delete;
	AMongsiri& operator=(AMongsiri&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void ChaseCheck(float _DeltaTime);

protected:

private:
	std::shared_ptr<class USpriteRenderer> MongsiriRenderer;
	std::shared_ptr<class UCollision> MongsiriCollision;
	std::shared_ptr<class ACameraActor> Camera;

	std::shared_ptr<class AEllie> Ellie;

	FVector MongsiriSize = { 50.0f, 50.0f };
	float AnimSpeed = 0.2f;
};

