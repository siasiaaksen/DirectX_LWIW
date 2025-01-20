#pragma once
#include "Creature.h"


class ATree : public ACreature
{
public:
	ATree();
	~ATree();

	ATree(const ATree& _Other) = delete;
	ATree(ATree&& _Other) noexcept = delete;
	ATree& operator=(const ATree& _Other) = delete;
	ATree& operator=(ATree&& _Other) noexcept = delete;

	std::shared_ptr<class USpriteRenderer>& GetSprite()
	{
		return TreeSprite;
	}

	std::shared_ptr<class UCollision>& GetCollision()
	{
		return TreeCollision;
	}

	void BeginPlay();
	void Tick(float _DeltaTime);

protected:

private:
	std::shared_ptr<class USpriteRenderer> TreeSprite;
	std::shared_ptr<class UCollision> TreeCollision;
};

