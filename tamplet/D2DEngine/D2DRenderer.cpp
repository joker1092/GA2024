#include "D2DRenderer.h"

D2DRenderer* D2DRenderer::rInstance = nullptr;

D2DRenderer* D2DRenderer::GetInstance()
{
	if (rInstance == nullptr)
		rInstance = new D2DRenderer();
	return rInstance;
}

BOOL D2DRenderer::D2DInitialize(HWND hWnd)
{
	WCHAR buffer[MAX_PATH];
	// Get the current working directory
	DWORD result = GetCurrentDirectory(MAX_PATH, buffer);
	OutputDebugString(buffer);


	HRESULT hr = S_OK;
	// COM 사용 시작
	hr = CoInitialize(NULL);
	if (FAILED(hr))
		return FALSE;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactorty);
	if (FAILED(hr))
		return FALSE;

	RECT rc;
	GetClientRect(hWnd, &rc);

	/*D2D1_SIZE_U size = D2D1::SizeU(
		rc.right - rc.left,
		rc.bottom - rc.top);*/

	size = D2D1::SizeU(
		rc.right - rc.left,
		rc.bottom - rc.top);

	// Create a Direct2D render target.
	hr = pD2DFactorty->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWnd, size),
		&pRenderTarget);

	if (FAILED(hr))
		return FALSE;
		
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&g_pWICFactory)
	);

	if (FAILED(hr))
		return FALSE;

	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(g_pDWriteFactory),
		reinterpret_cast<IUnknown**>(&g_pDWriteFactory));
	if (FAILED(hr))
		return FALSE;

	hr = g_pDWriteFactory->CreateTextFormat(
		L"", // FontName    제어판-모든제어판-항목-글꼴-클릭 으로 글꼴이름 확인가능
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		15.0f,   // Font Size
		L"", //locale
		&g_pDWriteTextFormat
	);

	if (SUCCEEDED(hr))
	{
		hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::GreenYellow), &g_pBrush);
	}

	if (FAILED(hr))
	{
		_com_error err(hr);
		::MessageBox(hWnd, err.ErrorMessage(), L"FAILED", MB_OK);
		return false;
	}

	return TRUE;
}

void D2DRenderer::D2DUninitialize()
{
	if (g_pWICFactory) g_pWICFactory->Release();
	if(pRenderTarget)pRenderTarget->Release();
	if (pD2DFactorty)pD2DFactorty->Release();

	CoUninitialize();
}

void D2DRenderer::BeginDraw()
{
	pRenderTarget->BeginDraw();
}
void D2DRenderer::Clear(D2D1::ColorF color) {
	pRenderTarget->Clear(D2D1::ColorF(color));
}

HRESULT D2DRenderer::CreateD2DBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** ppID2D1Bitmap)
{
	HRESULT hr;
	// Create a decoder
	IWICBitmapDecoder* pDecoder = NULL;
	IWICFormatConverter* pConverter = NULL;

	hr = g_pWICFactory->CreateDecoderFromFilename(
		szFilePath,                      // Image to be decoded
		NULL,                            // Do not prefer a particular vendor
		GENERIC_READ,                    // Desired read access to the file
		WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
		&pDecoder                        // Pointer to the decoder
	);

	// Retrieve the first frame of the image from the decoder
	IWICBitmapFrameDecode* pFrame = NULL;
	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pFrame);
	}

	//Step 3: Format convert the frame to 32bppPBGRA
	if (SUCCEEDED(hr))
	{
		hr = g_pWICFactory->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pFrame,                          // Input bitmap to convert
			GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
			WICBitmapDitherTypeNone,         // Specified dither pattern
			NULL,                            // Specify a particular palette 
			0.f,                             // Alpha threshold
			WICBitmapPaletteTypeCustom       // Palette translation type
		);
	}

	if (SUCCEEDED(hr))
	{
		hr = pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, ppID2D1Bitmap);
	}


	// 파일을 사용할때마다 다시 만든다.
	if (pConverter)
		pConverter->Release();

	if (pDecoder)
		pDecoder->Release();

	if (pFrame)
		pFrame->Release();

	return hr;
}

//void D2DRenderer::DrawBitmap(ID2D1Bitmap* pID2D1Bitmap, int x, int y)
//{
//	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
//	D2D1_VECTOR_2F pos{ x,y };
//	D2D1_SIZE_F size = pID2D1Bitmap->GetSize();
//	D2D1_RECT_F rect = { pos.x- size.width/2 , pos.y- size.height/2, pos.x + size.width/2 ,pos.y + size.height/2};
//	pRenderTarget->DrawBitmap(pID2D1Bitmap, rect);
//	//pRenderTarget->DrawBitmap(pID2D1Bitmap);
//}

void D2DRenderer::DrawBitmap(ID2D1Bitmap* pID2D1Bitmap, D2D_MATRIX_3X2_F mat)
{
	pRenderTarget->SetTransform(mat);
	pRenderTarget->DrawBitmap(pID2D1Bitmap);
	//pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void D2DRenderer::PrintMatrix(const wchar_t* str, D2D_MATRIX_3X2_F& mat, float left, float top)
{
	WCHAR buffer[256] = { 0 };
	swprintf_s(buffer, L"%.2f, %.2f\n%.2f, %.2f\n%.2f, %.2f\n",
		mat._11, mat._12, mat._21, mat._22, mat._31, mat._32);
	OutputDebugString(buffer);

	D2D1::Matrix3x2F matRender = D2D1::Matrix3x2F::Identity();
	pRenderTarget->SetTransform(matRender);

	g_pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
	pRenderTarget->FillRectangle(D2D1::RectF(left, top, left + 100, top + 150), g_pBrush);

	g_pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	pRenderTarget->DrawTextW(str, (UINT32)wcslen(str), g_pDWriteTextFormat, D2D1::RectF(left, top, left + 300, top + 300), g_pBrush);
	pRenderTarget->DrawTextW(buffer, (UINT32)wcslen(buffer), g_pDWriteTextFormat, D2D1::RectF(left, top + 60, left + 300, top + 60 + 300), g_pBrush);
}

void D2DRenderer::EndDraw() {
	pRenderTarget->EndDraw();
}

void D2DRenderer::DWDrawText(const wchar_t* str, D2D1_RECT_F rect)
{
	//WCHAR sc_helloWorld[] = L"Hello, World! Abg";
	pRenderTarget->DrawText(
		str, (UINT32)wcslen(str),
		g_pDWriteTextFormat,
		rect,
		g_pBrush
	);
}

void D2DRenderer::RenderSetTransform(D2D_MATRIX_3X2_F Transform)
{
	pRenderTarget->SetTransform(Transform);
}



