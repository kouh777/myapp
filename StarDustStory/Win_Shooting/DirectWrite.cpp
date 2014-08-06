
//--------------------------------------------------------
#include "DirectWrite.h"

//--------------------------------------------------------
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")


//--------------------------------------------------------
// ***目的***
// より綺麗なフォントの表示　＋　より高いパフォーマンスの維持
// せっかく文字描画用のインターフェースがあるので使ってみたい。
//
// ***課題***
// これのRenderTargetとD3DSurfaceを共有させたい。
// 今は描画先が別々になっている。
//
// ***解決策(その1)***
// VisualStudio2012 + DirectX11以降への移行
// DirectX11以降には
// RenderTargetの派生クラスでDirect3Dとの
// サーフェイスの共有が出来るものがあるらしい。
// この場合、Direct3Dの初期化の仕方が違うなど、
// 色々Direct9との違いがありそう。
// 
// ***解決策(その2)***
// 自力で描画先を共有させる(茨の道)
// 
// ***気になる点***
// そもそも本当にDirectWriteを使うことでパフォーマンスが上昇するのだろうか？
// (綺麗なフォント表示という点はクリア)
// 
// ***別の方法***
// 板ポリに文字を描画して、板ポリを表示(後で試してみたい)
//
//--------------------------------------------------------


//--------------------------------------------------------
TDirectWrite::TDirectWrite()
	:FpDWriteFactory(NULL),
	FpTextFormat(NULL),
	FwszText(NULL),
	FcTextLength(0),
	FpD2DFactory(NULL),
	FpRT(NULL),
	FpBlackBrush(NULL)
{

}

//--------------------------------------------------------
TDirectWrite::~TDirectWrite()
{
	Release();
}

//--------------------------------------------------------
bool TDirectWrite::Initialize(HWND hWnd, bool isWindowed)
{
	FhWnd = hWnd;

    //get the dpi information
    HDC screen = GetDC(0);
    FfdpiScaleX = GetDeviceCaps(screen, LOGPIXELSX) / 96.0f;
    FfdpiScaleY = GetDeviceCaps(screen, LOGPIXELSY) / 96.0f;
    ReleaseDC(0, screen);

	HRESULT hr;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &FpD2DFactory);
	if(FAILED(hr)){
		::OutputDebugString(TEXT("***Error - D2D1Factoryオブジェクトの生成に失敗しました。(TDirectWrite::GetInstance();)"));
		Release();
		return false;
	}
	if(FpD2DFactory){
		hr = DWriteCreateFactory(
					 DWRITE_FACTORY_TYPE_SHARED,
					 __uuidof(IDWriteFactory),
					reinterpret_cast<IUnknown**>(&FpDWriteFactory)
					);
	}
	if(FAILED(hr)){
		::OutputDebugString(TEXT("***Error - DWriteCreateFactoryオブジェクトの生成に失敗しました。(TDirectWrite::GetInstance();)"));
		return false;
	}
	FwszText = L"Hello World using  DirectWrite!";
	FcTextLength = (UINT32) wcslen(FwszText);
	
	if(SUCCEEDED(hr)){
		hr = FpDWriteFactory->CreateTextFormat(
		TEXT("メイリオ"),                // Font family name.
        NULL,                       // Font collection (NULL sets it to use the system font collection).
        DWRITE_FONT_WEIGHT_REGULAR,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        16.0f,
        TEXT("ja-jp"),
        &FpTextFormat
        );
	}
	if(FAILED(hr)){
		::OutputDebugString(TEXT("***Error - CreateTextFormatオブジェクトの生成に失敗しました。(TDirectWrite::GetInstance();)"));
		return false;
	}

	// Center align (horizontally) the text.
	if (SUCCEEDED(hr))
	{
	    hr = FpTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	}
	if (SUCCEEDED(hr))
	{
	    hr = FpTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}
	return true;
}

//--------------------------------------------------------
void TDirectWrite::Release(void)
{
	if(FpRT) FpRT->Release(); FpRT = NULL;
	if(FpBlackBrush) FpBlackBrush->Release(); FpBlackBrush = NULL;

}

//--------------------------------------------------------
HRESULT TDirectWrite::CreateResources(void)
{
	HRESULT hr = S_OK;
	RECT rc;
	GetClientRect(FhWnd, &rc);
	D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
	
	if (!FpRT)
	{
	    // Create a Direct2D render target.
	    hr = FpD2DFactory->CreateHwndRenderTarget(
	            D2D1::RenderTargetProperties(),
	            D2D1::HwndRenderTargetProperties(FhWnd,size),
	            &FpRT
	            );
		if(FAILED(hr)){
			::OutputDebugString(TEXT("***Error - CreateHwndRenderTargetオブジェクトの生成に失敗しました。(TDirectWrite::CreateResources();)"));	
		}
	
	    // Create a black brush.
	    if (SUCCEEDED(hr)){
	        hr = FpRT->CreateSolidColorBrush(
	            D2D1::ColorF(D2D1::ColorF::Black),
	            &FpBlackBrush
	            );
	    }
		if(FAILED(hr)){
			::OutputDebugString(TEXT("***Error - CreateSolidColorBrushオブジェクトの生成に失敗しました。(TDirectWrite::CreateResources();)"));	
		}
	}
	return hr;
}

//--------------------------------------------------------
HRESULT TDirectWrite::DrawText(void)
{
	RECT rc;
	GetClientRect(FhWnd, &rc);

	D2D1_RECT_F layoutRect = D2D1::RectF(
		static_cast<FLOAT>(rc.left)	/ FfdpiScaleX,	
		static_cast<FLOAT>(rc.top)	/ FfdpiScaleY,	
		static_cast<FLOAT>(rc.right - rc.left) / FfdpiScaleX,	
		static_cast<FLOAT>(rc.bottom - rc.top) / FfdpiScaleY	
	 );

	FpRT->DrawText(
		FwszText,        // The string to render.
		FcTextLength,    // The string's length.
		FpTextFormat,    // The text format.
		layoutRect,      // The region of the window where the text will be rendered.
		FpBlackBrush     // The brush used to draw the text.
	);
	return S_OK;
}

//--------------------------------------------------------
void TDirectWrite::BeginDrawing(void)
{
	FpRT->BeginDraw();
}

//--------------------------------------------------------
HRESULT TDirectWrite::EndDrawing(void)
{
	HRESULT hr;
	hr = FpRT->EndDraw();
	return hr;
}

//--------------------------------------------------------
HRESULT TDirectWrite::DrawD2DContent(void)
{
	HRESULT hr;
	hr = CreateResources(); 
	if (SUCCEEDED(hr))
	{
	    BeginDrawing();
	
	    FpRT->SetTransform(D2D1::IdentityMatrix());
	
	    FpRT->Clear(D2D1::ColorF(D2D1::ColorF::White));
	
	    // Call the DrawText method of this class.
		hr = DrawText();
	    if (SUCCEEDED(hr))
	    {
	        hr = EndDrawing();
	    }
        if (hr == D2DERR_RECREATE_TARGET)
        {
            hr = S_OK;
            Release();
        }
	}
	return hr;
}