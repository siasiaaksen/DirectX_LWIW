#pragma once
#include <EngineCore/Actor.h>


class ATitleMoon : public AActor
{
public:
	ATitleMoon();
	~ATitleMoon();

	ATitleMoon(const ATitleMoon& _Other) = delete;
	ATitleMoon(ATitleMoon&& _Other) noexcept = delete;
	ATitleMoon& operator=(const ATitleMoon& _Other) = delete;
	ATitleMoon& operator=(ATitleMoon&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> MoonRenderer;
};

