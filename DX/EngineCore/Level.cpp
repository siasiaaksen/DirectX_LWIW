#include "PreCompile.h"
#include "Level.h"
#include "Actor.h"
#include "Renderer.h"
#include "EngineCore.h"
#include "EngineCamera.h"
#include "CameraActor.h"
#include "EngineGUI.h"


std::shared_ptr<class ACameraActor> ULevel::SpawnCamera(int _Order)
{
	std::shared_ptr<ACameraActor> Camera = std::make_shared<ACameraActor>();

	if (true == Cameras.contains(_Order))
	{
		MSGASSERT("�̹� �����ϴ� ī�޶� �� ������� �߽��ϴ�.");
	}

	Camera->BeginPlay();

	Cameras.insert({ _Order , Camera });
	return Camera;
}

ULevel::ULevel()
{
	SpawnCamera(0);
}

ULevel::~ULevel()
{
}

void ULevel::LevelChangeStart()
{

}

void ULevel::LevelChangeEnd()
{

}

void ULevel::Tick(float _DeltaTime)
{
	std::list<std::shared_ptr<class AActor>>::iterator StartIter = BeginPlayList.begin();
	std::list<std::shared_ptr<class AActor>>::iterator EndIter = BeginPlayList.end();
	
	for (; StartIter != EndIter; )
	{
		std::shared_ptr<AActor> CurActor = *StartIter;

		if (false == CurActor->IsActive())
		{
			++StartIter;
			continue;
		}

		StartIter = BeginPlayList.erase(StartIter);

		CurActor->BeginPlay();
		AllActorList.push_back(CurActor);
	}

	for (std::shared_ptr<AActor> CurActor : AllActorList)
	{
		CurActor->Tick(_DeltaTime);
	}
}

void ULevel::Render(float _DeltaTime)
{
	// �����
	UEngineCore::Device.RenderStart();

	for (std::pair<const int, std::shared_ptr<ACameraActor>>& Camera : Cameras)
	{
		Camera.second->Tick(_DeltaTime);
		Camera.second->CameraComponent->Render(_DeltaTime);
	}

	if (true == UEngineWindow::IsApplicationOn())
	{
		UEngineGUI::GUIRender();
	}

	// ����Ѵ�
	UEngineCore::Device.RenderEnd();
}

void ULevel::ChangeRenderGroup(int _CameraOrder, int _PrevGroupOrder, std::shared_ptr<URenderer> _Renderer)
{
	if (false == Cameras.contains(_CameraOrder))
	{
		MSGASSERT("�������� �ʴ� ī�޶� �������� ����������� �߽��ϴ�.");
	}

	std::shared_ptr<ACameraActor> Camera = Cameras[_CameraOrder];

	Camera->CameraComponent->ChangeRenderGroup(_PrevGroupOrder, _Renderer);
}
