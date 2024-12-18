#pragma warning(disable:4996)
#include "Device.h"

// DX 및 장치 관련 전역 데이터들 
// 
//D3D 장치 인터페이스
IDXGIAdapter4* g_pAdapter = NULL;
ID3D12Device* g_pDevice = NULL;

//D3D 스왑체인 인터페이스
IDXGISwapChain4* g_pSwapChain = NULL;

//다중버퍼링 운용 인터페이스들
const UINT g_RTCnt = 2;
UINT g_RTDescSize = 0;
UINT g_RTIndex = 0;
ID3D12DescriptorHeap* g_pRTDescHeap = NULL;
//D3D12_CPU_DESCRIPTOR_HANDLE g_RTDescs;
ID3D12Resource* g_pRT[g_RTCnt] = { NULL, };
#define g_BB g_pRT[g_RTIndex]
#define g_BackBuffer g_pBB
//#define g_RTViews g_pRTDesc

//명령어큐 인터페이스들
ID3D12CommandQueue*         g_pCommandQueue = NULL;
ID3D12CommandAllocator*     g_pCommandAllocator = NULL;
ID3D12GraphicsCommandList*  g_pCommandList = NULL;

//렌더링 동기화 인터페이스
ID3D12Fence* g_pFence = NULL;
UINT64 g_FenceValue = 0;
//UINT64 g_FenceValues[g_RTCnt] = { 0, };
//UINT g_FrameIndex = 0;
HANDLE g_FenceEvent = NULL;

//뷰포트
D3D12_VIEWPORT g_VP;

//그래픽 메모리 관리 자동화 헬퍼 : DXTK/폰트 운용시 내부적으로 사용됨.
std::unique_ptr<GraphicsMemory> g_GraphicsMemory;

//장치 설정 기본 정보
DISPLAYMODE g_Mode = { 960,600,0,1,DXGI_FORMAT_R8G8B8A8_UNORM };

//AA & AF Option
DWORD g_dwAA = 1;
DWORD g_dwAF = 1;
BOOL g_bMipMap = TRUE;

//D3D 기능 레벨
D3D_FEATURE_LEVEL g_FeatLv = D3D_FEATURE_LEVEL_12_0; //DX12
//D3D_FEATURE_LEVEL g_FeatLv = D3D_FEATURE_LEVEL_12_1; //DX12.1
//D3D_FEATURE_LEVEL g_FeatLv = D3D_FEATURE_LEVEL_11_0; //DX11
//D3D_FEATURE_LEVEL g_FeatLv = D3D_FEATURE_LEVEL_9_3; //DX9.0c
TCHAR* g_strFeatLv = _T("N/A");

//장치 정보
DXGI_ADAPTER_DESC1 g_Adc;

//전체화면 여부
BOOL g_bWindowMode = TRUE;

//수직동기화 여부
BOOL g_bVSync = FALSE;

//===============================================================
//D3D 장치 운용함수

//DX 및 관련 객체 초기화
int DXSetup(HWND hwnd)
{
	//1단계 : 렌더링 장치 관련 필수 설정
	CreateDeviceSwapChain(hwnd);
	CreateRenderTarget();
	SetViewPort();
    GetDeviceInfo();

	//2단계 : 기타 렌더링 관련 추가 설정
	g_GraphicsMemory = std::make_unique<GraphicsMemory>(g_pDevice);
	ynFontCreate(g_pDevice);

	//3단계 : 추가 장치 설정
	//todo:...
    return YN_OK;
}

//장치 및 객체 제거
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

