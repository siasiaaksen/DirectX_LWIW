#include "PreCompile.h"
#include "TitleGameMode.h"
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EnginePlatform/EngineInput.h>
#include "TitleLogo.h"
#include "TitleBackground.h"
#include "TitleMoon.h"
#include "TitleMountain.h"
#include "TitleBridge.h"
#include "TitleTrain.h"
#include "TitleTree.h"
#include "TitleStar.h"


class TestWindow : public UEngineGUIWindow
{
public:
	void OnGUI() override
	{
		ImGui::Button("WindowButton");
		ImGui::SameLine();
		ImGui::Text("test");

	}
};


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

	// ī�޶�
	{
		std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
		Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
	}

	// imgui
	{
		UEngineGUI::CreateGUIWindow<TestWindow>("TestWindow");
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
}