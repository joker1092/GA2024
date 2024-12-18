#pragma warning(disable:4996)
#include "Device.h"

// DX �� ��ġ ���� ���� �����͵� 
// 
//D3D ��ġ �������̽�
IDXGIAdapter4* g_pAdapter = NULL;
ID3D12Device* g_pDevice = NULL;

//D3D ����ü�� �������̽�
IDXGISwapChain4* g_pSwapChain = NULL;

//���߹��۸� ��� �������̽���
const UINT g_RTCnt = 2;
UINT g_RTDescSize = 0;
UINT g_RTIndex = 0;
ID3D12DescriptorHeap* g_pRTDescHeap = NULL;
//D3D12_CPU_DESCRIPTOR_HANDLE g_RTDescs;
ID3D12Resource* g_pRT[g_RTCnt] = { NULL, };
#define g_BB g_pRT[g_RTIndex]
#define g_BackBuffer g_pBB
//#define g_RTViews g_pRTDesc

//��ɾ�ť �������̽���
ID3D12CommandQueue*         g_pCommandQueue = NULL;
ID3D12CommandAllocator*     g_pCommandAllocator = NULL;
ID3D12GraphicsCommandList*  g_pCommandList = NULL;

//������ ����ȭ �������̽�
ID3D12Fence* g_pFence = NULL;
UINT64 g_FenceValue = 0;
//UINT64 g_FenceValues[g_RTCnt] = { 0, };
//UINT g_FrameIndex = 0;
HANDLE g_FenceEvent = NULL;

//����Ʈ
D3D12_VIEWPORT g_VP;

//�׷��� �޸� ���� �ڵ�ȭ ���� : DXTK/��Ʈ ���� ���������� ����.
std::unique_ptr<GraphicsMemory> g_GraphicsMemory;

//��ġ ���� �⺻ ����
DISPLAYMODE g_Mode = { 960,600,0,1,DXGI_FORMAT_R8G8B8A8_UNORM };

//AA & AF Option
DWORD g_dwAA = 1;
DWORD g_dwAF = 1;
BOOL g_bMipMap = TRUE;

//D3D ��� ����
D3D_FEATURE_LEVEL g_FeatLv = D3D_FEATURE_LEVEL_12_0; //DX12
//D3D_FEATURE_LEVEL g_FeatLv = D3D_FEATURE_LEVEL_12_1; //DX12.1
//D3D_FEATURE_LEVEL g_FeatLv = D3D_FEATURE_LEVEL_11_0; //DX11
//D3D_FEATURE_LEVEL g_FeatLv = D3D_FEATURE_LEVEL_9_3; //DX9.0c
TCHAR* g_strFeatLv = _T("N/A");

//��ġ ����
DXGI_ADAPTER_DESC1 g_Adc;

//��üȭ�� ����
BOOL g_bWindowMode = TRUE;

//��������ȭ ����
BOOL g_bVSync = FALSE;

//===============================================================
//D3D ��ġ ����Լ�

//DX �� ���� ��ü �ʱ�ȭ
int DXSetup(HWND hwnd)
{
	//1�ܰ� : ������ ��ġ ���� �ʼ� ����
	CreateDeviceSwapChain(hwnd);
	CreateRenderTarget();
	SetViewPort();
    GetDeviceInfo();

	//2�ܰ� : ��Ÿ ������ ���� �߰� ����
	g_GraphicsMemory = std::make_unique<GraphicsMemory>(g_pDevice);
	ynFontCreate(g_pDevice);

	//3�ܰ� : �߰� ��ġ ����
	//todo:...
    return YN_OK;
}

//��ġ �� ��ü ����
void DXRelease()
{
	ynFontRelease();
	g_GraphicsMemory.reset();
	GPUSyncObjsRelease();
	CommandsRelease();

    for (UINT i = 0; i < g_RTCnt; i++)
    {
        SAFE_RELEASE(g_pRT[i]);
    }

	SAFE_RELEASE(g_pRTDescHeap);
	SAFE_RELEASE(g_pSwapChain);

	SAFE_RELEASE(g_pDevice);
}

