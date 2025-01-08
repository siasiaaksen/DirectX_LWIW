#pragma once
#include <EngineCore/GameMode.h>


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

	void CameraMove();

	void RoomChange();

protected:

private:
	std::shared_ptr<class AEllie> Ellie = nullptr;
	std::shared_ptr<class ARoom> Room = nullptr;
	std::shared_ptr<class ACameraActor> Camera = nullptr;
};

