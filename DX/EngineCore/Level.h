#pragma once
#include <EngineBase/Object.h>
#include <EngineBase/EngineDebug.h>


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
	void Render(float _DeltaTime);

	template<typename ActorType>
	std::shared_ptr<ActorType> SpawnActor()
	{
		static_assert(std::is_base_of_v<AActor, ActorType>, "액터를 상속받지 않은 클래스를 SpawnActor하려고 했습니다.");

		if (false == std::is_base_of_v<AActor, ActorType>)
		{
			MSGASSERT("액터를 상속받지 않은 클래스를 SpawnActor하려고 했습니다.");
			return nullptr;
		}

		char* ActorMemory = new char[sizeof(ActorType)];

		AActor* ActorPtr = reinterpret_cast<ActorType*>(ActorMemory);
		ActorPtr->World = this;

		ActorType* NewPtr = reinterpret_cast<ActorType*>(ActorMemory);
		std::shared_ptr<ActorType> NewActor(NewPtr = new(ActorMemory) ActorType());

		BeginPlayList.push_back(NewActor);

		return NewActor;
	}

	void ChangeRenderGroup(int _PrevGroupOrder, std::shared_ptr<class URenderer> _Renderer);

protected:

private:
	std::list<std::shared_ptr<class AActor>> BeginPlayList;

	std::list<std::shared_ptr<class AActor>> AllActorList;

	std::map<int, std::list<std::shared_ptr<class URenderer>>> Renderers;
};

