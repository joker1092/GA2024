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

	
	// WinApp��(��) ���� ��ӵ�
	void Render() override;

	ID3D11Device* m_pDevice = nullptr;		//3d11 ����̽�
	ID3D11DeviceContext* m_pDeviceContext = nullptr;	//3d11 ����̽� ���ؽ�Ʈ
	IDXGISwapChain* m_pSwapChain = nullptr; //����ü��
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr; //����Ÿ�ٺ�
	ID3D11DepthStencilView* m_pDepthStencilView = nullptr; //���̽��ٽǺ�==>���̰�ó��

	ID3D11DepthStencilState* m_pDefaultDepthstencilState =nullptr;
	ID3D11DepthStencilState* m_pSkyDepthstencilState = nullptr;

	//���ĺ���
	ID3D11BlendState* m_pAlphaBlendEnable = nullptr;

	// ������ ���������ο� �����ϴ�  ��ü�� ����
	ID3D11VertexShader* m_pVertexShader = nullptr;	// ���� ���̴�.�� --> �޽� vs
	ID3D11PixelShader* m_pPixelShader = nullptr;	// �ȼ� ���̴�.	--> �޽� ps
	ID3D11InputLayout* m_pInputLayout = nullptr;	// �Է� ���̾ƿ�. --> �޽�
	ID3D11VertexShader* m_pSkyVertexShader = nullptr;	// 
	ID3D11PixelShader* m_pSkyPixelShader = nullptr;
	ID3D11InputLayout* m_pSkyLayout = nullptr;	// �Է� ���̾ƿ�. --> skybox
	ID3D11Buffer* m_pVertexBuffer = nullptr;		// ���ؽ� ����.
	UINT m_VertextBufferStride = 0;					// ���ؽ� �ϳ��� ũ��.
	UINT m_VertextBufferOffset = 0;					// ���ؽ� ������ ������.
	ID3D11Buffer* m_pIndexBuffer = nullptr;			// �ε��� ����.
	ID3D11Buffer* pTransformBuffer = nullptr;		// 
	ID3D11Buffer* pShadingBuffer = nullptr;			// 
	ID3D11SamplerState* m_pDefaultSamplerState = nullptr;	// ���÷� ����.
	ID3D11SamplerState* m_pBRDFSamplerState = nullptr;	// ���÷� ����.

	int m_nIndices = 0;								// �ε��� ����.


	//Light
	Vector3 Light1Direction = { -1.0f,  0.0f, 0.0f }; //����Ʈ ����// ����
	Vector3 Light1Radiance = { 1.0f, 1.0f, 1.0f }; // ����

	Vector3 Light2Direction = { 1.0f,  0.0f, 0.0f }; // ����
	Vector3 Light2Radiance = { 1.0f, 1.0f, 1.0f }; // ����

	Vector3 Light3Direction = { 0.0f, -1.0f, 0.0f }; // ����
	Vector3 Light3Radiance = { 1.0f, 1.0f, 1.0f }; // ����
	//float3 EyePosition;	   // ī�޶� ��ġ


	Vector4 m_ClearColor = { 0.5f, 0.0f, 0.5f, 1.0f }; // Ŭ���� ����

	bool m_bShowImGUI = true; // ImGUI�� �������� ����
	bool m_bShowImGUI_help = false; // ImGUI ���� �������� ����

	//bool m_bUseNormal = true; // �븻�� ��� ����
	//bool m_bUseSpecular = true; // ����ŧ�� ��� ����

	float m_f;		//test �� float
	int m_counter;  //test �� int count

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

	Mesh* m_Mesh; //-->�𵨿�
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

	bool InitScene();		// ���̴�,���ؽ�,�ε���
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

