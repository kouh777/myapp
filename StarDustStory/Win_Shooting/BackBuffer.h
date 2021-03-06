#ifndef __BACKBUFFER_H__
#define __BACKBUFFER_H__

//--------------------------------------------------------
#include <d3dx9.h>

//--------------------------------------------------------
class TBackBuffer
{
private:
	HDC					FhDC;
	LPDIRECT3DDEVICE9	FpD3DDevice;
	LPDIRECT3DSURFACE9	FpD3DSurface;
	D3DSURFACE_DESC		*FpSurfaceinfo;

public:
	TBackBuffer(LPDIRECT3DDEVICE9 pD3DDevice);
	virtual ~TBackBuffer(void);

	void OnLostDevice(void);
	void OnResetDevice(void);

	void ColorFill(const RECT *pFill, const D3DCOLOR inColor);

	HDC GetDC(void);
	void ReleaseDC(void);
};

#endif // __BACKBUFFER_H__