#pragma once
#include <EngineCore/Actor.h>


class ATitleBackground : public AActor
{
public:
	ATitleBackground();
	~ATitleBackground();

	ATitleBackground(const ATitleBackground& _Other) = delete;
	ATitleBackground(ATitleBackground&& _Other) noexcept = delete;
	ATitleBackground& operator=(const ATitleBackground& _Other) = delete;
	ATitleBackground& operator=(ATitleBackground&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> BGRenderer;
};

