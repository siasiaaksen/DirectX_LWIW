#include "PreCompile.h"
#include "EngineCore.h"
#include <EngineBase/EngineDebug.h>
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineInput.h>
#include "IContentsCore.h"
#include "EngineResources.h"
#include "EngineGUI.h"
#include "Level.h"


UEngineGraphicDevice UEngineCore::Device;
UEngineWindow UEngineCore::MainWindow;
HMODULE UEngineCore::ContentsDLL = nullptr;
std::shared_ptr<IContentsCore> UEngineCore::Core;
UEngineInitData UEngineCore::Data;
UEngineTimer UEngineCore::Timer;

std::shared_ptr<class ULevel> UEngineCore::NextLevel;
std::shared_ptr<class ULevel> UEngineCore::CurLevel = nullptr;

std::map<std::string, std::shared_ptr<class ULevel>> UEngineCore::LevelMap;

FVector UEngineCore::GetScreenScale()
{
	return Data.WindowSize;
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
	MainWindow.Open("MainWindow");
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
	// 내 컨텐츠 dll 로드
	ContentsDLL = LoadLibraryA(FullPath.c_str());

	if (nullptr == ContentsDLL)
	{
		MSGASSERT("컨텐츠 기능을 로드할수가 없습니다.");
		return;
	}

	//                                                                                                                            내 컨텐츠 코어, 의 함수 "CreateContentsCore"의 주소를
	//                                                                                                                            함수 포인터 Ptr에 저장
	INT_PTR(__stdcall * Ptr)(std::shared_ptr<IContentsCore>&) = (INT_PTR(__stdcall*)(std::shared_ptr<IContentsCore>&))GetProcAddress(ContentsDLL, "CreateContentsCore");
	// 컨텐츠 코어에서 CreateContentsCore를 찾기 때문에 무조건 BreateContentsCoreDefine을 해야됨

	if (nullptr == Ptr)
	{
		MSGASSERT("컨텐츠 코어 내부에 CreateContentsCoreDefine을 정의하지 않았습니다.");
		return;
	}

	Ptr(Core);

	if (nullptr == Core)
	{
		MSGASSERT("컨텐츠 코어 생성에 실패했습니다.");
		return;
	}
}

void UEngineCore::EngineStart(HINSTANCE _Instance, std::string_view _DllName)
{
	UEngineDebug::LeakCheck();

	WindowInit(_Instance);

	LoadContents(_DllName);

	UEngineWindow::WindowMessageLoop(
		[]()
		{
			// 시작할때 하고 싶은것

			Device.CreateDeviceAndContext();
			Core->EngineStart(Data);
			MainWindow.SetWindowPosAndScale(Data.WindowPos, Data.WindowSize);
			Device.CreateBackBuffer(MainWindow);

			UEngineGUI::Init();
		},
		[]()
		{
			// 엔진이 돌아갈때 하고 싶은것

			EngineFrame();
		},
		[]()
		{
			// 엔진이 끝났을때 하고 싶은것.

			EngineEnd();
		});
}

std::shared_ptr<ULevel> UEngineCore::NewLevelCreate(std::string_view _Name)
{
	std::shared_ptr<ULevel> Ptr = std::make_shared<ULevel>();
	Ptr->SetName(_Name);

	LevelMap.insert({ _Name.data(), Ptr });

	std::cout << "NewLevelCreate" << std::endl;

	return Ptr;
}

void UEngineCore::OpenLevel(std::string_view _Name)
{
	if (false == LevelMap.contains(_Name.data()))
	{
		MSGASSERT("만들지 않은 레벨로 변경하려고 했습니다." + std::string(_Name));
		return;
	}

	NextLevel = LevelMap[_Name.data()];
}

void UEngineCore::EngineFrame()
{
	if (nullptr != NextLevel)
	{
		if (nullptr != CurLevel)
		{
			CurLevel->LevelChangeEnd();
		}

		CurLevel = NextLevel;

		CurLevel->LevelChangeStart();
		NextLevel = nullptr;
		Timer.TimeStart();
	}

	Timer.TimeCheck();
	float DeltaTime = Timer.GetDeltaTime();
	UEngineInput::KeyCheck(DeltaTime);

	CurLevel->Tick(DeltaTime);
	CurLevel->Render(DeltaTime);
}

void UEngineCore::EngineEnd()
{
	UEngineGUI::Release();

	Device.Release();

	UEngineResources::Release();

	CurLevel = nullptr;
	NextLevel = nullptr;
	LevelMap.clear();

	UEngineDebug::EndConsole();
}