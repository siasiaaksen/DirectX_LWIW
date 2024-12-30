#include "PreCompile.h"
#include "PlayGameMode.h"
#include "EnginePlatform/EngineInput.h"
#include "Ellie.h"


APlayGameMode::APlayGameMode()
{
	Ellie = GetWorld()->SpawnActor<AEllie>();
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::Tick(float _DeltaTime)
{
	// 부모 호출
	AActor::Tick(_DeltaTime);

	if (true == UEngineInput::IsPress('W'))
	{
		Ellie->AddActorLocation(FVector({ 0.0f, 1.0f }) * _DeltaTime * 80.0f);
		Ellie->GetRenderer()->ChangeAnimation("Ellie_Walk_Back");
	}
	if (true == UEngineInput::IsPress('S'))
	{
		Ellie->AddActorLocation(FVector({ 0.0f, -1.0f }) * _DeltaTime * 80.0f);
		Ellie->GetRenderer()->ChangeAnimation("Ellie_Walk_Front");
	}
	if (true == UEngineInput::IsPress('A'))
	{
		Ellie->AddActorLocation(FVector({ -1.0f, 0.0f }) * _DeltaTime * 80.0f);
		Ellie->GetRenderer()->ChangeAnimation("Ellie_Walk_FLeft");
	}
	if (true == UEngineInput::IsPress('D'))
	{
		Ellie->AddActorLocation(FVector({ 1.0f, 0.0f }) * _DeltaTime * 80.0f);
		Ellie->GetRenderer()->ChangeAnimation("Ellie_Walk_FRight");
	}
}