//D3D ��ġ ���� �� ����ü�� ����
HRESULT CreateDeviceSwapChain(HWND Hwnd)
{
	HRESULT hr = S_OK;

    //DXGI �������̽� ����
	IDXGIFactory4* pFactory = nullptr;
	CreateDXGIFactory2(0, IID_PPV_ARGS(&pFactory));

    //DX ������ ��ġ ����
    hr = D3D12CreateDevice(0, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&g_pDevice));
    //hr = D3D12CreateDevice(0, D3D_FEATURE_LEVEL_12_0, __uuidof(ID3D12Device),(void**)&g_pDevice);
	//hr = D3D12CreateDevice(g_pAdapter, D3D_FEATURE_LEVEL_12_0, __uuidof(ID3D12Device), (void**)&g_pDevice);
    if (FAILED(hr)) 
    {
        ynError(hr, _T("����̽� ���� ����."));
    }

	//Ŀ�ǵ� ��ü ����
	CommandsCreate();

    //����ȭ ��ü ����
	GPUSyncObjsCreate();

    //���� ���۸� ����
    //����ü�� ���� ����
    DXGI_SWAP_CHAIN_DESC1 sd = {};
    sd.Width = g_Mode.Width;                            //�ػ�
    sd.Height = g_Mode.Height;
    sd.Format = g_Mode.Format;                          //����� �԰�
    sd.SampleDesc.Count = g_dwAA;                       //AA����
    sd.SampleDesc.Quality = 0;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   //�뵵����
    sd.BufferCount = g_RTCnt;                           //����� ����
    sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;      //���� ���۸� (�ɼ�)
    //sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;      //���� ���۸� (�ɼ�)

    //����ü�� ����
    IDXGISwapChain1* pSwapchain = nullptr;
    hr = pFactory->CreateSwapChainForHwnd(g_pCommandQueue, g_hWnd, &sd, nullptr, nullptr, &pSwapchain);
    if (FAILED(hr))
    {
        ynError(hr, _T("����̽� / ����ü�� / CreateSwapChainForHwnd ���� ����""\nRes={%dx%d} RT=%d AA=%d \n"),
            g_Mode.Width,g_Mode.Height,g_RTCnt,g_dwAA);
    }

    //����ü�� : �ű� �������̽� ȹ��.
    hr = pSwapchain->QueryInterface(IID_PPV_ARGS(&g_pSwapChain));
    if (FAILED(hr))
    {
        ynError(hr, _T("����̽� / ����ü�� ���� ����"));
    }

    //���� ������ "�����"���
    g_RTIndex = g_pSwapChain->GetCurrentBackBufferIndex();

    //��ġ �߰�
    //��üȭ�� ����
    pFactory->MakeWindowAssociation(g_hWnd, DXGI_MWA_NO_ALT_ENTER);

    //�ӽ� �������̽� ����
    SAFE_RELEASE(pFactory);
    SAFE_RELEASE(pSwapchain);

    return hr;
}

//��ġ-����ü���� ����Ÿ��(�����) ȹ��
HRESULT CreateRenderTarget()
{
    HRESULT hr = S_OK;

    //����� �ε��� ���
    //UINT bbidx = g_pSwapChain->GetCurrentBackBufferIndex();

    //��ũ����-�� ����
    D3D12_DESCRIPTOR_HEAP_DESC hd = {};
    hd.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    hd.NumDescriptors = g_RTCnt;
    //hd.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    //hd.NodeMask = 0;
    hr = g_pDevice->CreateDescriptorHeap(&hd, IID_PPV_ARGS(&g_pRTDescHeap));
    if (FAILED(hr))
    {
        ynError(hr, _T("�����-����Ÿ�� : ��ũ����-�� ���� ����"));
        return hr;
    }

    //����Ÿ��-�� ����
    g_RTDescSize = g_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    D3D12_CPU_DESCRIPTOR_HANDLE dh = g_pRTDescHeap->GetCPUDescriptorHandleForHeapStart();
    for (UINT i = 0; i < g_RTCnt; i++) {
        hr = g_pSwapChain->GetBuffer(i, IID_PPV_ARGS(&g_pRT[i]));
        g_pDevice->CreateRenderTargetView(g_pRT[i], nullptr, dh);
        dh.ptr += g_RTDescSize;
    }

    if (FAILED(hr))
    {
        ynError(hr, _T("�����-����Ÿ�ٺ� ���� ����"));
    }

    return hr;
}

