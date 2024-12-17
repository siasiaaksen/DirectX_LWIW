#pragma once
#include <EngineBase/Object.h>


class AActor : public UObject
{
	friend class ULevel;

public:
	ENGINEAPI AActor();
	ENGINEAPI ~AActor();

	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	ENGINEAPI virtual void BeginPlay();
	ENGINEAPI virtual void Tick(float _DeltaTime);

	virtual void LevelChangeStart() {}
	virtual void LevelChangeEnd() {}

	void CreateDefaultSubObject()
	{

	}

	ULevel* GetWorld()
	{
		return World;
	}

protected:

private:
	ULevel* World;

	std::shared_ptr<class USceneComponent> RootComponent;
	std::list<std::shared_ptr<class UActorComponent>> ActorComponentList;
};

