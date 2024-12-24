#include "Windows.h"
#include "tchar.h"
#include "Device.h"
#include "Render.h"
#include "Shader.h"

TCHAR* g_WindowName = _T("DX12Project1");

//기하 데이터

//정점 구조체
struct Vertex
{
	float x, y, z;
	float r, g, b, a;
};

//정점 버퍼
ID3D12Resource* g_pVB = nullptr;
D3D12_VERTEX_BUFFER_VIEW* g_pVBView = nullptr;

//입력 레이아웃
D3D12_INPUT_LAYOUT_DESC* g_pVBLayout = nullptr; //DX12


//=============================================================================
//전역 데이터들

COLOR g_ClearColor = { 0.0f, 0.125f, 0.3f, 1 }; //배경색
//COLOR g_ClearColor(0.7f, 0.7f, 0.7f, 1);

//게임 데이터 및 레더링 자원을 불러온다
int DataLoading()
{
	//데이터 로딩/생성 코드
	//todo:...

	return TRUE;
}

//게임 데이터 및 레더링 자원을 해재한다
void DataRelease()
{
	//todo:...
}

//도움말 출력
void ShowInfo()
{
	PutFPS(0, 0);

	static bool bShow = true;

	if (IsKeyUp(VK_F1)) bShow ^= true;

	if (!bShow)
	{
		//ynTextDraw(1,20, COLOR(1, 1, 0, 1), _T("[Help] F1"));
		return;
	}

	//topic
	{
		int x = 300, y = 50;
		COLOR col(1, 1, 1, 1);
		COLOR col2(1, 1, 0, 1);
		ynTextDraw(x, y, col, _T("■ %s"), g_WindowName);

		y += 24;
		WCHAR* msg = _T(
			"1.기본프레임워크 구축.\n"
			"2.HW 렌더링 디바이스(D3D Device) 를 생성.\n"
			"3.Idle 시간 렌더링.\n"
			"4.스왑체인 Swap(Flipping) chain 의 이해 \n"
		);
		ynTextDraw(x, y, col2, msg);
	}

	//시스템 정보
	{
		int x = 1, y = 14;
		COLOR col(0, 1, 0, 1);
		SystemInfo(x, y, col);
	}

	int x = 300, y = 300;
	static int cnt = 0;
	COLOR col(1, 1, 0, 1);
	ynTextDraw(x, y, col, _T("Hello, Device!!    cnt=%08d"), ++cnt);

	y += 24;
	ynTextDraw(x, y, col, _T("* HW Rendering Device (%s) 버전 *"), g_strFeatLv);

}

//게임 장면 렌더링
void SceneRender()
{
	//===============================================================
	//엔진 / 시스템 갱신

	//렌더링 상태, 조명, 카메라 등 조절

	//장면 갱신

	//===============================================================
	//장면 그리기
	//렌더타겟 지우기
	ClearBackBuffer(g_ClearColor);

	//장면 렌더링

	//도움말 출력
	ShowInfo();

	//===============================================================
	//장면 그리기 종료
	Flip();
}
