#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineRandom.h>


enum class EMongsiriState
{
	IDLE,
	MOVE,
	COLLECTED,
	ESCAPE,
	MAX,
};


class AMongsiri : public AActor
{
public:
	AMongsiri();
	~AMongsiri();

	AMongsiri(const AMongsiri& _Other) = delete;
	AMongsiri(AMongsiri&& _Other) noexcept = delete;
	AMongsiri& operator=(const AMongsiri& _Other) = delete;
	AMongsiri& operator=(AMongsiri&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle(float _DeltaTime);
	void MOVE(float _DeltaTime);

	void FindCheck(float _DeltaTime);
	void ChaseCheck(float _DeltaTime);
	void MoveToEllie(float _DeltaTime);

	void SwitchAnim();

	void SetState(EMongsiriState _State)
	{
		State = _State;
	}

protected:

private:
	std::shared_ptr<class USpriteRenderer> FindMark;
	std::shared_ptr<class USpriteRenderer> MongsiriRenderer;
	std::shared_ptr<class UCollision> MongsiriOuterCol;
	std::shared_ptr<class UCollision> MongsiriInnerCol;
	std::shared_ptr<class ACameraActor> Camera;

	EMongsiriState State;

	std::string DirName = "_Front";
	FVector MongsiriSize = { 50.0f, 50.0f };
	float AnimSpeed = 0.2f;
	float MoveSpeed = 0.3f;

	UEngineRandom random;
};

