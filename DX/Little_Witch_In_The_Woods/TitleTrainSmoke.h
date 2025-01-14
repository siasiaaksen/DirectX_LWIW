#pragma once
#include <EngineCore/Actor.h>


class ATitleTrainSmoke : public AActor
{
public:
	ATitleTrainSmoke();
	~ATitleTrainSmoke();

	ATitleTrainSmoke(const ATitleTrainSmoke& _Other) = delete;
	ATitleTrainSmoke(ATitleTrainSmoke&& _Other) noexcept = delete;
	ATitleTrainSmoke& operator=(const ATitleTrainSmoke& _Other) = delete;
	ATitleTrainSmoke& operator=(ATitleTrainSmoke&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> BigSmokeRenderer;
	std::shared_ptr<class USpriteRenderer> MidSmokeRenderer;
	std::shared_ptr<class USpriteRenderer> SmallSmokeRenderer;

	float SmokeAlpha = 0.5f;
};

