#pragma once
#include <EngineCore/GameMode.h>


enum class EPlayType
{
	PLAY,
	POTION,
	MAX
};


class APlayGameMode : public AGameMode
{
public:
	APlayGameMode();
	~APlayGameMode();

	APlayGameMode(const APlayGameMode& _Other) = delete;
	APlayGameMode(APlayGameMode&& _Other) noexcept = delete;
	APlayGameMode& operator=(const APlayGameMode& _Other) = delete;
	APlayGameMode& operator=(APlayGameMode&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Play();
	void Potion();

	void KeyInput();

	void CameraMove();

	void RoomChange();

	void LoadData(UEngineSerializer _Ser, int _ListNum);

protected:
	void LevelChangeStart() override;

private:
	class AEllie* Ellie = nullptr;
	std::shared_ptr<class ARoom> Room = nullptr;
	std::shared_ptr<class AMongsiri> Mongsiri = nullptr;
	std::shared_ptr<class AWitchFlower> WitchFlower = nullptr;
	std::shared_ptr<class AInteractCollision> EntranceCol = nullptr;
	std::shared_ptr<class ACameraActor> Camera = nullptr;

	FVector RoomSize;
	std::string RoomName;

	EPlayType PlayType = EPlayType::MAX;
};

