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
	std::shared_ptr<class USpriteRenderer> SmokeRenderer;
};

