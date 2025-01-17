#pragma once
#include <EngineCore/Actor.h>


class AEntranceCollision : public AActor
{
public:
	AEntranceCollision();
	~AEntranceCollision();

	// delete Function
	AEntranceCollision(const AEntranceCollision& _Other) = delete;
	AEntranceCollision(AEntranceCollision&& _Other) noexcept = delete;
	AEntranceCollision& operator=(const AEntranceCollision& _Other) = delete;
	AEntranceCollision& operator=(AEntranceCollision&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetEntranceSize(FVector _EntranceSize)
	{
		EntranceSize = _EntranceSize;
	}

	FVector& GetEntranceSize()
	{
		return EntranceSize;
	}

	void SetEntrancePos(FVector _EntrancePos)
	{
		EntrancePos = _EntrancePos;
	}

	FVector& GetEntrancePos()
	{
		return EntrancePos;
	}

	std::shared_ptr<class UCollision>& GetEntranceCol()
	{
		return EntranceCol;
	}

protected:

private:
	std::shared_ptr<class UCollision> EntranceCol;

	FVector EntranceSize/* = { 300.0f, 100.0f }*/;
	FVector EntrancePos/* = { 1000.0f, 1395, 0.0f }*/;
};

