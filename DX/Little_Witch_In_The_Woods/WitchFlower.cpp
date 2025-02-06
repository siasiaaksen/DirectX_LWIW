#include "PreCompile.h"
#include "WitchFlower.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/Collision.h>
#include <EngineCore/CameraActor.h>


AWitchFlower::AWitchFlower()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	{
		WitchFlowerRenderer = CreateDefaultSubObject<USpriteRenderer>();
		WitchFlowerRenderer->SetupAttachment(RootComponent);
		WitchFlowerRenderer->SetAutoScaleRatio(2.5f);

		WitchFlowerRenderer->SetSprite("WitchFlower.png", 0);
		WitchFlowerRenderer->CreateAnimation("WitchFlower", "WitchFlower.png", 0, 8, AnimSpeed, false);
	}

	{
		WitchFlowerCol = CreateDefaultSubObject<UCollision>();
		WitchFlowerCol->SetCollisionProfileName("WitchFlower");
		WitchFlowerCol->SetScale3D(WitchFlowerSize);
		FVector CollisionCenter;
		CollisionCenter.Y = WitchFlowerSize.Y - WitchFlowerSize.Half().Y;
		WitchFlowerCol->SetWorldLocation(CollisionCenter);
		WitchFlowerCol->SetupAttachment(RootComponent);
	}

	State = EWitchFlowerState::IDLE;
	SetActive(true);
}

AWitchFlower::~AWitchFlower()
{
}

void AWitchFlower::BeginPlay()
{
	AInteractObject::BeginPlay();
}

void AWitchFlower::Tick(float _DeltaTime)
{
	AInteractObject::Tick(_DeltaTime);

	switch (State)
	{
	case EWitchFlowerState::IDLE:
		break;
	case EWitchFlowerState::COLLECTED:
		Collected();
		break;
	case EWitchFlowerState::DISAPPEAR:
		Disappear();
		break;
	default:
		break;
	}

	{
		FVector Pos = GetActorLocation();
		Pos.Z = Pos.Y;

		SetActorLocation(Pos);
	}
}

void AWitchFlower::Collected()
{
	WitchFlowerRenderer->ChangeAnimation("WitchFlower");
	WitchFlowerRenderer->SetAnimationEvent("WitchFlower", 8,
		[this]()
		{
			State = EWitchFlowerState::DISAPPEAR;
		});
}

void AWitchFlower::Disappear()
{
	SetActive(false);
}
