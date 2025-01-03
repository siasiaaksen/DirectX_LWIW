#pragma once
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
	
protected:

private:
	std::shared_ptr<USpriteRenderer> EllieRenderer;
	std::shared_ptr<class ACameraActor> Camera;

	EEllieState State;
	int PosValue = 0;
};

