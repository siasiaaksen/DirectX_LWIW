#pragma once
#include <EngineCore/Actor.h>


class ATitleTrain : public AActor
{
public:
	ATitleTrain();
	~ATitleTrain();

	ATitleTrain(const ATitleTrain& _Other) = delete;
	ATitleTrain(ATitleTrain&& _Other) noexcept = delete;
	ATitleTrain& operator=(const ATitleTrain& _Other) = delete;
	ATitleTrain& operator=(ATitleTrain&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> TrainRenderer;
	std::shared_ptr<class USpriteRenderer> TrainBlurRenderer;
};

