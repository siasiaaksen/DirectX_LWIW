#pragma once
#include <EngineCore/Actor.h>


class ATitleTree : public AActor
{
public:
	ATitleTree();
	~ATitleTree();

	ATitleTree(const ATitleTree& _Other) = delete;
	ATitleTree(ATitleTree&& _Other) noexcept = delete;
	ATitleTree& operator=(const ATitleTree& _Other) = delete;
	ATitleTree& operator=(ATitleTree&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> TreeRenderer;
};

