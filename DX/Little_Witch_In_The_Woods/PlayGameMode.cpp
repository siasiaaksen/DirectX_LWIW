#include "PreCompile.h"
#include "PlayGameMode.h"
#include <EnginePlatform/EngineInput.h>
#include "Ellie.h"


APlayGameMode::APlayGameMode()
{
	Ellie = GetWorld()->SpawnActor<AEllie>();
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	AActor::BeginPlay();
}

void APlayGameMode::Tick(float _DeltaTime)
{
	// �θ� ȣ��
	AActor::Tick(_DeltaTime);

	if (true == UEngineInput::IsDown(VK_HOME))
	{
		UEngineCore::OpenLevel("TitleLevel");
	}
}

