#pragma once
#include <EnginePlatform/EngineWinImage.h>
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
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

	void SetRoomSprite(std::string_view _Name, FVector _RoomSize)
	{
		BaseSprite->SetTexture(_Name);
		BaseSprite->SetScale3D(_RoomSize);
		BaseSprite->SetWorldLocation({ 0.0f, 0.0f, 1000.0f });
	}

	void SetRoomColSprite(std::string_view _Name)
	{
		BaseColSprite->SetTexture(_Name, true, 1.0f);
		BaseColSprite->SetWorldLocation({ 0.0f, 0.0f, 800.0f });
	}

	void SetRoomSize(FVector _Value)
	{
		RoomSize = _Value;
		BaseSprite->SetScale3D(RoomSize);
		//BaseColSprite->SetScale3D(RoomSize);
	}

	FVector GetRoomSize()
	{
		return ColImage.GetImageScale();
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

	void SetColImage(std::string_view _ColImageName, std::string_view _FolderName);

	UEngineWinImage& GetColImage()
	{
		return ColImage;
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

	UEngineWinImage ColImage;
};

