#include "PreCompile.h"
#include "MapEditorMode.h"
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/CameraActor.h>
#include <EnginePlatform/EngineInput.h>


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


AMapEditorMode::AMapEditorMode()
{
	// Ä«¸Þ¶ó
	{
		std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
		Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
	}
}

AMapEditorMode::~AMapEditorMode()
{
}

void AMapEditorMode::BeginPlay()
{
	AActor::BeginPlay();

	// imgui
	{
		UEngineGUI::CreateGUIWindow<TestWindow>("TestWindow");
	}
}

void AMapEditorMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (true == UEngineInput::IsDown(VK_HOME))
	{
		UEngineCore::OpenLevel("TitleLevel");
	}
}