//����Ʈ ����
void SetViewPort()
{
    D3D12_VIEWPORT vp;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.Width = (FLOAT)g_Mode.Width;
    vp.Height = (FLOAT)g_Mode.Height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    //g_CmdList->RSSetViewports(1, &vp);
    g_VP = vp;
}

//===============================================================
//Ŀ�ǵ� ��ü ����
int CommandsCreate()
{
    HRESULT hr = S_OK;

    D3D12_COMMAND_QUEUE_DESC qd = {};
    qd.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    qd.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	qd.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	qd.NodeMask = 0;
	hr = g_pDevice->CreateCommandQueue(&qd, IID_PPV_ARGS(&g_pCommandQueue));
	hr = g_pDevice->CreateCommandAllocator(qd.Type, IID_PPV_ARGS(&g_pCommandAllocator));
	hr = g_pDevice->CreateCommandList(0, qd.Type, g_pCommandAllocator, nullptr, IID_PPV_ARGS(&g_pCommandList));
	g_pCommandList->Close();
	
    if (FAILED(hr))
    {
		ynError(hr, _T("Ŀ�ǵ� ��ü���� ����"));
    }

    return YN_OK;
}

//��ɾ� ��ü ����
int CommandsReset()
{
	g_CmdAlloc->Reset();
	g_CmdList->Reset(g_CmdAlloc, nullptr);

	return YN_OK;
}

//��ɾ ����
int CommandsExecute()
{
	ID3D12CommandList* cmdLists[] = { g_CmdList, };
	g_CmdList->Close();
	g_CmdQueue->ExecuteCommandLists(_countof(cmdLists), cmdLists);

	return YN_OK;
}

//��ɾ� ��ü ����
void CommandsRelease()
{
	SAFE_RELEASE(g_pCommandQueue);
	SAFE_RELEASE(g_pCommandAllocator);
	SAFE_RELEASE(g_pCommandList);
}

//===============================================================
//GPU ����ȭ / ����ȭ �Լ�

//����ȭ ��ü ����
int GPUSyncObjsCreate()
{
	HRESULT hr = S_OK;

	//GPU�� ����ȭ ��ü ����
	hr = g_pDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&g_pFence));
	g_FenceValue = 1;

	//CPU�� ����ȭ ��ü ����
	g_FenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (FAILED(hr) || g_FenceEvent == NULL)
    {
		ynError(hr, _T("����ȭ ��ü / �̺�Ʈ ���� ����"));
    }

	return YN_OK;
}

//����ȭ ��ü ����
void GPUSyncObjsRelease()
{
	SAFE_RELEASE(g_pFence);
	CloseHandle(g_FenceEvent);
}

//GPU �۾��� ��� �Ѵ� : ����ȭ
int GPUSync()
{
	const UINT64 fence = g_FenceValue;
	g_CmdQueue->Signal(g_pFence, fence);                //Fence �� ����
    g_FenceValue++;

	if (g_pFence->GetCompletedValue() < fence)          //GPU �� ���� Fence �� Ȯ��
	{
		g_pFence->SetEventOnCompletion(fence, g_FenceEvent);        //�̺�Ʈ ����
		WaitForSingleObject(g_FenceEvent, INFINITE);				 // ���   
	}
	
	return YN_OK;
}



