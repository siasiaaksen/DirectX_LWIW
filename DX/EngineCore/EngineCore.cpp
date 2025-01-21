#include "PreCompile.h"
#include "EngineCore.h"
#include <EngineBase/EngineDebug.h>
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineInput.h>
#include "IContentsCore.h"
#include "EngineResources.h"
#include "EngineConstantBuffer.h"
#include "EngineStructuredBuffer.h"
#include "EngineGUI.h"
#include "Level.h"
#include "GameInstance.h"


UEngineGraphicDevice& UEngineCore::GetDevice()
{
	return GEngine->Device;
}

UEngineWindow& UEngineCore::GetMainWindow()
{
	return GEngine->MainWindow;
}

std::map<std::string, std::shared_ptr<class ULevel>> UEngineCore::GetAllLevelMap()
{
	return GEngine->LevelMap;
}

UEngineWorkThreadPool& UEngineCore::GetThreadPool()
{
	return GEngine->ThreadPool;
}

UGameInstance* UEngineCore::GetGameInstance()
{
	return GEngine->GameInstance.get();
}

UEngineCore* GEngine = nullptr;

FVector UEngineCore::GetScreenScale()
{
	return GEngine->Data.WindowSize;
}

UEngineCore::UEngineCore()
{
}

UEngineCore::~UEngineCore()
{
}

void UEngineCore::WindowInit(HINSTANCE _Instance)
{
	UEngineWindow::EngineWindowInit(_Instance);
	GEngine->MainWindow.Open("MainWindow");
}

void UEngineCore::LoadContents(std::string_view _DllName)
{
	UEngineDirectory Dir;

	Dir.MoveParentToDirectory("Build");
	Dir.Move("bin/x64");

#ifdef _DEBUG
	Dir.Move("Debug");
#else
	Dir.Move("Release");
#endif

	UEngineFile File = Dir.GetFile(_DllName);

	std::string FullPath = File.GetPathToString();
	// �� ������ dll �ε�
	GEngine->ContentsDLL = LoadLibraryA(FullPath.c_str());

	if (nullptr == GEngine->ContentsDLL)
	{
		MSGASSERT("������ ����� �ε��Ҽ��� �����ϴ�.");
		return;
	}

	//                                                                                                                            �� ������ �ھ�, �� �Լ� "CreateContentsCore"�� �ּҸ�
	//                                                                                                                            �Լ� ������ Ptr�� ����
	INT_PTR(__stdcall * Ptr)(std::shared_ptr<IContentsCore>&) = (INT_PTR(__stdcall*)(std::shared_ptr<IContentsCore>&))GetProcAddress(GEngine->ContentsDLL, "CreateContentsCore");
	// ������ �ھ�� CreateContentsCore�� ã�� ������ ������ BreateContentsCoreDefine�� �ؾߵ�

	if (nullptr == Ptr)
	{
		MSGASSERT("������ �ھ� ���ο� CreateContentsCoreDefine�� �������� �ʾҽ��ϴ�.");
		return;
	}

	Ptr(GEngine->Core);

	if (nullptr == GEngine->Core)
	{
		MSGASSERT("������ �ھ� ������ �����߽��ϴ�.");
		return;
	}
}

void UEngineCore::EngineStart(HINSTANCE _Instance, std::string_view _DllName)
{
	UEngineDebug::LeakCheck();

	UEngineCore EngineCore;

	GEngine = &EngineCore;

	GEngine->ThreadPool.Initialize();

	WindowInit(_Instance);

	LoadContents(_DllName);

	UEngineWindow::WindowMessageLoop(
		[]()
		{
			// �����Ҷ� �ϰ� ������

			GEngine->Device.CreateDeviceAndContext();
			GEngine->Core->EngineStart(GEngine->Data);
			GEngine->MainWindow.SetWindowPosAndScale(GEngine->Data.WindowPos, GEngine->Data.WindowSize);
			GEngine->Device.CreateBackBuffer(GEngine->MainWindow);

			UEngineGUI::Init();
		},
		[]()
		{
			// ������ ���ư��� �ϰ� ������

			EngineFrame();
		},
		[]()
		{
			// ������ �������� �ϰ� ������.

			EngineEnd();
		});
}

std::shared_ptr<ULevel> UEngineCore::NewLevelCreate(std::string_view _Name)
{
	if (true == GEngine->LevelMap.contains(_Name.data()))
	{
		MSGASSERT("���� �̸��� ������ �� ������� �����ϴ�." + std::string(_Name.data()));
		return nullptr;
	}

	std::shared_ptr<ULevel> Ptr = std::make_shared<ULevel>();
	Ptr->SetName(_Name);

	GEngine->LevelMap.insert({ _Name.data(), Ptr });

	std::cout << "NewLevelCreate" << std::endl;

	return Ptr;
}

void UEngineCore::OpenLevel(std::string_view _Name)
{
	std::string UpperString = UEngineString::ToUpper(_Name);

	if (false == GEngine->LevelMap.contains(UpperString))
	{
		MSGASSERT("������ ���� ������ �����Ϸ��� �߽��ϴ�." + UpperString);
		return;
	}

	GEngine->NextLevel = GEngine->LevelMap[UpperString];
}

void UEngineCore::EngineFrame()
{
	if (nullptr != GEngine->NextLevel)
	{
		if (nullptr != GEngine->CurLevel)
		{
			GEngine->CurLevel->LevelChangeEnd();
		}

		GEngine->CurLevel = GEngine->NextLevel;

		GEngine->CurLevel->LevelChangeStart();
		GEngine->NextLevel = nullptr;
		GEngine->Timer.TimeStart();
	}

	GEngine->Timer.TimeCheck();
	float DeltaTime = GEngine->Timer.GetDeltaTime();

	if (true == GEngine->MainWindow.IsFocus())
	{
		UEngineInput::KeyCheck(DeltaTime);
	}
	else 
	{
		UEngineInput::KeyReset();
	}

	GEngine->CurLevel->Tick(DeltaTime);
	GEngine->CurLevel->Render(DeltaTime);
	GEngine->CurLevel->Collision(DeltaTime);
	GEngine->CurLevel->Release(DeltaTime);
}

void UEngineCore::EngineEnd()
{
	UEngineGUI::Release();

	GEngine->Device.Release();

	UEngineResources::Release();

	UEngineConstantBuffer::Release();
	UEngineStructuredBuffer::Release();

	GEngine->CurLevel = nullptr;
	GEngine->NextLevel = nullptr;
	GEngine->LevelMap.clear();

	UEngineDebug::EndConsole();
}

void UEngineCore::SetGameInstance(std::shared_ptr<UGameInstance> _Inst)
{
	GEngine->GameInstance = _Inst;
}