//D3D 장치 생성 및 스왑체인 생성
HRESULT CreateDeviceSwapChain(HWND Hwnd)
{
	HRESULT hr = S_OK;

    //DXGI 인터페이스 생성
	IDXGIFactory4* pFactory = nullptr;
	CreateDXGIFactory2(0, IID_PPV_ARGS(&pFactory));

    //DX 렌더링 장치 구성
    hr = D3D12CreateDevice(0, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&g_pDevice));
    //hr = D3D12CreateDevice(0, D3D_FEATURE_LEVEL_12_0, __uuidof(ID3D12Device),(void**)&g_pDevice);
	//hr = D3D12CreateDevice(g_pAdapter, D3D_FEATURE_LEVEL_12_0, __uuidof(ID3D12Device), (void**)&g_pDevice);
    if (FAILED(hr)) 
    {
        ynError(hr, _T("디바이스 생성 실패."));
    }

	//커맨드 객체 생성
	CommandsCreate();

    //동기화 객체 생성
	GPUSyncObjsCreate();

    //다중 버퍼링 구성
    //스왑체인 정보 구성
    DXGI_SWAP_CHAIN_DESC1 sd = {};
    sd.Width = g_Mode.Width;                            //해상도
    sd.Height = g_Mode.Height;
    sd.Format = g_Mode.Format;                          //백버퍼 규격
    sd.SampleDesc.Count = g_dwAA;                       //AA설정
    sd.SampleDesc.Quality = 0;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   //용도설정
    sd.BufferCount = g_RTCnt;                           //백버퍼 개수
    sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;      //다중 버퍼링 (옵션)
    //sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;      //다중 버퍼링 (옵션)

    //스왑체인 생성
    IDXGISwapChain1* pSwapchain = nullptr;
    hr = pFactory->CreateSwapChainForHwnd(g_pCommandQueue, g_hWnd, &sd, nullptr, nullptr, &pSwapchain);
    if (FAILED(hr))
    {
        ynError(hr, _T("디바이스 / 스왑체인 / CreateSwapChainForHwnd 생성 실패""\nRes={%dx%d} RT=%d AA=%d \n"),
            g_Mode.Width,g_Mode.Height,g_RTCnt,g_dwAA);
    }

    //스왑체인 : 신규 인터페이스 획득.
    hr = pSwapchain->QueryInterface(IID_PPV_ARGS(&g_pSwapChain));
    if (FAILED(hr))
    {
        ynError(hr, _T("디바이스 / 스왑체인 생성 실패"));
    }

    //현재 프레임 "백버퍼"얻기
    g_RTIndex = g_pSwapChain->GetCurrentBackBufferIndex();

    //장치 추가
    //전체화면 방지
    pFactory->MakeWindowAssociation(g_hWnd, DXGI_MWA_NO_ALT_ENTER);

    //임시 인터페이스 제거
    SAFE_RELEASE(pFactory);
    SAFE_RELEASE(pSwapchain);

    return hr;
}

//장치-스왑체인의 렌더타겟(백버퍼) 획득
HRESULT CreateRenderTarget()
{
    HRESULT hr = S_OK;

    //백버퍼 인덱스 얻기
    //UINT bbidx = g_pSwapChain->GetCurrentBackBufferIndex();

    //디스크립터-힙 구성
    D3D12_DESCRIPTOR_HEAP_DESC hd = {};
    hd.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    hd.NumDescriptors = g_RTCnt;
    //hd.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    //hd.NodeMask = 0;
    hr = g_pDevice->CreateDescriptorHeap(&hd, IID_PPV_ARGS(&g_pRTDescHeap));
    if (FAILED(hr))
    {
        ynError(hr, _T("백버퍼-렌더타겟 : 디스크립터-힙 생성 실패"));
        return hr;
    }

    //렌더타겟-뷰 생성
    g_RTDescSize = g_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    D3D12_CPU_DESCRIPTOR_HANDLE dh = g_pRTDescHeap->GetCPUDescriptorHandleForHeapStart();
    for (UINT i = 0; i < g_RTCnt; i++) {
        hr = g_pSwapChain->GetBuffer(i, IID_PPV_ARGS(&g_pRT[i]));
        g_pDevice->CreateRenderTargetView(g_pRT[i], nullptr, dh);
        dh.ptr += g_RTDescSize;
    }

    if (FAILED(hr))
    {
        ynError(hr, _T("백버퍼-렌더타겟뷰 생성 실패"));
    }

    return hr;
}

//뷰포트 설정
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
//커맨드 객체 생성
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
		ynError(hr, _T("커맨드 객체생성 실패"));
    }

    return YN_OK;
}

//명령어 객체 리셋
int CommandsReset()
{
	g_CmdAlloc->Reset();
	g_CmdList->Reset(g_CmdAlloc, nullptr);

	return YN_OK;
}

//명령어를 실행
int CommandsExecute()
{
	ID3D12CommandList* cmdLists[] = { g_CmdList, };
	g_CmdList->Close();
	g_CmdQueue->ExecuteCommandLists(_countof(cmdLists), cmdLists);

	return YN_OK;
}

