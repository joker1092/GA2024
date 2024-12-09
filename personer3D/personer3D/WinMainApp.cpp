#include "framework.h"
#include "Camera.h"
#include "WinMainApp.h"
#include "Structs.h"



WinMainApp::WinMainApp(HINSTANCE hInstance) : WinApp(hInstance)
{
	m_nCmdShow = 0;
}

WinMainApp::~WinMainApp()
{
	UninitScene();
	UninitImGUI();
	UninitD3D();
}

bool WinMainApp::Initialize(UINT Width, UINT Height)
{
	WinApp::Initialize(Width, Height);
	if (!InitD3D())
		return false;
	if (!InitImGUI())
		return false;
	if (!InitScene())
		return false;



	return true;
}

void WinMainApp::Update()
{
	WinApp::Update();
	m_pCamera->Update(m_TimeSystem.DeltaTime());
	m_pCamera->GetViewMatrix(g_View);

	//�������� ���
	g_Projection = DirectX::XMMatrixPerspectiveFovLH(m_FovAngleY, m_AspectRatio, m_NearZ, m_FarZ);

}

void WinMainApp::Render()
{
	//const glm::mat4 projectionMatrix = glm::perspectiveFov(view.fov, float(m_framebuffer.width), float(m_framebuffer.height), 1.0f, 1000.0f);
	//const glm::mat4 viewRotationMatrix = glm::eulerAngleXY(glm::radians(view.pitch), glm::radians(view.yaw));
	//const glm::mat4 sceneRotationMatrix = glm::eulerAngleXY(glm::radians(scene.pitch), glm::radians(scene.yaw));
	//const glm::mat4 viewMatrix = glm::translate(glm::mat4{ 1.0f }, { 0.0f, 0.0f, -view.distance }) * viewRotationMatrix;
	//const glm::vec3 eyePosition = glm::inverse(viewMatrix)[3];


	//// Update transform constant buffer (for vertex shaders).
	//{
	//	TransformCB transformConstants;
	//	transformConstants.viewProjectionMatrix = projectionMatrix * viewMatrix;
	//	transformConstants.skyProjectionMatrix = projectionMatrix * viewRotationMatrix;
	//	transformConstants.sceneRotationMatrix = sceneRotationMatrix;
	//	m_context->UpdateSubresource(m_transformCB.Get(), 0, nullptr, &transformConstants, 0, 0);
	//}

	//// Update shading constant buffer (for pixel shader).
	//{
	//	ShadingCB shadingConstants;
	//	shadingConstants.eyePosition = glm::vec4{ eyePosition, 0.0f };
	//	shadingConstants.useIBL.r = scene.useIBL ? 1.0f : 0;
	//	for (int i = 0; i < SceneSettings::NumLights; ++i) {
	//		const SceneSettings::Light& light = scene.lights[i];
	//		shadingConstants.lights[i].direction = glm::vec4{ light.direction, 0.0f };
	//		if (light.enabled) {
	//			shadingConstants.lights[i].radiance = glm::vec4{ light.radiance, 0.0f };
	//		}
	//		else {
	//			shadingConstants.lights[i].radiance = glm::vec4{};
	//		}
	//	}
	//	m_context->UpdateSubresource(m_shadingCB.Get(), 0, nullptr, &shadingConstants, 0, 0);
	//}


	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	//clear render target view
	float clearColor[4] = { m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w };
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	//���ĺ���
	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_pDeviceContext->OMSetBlendState(m_pAlphaBlendEnable, blendFactor, 0xFFFFFFFF);
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);  //���� �׸��� ���


	/*DirectX::XMMATRIX viewProjectionMatrix;
	DirectX::XMMATRIX skyProjectionMatrix;
	DirectX::XMMATRIX sceneRotationMatrix;*/
	Matrix viewRotationMatrix = Matrix::CreateFromYawPitchRoll(m_pCamera->m_Rotation);
	Matrix sceneRotationMatrix = Matrix::CreateFromYawPitchRoll(m_SceanRotation);
	TransformCB TB; 
	TB.viewProjectionMatrix = g_Projection * g_View;
	TB.skyProjectionMatrix = g_Projection * viewRotationMatrix;
	TB.sceneRotationMatrix = sceneRotationMatrix;
	/*lb.LightDirection = m_LightDiretion;
	lb.LightAmbient = LightAmbient;
	lb.LightDiffuse = LightDiffuse;
	lb.LightSpecular = LightSpecular;*/

	/*struct
	{
		Vector3 direction;
		Vector3 radiance;
	} lights[3];
	Vector3 eyePosition;
	Vector4 useIBL;*/
	ShadingCB SB;
	SB.lights[0].direction = Vector4{Light1Direction.x,Light1Direction.y,Light1Direction.z,0.0f};
	SB.lights[0].radiance = Vector4{ Light1Radiance.x,Light1Radiance.y,Light1Radiance.z,0.0f };

	SB.lights[1].direction = Vector4{ Light2Direction.x,Light2Direction.y,Light2Direction.z,0.0f };
	SB.lights[1].radiance = Vector4{ Light2Radiance.x,Light2Radiance.y,Light2Radiance.z,0.0f };

	SB.lights[2].direction = Vector4{ Light3Direction.x,Light3Direction.y,Light3Direction.z,0.0f };
	SB.lights[2].radiance = Vector4{ Light3Radiance.x,Light3Radiance.y,Light3Radiance.z,0.0f };

	SB.eyePosition = Vector4{ m_pCamera->m_Position.x,m_pCamera->m_Position.y,m_pCamera->m_Position.z,0.0f }; 

	SB.useIBL.x = useIBL ? 1.0f : 0;

	//cab.vCameraPos = XMVECTOR{ m_pCamera->m_Position.x, m_pCamera->m_Position.y, m_pCamera->m_Position.z, 1.0f };


	m_pDeviceContext->UpdateSubresource(pTransformBuffer, 0, nullptr, &TB, 0, 0);
	m_pDeviceContext->UpdateSubresource(pShadingBuffer, 0, nullptr, &SB, 0, 0);

	m_pDeviceContext->VSSetShader(m_pVertexShader, nullptr, 0); //���� ���̴� ����
	m_pDeviceContext->PSSetShader(m_pPixelShader, nullptr, 0);//�ȼ� ���̴� ����

	
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &pTransformBuffer);
	m_pDeviceContext->PSSetConstantBuffers(1, 1, &pTransformBuffer); //��� ���� ����
	m_pDeviceContext->PSSetConstantBuffers(2, 1, &pShadingBuffer); //��� ���� ����


	//m_pModelLoader->Draw(m_pDeviceContext);

	//m_pModelLoader2->Draw(m_pDeviceContext);

	//m_pModelLoader3->Draw(m_pDeviceContext);

	// ImGUI ������
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// ImGUI ������
	if (m_bShowImGUI)
	{
		ImGui::Begin("properties"); // Create a window 

		ImGui::Text("Camera");
		ImGui::SliderFloat("MoveSpeed", &m_pCamera->m_Speed, 10.0f, 1000.0f);
		ImGui::Text("");
		

		ImGui::Text("Light");

		ImGui::SliderFloat3("LightDirection", &m_LightDiretion.x, -1.0f, 1.0f);
		/*ImGui::ColorEdit3("LightAmbient", &LightAmbient.x);
		ImGui::ColorEdit3("LightDiffuse", &LightDiffuse.x);
		ImGui::ColorEdit3("LightSopecular", &LightSpecular.x);*/


		ImGui::Text("Clear Color");
		ImGui::ColorEdit4("ClearColor", &m_ClearColor.x);

		ImGui::End();
	}


	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	m_pSwapChain->Present(0, 0);
}


