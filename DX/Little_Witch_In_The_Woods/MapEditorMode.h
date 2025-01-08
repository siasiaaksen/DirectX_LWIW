#pragma once
#include <EngineCore/GameMode.h>


class AMapEditorMode : public AGameMode
{
public:
	AMapEditorMode();
	~AMapEditorMode();

	AMapEditorMode(const AMapEditorMode& _Other) = delete;
	AMapEditorMode(AMapEditorMode&& _Other) noexcept = delete;
	AMapEditorMode& operator=(const AMapEditorMode& _Other) = delete;
	AMapEditorMode& operator=(AMapEditorMode&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:

};

