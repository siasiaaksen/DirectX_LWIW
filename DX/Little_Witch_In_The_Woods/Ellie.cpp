#include "PreCompile.h"
#include "Ellie.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineSprite.h>
#include <EnginePlatform/EngineInput.h>


AEllie::AEllie()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	EllieRenderer = CreateDefaultSubObject<USpriteRenderer>();

	{
		EllieRenderer->SetSprite("Ellie_Walk.png", 0);
		EllieRenderer->SetRelativeScale3D({ 80, 100, 1.0f });
		EllieRenderer->CreateAnimation("Ellie_Walk_FLeft", "Ellie_Walk.png", 28, 35, 0.1f);
		EllieRenderer->CreateAnimation("Ellie_Walk_Front", "Ellie_Walk.png", 12, 19, 0.1f);
		EllieRenderer->CreateAnimation("Ellie_Walk_FRight", "Ellie_Walk.png", 44, 51, 0.1f);
		EllieRenderer->CreateAnimation("Ellie_Walk_BLeft", "Ellie_Walk.png", 56, 63, 0.1f);
		EllieRenderer->CreateAnimation("Ellie_Walk_Back", "Ellie_Walk.png", 68, 75, 0.1f);
		EllieRenderer->CreateAnimation("Ellie_Walk_BRight", "Ellie_Walk.png", 80, 87, 0.1f);
	}

	{
		EllieRenderer->SetSprite("Ellie_Idle.png", 0);
		EllieRenderer->SetRelativeScale3D({ 80, 100, 1.0f });
		EllieRenderer->CreateAnimation("Ellie_Idle_FLeft", "Ellie_Idle.png", 0, 3, 0.1f);
		EllieRenderer->CreateAnimation("Ellie_Idle_Front", "Ellie_Idle.png", 4, 7, 0.1f);
		EllieRenderer->CreateAnimation("Ellie_Idle_FRight", "Ellie_Idle.png", 8, 11, 0.1f);
		EllieRenderer->CreateAnimation("Ellie_Idle_BLeft", "Ellie_Idle.png", 12, 15, 0.1f);
		EllieRenderer->CreateAnimation("Ellie_Idle_Back", "Ellie_Idle.png", 16, 19, 0.1f);
		EllieRenderer->CreateAnimation("Ellie_Idle_BRight", "Ellie_Idle.png", 20, 3, 0.1f);
	}

	EllieRenderer->SetupAttachment(RootComponent);
}

AEllie::~AEllie()
{
}

void AEllie::BeginPlay()
{
	APawn::BeginPlay();
}

void AEllie::Tick(float _DeltaTime)
{
	APawn::Tick(_DeltaTime);

	if (true == UEngineInput::IsPress('W'))
	{
		AddActorLocation(FVector({ 0.0f, 1.0f }) * _DeltaTime * 80.0f);
		EllieRenderer->ChangeAnimation("Ellie_Walk_Back");
	}
	if (true == UEngineInput::IsPress('S'))
	{
		AddActorLocation(FVector({ 0.0f, -1.0f }) * _DeltaTime * 80.0f);
		EllieRenderer->ChangeAnimation("Ellie_Walk_Front");
	}
	if (true == UEngineInput::IsPress('A'))
	{
		AddActorLocation(FVector({ -1.0f, 0.0f }) * _DeltaTime * 80.0f);
		EllieRenderer->ChangeAnimation("Ellie_Walk_FLeft");
	}
	if (true == UEngineInput::IsPress('D'))
	{
		AddActorLocation(FVector({ 1.0f, 0.0f }) * _DeltaTime * 80.0f);
		EllieRenderer->ChangeAnimation("Ellie_Walk_FRight");
	}

	if (false == UEngineInput::IsPress('W'))
	{
		EllieRenderer->ChangeAnimation("Ellie_Idle_Back");
	}
	if (false == UEngineInput::IsPress('S'))
	{
		EllieRenderer->ChangeAnimation("Ellie_Idle_Front");
	}
	if (false == UEngineInput::IsPress('A'))
	{
		EllieRenderer->ChangeAnimation("Ellie_Idle_FLeft");
	}
	if (false == UEngineInput::IsPress('D'))
	{
		EllieRenderer->ChangeAnimation("Ellie_Idle_FRight");
	}
}

