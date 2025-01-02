#pragma once
typedef ID3DBlob* LPSHADER;
typedef LPSHADER LPVERTEXSHADER;
typedef LPSHADER LPPIXELSHADER;
typedef LPSHADER LPGEOMETRYSHADER;
typedef ID3D12Resource* LPRESOURCE;
typedef LPRESOURCE LPCONSTBUFFER;

int ShaderLoad();
HRESULT ShaderLoad(TCHAR* filename, CHAR* entry, CHAR* sm, MY_OUT LPSHADER* ppfx);
//HRESULT ShaderLoad(TCHAR* filename, CHAR* entry, CHAR* sm, D3D12_SHADER_BYTECODE* pshader);
void ShaderRelease();
HRESULT ShaderCompile(WCHAR* filename, char* entry, char* sm, MY_OUT ID3DBlob** ppCode);
void ShaderCreate();
void ShaderUpdate();

//셰이더 관련 전역 변수
//extern ID3D11VertexShader* g_pVS; //dx11
//extern ID3D11PixelShader* g_pPS; //dx11
//extern D3D12_SHADER_BYTECODE g_VS; //dx12
//extern D3D12_SHADER_BYTECODE g_PS; //dx12
extern LPSHADER g_pVS;
extern LPSHADER g_pPS;



//===============================================================
//루트 시그니처
extern ID3D12RootSignature* g_pRootSign;

int RootSignatureCreate();
void RootSignatureRelease();

#define ToConst(v) *(UINT*)&(v)
#define ToConsts(v) (void*)&(v)


//===============================================================
//셰이더 상수 데이터

struct CONSTS	//transform
{
	float trans = 0;
	float scale = 1.0f;
	float rot = 0;
};

struct  COLANI
{
	COLOR color = { 1,1,1,1 };

	float per = 0;
	DWORD frm = 0;
};



