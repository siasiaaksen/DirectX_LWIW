#include "PreCompile.h"
#include "MongsiriHole.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/Collision.h>


AMongsiriHole::AMongsiriHole()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	std::shared_ptr<USpriteRenderer> HoleRenderer = CreateDefaultSubObject<USpriteRenderer>();
	{
		HoleRenderer->SetupAttachment(RootComponent);
		HoleRenderer->SetTexture("Mongsiri_Hole.png", true, 2.5f);
		HoleRenderer->SetWorldLocation({ 50.0f, 50.0f, 0.0f });
	}

	{
		std::shared_ptr<UCollision> HoleCollision = CreateDefaultSubObject<UCollision>();
		HoleCollision->SetCollisionProfileName("MongsiriHole");
		HoleCollision->SetupAttachment(RootComponent);
		HoleCollision->SetScale3D(HoleRenderer->GetWorldScale3D());
		HoleCollision->SetWorldLocation(HoleRenderer->GetWorldLocation());
	}
}

AMongsiriHole::~AMongsiriHole()
{
}

void AMongsiriHole::BeginPlay()
{
	AActor::BeginPlay();
}

void AMongsiriHole::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

void AMongsiriHole::YSorting()
{
	FVector Pos = GetActorLocation();
	Pos.Z = Pos.Y;

	SetActorLocation(Pos);
}
