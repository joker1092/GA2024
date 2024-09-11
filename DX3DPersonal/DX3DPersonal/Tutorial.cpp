#include "framework.h"
#include "Tutorial.h"
#include "Vertex.h"


//��� ����
struct ConstantBuffer
{
	DirectX::XMMATRIX mWorld;
	DirectX::XMMATRIX mView;
	DirectX::XMMATRIX mProjection;
};



Tutorial::Tutorial(HINSTANCE hInstance): WinApp(hInstance)
{
}

Tutorial::~Tutorial()
{
	UninitScene();
	UninitD3D();
}

bool Tutorial::Initialize(UINT Width, UINT Height)
{
	WinApp::Initialize(Width, Height);
	if (!InitD3D())
		return false;
	if(!InitScene())
		return false;

	return true;
}

void Tutorial::Update()
{
	WinApp::Update();
	//�ð� �帧�� ����
	//static float t = 0.0f;
	//t += (float)DirectX::XM_PI * 0.0125f;
	//t+= 0.0125f;
	//g_World = DirectX::XMMatrixRotationY(t);
	t += (float)DirectX::XM_PI * 0.0125f;
	g_World = DirectX::XMMatrixRotationY(t);

}

void Tutorial::Render()
{
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);

	Color clearColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);


	

	ConstantBuffer cb;
	cb.mWorld = XMMatrixTranspose(g_World);
	cb.mView = XMMatrixTranspose(g_View);
	cb.mProjection = XMMatrixTranspose(g_Projection);
	m_pDeviceContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb, 0, 0);


	/// ������ �۾�
	
	m_pDeviceContext->VSSetShader(m_pVertexShader, nullptr, 0); //���� ���̴� ����
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pDeviceContext->PSSetShader(m_pPixelShader, nullptr, 0);//�ȼ� ���̴� ����

	m_pDeviceContext->DrawIndexed(m_nIndices, 0, 0); //�ε����� �׸���
	

	m_pSwapChain->Present(0, 0);
}


bool Tutorial::InitD3D()
{
	// �����
	HRESULT hr = S_OK;

	DXGI_SWAP_CHAIN_DESC swapChainDesc={};

	swapChainDesc.BufferCount = 2; // ���� ����
	swapChainDesc.SwapEffect= DXGI_SWAP_EFFECT_FLIP_DISCARD; // ����ȿ�� ==> flip
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // ���� ����
	swapChainDesc.OutputWindow = m_hWnd; // ��� ������
	swapChainDesc.Windowed = TRUE; // â���
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // ���� ����
	swapChainDesc.BufferDesc.Width = m_ClientWidth; // ���� �ʺ�
	swapChainDesc.BufferDesc.Height = m_ClientHeight; // ���� ����
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60; // �ֻ���
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1; // �ֻ���
	swapChainDesc.SampleDesc.Count = 1; // ���ø� ����
	swapChainDesc.SampleDesc.Quality = 0; // ���ø� ǰ��

	UINT createDeviceFlags = 0;

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	// ����̽� ����, ����ü�� ����, ����̽� ���ؽ�Ʈ ����
	HR_T(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, NULL, NULL,
		D3D11_SDK_VERSION, &swapChainDesc, &m_pSwapChain, &m_pDevice, NULL, &m_pDeviceContext));

	// ����Ÿ�ٺ� ����
	ID3D11Texture2D* pBackBufferTexture = nullptr;
	HR_T(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBufferTexture));
	HR_T(m_pDevice->CreateRenderTargetView(pBackBufferTexture, NULL, &m_pRenderTargetView));
	SAFE_RELEASE(pBackBufferTexture);

	// ����Ʈ ����
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(m_ClientWidth);
	viewport.Height = static_cast<float>(m_ClientHeight);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	m_pDeviceContext->RSSetViewports(1, &viewport);

	//init world matrix
	g_World = DirectX::XMMatrixIdentity();

	//init view matrix
	g_View = DirectX::XMMatrixLookAtLH(Vector4(0.0f, 1.0f, -5.0f, 0.0f), Vector4(0.0f, 1.0f, 0.0f, 0.0f), Vector4(0.0f, 1.0f, 0.0f, 0.0f));

	//init projection matrix
	g_Projection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2, m_ClientWidth / (FLOAT)m_ClientHeight, 0.01f, 100.0f);


	return true;
}

void Tutorial::UninitD3D()
{
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pDeviceContext);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pRenderTargetView);
}


