#include "PreCompile.h"
#include "EngineGraphicDevice.h"
#include "EngineTexture.h"
#include "EngineDepthStencilState.h"


UEngineGraphicDevice::UEngineGraphicDevice()
{
}

UEngineGraphicDevice::~UEngineGraphicDevice()
{
    Release();
}

void UEngineGraphicDevice::Release()
{
    MainAdapter = nullptr;
    DXBackBufferTexture = nullptr;
    RTV = nullptr;
    SwapChain = nullptr;
    Context = nullptr;
    Device = nullptr;
}

IDXGIAdapter* UEngineGraphicDevice::GetHighPerFormanceAdapter()
{
    IDXGIFactory* Factory = nullptr;
    unsigned __int64 MaxVideoMemory = 0;
    IDXGIAdapter* ResultAdapter = nullptr;

    HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&Factory));

    if (nullptr == Factory)
    {
        MSGASSERT("�׷���ī�� ����� ���丮 ������ �����߽��ϴ�.");
        return nullptr;
    }

    for (int Index = 0;; ++Index)
    {
        IDXGIAdapter* CurAdapter = nullptr;

        Factory->EnumAdapters(Index, &CurAdapter);

        if (nullptr == CurAdapter)
        {
            break;
        }

        DXGI_ADAPTER_DESC Desc;

        CurAdapter->GetDesc(&Desc);

        if (MaxVideoMemory <= Desc.DedicatedVideoMemory)
        {
            MaxVideoMemory = Desc.DedicatedVideoMemory;

            if (nullptr != ResultAdapter)
            {
                ResultAdapter->Release();
            }

            ResultAdapter = CurAdapter;
            continue;
        }

        CurAdapter->Release();
    }

    if (nullptr != Factory)
    {
        Factory->Release();
    }

    if (nullptr == ResultAdapter)
    {
        MSGASSERT("�׷���ī�尡 �޷����� ���� ��ǻ���Դϴ�.");
        return nullptr;
    }

    return ResultAdapter;
}

void UEngineGraphicDevice::CreateDeviceAndContext()
{
    MainAdapter = GetHighPerFormanceAdapter();

    int iFlag = 0;

#ifdef _DEBUG
    iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL ResultLevel;

    HRESULT Result = D3D11CreateDevice(
        MainAdapter.Get(),
        D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,
        nullptr,
        iFlag,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &Device,
        &ResultLevel,
        &Context);

    if (nullptr == Device)
    {
        MSGASSERT("�׷��� ����̽� ������ �����߽��ϴ�.");
        return;
    }

    if (nullptr == Context)
    {
        MSGASSERT("�׷��� ���ؽ�Ʈ ������ �����߽��ϴ�.");
        return;
    }

    if (Result != S_OK)
    {
        MSGASSERT("���� �߸���.");
        return;
    }

    if (ResultLevel != D3D_FEATURE_LEVEL_11_0
        && ResultLevel != D3D_FEATURE_LEVEL_11_1)
    {
        MSGASSERT("���̷�Ʈ 11������ �������� �ʴ� �׷���ī�� �Դϴ�.");
        return;
    }

    Result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    if (Result != S_OK)
    {
        MSGASSERT("������ ������ ���뿡 ������ ������ϴ�.");
        return;
    }

    DefaultResourcesInit();
}

void UEngineGraphicDevice::CreateBackBuffer(const UEngineWindow& _Window)
{
    FVector Size = _Window.GetWindowSize();

    D3D11_TEXTURE2D_DESC Desc = { 0 };
    Desc.ArraySize = 1;
    Desc.Width = Size.iX();
    Desc.Height = Size.iY();
    Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

    Desc.SampleDesc.Count = 1;
    Desc.SampleDesc.Quality = 0;

    Desc.MipLevels = 1;
    Desc.Usage = D3D11_USAGE_DEFAULT;
    Desc.CPUAccessFlags = 0;
    Desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;

    DepthTex = std::make_shared<UEngineTexture>();

    DepthTex->ResCreate(Desc);

    DXGI_SWAP_CHAIN_DESC ScInfo = { 0 };

    ScInfo.BufferCount = 2;
    ScInfo.BufferDesc.Width = Size.iX();
    ScInfo.BufferDesc.Height = Size.iY();
    ScInfo.OutputWindow = _Window.GetWindowHandle();
    // ��üȭ��, âȭ��
    ScInfo.Windowed = true;

    // �ֻ��� ����Ϳ� �󸶳� ������ ����
    ScInfo.BufferDesc.RefreshRate.Denominator = 1;
    ScInfo.BufferDesc.RefreshRate.Numerator = 60;

    // ������� �������
    ScInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

    // ����ͳ� �����쿡 �ȼ��� ���ŵǴ� ����
    ScInfo.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    ScInfo.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    // �뵵
    ScInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;

    // ���ø�
    ScInfo.SampleDesc.Quality = 0;
    ScInfo.SampleDesc.Count = 1;

    // n���� ���ۿ� ���� 
    ScInfo.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    ScInfo.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    IDXGIFactory* pF = nullptr;

    MainAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pF));

    pF->CreateSwapChain(Device.Get(), &ScInfo, &SwapChain);

    pF->Release();
    MainAdapter->Release();

    if (nullptr == SwapChain)
    {
        MSGASSERT("����ü�� ���ۿ� �����߽��ϴ�.");
    }

    ID3D11Texture2D* TexPtr = nullptr;

    if (S_OK != SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &DXBackBufferTexture))
    {
        MSGASSERT("����� �ؽ�ó�� �����µ� �����߽��ϴ�.");
    };

    //                                         ��ĳ����(ID3D11Texture2D�� ~���ҽ��� ��ӹް� ����)
    if (S_OK != Device->CreateRenderTargetView(DXBackBufferTexture.Get(), nullptr, &RTV))
    {
        MSGASSERT("�ؽ�ó �������� ȹ�濡 �����߽��ϴ�");
    }
}

void UEngineGraphicDevice::RenderStart()
{
    FVector ClearColor;

    // �ƹ��͵� �� ����� �� ó�� ȭ�� ����
    // �� �� �� ����
    ClearColor = FVector(0.46f, 0.75f, 0.65f, 1.0f);

    Context->ClearRenderTargetView(RTV.Get(), ClearColor.Arr1D);
    Context->ClearDepthStencilView(DepthTex->GetDSV(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    // ���⿡ �ٽ� �׷�
    ID3D11RenderTargetView* RTV = UEngineCore::GetDevice().GetRTV();
    ID3D11RenderTargetView* ArrRtv[16] = { 0 };
    ArrRtv[0] = RTV; 
    Context->OMSetRenderTargets(1, &ArrRtv[0], DepthTex->GetDSV());
}

void UEngineGraphicDevice::RenderEnd()
{
    HRESULT Result = SwapChain->Present(0, 0);

    if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
    {
        MSGASSERT("�ػ� �����̳� ����̽� ���� ������ ��Ÿ�� ���� �����Ǿ����ϴ�");
        return;
    }
}