bool WinMainApp::InitD3D()
{
	// �����
	HRESULT hr = S_OK;

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

	swapChainDesc.BufferCount = 2; // ���� ����
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // ����ȿ�� ==> flip
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
	


	/*D3D11_TEXTURE2D_DESC textuerDesc = {};
	textuerDesc.ArraySize = 1;
	textuerDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textuerDesc.CPUAccessFlags = 0;
	textuerDesc.Format = DXGI_FORMAT_R32_FLOAT;
	textuerDesc.Height = m_ClientHeight;
	textuerDesc.Width = m_ClientWidth;
	textuerDesc.MipLevels = 1;
	textuerDesc.MiscFlags = 0;
	textuerDesc.SampleDesc.Count = 1;
	textuerDesc.SampleDesc.Quality = 0;
	textuerDesc.Usage = D3D11_USAGE_DEFAULT;*/


	// ����Ʈ ����
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(m_ClientWidth);
	viewport.Height = static_cast<float>(m_ClientHeight);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	m_pDeviceContext->RSSetViewports(1, &viewport);

	//depth Stencil Buffer ����
	D3D11_TEXTURE2D_DESC depthStencilDesc = {};
	depthStencilDesc.Width = m_ClientWidth;
	depthStencilDesc.Height = m_ClientHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	ID3D11Texture2D* pDepthStencilBuffer = nullptr;
	HR_T(m_pDevice->CreateTexture2D(&depthStencilDesc, nullptr, &pDepthStencilBuffer));

	//depth Stencil �� ����
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
	depthStencilViewDesc.Format = depthStencilDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	HR_T(m_pDevice->CreateDepthStencilView(pDepthStencilBuffer, &depthStencilViewDesc, &m_pDepthStencilView));
	SAFE_RELEASE(pDepthStencilBuffer);

	//BlendState ����
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;

	D3D11_RENDER_TARGET_BLEND_DESC rtbd = {};
	rtbd.BlendEnable = true;
	//FinalRGB = (SourceRGB * SourceBlend) + (DestRGB * DestBlend);
	rtbd.BlendOp = D3D11_BLEND_OP_ADD;
	rtbd.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	rtbd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	//FinalAlpha = (SourceAlpha * SourceBlendAlpha) + (DestAlpha * DestBlendAlpha);
	rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;
	rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
	rtbd.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	blendDesc.RenderTarget[0] = rtbd;
	HR_T(m_pDevice->CreateBlendState(&blendDesc, &m_pAlphaBlendEnable));


	return true;
}

