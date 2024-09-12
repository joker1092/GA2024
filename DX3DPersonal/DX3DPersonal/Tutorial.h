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
	// WinApp��(��) ���� ��ӵ�
	void Render() override;

	ID3D11Device* m_pDevice = nullptr;		//3d11 ����̽�
	ID3D11DeviceContext* m_pDeviceContext = nullptr;	//3d11 ����̽� ���ؽ�Ʈ
	IDXGISwapChain* m_pSwapChain = nullptr; //����ü��
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr; //����Ÿ�ٺ�

	// ������ ���������ο� �����ϴ�  ��ü�� ����
	ID3D11VertexShader* m_pVertexShader = nullptr;	// ���� ���̴�.
	ID3D11PixelShader* m_pPixelShader = nullptr;	// �ȼ� ���̴�.	
	ID3D11InputLayout* m_pInputLayout = nullptr;	// �Է� ���̾ƿ�.
	ID3D11Buffer* m_pVertexBuffer = nullptr;		// ���ؽ� ����.
	UINT m_VertextBufferStride = 0;					// ���ؽ� �ϳ��� ũ��.
	UINT m_VertextBufferOffset = 0;					// ���ؽ� ������ ������.
	ID3D11Buffer* m_pIndexBuffer = nullptr;			// �ε��� ����.
	ID3D11Buffer* m_pConstantBuffer = nullptr;		// ��� ����.
	int m_nIndices = 0;								// �ε��� ����.
	float t = 0.0f; // �ð� �帧��

	DirectX::XMMATRIX                g_World; // ���� ���
	DirectX::XMMATRIX                g_View; // �� ���
	DirectX::XMMATRIX                g_Projection; // �������� ���

	Sphere* m_pSphere = nullptr;

	bool InitScene();		// ���̴�,���ؽ�,�ε���
	void UninitScene();
};