//��ġ-����ü�� / ����Ÿ�� / ����-���ٽ� ���� Ŭ����
int ClearBackBuffer(COLOR col)
{
	D3D12_RECT rc = { 0,0,(LONG)g_Mode.Width,(LONG)g_Mode.Height };

    //Ŀ�ǵ� ����
	g_CmdAlloc->Reset();
	g_CmdList->Reset(g_CmdAlloc, nullptr);

    //��ġ ���� �缳��
    g_CmdList->RSSetViewports(1, &g_VP);
	g_CmdList->RSSetScissorRects(1, &rc);

    //����Ÿ�� ���� ��ȯ
	D3D12_RESOURCE_BARRIER br = {};  //<���ҽ� ������> �� ���ҽ��� ���°��� �������̽�
	br.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	br.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	br.Transition.pResource = g_BB;
	br.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	br.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	br.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	g_CmdList->ResourceBarrier(1, &br);
	
    //���� ����Ÿ�� ��ũ���� ȹ�� 
    D3D12_CPU_DESCRIPTOR_HANDLE rtv;
	rtv = g_pRTDescHeap->GetCPUDescriptorHandleForHeapStart();
	rtv.ptr += (SIZE_T)g_RTIndex * (SIZE_T)g_RTDescSize;
	
    //����Ÿ�� "�����" �缳��
	g_CmdList->OMSetRenderTargets(1, &rtv, FALSE, nullptr);

    //��� : ������ ���� �����
	g_CmdList->ClearRenderTargetView(rtv, (float*)&col, 0, nullptr);

	return YN_OK;
}



//��ġ - ����ü�� ��ȯ : ��� �׸��� �Ϸ�� �� ȣ��
int Flip()
{
	ID3D12CommandList* cmdLists[] = { g_CmdList, };

	D3D12_RESOURCE_BARRIER br = {};
	br.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	br.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	br.Transition.pResource = g_BB;
	br.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	br.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	br.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	g_CmdList->ResourceBarrier(1, &br);

    //��� Ŀ�ǵ� ����Ʈ ����
	g_CmdList->Close();
	g_CmdQueue->ExecuteCommandLists(_countof(cmdLists), cmdLists);
	
    //ȭ�� ��� : Flip
	g_pSwapChain->Present(0, 0);
    //g_pSwapChain->Present(g_bVSync ? 1 : 0, 0);

	//GPU ����ȭ
	GPUSync();
	
    //�� ������ �غ�
	g_RTIndex = g_pSwapChain->GetCurrentBackBufferIndex();

	return YN_OK;
}

//���� ����ȭ�� ����ð� ȹ��
float GetEngindTime()
{
	static ULONGLONG oldTime = GetTickCount64();
	ULONGLONG nowTime = GetTickCount64();
	float dTime = (nowTime - oldTime) / 0.001f;
	oldTime = nowTime;

	return dTime;
}

//Ÿ�̸��� �ʴ� �����ӷ�(fps)�� ���
void PutFPS(int x, int y)
{
	static ULONGLONG oldTime = GetTickCount64();
	ULONGLONG nowTime = GetTickCount64();
	static ULONGLONG frmcnt = 0;
	static float fps = 0.0f;

	++frmcnt;
	ULONGLONG time = nowTime - oldTime;
    if (time >= 999)
    {
        oldTime = nowTime;
		fps = (float)frmcnt*1000/(float)time;
		frmcnt = 0;
    }
    //ynTextDraw(x, y, RGB(0, 0, 255), _T("FPS:%.1f/%d"), fps, frmcnt );
    ynTextDraw(x, y, COLOR(0, 1, 0, 1), _T("FPS:%.1f/%d"), fps, frmcnt);
}
//===============================================================
// ��ġ/GPU ���� ȹ�� �Լ���

//��ġ/GPU ���� ȹ��
void GetDeviceInfo()
{
    //��ġ ��� ���� Ȯ��
	GetFeatureLevel();

    //GPU ���� ���
	GetAdapterInfo(&g_Adc);

    //����� ���� ���
    //todo:...
}


