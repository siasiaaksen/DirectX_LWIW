#pragma once
#include <EngineCore/Actor.h>


class AInteractCollision : public AActor
{
public:
	AInteractCollision();
	~AInteractCollision();

	// delete Function
	AInteractCollision(const AInteractCollision& _Other) = delete;
	AInteractCollision(AInteractCollision&& _Other) noexcept = delete;
	AInteractCollision& operator=(const AInteractCollision& _Other) = delete;
	AInteractCollision& operator=(AInteractCollision&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Serialize(UEngineSerializer& _Ser) override;
	void DeSerialize(UEngineSerializer& _Ser) override;

	void SetInterColSize(FVector _EntranceSize)
	{
		InterColSize = _EntranceSize;
	}

	FVector& GetInterColSize()
	{
		return InterColSize;
	}

	void SetInterColPos(FVector _InterColPos)
	{
		InterColPos = _InterColPos;
	}

	FVector& GetInterColPos()
	{
		return InterColPos;
	}

	std::shared_ptr<class UCollision>& GetInterCol()
	{
		return InterCol;
	}

	void SetInterColName(std::string _EntName)
	{
		InterColName = _EntName;
	}

	std::string& GetInterColName()
	{
		return InterColName;
	}

protected:

private:
	std::shared_ptr<class UCollision> InterCol;

	FVector InterColPos/* = { 1000.0f, 1395, 0.0f }*/;
	FVector InterColSize/* = { 300.0f, 100.0f }*/;

	std::string InterColName;
};

