#ifndef __DIRECTWRITE_H__
#define __DIRECTWRITE_H__

#include <Windows.h>
#include <d2d1.h>
#include <dwrite.h>

//--------------------------------------------------------
class TDirectWrite{
private:
	TDirectWrite(void);
	TDirectWrite(const TDirectWrite & );
	TDirectWrite operator = (const TDirectWrite & );

    float FfdpiScaleX;
    float FfdpiScaleY;

	// for using direct write
	IDWriteFactory			*FpDWriteFactory;
	IDWriteTextFormat		*FpTextFormat;
	const wchar_t			*FwszText;
	UINT32					FcTextLength;
	ID2D1Factory			*FpD2DFactory;
	ID2D1HwndRenderTarget	*FpRT;
	ID2D1SolidColorBrush	*FpBlackBrush;

	HWND FhWnd;

	void Release(void);
	HRESULT CreateResources(void);
	HRESULT DrawText(void);

public:
	~TDirectWrite(void);
	static TDirectWrite &GetInstance(void){
		static TDirectWrite instance;
		return instance;
	}
	// for using direct write
	bool Initialize(HWND hWnd, bool isWindowed);
	HRESULT DrawD2DContent(void);
	void BeginDrawing(void);
	HRESULT EndDrawing(void);
};

inline TDirectWrite &DxWrite(void){return TDirectWrite::GetInstance();};

#endif __DIRECTWRITE_H__