//DX��� ����(Feature Level) ��� ���ڿ�
static TCHAR* strFeature[4][4] =
{
	{_T("DX9"),_T("DX9.1"),_T("DX9.2"),_T("DX9.3")},
	{_T("DX10"),_T("DX10.1"),_T("N/A"),_T("N/A")},
	{_T("DX11"),_T("DX11.1"),_T("DX11.2"),_T("DX11.3")},
	{_T("DX12"),_T("DX12.1"),_T("DX12.2"),_T("N/A")}
};

//DX ��� ���� ���ϱ�
void GetFeatureLevel()
{
    UINT feat = g_FeatLv;
    UINT ver = 0;
	UINT sub = 0;
    #define OFFSET 0x9;
    ver = ((feat&0xf000) >> 12) - OFFSET;
    sub = ((feat&0x0f00) >> 8);

	g_strFeatLv = strFeature[ver][sub];
}

//��ġ/GPU ���� ȹ��
HRESULT GetAdapterInfo(DXGI_ADAPTER_DESC1* pAd)
{
	IDXGIAdapter1* pAdapter;
	IDXGIFactory1* pFactory = NULL;
	//DXGI_ADAPTER_DESC ad;

	//DXGIFactory ��ä ����
	if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&pFactory))))
	{
		return E_FAIL;
	}

	pFactory->EnumAdapters1(0, &pAdapter);  //��� ȹ��
	pAdapter->GetDesc1(pAd);                //��� ���� ȹ��
	//*pAd = ad; 							//�ܺη� ����

	SAFE_RELEASE(pAdapter);
	SAFE_RELEASE(pFactory);

	return S_OK;
}

