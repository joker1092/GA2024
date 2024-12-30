#pragma warning(disable:4996)
#include "Windows.h"
#include "stdio.h"
#include "Device.h"
#include "Render.h"

#include "d3dcompiler.h"
#pragma comment(lib,"d3dcompiler.lib")
#include "Shader.h"

//=============================================================================
//전역 데이터 
LPSHADER g_pVS = nullptr;
LPSHADER g_pPS = nullptr;

extern CONSTS g_Consts;
extern LPCONSTBUFFER g_pCB;

extern COLANI g_ColAni;
extern LPCONSTBUFFER g_pCB2;

//=============================================================================
//셰이더 함수
int ShaderLoad()
{
	TCHAR* filename = _T("./Default.fx");

	ShaderLoad(filename, "VSMain", "vs_5_1", &g_pVS);
	ShaderLoad(filename, "PSMain", "ps_5_1", &g_pPS);

	return YN_OK;
}
