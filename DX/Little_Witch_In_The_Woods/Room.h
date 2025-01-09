#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineWinImage.h>
#include <EngineCore/Collision.h>


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
		BaseSprite->SetScale3D(RoomSize);
		//BaseColSprite->SetScale3D(RoomSize);
	}

	FVector GetRoomSize()
	{
		return RoomSize;
	}

	void SetCollisionSize(FVector _Value)
	{
		CollisionSize = _Value;
		BaseCollision->SetScale3D(CollisionSize);
	}

	FVector GetCollisionSize()
	{
		return CollisionSize;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<USpriteRenderer> BaseSprite = nullptr;
	std::shared_ptr<USpriteRenderer> BaseColSprite = nullptr;
	std::shared_ptr<UCollision> BaseCollision = nullptr;

	FVector RoomSize/* = { 1280.0f, 720.0f }*/;
	FVector CollisionSize;
};

