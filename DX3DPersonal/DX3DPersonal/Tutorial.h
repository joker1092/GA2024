#pragma once
#include "../common/WinApp.h"

class Sphere;
class Tutorial : public WinApp
{


public:
	Tutorial(HINSTANCE hInstance);
	~Tutorial();

	bool Initialize(UINT Width, UINT Height);
	void Update(); 
	
	bool InitD3D();
	void UninitD3D();
	// WinApp을(를) 통해 상속됨
	void Render() override;

	ID3D11Device* m_pDevice = nullptr;		//3d11 디바이스
	ID3D11DeviceContext* m_pDeviceContext = nullptr;	//3d11 디바이스 컨텍스트
	IDXGISwapChain* m_pSwapChain = nullptr; //스왑체인
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr; //렌더타겟뷰

	// 렌더링 파이프라인에 적용하는  객체와 정보
	ID3D11VertexShader* m_pVertexShader = nullptr;	// 정점 셰이더.
	ID3D11PixelShader* m_pPixelShader = nullptr;	// 픽셀 셰이더.	
	ID3D11InputLayout* m_pInputLayout = nullptr;	// 입력 레이아웃.
	ID3D11Buffer* m_pVertexBuffer = nullptr;		// 버텍스 버퍼.
	UINT m_VertextBufferStride = 0;					// 버텍스 하나의 크기.
	UINT m_VertextBufferOffset = 0;					// 버텍스 버퍼의 오프셋.
	ID3D11Buffer* m_pIndexBuffer = nullptr;			// 인덱스 버퍼.
	ID3D11Buffer* m_pConstantBuffer = nullptr;		// 상수 버퍼.
	int m_nIndices = 0;								// 인덱스 개수.
	float t = 0.0f; // 시간 흐름값

	DirectX::XMMATRIX                g_World; // 월드 행렬
	DirectX::XMMATRIX                g_View; // 뷰 행렬
	DirectX::XMMATRIX                g_Projection; // 프로젝션 행렬

	Sphere* m_pSphere = nullptr;

	bool InitScene();		// 쉐이더,버텍스,인덱스
	void UninitScene();
};

