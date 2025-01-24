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

	void Serialize(UEngineSerializer& _Ser) override;
	void DeSerialize(UEngineSerializer& _Ser) override;

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

	void SetEntranceName(std::string _EntName)
	{
		EntranceName = _EntName;
	}

	std::string& GetEntranceName()
	{
		return EntranceName;
	}

protected:

private:
	std::shared_ptr<class UCollision> EntranceCol;

	FVector EntrancePos/* = { 1000.0f, 1395, 0.0f }*/;
	FVector EntranceSize/* = { 300.0f, 100.0f }*/;

	std::string EntranceName;
};

