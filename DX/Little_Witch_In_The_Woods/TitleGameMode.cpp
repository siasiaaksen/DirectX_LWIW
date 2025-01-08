#include "PreCompile.h"
#include "TitleGameMode.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCamera.h>
#include "TitleLogo.h"
#include "TitleBackground.h"
#include "TitleMoon.h"
#include "TitleMountain.h"
#include "TitleBridge.h"
#include "TitleTrain.h"
#include "TitleTree.h"
#include "TitleStar.h"
#include "TitleTrainSmoke.h"
#include "TitleCloud.h"


ATitleGameMode::ATitleGameMode()
{
	GetWorld()->CreateCollisionProfile("BG");
	GetWorld()->CreateCollisionProfile("Cloud");
	GetWorld()->LinkCollisionProfile("BG", "Cloud");

	{
		std::shared_ptr<ATitleBackground> BG = GetWorld()->SpawnActor<ATitleBackground>();
		std::shared_ptr<ATitleStar> Star = GetWorld()->SpawnActor<ATitleStar>();
		std::shared_ptr<ATitleMoon> Moon = GetWorld()->SpawnActor<ATitleMoon>();
		std::shared_ptr<ATitleCloud> Cloud = GetWorld()->SpawnActor<ATitleCloud>();
		std::shared_ptr<ATitleMountain> Mountain = GetWorld()->SpawnActor<ATitleMountain>();
		std::shared_ptr<ATitleTrain> Train = GetWorld()->SpawnActor<ATitleTrain>();
		std::shared_ptr<ATitleTrainSmoke> Smoke = GetWorld()->SpawnActor<ATitleTrainSmoke>();
		std::shared_ptr<ATitleBridge> Bridge = GetWorld()->SpawnActor<ATitleBridge>();
		std::shared_ptr<ATitleTree> Tree = GetWorld()->SpawnActor<ATitleTree>();
		std::shared_ptr<ATitleLogo> Logo = GetWorld()->SpawnActor<ATitleLogo>();
	}

	// ī�޶�
	{
		std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
		Camera->SetActorLocation({ 0.0f, 0.0f, -609.0f, 1.0f });
		Camera->GetCameraComponent()->SetProjectionType(EProjectionType::Perspective);
		Camera->GetCameraComponent()->SetZSort(0, true);
	}
}

ATitleGameMode::~ATitleGameMode()
{
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	// �θ� ȣ��
	AActor::Tick(_DeltaTime);

	if (true == UEngineInput::IsPress(VK_SPACE))
	{
		UEngineCore::OpenLevel("PlayLevel");
	}
	if (true == UEngineInput::IsPress(VK_F1))
	{
		UEngineCore::OpenLevel("MapEditorLevel");
	}
}