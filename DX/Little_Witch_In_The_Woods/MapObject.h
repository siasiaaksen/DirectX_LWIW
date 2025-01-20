#pragma once
#include <EngineCore/Actor.h>


class AMapObject :public AActor
{
public:
	AMapObject();
	~AMapObject();

	AMapObject(const AMapObject& _Other) = delete;
	AMapObject(AMapObject&& _Other) noexcept = delete;
	AMapObject& operator=(const AMapObject& _Other) = delete;
	AMapObject& operator=(AMapObject&& _Other) noexcept = delete;

	void BeginPlay();
	void Tick(float _DeltaTime);
	std::shared_ptr<class USpriteRenderer> Sprite;

protected:

private:
};

