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


ATitleGameMode::ATitleGameMode()
{
	{
		std::shared_ptr<class ATitleBackground> BG = GetWorld()->SpawnActor<ATitleBackground>();
		std::shared_ptr<class ATitleStar> Star = GetWorld()->SpawnActor<ATitleStar>();
		std::shared_ptr<class ATitleMoon> Moon = GetWorld()->SpawnActor<ATitleMoon>();
		std::shared_ptr<class ATitleMountain> Mountain = GetWorld()->SpawnActor<ATitleMountain>();
		std::shared_ptr<class ATitleTrain> Train = GetWorld()->SpawnActor<ATitleTrain>();
		std::shared_ptr<class ATitleBridge> Bridge = GetWorld()->SpawnActor<ATitleBridge>();
		std::shared_ptr<class ATitleTree> Tree = GetWorld()->SpawnActor<ATitleTree>();
		std::shared_ptr<class ATitleLogo> Logo = GetWorld()->SpawnActor<ATitleLogo>();
	}

	// 카메라
	{
		std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
		Camera->SetActorLocation({ 0.0f, 0.0f, -624.0f, 1.0f });
		Camera->GetCameraComponent()->SetProjectionType(EProjectionType::Perspective);
		Camera->GetCameraComponent()->SetZSort(0, true);
	}
}

ATitleGameMode::~ATitleGameMode()
{
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	// 부모 호출
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