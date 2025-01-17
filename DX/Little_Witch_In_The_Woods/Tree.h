#pragma once
#include <EngineCore/Actor.h>


class ATree : public AActor
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

protected:

private:
	std::shared_ptr<class USpriteRenderer> TreeSprite;
	std::shared_ptr<class UCollision> TreeCollision;
};

