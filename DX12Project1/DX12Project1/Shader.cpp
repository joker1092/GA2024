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

HRESULT ShaderLoad(TCHAR* filename, CHAR* entry, CHAR* sm, MY_OUT LPSHADER* ppShader) {
	
	ID3DBlob* pCode = nullptr;
	HRESULT hr = ShaderCompile(filename, entry, sm, &pCode);
	if (FAILED(hr)) {
		ynError(hr, _T("[실패] ShaderLoad :: 컴파일 실패"));
		return hr;
	}

	*ppShader = pCode;

	return hr;
}

//셰이더 제거
void ShaderRelease()
{
	SAFE_RELEASE(g_pVS);
	SAFE_RELEASE(g_pPS);

	SAFE_RELEASE(g_pCB);
	SAFE_RELEASE(g_pCB2);

	RootSignatureRelease();
}



//셰이더 소스 컴파일
HRESULT ShaderCompile(WCHAR* Filename, char* EntryPoint, char* ShaderModel, MY_OUT ID3DBlob** ppCode)
{
	HRESULT hr = S_OK;
	ID3DBlob* pError = nullptr;

	UINT Flags = D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
	//UINT Flags = D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR;
	//UINT Flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

#ifdef _DEBUG
	Flags |= D3DCOMPILE_DEBUG;
#endif // _DEBUG

	hr = D3DCompileFromFile(Filename, nullptr, nullptr, EntryPoint, ShaderModel, Flags, 0, ppCode, &pError);

	if (FAILED(hr)) {
		ynErrorW(TRUE, _T("셰이더 컴파일 실패"), hr, pError, Filename, EntryPoint, ShaderModel);
	}
	
	SAFE_RELEASE(pError);

	return hr;
}


//=============================================================================
//루트 시그니처 함수

//루트 시그니처
ID3D12RootSignature* g_pRootSign = nullptr;

int RootSignatureCreate() {
	HRESULT hr = S_OK;

	//루트 파라미터
	#define PARAM_MAX 2
	D3D12_ROOT_PARAMETER params[PARAM_MAX] = {};
	for (UINT i = 0; i < PARAM_MAX; i++)
	{
		params[i].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
		params[i].Descriptor.ShaderRegister = i;
		params[i].Descriptor.RegisterSpace = 0;
		params[i].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	}

	D3D12_ROOT_SIGNATURE_DESC rts = {};
	rts.NumParameters = PARAM_MAX;
	rts.pParameters = params;
	rts.NumStaticSamplers = 0;
	rts.pStaticSamplers = nullptr;
	//rts.Flags = D3D12_ROOT_SIGNATURE_FLAG_NONE;
	rts.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	ID3DBlob* pSign = nullptr;
	ID3DBlob* pError = nullptr;
	hr = D3D12SerializeRootSignature(&rts, D3D_ROOT_SIGNATURE_VERSION_1_0, &pSign, &pError);

	if (FAILED(hr)) {
		ynError(hr, _T("루트 시그니처 시리얼라이즈 실패"));
		return hr;
	}

	hr = g_pDevice->CreateRootSignature(0, pSign->GetBufferPointer(), pSign->GetBufferSize(), IID_PPV_ARGS(&g_pRootSign));

	if (FAILED(hr)) {
		ynError(hr, _T("루트 시그니처 생성 실패"));
		return hr;
	}
	
	SAFE_RELEASE(pSign);
	SAFE_RELEASE(pError);

	return YN_OK;

}


void RootSignatureRelease() {
	SAFE_RELEASE(g_pRootSign);
}


//=============================================================================
//기본 셰이더 구성
void ShaderCreate() {
	//루트 시그니처 생성
	RootSignatureCreate();
	//쉐이더 생성
	ShaderLoad();

	//상수 버퍼 생성
	CreateConstantBuffer(g_pDevice, &g_Consts, sizeof(CONSTS), &g_pCB);
	CreateConstantBuffer(g_pDevice, &g_ColAni, sizeof(COLANI), &g_pCB2);
}


//기본 셰이더 시스템 갱신
void ShaderUpdate() {
	
	//셰이더 설정
	//todo:..

	//상수 버퍼 갱신
	//todo:..
	/*UpdateBuffer(g_pCB, &g_Consts, sizeof(CONSTS));
	UpdateBuffer(g_pCB2, &g_ColAni, sizeof(COLANI));*/

	//셰이더 상수 버퍼 설정
	//todo:..
}