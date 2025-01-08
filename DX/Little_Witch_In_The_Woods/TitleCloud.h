#pragma once
#include <EngineCore/Actor.h>


class ATitleCloud : public AActor
{
public:
	ATitleCloud();
	~ATitleCloud();

	ATitleCloud(const ATitleCloud& _Other) = delete;
	ATitleCloud(ATitleCloud&& _Other) noexcept = delete;
	ATitleCloud& operator=(const ATitleCloud& _Other) = delete;
	ATitleCloud& operator=(ATitleCloud&& _Other) noexcept = delete;

	void CloudMove(float _DeltaTime);
	void CloudCheck(FVector _Dir);

	float RandomCloudSpeed();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> CloudRenderer = nullptr;
	std::shared_ptr<class UCollision> CloudCollision = nullptr;

	std::vector<std::shared_ptr<class USpriteRenderer>> CloudRendV;
	std::vector<std::shared_ptr<class UCollision>> CloudColV;
	std::vector<float> CloudSpeed;

	float CloudAlpha = 0.8f;
	float Speed = 1.0f;
};