bool Tutorial::InitScene()
{
	// �����
	HRESULT hr = S_OK;

	// ���� ����.
	//Vertex vertices[] =
	//{
	//	Vertex(Vector3(-1.0f,  0.5f, 0.5f), Vector4(1.0f, 0.0f, 0.0f, 1.0f)),   // 0
	//	Vertex(Vector3(0.5f,  0.5f, 0.5f), Vector4(0.0f, 1.0f, 0.0f, 1.0f)),	// 1
	//	Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector4(1.0f, 0.0f, 1.0f, 1.0f)),	// 2
	//	Vertex(Vector3(1.0f, -0.5f, 0.5f), Vector4(0.0f, 0.0f, 1.0f, 1.0f)),	// 3
	//}; // �簢��
	Vertex vertices[] =
	{
		Vertex(Vector3(-0.5f,  0.5f, 0.5f), Vector4(1.0f, 0.0f, 0.0f, 1.0f)),   // 0
		Vertex(Vector3(0.5f,  0.5f, 0.5f), Vector4(0.0f, 1.0f, 0.0f, 1.0f)),	// 1
		Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector4(0.0f, 0.0f, 1.0f, 1.0f)),	// 2
		Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector4(1.0f, 1.0f, 1.0f, 1.0f)),	// 3
		Vertex(Vector3(-0.5f,  0.5f,-0.5f), Vector4(0.0f, 1.0f, 1.0f, 1.0f)),   // 4
		Vertex(Vector3(0.5f,  0.5f, -0.5f), Vector4(1.0f, 1.0f, 0.0f, 1.0f)),	// 5
		Vertex(Vector3(-0.5f, -0.5f,-0.5f), Vector4(1.0f, 0.0f, 1.0f, 1.0f)),	// 6
		Vertex(Vector3(0.5f, -0.5f, -0.5f), Vector4(0.0f, 0.0f, 0.0f, 1.0f)),	// 7
	}; // ť��

	//   0-----1
	//   |    /|
	//   |  /  |              
	//   |/    |
	//	 2-----3

	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.ByteWidth = sizeof(Vertex)* ARRAYSIZE(vertices);
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	D3D11_SUBRESOURCE_DATA vertexBufferData = {};
	vertexBufferData.pSysMem = vertices;
	HR_T(m_pDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &m_pVertexBuffer));
	m_VertextBufferStride = sizeof(Vertex);
	m_VertextBufferOffset = 0;
	
	ID3DBlob* pVertexShaderBlob = nullptr;
	ID3DBlob* pPixelShaderBlob = nullptr;

	// ���� ���̴� ������
	HR_T(CompileShaderFromFile(L"BasicVertexShader.hlsl", "main", "vs_4_0", &pVertexShaderBlob));

	//input layout ����
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	HR_T(m_pDevice->CreateInputLayout(layout, ARRAYSIZE(layout), pVertexShaderBlob->GetBufferPointer(), pVertexShaderBlob->GetBufferSize(), &m_pInputLayout));

	// ���� ���̴� ����
	HR_T(m_pDevice->CreateVertexShader(pVertexShaderBlob->GetBufferPointer(), pVertexShaderBlob->GetBufferSize(), NULL, &m_pVertexShader));
	SAFE_RELEASE(pVertexShaderBlob);

	//�ﰢ���� ������� �׸��� ���� �ε��� ����
	/*DWORD indices[] = {
		0, 1, 2,
		2, 1, 3,
	};*/	// �簢��

	DWORD indices[] = {
		0, 1, 2,
		2, 1, 3,
		1, 5, 3,
		3, 5, 7,
		5, 4, 7,
		7, 4, 6,
		4, 0, 6,
		6, 0, 2,
		2, 3, 6,
		6, 3, 7,
		4, 5, 0,
		0, 5, 1
	}; // ť��
	//
	//				4-----5
	//   0-----1	|	  |	
	//   |    /|	|	  |
	//   |	/  |	|	  |
	//   | /   |    6-----7          
	//	 2-----3
	
	//�ε��� ���� ����
	m_nIndices = ARRAYSIZE(indices);
	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.ByteWidth = sizeof(DWORD)* ARRAYSIZE(indices);
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	D3D11_SUBRESOURCE_DATA indexBufferData = {};
	indexBufferData.pSysMem = indices;
	HR_T(m_pDevice->CreateBuffer(&indexBufferDesc, &indexBufferData, &m_pIndexBuffer));

	// ��� ���� ����
	D3D11_BUFFER_DESC constantBufferDesc = {};
	constantBufferDesc.ByteWidth = sizeof(ConstantBuffer);
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	HR_T(m_pDevice->CreateBuffer(&constantBufferDesc, nullptr, &m_pConstantBuffer));


	// �ȼ� ���̴� ������ �� ����
	HR_T(CompileShaderFromFile(L"BasicPixelShader.hlsl", "main", "ps_4_0", &pPixelShaderBlob));
	HR_T(m_pDevice->CreatePixelShader(pPixelShaderBlob->GetBufferPointer(), pPixelShaderBlob->GetBufferSize(), NULL, &m_pPixelShader));
	SAFE_RELEASE(pPixelShaderBlob);


	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);  //���� �׸��� ���
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &m_VertextBufferStride, &m_VertextBufferOffset); //���� ���� ����
	m_pDeviceContext->IASetInputLayout(m_pInputLayout); //�Է� ���̾ƿ� ����
	m_pDeviceContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0); //�ε��� ���� ����

	return true;
}

void Tutorial::UninitScene()
{
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pInputLayout);
	SAFE_RELEASE(m_pVertexBuffer);
}