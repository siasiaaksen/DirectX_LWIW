#include "PreCompile.h"
#include "EngineCore.h"
#include <EngineBase/EngineDebug.h>
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineSound.h>
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
	// 내 컨텐츠 dll 로드
	GEngine->ContentsDLL = LoadLibraryA(FullPath.c_str());

	if (nullptr == GEngine->ContentsDLL)
	{
		MSGASSERT("컨텐츠 기능을 로드할수가 없습니다.");
		return;
	}

	//                                                                                                                            내 컨텐츠 코어, 의 함수 "CreateContentsCore"의 주소를
	//                                                                                                                            함수 포인터 Ptr에 저장
	INT_PTR(__stdcall * Ptr)(std::shared_ptr<IContentsCore>&) = (INT_PTR(__stdcall*)(std::shared_ptr<IContentsCore>&))GetProcAddress(GEngine->ContentsDLL, "CreateContentsCore");
	// 컨텐츠 코어에서 CreateContentsCore를 찾기 때문에 무조건 BreateContentsCoreDefine을 해야됨

	if (nullptr == Ptr)
	{
		MSGASSERT("컨텐츠 코어 내부에 CreateContentsCoreDefine을 정의하지 않았습니다.");
		return;
	}

	Ptr(GEngine->Core);

	if (nullptr == GEngine->Core)
	{
		MSGASSERT("컨텐츠 코어 생성에 실패했습니다.");
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
			// 시작할때 하고 싶은것

			UEngineSound::Init();

			GEngine->Device.CreateDeviceAndContext();
			GEngine->Core->EngineStart(GEngine->Data);
			GEngine->MainWindow.SetWindowPosAndScale(GEngine->Data.WindowPos, GEngine->Data.WindowSize);
			GEngine->Device.CreateBackBuffer(GEngine->MainWindow);

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
	if (true == GEngine->LevelMap.contains(_Name.data()))
	{
		MSGASSERT("같은 이름의 레벨을 또 만들수는 없습니다." + std::string(_Name.data()));
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
		MSGASSERT("만들지 않은 레벨로 변경하려고 했습니다." + UpperString);
		return;
	}

	GEngine->NextLevel = GEngine->LevelMap[UpperString];
}

void UEngineCore::EngineFrame()
{
	if (true == GEngine->IsCurLevelReset) // 레벨 리셋
	{
		GEngine->CurLevel = nullptr;
		GEngine->IsCurLevelReset = false;
	}

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

	UEngineSound::Update();

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

	UEngineSound::Release();

	GEngine->CurLevel = nullptr;
	GEngine->NextLevel = nullptr;
	GEngine->LevelMap.clear();

	UEngineDebug::EndConsole();
}

void UEngineCore::SetGameInstance(std::shared_ptr<UGameInstance> _Inst)
{
	GEngine->GameInstance = _Inst;
}

bool UEngineCore::IsCurLevel(std::string_view _LevelName)
{
	std::string UpperName = UEngineString::ToUpper(_LevelName);

	if (GEngine->CurLevel->GetName() != UpperName)
	{
		DestroyLevel(_LevelName); // 지우고
		return false;
	}
	return true;
}

std::shared_ptr<ULevel> UEngineCore::ReadyToNextLevel(std::string_view _LevelName)
{
	std::string UpperName = UEngineString::ToUpper(_LevelName);

	std::map<std::string, std::shared_ptr<ULevel>>::iterator FindIter = GEngine->LevelMap.find(UpperName);
	GEngine->LevelMap.erase(FindIter); // 현재 레벨을 Level 관리구조에서 제외시키고
	GEngine->IsCurLevelReset = true; // 다음 프레임까지 현재 레벨을 살려둔다.

	return 	GEngine->NextLevel;
}

void UEngineCore::SetNextLevel(std::shared_ptr<class ULevel> _NextLevel)
{
	GEngine->NextLevel = _NextLevel;
}

void UEngineCore::DestroyLevel(std::string_view _LevelName)
{
	std::string UpperName = UEngineString::ToUpper(_LevelName);

	if (false == GEngine->LevelMap.contains(UpperName))
	{
		return;
	}

	std::map<std::string, std::shared_ptr<class ULevel>>::iterator FindIter = GEngine->LevelMap.find(UpperName);

	if (nullptr != FindIter->second)
	{
		FindIter->second = nullptr;
	}

	GEngine->LevelMap.erase(FindIter);
}