//��ġ/GPU ���� ���
void AdapterInfo(int x, int y, COLOR col) {
	DXGI_ADAPTER_DESC1& dc = g_Adc;
	ynTextDraw(x, y += 14, COLOR(0,1,0,1), _T("[GPU #%d]"),0);
	ynTextDraw(x, y += 14, col, _T("Adapter: %u"), 0);
	ynTextDraw(x, y += 14, col, _T("Description: %s"), dc.Description);
	ynTextDraw(x, y += 14, col, _T("VendorID: %u"), dc.VendorId);
	ynTextDraw(x, y += 14, col, _T("DeviceID: %u"), dc.DeviceId);
	ynTextDraw(x, y += 14, col, _T("SubSysID: %u"), dc.SubSysId);
	ynTextDraw(x, y += 14, col, _T("Revision: %u"), dc.Revision);
	SIZE_T totVramGB = toGB(dc.DedicatedVideoMemory + dc.DedicatedSystemMemory + dc.SharedSystemMemory);
	SIZE_T totVramMB = toMB(dc.DedicatedVideoMemory + dc.DedicatedSystemMemory + dc.SharedSystemMemory);
	ynTextDraw(x, y += 14, col, _T("Total.VRAM: %zu GB (%zu MB)"), totVramGB, totVramMB);
	ynTextDraw(x, y += 14, col, _T("Dedic.VRAM: %zu GB (%zu MB)"), toGB(dc.DedicatedVideoMemory), toMB(dc.DedicatedVideoMemory));
	ynTextDraw(x, y += 14, col, _T("Dedic.SYSM: %zu GB (%zu MB)"), toGB(dc.DedicatedSystemMemory), toMB(dc.DedicatedSystemMemory));
	ynTextDraw(x, y += 14, col, _T("Shared.SYSM: %zu GB (%zu MB)"), toGB(dc.SharedSystemMemory), toMB(dc.SharedSystemMemory));
	ynTextDraw(x, y += 14, col, _T("Adpater.Luid: %d.%u"), dc.AdapterLuid.HighPart, dc.AdapterLuid.LowPart);

	{
		auto stats = g_GraphicsMemory->GetStatistics();
		y += 14;
		col = COLOR(1, 0.7f, 0.3f, 1);
		ynTextDraw(x, y += 14, col, _T("[Graphics Memory] \n"
			"Committed = %.1f MB (%zu KB) \n"
			"Total.Mem = %.1f MB (%zu KB) \n"
			"Total.Page = %zu \n"
			"Peak.Committed = %.1f MB (%zu KB) \n"
			"Peak.Total.Mem = %.1f MB (%zu KB) \n"
			"Peak.Total.Page = %zu "),
			toMBf(stats.committedMemory), toKB(stats.committedMemory),
			toMBf(stats.totalMemory), toKB(stats.totalMemory),
			stats.totalPages,
			toMBf(stats.peakCommitedMemory), toKB(stats.peakCommitedMemory),
			toMBf(stats.peakTotalMemory), toKB(stats.peakTotalMemory),
			stats.peakTotalPages);
	}


	{
		ComPtr<IDXGIAdapter1>  adapter;
		ComPtr<IDXGIAdapter4>  adapter4;
		ComPtr<IDXGIFactory2>  factory;
		CreateDXGIFactory2(0, IID_PPV_ARGS(&factory));
		factory->EnumAdapters1(0, &adapter);
		adapter->QueryInterface(IID_PPV_ARGS(&adapter4));

		//IDXGIAdapter3::QueryVideoMemoryInfo method (dxgi1_4.h)
		DXGI_QUERY_VIDEO_MEMORY_INFO vmi;
		adapter4->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &vmi);
		y += 14 * 8;
		COLOR pink(1.0f, 0.5f, 1.0f, 1);

		UINT64 Budget = vmi.Budget / 1024 / 1024 / 1000;

		ynTextDraw(x, y += 14, pink * 1.5f, _T("[VRAM] \n"
			"Budget = %llu GB (%llu MB) \n"
			"Curr.Usage = %.3f GB (%llu MB) (%.2f%%) \n"
			"Avail.Reservation = %llu GB (%llu MB) \n"
			"Curr.Reserved = %llu GB (%llu MB)"),
			toGB(vmi.Budget), toMB(vmi.Budget),
			toGBf(vmi.CurrentUsage), toMB(vmi.CurrentUsage), toMBf(vmi.CurrentUsage) / toMBf(vmi.Budget) * 100.0f,
			toGB(vmi.AvailableForReservation), toMB(vmi.AvailableForReservation),
			toGB(vmi.CurrentReservation), toMB(vmi.CurrentReservation));
	}
}


//��ġ/GPU �� �ý��� ���� ���
void SystemInfo(int x, int y, COLOR col)
{
	COLOR col2 = col * 0.7f;

	ynTextDraw(x, y += 14, col, _T("[SYSTEM]"));
	ynTextDraw(x, y += 14, col2, _T("GPU : %s"), g_Adc.Description);
	ynTextDraw(x, y += 14, col2, _T("Feat : %s"), g_strFeatLv);
	ynTextDraw(x, y += 14, col2, _T("Res : %dx%d"), g_Mode.Width,g_Mode.Height);
	ynTextDraw(x, y += 14, col2, _T("Build : %s"), g_Platform);

	//GPU ���� ���
	AdapterInfo(700, y += 14, col);

	//�׷��� �ɼ� ���
	{
		x = g_Mode.Width - 70;
		y = 14;
		ynTextDraw(x, y += 14, col, _T("[Graphics]"));
		ynTextDraw(x, y += 14, col2, _T("AA = x%d"), g_dwAA);
		ynTextDraw(x, y += 14, col2, _T("AF = x%d"), g_dwAF);
		//ynTextDraw(x, y += 14, g_bMipMap ? col : col*0.7f, _T("MipMap = %s"), g_bMipMap ? _T("ON") : _T("OFF"));
	}
}

//���� ������ �����ε�
COLOR operator*(COLOR& lhs, float s)
{
    COLOR col;
	col.x = lhs.x * s;
	col.y = lhs.y * s;
	col.z = lhs.z * s;
	col.w = lhs.w * s;

	return col;
}

