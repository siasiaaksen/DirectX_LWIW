#pragma once
#include <EngineBase/EngineRandom.h>
#include "InteractObject.h"


enum class EMongsiriState
{
	IDLE,
	MOVE,
	COLLECTED,
	ESCAPE,
	DISAPPEAR,
	MAX,
};


class AMongsiri : public AInteractObject
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
	void Move(float _DeltaTime);
	void Collected(float _DeltaTime);
	void Escape(float _DeltaTime);
	void Disappear(float _DeltaTime);

	void FindCheck(float _DeltaTime);
	void MoveToEllie(float _DeltaTime);

	void SwitchAnim();

	void SetState(EMongsiriState _State)
	{
		State = _State;
	}

	void SetSort(bool _Value)
	{
		IsSort = _Value;
	}

	void YSorting();

protected:

private:
	std::shared_ptr<class USpriteRenderer> FindMark;
	std::shared_ptr<class USpriteRenderer> MongsiriRenderer;
	std::shared_ptr<class UCollision> MongsiriOuterCol;
	std::shared_ptr<class UCollision> MongsiriInnerCol;
	std::shared_ptr<class UCollision> MongsiriEscapeCol;
	std::shared_ptr<class ACameraActor> Camera;

	EMongsiriState State;

	std::string DirName = "_FLeft";
	FVector MongsiriSize = { 50.0f, 50.0f };
	float AnimSpeed = 0.2f;
	float MoveSpeed = 0.3f;

	bool IsSort = true;
	bool IsEscape = false;
};

