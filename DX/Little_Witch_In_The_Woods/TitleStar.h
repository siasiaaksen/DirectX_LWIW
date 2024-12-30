#pragma once
#include <EngineCore/Actor.h>


class ATitleStar : public AActor
{
public:
	ATitleStar();
	~ATitleStar();

	ATitleStar(const ATitleStar& _Other) = delete;
	ATitleStar(ATitleStar&& _Other) noexcept = delete;
	ATitleStar& operator=(const ATitleStar& _Other) = delete;
	ATitleStar& operator=(ATitleStar&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> StarRenderer;
};

