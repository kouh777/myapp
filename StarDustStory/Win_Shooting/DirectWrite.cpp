
//--------------------------------------------------------
#include "DirectWrite.h"

//--------------------------------------------------------
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")


//--------------------------------------------------------
// ***�ړI***
// ����Y��ȃt�H���g�̕\���@�{�@��荂���p�t�H�[�}���X�̈ێ�
// �������������`��p�̃C���^�[�t�F�[�X������̂Ŏg���Ă݂����B
//
// ***�ۑ�***
// �����RenderTarget��D3DSurface�����L���������B
// ���͕`��悪�ʁX�ɂȂ��Ă���B
//
// ***������(����1)***
// VisualStudio2012 + DirectX11�ȍ~�ւ̈ڍs
// DirectX11�ȍ~�ɂ�
// RenderTarget�̔h���N���X��Direct3D�Ƃ�
// �T�[�t�F�C�X�̋��L���o������̂�����炵���B
// ���̏ꍇ�ADirect3D�̏������̎d�����Ⴄ�ȂǁA
// �F�XDirect9�Ƃ̈Ⴂ�����肻���B
// 
// ***������(����2)***
// ���͂ŕ`�������L������(��̓�)
// 
// ***�C�ɂȂ�_***
// ���������{����DirectWrite���g�����ƂŃp�t�H�[�}���X���㏸����̂��낤���H
// (�Y��ȃt�H���g�\���Ƃ����_�̓N���A)
// 
// ***�ʂ̕��@***
// �|���ɕ�����`�悵�āA�|����\��(��Ŏ����Ă݂���)
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
		::OutputDebugString(TEXT("***Error - D2D1Factory�I�u�W�F�N�g�̐����Ɏ��s���܂����B(TDirectWrite::GetInstance();)"));
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
		::OutputDebugString(TEXT("***Error - DWriteCreateFactory�I�u�W�F�N�g�̐����Ɏ��s���܂����B(TDirectWrite::GetInstance();)"));
		return false;
	}
	FwszText = L"Hello World using  DirectWrite!";
	FcTextLength = (UINT32) wcslen(FwszText);
	
	if(SUCCEEDED(hr)){
		hr = FpDWriteFactory->CreateTextFormat(
		TEXT("���C���I"),                // Font family name.
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
		::OutputDebugString(TEXT("***Error - CreateTextFormat�I�u�W�F�N�g�̐����Ɏ��s���܂����B(TDirectWrite::GetInstance();)"));
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
			::OutputDebugString(TEXT("***Error - CreateHwndRenderTarget�I�u�W�F�N�g�̐����Ɏ��s���܂����B(TDirectWrite::CreateResources();)"));	
		}
	
	    // Create a black brush.
	    if (SUCCEEDED(hr)){
	        hr = FpRT->CreateSolidColorBrush(
	            D2D1::ColorF(D2D1::ColorF::Black),
	            &FpBlackBrush
	            );
	    }
		if(FAILED(hr)){
			::OutputDebugString(TEXT("***Error - CreateSolidColorBrush�I�u�W�F�N�g�̐����Ɏ��s���܂����B(TDirectWrite::CreateResources();)"));	
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