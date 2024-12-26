#pragma once
#include "ActorComponent.h"


class USceneComponent : public UActorComponent
{
public:
	USceneComponent();
	~USceneComponent();

	USceneComponent(const USceneComponent& _Other) = delete;
	USceneComponent(USceneComponent&& _Other) noexcept = delete;
	USceneComponent& operator=(const USceneComponent& _Other) = delete;
	USceneComponent& operator=(USceneComponent&& _Other) noexcept = delete;

	void AddLocation(const FVector& _Value)
	{
		Transform.Location += _Value;
		Transform.TransformUpdate();
	}

	void SetRelativeScale3D(const FVector& _Value)
	{
		Transform.Scale = _Value;
		Transform.TransformUpdate();
	}

	void SetLocation(const FVector& _Value)
	{
		Transform.Location = _Value;
		Transform.TransformUpdate();
	}

	FTransform& GetTransformRef()
	{
		return Transform;
	}

	void SetupAttachment(USceneComponent* _Parent);

protected:
	FTransform Transform;

private:
	USceneComponent* Parent;
	std::list<std::shared_ptr<USceneComponent>> Childs;
};

