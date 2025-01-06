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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> CloudRenderer;
};

