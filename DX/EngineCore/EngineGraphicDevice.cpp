#include "PreCompile.h"
#include "EngineGraphicDevice.h"

UEngineGraphicDevice::UEngineGraphicDevice()
{
}

UEngineGraphicDevice::~UEngineGraphicDevice()
{
}

void UEngineGraphicDevice::GetHighPerFormanceAdapter()
{
    IDXGIFactory* Factory = nullptr;
    IDXGIAdapter* Adapter = nullptr;

    HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&Factory));

    if (nullptr == Factory)
    {
        MSGASSERT("�׷���ī�� ����� ���丮 ������ �����߽��ϴ�.");
        return;
    }

    for (int Index = 0;; ++Index)
    {
        IDXGIAdapter* CurAdapter = nullptr;

        Factory->EnumAdapters(Index, &CurAdapter);

        if (nullptr == CurAdapter)
        {
            break;
        }

        Adapter = CurAdapter;
    }

    if (nullptr != Factory)
    {
        Factory->Release();
    }

    if (nullptr == Adapter)
    {
        MSGASSERT("�׷���ī�尡 �޷����� ���� ��ǻ���Դϴ�.");
        return;
    }

    Adapter->Release();
}

void UEngineGraphicDevice::CreateDeviceAndContext()
{
    GetHighPerFormanceAdapter();

#ifdef _DEBUG
#endif
}

void UEngineGraphicDevice::CreateBackBuffer(const UEngineWindow& _Window)
{
    int a = 0;
}