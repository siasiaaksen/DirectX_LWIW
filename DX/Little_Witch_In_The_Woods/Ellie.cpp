#include "PreCompile.h"
#include "Ellie.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineSprite.h>


AEllie::AEllie()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	EllieRenderer = CreateDefaultSubObject<USpriteRenderer>();

	{
		EllieRenderer->SetSprite("Ellie_Walk.png", 0);
		EllieRenderer->SetRelativeScale3D({ 80, 100, 1.0f });
		EllieRenderer->CreateAnimation("Ellie_Walk_FLeft", "Ellie_Walk.png", 0, 7, 0.2f);
		EllieRenderer->CreateAnimation("Ellie_Walk_Front", "Ellie_Walk.png", 12, 19, 0.2f);
		EllieRenderer->CreateAnimation("Ellie_Walk_FRight", "Ellie_Walk.png", 44, 51, 0.2f);
		EllieRenderer->CreateAnimation("Ellie_Walk_BLeft", "Ellie_Walk.png", 56, 63, 0.2f);
		EllieRenderer->CreateAnimation("Ellie_Walk_Back", "Ellie_Walk.png", 68, 75, 0.2f);
		EllieRenderer->CreateAnimation("Ellie_Walk_BRight", "Ellie_Walk.png", 80, 87, 0.2f);
	}

	{
		EllieRenderer->SetSprite("Ellie_Idle.png", 0);
		EllieRenderer->SetRelativeScale3D({ 80, 100, 1.0f });
		EllieRenderer->CreateAnimation("Ellie_Idle_FLeft", "Ellie_Idle.png", 0, 3, 0.2f);
		EllieRenderer->CreateAnimation("Ellie_Idle_Front", "Ellie_Idle.png", 4, 7, 0.2f);
		EllieRenderer->CreateAnimation("Ellie_Idle_FRight", "Ellie_Idle.png", 8, 11, 0.2f);
		EllieRenderer->CreateAnimation("Ellie_Idle_BLeft", "Ellie_Idle.png", 12, 15, 0.2f);
		EllieRenderer->CreateAnimation("Ellie_Idle_Back", "Ellie_Idle.png", 16, 19, 0.2f);
		EllieRenderer->CreateAnimation("Ellie_Idle_BRight", "Ellie_Idle.png", 20, 3, 0.2f);
	}

	EllieRenderer->SetupAttachment(RootComponent);
}

AEllie::~AEllie()
{
}