//명령어 객체 제거
void CommandsRelease()
{
	SAFE_RELEASE(g_pCommandQueue);
	SAFE_RELEASE(g_pCommandAllocator);
	SAFE_RELEASE(g_pCommandList);
}

//===============================================================
//GPU 동기화 / 병렬화 함수

//동기화 객체 생성
int GPUSyncObjsCreate()
{
	HRESULT hr = S_OK;

	//GPU측 동기화 객체 생성
	hr = g_pDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&g_pFence));
	g_FenceValue = 1;

	//CPU측 동기화 객체 생성
	g_FenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (FAILED(hr) || g_FenceEvent == NULL)
    {
		ynError(hr, _T("동기화 객체 / 이벤트 생성 실패"));
    }

	return YN_OK;
}

//동기화 객체 제거
void GPUSyncObjsRelease()
{
	SAFE_RELEASE(g_pFence);
	CloseHandle(g_FenceEvent);
}

//GPU 작업을 대기 한다 : 동기화
int GPUSync()
{
	const UINT64 fence = g_FenceValue;
	g_CmdQueue->Signal(g_pFence, fence);                //Fence 값 갱신
    g_FenceValue++;

	if (g_pFence->GetCompletedValue() < fence)          //GPU 의 현재 Fence 값 확인
	{
		g_pFence->SetEventOnCompletion(fence, g_FenceEvent);        //이벤트 설정
		WaitForSingleObject(g_FenceEvent, INFINITE);				 // 대기   
	}
	
	return YN_OK;
}



//장치-스왑체인 / 렌더타겟 / 깊이-스텐실 버퍼 클리어
int ClearBackBuffer(COLOR col)
{
	D3D12_RECT rc = { 0,0,(LONG)g_Mode.Width,(LONG)g_Mode.Height };

    //커맨드 리셋
	g_CmdAlloc->Reset();
	g_CmdList->Reset(g_CmdAlloc, nullptr);

    //장치 상태 재설정
    g_CmdList->RSSetViewports(1, &g_VP);
	g_CmdList->RSSetScissorRects(1, &rc);

    //렌더타겟 상태 전환
	D3D12_RESOURCE_BARRIER br = {};  //<리소스 베리어> 각 리소스의 상태관리 인터페이스
	br.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	br.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	br.Transition.pResource = g_BB;
	br.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	br.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	br.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	g_CmdList->ResourceBarrier(1, &br);
	
    //현재 렌더타겟 디스크립터 획득 
    D3D12_CPU_DESCRIPTOR_HANDLE rtv;
	rtv = g_pRTDescHeap->GetCPUDescriptorHandleForHeapStart();
	rtv.ptr += (SIZE_T)g_RTIndex * (SIZE_T)g_RTDescSize;
	
    //렌더타겟 "백버퍼" 재설정
	g_CmdList->OMSetRenderTargets(1, &rtv, FALSE, nullptr);

    //장명 : 프레임 버퍼 지우기
	g_CmdList->ClearRenderTargetView(rtv, (float*)&col, 0, nullptr);

	return YN_OK;
}



//장치 - 스왑체인 전환 : 장면 그리기 완료시 꼭 호출
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

    //모든 커맨드 리스트 실행
	g_CmdList->Close();
	g_CmdQueue->ExecuteCommandLists(_countof(cmdLists), cmdLists);
	
    //화면 출력 : Flip
	g_pSwapChain->Present(0, 0);
    //g_pSwapChain->Present(g_bVSync ? 1 : 0, 0);

	//GPU 동기화
	GPUSync();
	
    //새 프레임 준비
	g_RTIndex = g_pSwapChain->GetCurrentBackBufferIndex();

	return YN_OK;
}

//엔진 동기화용 경과시간 획득
float GetEngindTime()
{
	static ULONGLONG oldTime = GetTickCount64();
	ULONGLONG nowTime = GetTickCount64();
	float dTime = (nowTime - oldTime) / 0.001f;
	oldTime = nowTime;

	return dTime;
}

//타이머의 초당 프레임률(fps)를 출력
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
// 장치/GPU 정보 획득 함수들

//장치/GPU 정보 획득
void GetDeviceInfo()
{
    //장치 기능 레벨 확인
	GetFeatureLevel();

    //GPU 정보 얻기
	GetAdapterInfo(&g_Adc);

    //모니터 정보 얻기
    //todo:...
}


