#pragma once
#include "../common/WinApp.h"


class Camera;
class Image;
class Mesh;
class Model;
class WinMainApp : public WinApp
{

public:
	WinMainApp(HINSTANCE hInstance);
	~WinMainApp();

	bool Initialize(UINT Width, UINT Height);
	void Update();

	bool InitD3D();
	void UninitD3D();

	bool InitImGUI();
	void UninitImGUI();

	
	// WinApp을(를) 통해 상속됨
	void Render() override;

	ID3D11Device* m_pDevice = nullptr;		//3d11 디바이스
	ID3D11DeviceContext* m_pDeviceContext = nullptr;	//3d11 디바이스 컨텍스트
	IDXGISwapChain* m_pSwapChain = nullptr; //스왑체인
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr; //렌더타겟뷰
	ID3D11DepthStencilView* m_pDepthStencilView = nullptr; //깊이스텐실뷰==>깊이값처리

	ID3D11DepthStencilState* m_pDefaultDepthstencilState =nullptr;
	ID3D11DepthStencilState* m_pSkyDepthstencilState = nullptr;

	//알파블렌딩
	ID3D11BlendState* m_pAlphaBlendEnable = nullptr;

	// 렌더링 파이프라인에 적용하는  객체와 정보
	ID3D11VertexShader* m_pVertexShader = nullptr;	// 정점 셰이더.　 --> 메쉬 vs
	ID3D11PixelShader* m_pPixelShader = nullptr;	// 픽셀 셰이더.	--> 메쉬 ps
	ID3D11InputLayout* m_pInputLayout = nullptr;	// 입력 레이아웃. --> 메쉬
	ID3D11VertexShader* m_pSkyVertexShader = nullptr;	// 
	ID3D11PixelShader* m_pSkyPixelShader = nullptr;
	ID3D11InputLayout* m_pSkyLayout = nullptr;	// 입력 레이아웃. --> skybox
	ID3D11Buffer* m_pVertexBuffer = nullptr;		// 버텍스 버퍼.
	UINT m_VertextBufferStride = 0;					// 버텍스 하나의 크기.
	UINT m_VertextBufferOffset = 0;					// 버텍스 버퍼의 오프셋.
	ID3D11Buffer* m_pIndexBuffer = nullptr;			// 인덱스 버퍼.
	ID3D11Buffer* pTransformBuffer = nullptr;		// 
	ID3D11Buffer* pShadingBuffer = nullptr;			// 
	ID3D11SamplerState* m_pDefaultSamplerState = nullptr;	// 샘플러 상태.
	ID3D11SamplerState* m_pBRDFSamplerState = nullptr;	// 샘플러 상태.

	int m_nIndices = 0;								// 인덱스 개수.


	//Light
	Vector3 Light1Direction = { -1.0f,  0.0f, 0.0f }; //라이트 방향// 방향
	Vector3 Light1Radiance = { 1.0f, 1.0f, 1.0f }; // 방향

	Vector3 Light2Direction = { 1.0f,  0.0f, 0.0f }; // 방향
	Vector3 Light2Radiance = { 1.0f, 1.0f, 1.0f }; // 방향

	Vector3 Light3Direction = { 0.0f, -1.0f, 0.0f }; // 방향
	Vector3 Light3Radiance = { 1.0f, 1.0f, 1.0f }; // 방향
	//float3 EyePosition;	   // 카메라 위치


	Vector4 m_ClearColor = { 0.5f, 0.0f, 0.5f, 1.0f }; // 클리어 색상

	bool m_bShowImGUI = true; // ImGUI를 보여줄지 여부
	bool m_bShowImGUI_help = false; // ImGUI 도움말 보여줄지 여부

	//bool m_bUseNormal = true; // 노말맵 사용 여부
	//bool m_bUseSpecular = true; // 스페큘러 사용 여부

	float m_f;		//test 용 float
	int m_counter;  //test 용 int count

	Camera* m_pCamera;

	Vector3 m_SceanRotation;
	bool useIBL = false;

	bool m_bUseCustomMetal = false;
	float m_fCustomMetal = 0.0f;

	bool m_bUseCustomRough = false;
	float m_fCustomRough = 0.1f;

	Matrix g_world;
	Matrix g_View;
	Matrix g_Projection;

	Mesh* m_Mesh; //-->모델용
	Model* m_Model;

	Mesh* m_pSky;
	Model* m_pModelSky;

	float m_FovAngleY = DirectX::XM_PIDIV2;
	float m_AspectRatio = m_ClientWidth / (FLOAT)m_ClientHeight; // AspectRatio
	float m_NearZ = 0.1f; // NearZ
	float m_FarZ = 1000.0f; // FarZ


	Texture m_albedoTexture;
	Texture m_normalTexture;
	Texture m_metalnessTexture;
	Texture m_roughnessTexture;

	ID3D11ShaderResourceView* m_envTexture;
	ID3D11ShaderResourceView* m_irmapTexture;
	ID3D11ShaderResourceView* m_SpecularTexture;
	ID3D11ShaderResourceView* m_spBRDF_LUT;

	bool InitScene();		// 쉐이더,버텍스,인덱스
	void UninitScene();

	virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	void OnInputProcess(const Keyboard::State& KeyState, const Keyboard::KeyboardStateTracker& KeyTracker, const Mouse::State& MouseState, const Mouse::ButtonStateTracker& MouseTracker);


	Texture createTexture(UINT width, UINT height, DXGI_FORMAT format, UINT levels = 0) const;
	Texture createTexture(const Image* image, DXGI_FORMAT format, UINT levels = 0) const;
	Texture createTextureCube(UINT width, UINT height, DXGI_FORMAT format, UINT levels = 0) const;
	ID3D11ShaderResourceView* createShaderResourceViewDDS(const std::string& path) const;


	void createTextureUAV(Texture& texture, UINT mipSlice) const;

	template<typename T> static constexpr T numMipmapLevels(T width, T height)
	{
		T levels = 1;
		while ((width | height) >> levels) {
			++levels;
		}
		return levels;
	}
};

