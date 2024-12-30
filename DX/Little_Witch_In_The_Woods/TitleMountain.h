#pragma once
#include <EngineCore/Actor.h>


class ATitleMountain : public AActor
{
public:
	ATitleMountain();
	~ATitleMountain();

	ATitleMountain(const ATitleMountain& _Other) = delete;
	ATitleMountain(ATitleMountain&& _Other) noexcept = delete;
	ATitleMountain& operator=(const ATitleMountain& _Other) = delete;
	ATitleMountain& operator=(ATitleMountain&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> MountainRenderer;
};