//===============================================================
// ���� ó�� �Լ�

//���� �޼��� ó��
int ynErrorW(TCHAR* file, UINT line, TCHAR* func, BOOL bMBox, HRESULT hr, TCHAR* msg, ...)
{
	TCHAR msgva[1024] = _T("");
	va_list vl;
	va_start(vl, msg);
	_vstprintf_s(msgva, msg, vl);
	va_end(vl);

	TCHAR herr[1024] = _T("");
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, hr, MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT), herr, 1024, NULL);

	TCHAR errmsg[2048] = _T("");
	_stprintf_s(errmsg, _T("%s \n�����ڵ�(0x%X) :%s \n File = %s (%d)\nFunc = %s\n\n"),msgva, hr, herr, file, line, func);

	//(����� ��) VS ���â�� ���
    OutputDebugString(_T("\n"));
	OutputDebugString(errmsg);

    //�α� ���Ϸ� ���
    //todo:...

	//�޼��� â ���
	if (bMBox)
	{
        MessageBox(NULL, errmsg, _T("Yena::Error"), MB_OK | MB_ICONERROR);
	}

    return YN_OK;
}

SpriteFont* g_pFont = nullptr;
SpriteBatch* g_pFontBatch = nullptr;
DescriptorHeap* g_pFontResDesc = nullptr;

int ynFontCreate(LPDEVICE pDev)
{
	TCHAR* filename = _T("../Yena/Font/����9k.sfont");
	try {
		RenderTargetState rtState(g_Mode.Format,DXGI_FORMAT_D32_FLOAT);
		SpriteBatchPipelineStateDescription pd(rtState);
		ResourceUploadBatch resUpload(pDev);
		resUpload.Begin();
		
		//��Ʈ ���ҽ� ����
		g_pFontResDesc = new DescriptorHeap(pDev, 1);
		g_pFontBatch = new SpriteBatch(pDev, resUpload, pd,&g_VP);
		//g_pFontBatch->SetViewport(g_VP);

		//Directx Toolkit : Sprite Font ��ü ����
		
		g_pFont = new SpriteFont(pDev, resUpload, filename, g_pFontResDesc->GetCpuHandle(0), g_pFontResDesc->GetGpuHandle(0));
		g_pFont->SetLineSpacing(14.0f);
		g_pFont->SetDefaultCharacter('_');

		auto uploadFinish = resUpload.End(g_pCommandQueue);
		uploadFinish.wait();
	}
	catch (std::exception& e)
	{
		TCHAR msg[1024] = _T("");
		mbstowcs(msg, e.what(), strlen(e.what()));
		ynError(0, _T("��Ʈ ���� ���� : %s \n File=%s"), msg,filename);
	}

	return YN_OK;
}

//��Ʈ ����
void ynFontRelease()
{
	SAFE_DELETE(g_pFontResDesc);
	SAFE_DELETE(g_pFontBatch);
	SAFE_DELETE(g_pFont);
}

//��Ʈ ��ġ �ҽ� �ڵ鷯 
void ynFontOnDeviceLost()
{
	/*g_pFont->Reset();
	g_pFontResDesc->Reset();
	g_pFontBatch->Reset();*/
}

void ynTextDraw(int x, int y, COLOR col, TCHAR* msg, ...)
{
	TCHAR buff[2048] = _T("");
	va_list vl;
	va_start(vl, msg);
	_vstprintf_s(buff, msg, vl);
	va_end(vl);

	ID3D12DescriptorHeap* dhs[] = { g_pFontResDesc->Heap() };
	g_CmdList->SetDescriptorHeaps(_countof(dhs), dhs);

	g_pFontBatch->Begin(g_CmdList);
	g_pFont->DrawString(g_pFontBatch, buff, Vector2((float)x,(float)y), Vector4(col));
	g_pFontBatch->End();
}
