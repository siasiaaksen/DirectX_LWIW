#pragma once
#include <EngineBase/Object.h>

#include "EngineCore.h"


class ULevel : public UObject
{
public:
	ENGINEAPI ULevel();
	ENGINEAPI ~ULevel();

	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	// 이제 실행되는 레벨이 되었을때
	void LevelChangeStart();
	// 교체 당했을때
	void LevelChangeEnd();

	void Tick(float _DeltaTime);

	template<typename ActorType>
	std::shared_ptr<ActorType> SpawnActor()
	{
		std::shared_ptr<ActorType> NewActor = std::make_shared<ActorType>();

		BeginPlayList.push_back(NewActor);

		return NewActor;
	}

protected:

private:
	std::list<std::shared_ptr<class AActor>> BeginPlayList;

	std::list<std::shared_ptr<class AActor>> AllActorList;
};

