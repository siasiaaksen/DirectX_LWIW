#pragma once
#include <EnginePlatform/EngineWinImage.h>
#include <EngineCore/Pawn.h>
#include <EngineCore/SpriteRenderer.h>


enum class EEllieState
{
	IDLE,
	MOVE,
	MAX,
};


class AEllie : public APawn
{
public:
	AEllie();
	~AEllie();

	AEllie(const AEllie& _Other) = delete;
	AEllie(AEllie&& _Other) noexcept = delete;
	AEllie& operator=(const AEllie& _Other) = delete;
	AEllie& operator=(AEllie&& _Other) noexcept = delete;

	std::shared_ptr<USpriteRenderer>& GetRenderer()
	{
		return EllieRenderer;
	}

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle();
	void Move(float _DeltaTime);

	bool IsMoveCheck(FVector _Dir);
	void DirCheck();

	void CollectItem();

	FVector GetEllieSize()
	{
		return EllieSize;
	}

	void SetColImage(std::string_view _ColImageName, std::string_view _FolderName);

	UEngineWinImage& GetColImage()
	{
		return ColImage;
	}

protected:

private:
	std::shared_ptr<USpriteRenderer> EllieRenderer;
	std::shared_ptr<class UCollision> EllieCollision;
	std::shared_ptr<class ACameraActor> Camera;
	std::shared_ptr<class ARoom> Room;

	EEllieState State;
	float Speed = 200.0f;

	FVector EllieSize = { 70.0f, 100.0f };
	std::string DirString = "_Front";

	UEngineWinImage ColImage;
};