//DX기능 레벨(Feature Level) 출력 문자열
static TCHAR* strFeature[4][4] =
{
	{_T("DX9"),_T("DX9.1"),_T("DX9.2"),_T("DX9.3")},
	{_T("DX10"),_T("DX10.1"),_T("N/A"),_T("N/A")},
	{_T("DX11"),_T("DX11.1"),_T("DX11.2"),_T("DX11.3")},
	{_T("DX12"),_T("DX12.1"),_T("DX12.2"),_T("N/A")}
};

//DX 기능 레벨 구하기
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

//장치/GPU 정보 획득
HRESULT GetAdapterInfo(DXGI_ADAPTER_DESC1* pAd)
{
	IDXGIAdapter1* pAdapter;
	IDXGIFactory1* pFactory = NULL;
	//DXGI_ADAPTER_DESC ad;

	//DXGIFactory 개채 생성
	if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&pFactory))))
	{
		return E_FAIL;
	}

	pFactory->EnumAdapters1(0, &pAdapter);  //어뎁터 획득
	pAdapter->GetDesc1(pAd);                //어뎁터 정보 획득
	//*pAd = ad; 							//외부로 복사

	SAFE_RELEASE(pAdapter);
	SAFE_RELEASE(pFactory);

	return S_OK;
}

//장치/GPU 정보 출력
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


//장치/GPU 및 시스템 정보 출력
void SystemInfo(int x, int y, COLOR col)
{
	COLOR col2 = col * 0.7f;

	ynTextDraw(x, y += 14, col, _T("[SYSTEM]"));
	ynTextDraw(x, y += 14, col2, _T("GPU : %s"), g_Adc.Description);
	ynTextDraw(x, y += 14, col2, _T("Feat : %s"), g_strFeatLv);
	ynTextDraw(x, y += 14, col2, _T("Res : %dx%d"), g_Mode.Width,g_Mode.Height);
	ynTextDraw(x, y += 14, col2, _T("Build : %s"), g_Platform);

	//GPU 정보 출력
	AdapterInfo(700, y += 14, col);

	//그래픽 옵션 출력
	{
		x = g_Mode.Width - 70;
		y = 14;
		ynTextDraw(x, y += 14, col, _T("[Graphics]"));
		ynTextDraw(x, y += 14, col2, _T("AA = x%d"), g_dwAA);
		ynTextDraw(x, y += 14, col2, _T("AF = x%d"), g_dwAF);
		//ynTextDraw(x, y += 14, g_bMipMap ? col : col*0.7f, _T("MipMap = %s"), g_bMipMap ? _T("ON") : _T("OFF"));
	}
}

//색상 연산자 오버로딩
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
// 에러 처리 함수

//에러 메세지 처리
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
	_stprintf_s(errmsg, _T("%s \n에러코드(0x%X) :%s \n File = %s (%d)\nFunc = %s\n\n"),msgva, hr, herr, file, line, func);

	//(디버깅 중) VS 출력창에 출력
    OutputDebugString(_T("\n"));
	OutputDebugString(errmsg);

    //로그 파일로 출력
    //todo:...

	//메세지 창 출력
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
	TCHAR* filename = _T("../Yena/Font/굴림9k.sfont");
	try {
		RenderTargetState rtState(g_Mode.Format,DXGI_FORMAT_D32_FLOAT);
		SpriteBatchPipelineStateDescription pd(rtState);
		ResourceUploadBatch resUpload(pDev);
		resUpload.Begin();
		
		//폰트 리소스 생성
		g_pFontResDesc = new DescriptorHeap(pDev, 1);
		g_pFontBatch = new SpriteBatch(pDev, resUpload, pd,&g_VP);
		//g_pFontBatch->SetViewport(g_VP);

		//Directx Toolkit : Sprite Font 객체 생성
		
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
		ynError(0, _T("폰트 생성 실패 : %s \n File=%s"), msg,filename);
	}

	return YN_OK;
}

//폰트 제거
void ynFontRelease()
{
	SAFE_DELETE(g_pFontResDesc);
	SAFE_DELETE(g_pFontBatch);
	SAFE_DELETE(g_pFont);
}

//폰트 장치 소실 핸들러 
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