void WinMainApp::UninitD3D()
{
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pDeviceContext);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pRenderTargetView);
	SAFE_RELEASE(m_pDepthStencilView);
}

// ImGUI �ʱ�ȭ
bool WinMainApp::InitImGUI()
{
	IMGUI_CHECKVERSION();

	ImGui::CreateContext();

	// StyleColor
	ImGui::StyleColorsDark();

	//
	ImGui_ImplWin32_Init(m_hWnd);
	ImGui_ImplDX11_Init(m_pDevice, m_pDeviceContext);

	return true;
}

void WinMainApp::UninitImGUI()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}


bool WinMainApp::InitScene()
{
	// �����
	HRESULT hr = S_OK;

	m_pCamera = new Camera();


	ID3DBlob* pVertexShaderBlob = nullptr;
	ID3DBlob* pPixelShaderBlob = nullptr;
	ID3DBlob* pErrorBlob = nullptr;


	//D3D_SHADER_MACRO defines[] = {
	//	{"VERTEX_SKINNING", ""},
	//	{nullptr,nullptr}
	//};

	//UINT flags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

	//hr = D3DCompileFromFile(L"Shaders/PBR_VS.hlsl", defines, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main_vs", "vs_5_0", flags, 0, &pVertexShaderBlob, &pErrorBlob);
	//if (FAILED(hr)) {
	//	if (pErrorBlob) {
	//		std::string errorMsg = (char*)pErrorBlob->GetBufferPointer();
	//		pErrorBlob->Release();
	//	}
	//	// �߰� ���� ó�� �ڵ�
	//	return hr;
	//}

	HR_T(CompileShaderFromFile(L"Shaders/PBR_VS.hlsl", "main_vs", "vs_5_0", &pVertexShaderBlob));

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BITANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	HR_T(m_pDevice->CreateInputLayout(layout, ARRAYSIZE(layout), pVertexShaderBlob->GetBufferPointer(), pVertexShaderBlob->GetBufferSize(), &m_pInputLayout));

	// ���� ���̴� ����
	HR_T(m_pDevice->CreateVertexShader(pVertexShaderBlob->GetBufferPointer(), pVertexShaderBlob->GetBufferSize(), NULL, &m_pVertexShader));
	SAFE_RELEASE(pVertexShaderBlob);
	//SAFE_RELEASE(pErrorBlob);


	// �ȼ� ���̴� ������ �� ����
	HR_T(CompileShaderFromFile(L"Shaders/PBR_PS.hlsl", "main_ps", "ps_5_0", &pPixelShaderBlob));
	HR_T(m_pDevice->CreatePixelShader(pPixelShaderBlob->GetBufferPointer(), pPixelShaderBlob->GetBufferSize(), NULL, &m_pPixelShader));
	SAFE_RELEASE(pPixelShaderBlob);


	//TransformCB buffer ����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(TransformCB);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	HR_T(m_pDevice->CreateBuffer(&bd, nullptr, &pTransformBuffer));

	//ShadingCB buffer ����

	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ShadingCB);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	HR_T(m_pDevice->CreateBuffer(&bd, nullptr, &pShadingBuffer));



	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	HR_T(m_pDevice->CreateSamplerState(&sampDesc, &TexSamplerState));

	//m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);  //���� �׸��� ���
	//m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &m_VertextBufferStride, &m_VertextBufferOffset); //���� ���� ����
	m_pDeviceContext->IASetInputLayout(m_pInputLayout); //�Է� ���̾ƿ� ����
	//pDeviceContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0); //�ε��� ���� ����


	m_pDeviceContext->PSSetSamplers(0, 1, &TexSamplerState);


	std::string g_ModelPath = "Resources/sphere.fbx";
	

	return true;
}

void WinMainApp::UninitScene()
{

	SAFE_DELETE(m_pCamera);

	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pInputLayout);
	SAFE_RELEASE(m_pVertexBuffer);
}

// ImGui Win32 Message Handler
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// ������ ���ν��� ==> imgui ó���� ���� override
LRESULT WinMainApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;

	return WinApp::WndProc(hWnd, message, wParam, lParam);
}

void WinMainApp::OnInputProcess(const Keyboard::State& KeyState, const Keyboard::KeyboardStateTracker& KeyTracker, const Mouse::State& MouseState, const Mouse::ButtonStateTracker& MouseTracker)
{
	if (KeyTracker.IsKeyPressed(Keyboard::Keys::P))
	{
		m_bShowImGUI = !m_bShowImGUI;
	}

	m_pCamera->OnInputProcess(KeyState, KeyTracker, MouseState, MouseTracker);
}