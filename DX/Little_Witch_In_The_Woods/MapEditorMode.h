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
	void LevelChangeStart() override;

private:
	std::shared_ptr<class UMapEditorWindow> TileMapWindow;
	std::shared_ptr<class USpriteRenderer> PivotSpriteRenderer;
	std::shared_ptr<class UTileMapRenderer> TileMapRenderer;

	FVector TileSize = { 32.0f, 32.0f };
};

