#pragma once
#include <EngineCore/HUD.h>


class APlayHUD : public AHUD
{
public:
	APlayHUD();
	~APlayHUD();

	APlayHUD(const APlayHUD& _Other) = delete;
	APlayHUD(APlayHUD&& _Other) noexcept = delete;
	APlayHUD& operator=(const APlayHUD& _Other) = delete;
	APlayHUD& operator=(APlayHUD&& _Other) noexcept = delete;

	void BeginPlay();
	void Tick(float _DeltaTime);

protected:

private:

};

