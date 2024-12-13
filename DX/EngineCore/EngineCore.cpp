#include "PreCompile.h"
#include "EngineCore.h"
#include <EngineBase/EngineDebug.h>
#include <EnginePlatform/EngineWindow.h>


UEngineCore::UEngineCore()
{
}

UEngineCore::~UEngineCore()
{
}

void UEngineCore::EngineStart(HINSTANCE _Instance)
{
	UEngineDebug::LeakCheck();

	UEngineWindow::EngineWindowInit(_Instance);

	UEngineWindow MainWindow;

	MainWindow.Open("MainWindow");

	UEngineWindow::WindowMessageLoop(
		[]()
		{
			// 시작할때 하고 싶은것
		},
		[]()
		{
			// 엔진이 돌아갈때 하고 싶은것
		},
		[]()
		{
			// 엔진이 끝났을때 하고 싶은것.
		});
}