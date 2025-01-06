#pragma once
#include <EngineCore/Actor.h>


class ARoom : public AActor
{
public:
	ARoom();
	~ARoom();

	ARoom(const ARoom& _Other) = delete;
	ARoom(ARoom&& _Other) noexcept = delete;
	ARoom& operator=(const ARoom& _Other) = delete;
	ARoom& operator=(ARoom&& _Other) noexcept = delete;

	void SetRoomSize(FVector _Value)
	{
		RoomSize = _Value;
	}

	FVector& GetRoomSize()
	{
		return RoomSize;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> BaseSprite = nullptr;
	FVector RoomSize = { 1280.0f, 720.0f };
};

