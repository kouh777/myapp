#include "BackBuffer.h"
#include <cassert>

//--------------------------------------------------------
// constract
TBackBuffer::TBackBuffer(LPDIRECT3DDEVICE9 pD3DDevice)
	:FpD3DDevice(NULL), FpD3DSurface(NULL), FhDC(NULL)
{
	assert ( pD3DDevice != NULL);

	FpD3DDevice = pD3DDevice;
	FpD3DDevice->AddRef();

	FpD3DDevice->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &FpD3DSurface);

}

//--------------------------------------------------------
//destract
TBackBuffer::~TBackBuffer(void)
{
	if(FpD3DSurface){
		FpD3DSurface->Release();
		FpD3DSurface=NULL;
	}
	if(FpD3DDevice){
		FpD3DDevice->Release();
		FpD3DDevice=NULL;
	}
}

//--------------------------------------------------------
//lost device
void TBackBuffer::OnLostDevice(void)
{
	if(FpD3DSurface){
		FpD3DSurface->Release();
		FpD3DSurface=NULL;
	}
}

//--------------------------------------------------------
//reset device
void TBackBuffer::OnResetDevice(void)
{
	FpD3DDevice->GetBackBuffer(0 , 0 , D3DBACKBUFFER_TYPE_MONO, &FpD3DSurface);
}

//--------------------------------------------------------
//color fill
void TBackBuffer::ColorFill(const RECT *pFill, const D3DCOLOR inColor)
{
	FpD3DDevice->ColorFill(FpD3DSurface, pFill, inColor);
}

//--------------------------------------------------------
HDC TBackBuffer::GetDC(void)
{
	HRESULT result;
	if(FhDC==NULL){
		/*
		// FpD3DSurfaceがNULLならばGetBackBufferでバックバッファーのサーフェースを取得
		if(FpD3DSurface==NULL){
//			result = FpD3DSurface->GetDesc(FpSurfaceinfo);

			// メソッドの呼び出しが無効。FpD3DSurfaceが有効なポインタでない
			result = FpD3DDevice->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &FpD3DSurface);
			if(	result ==	D3DERR_INVALIDCALL)
				int out = 0;
			else
				int god = 0;
		}
		*/
		FpD3DSurface->GetDC(&FhDC);
	}
	return FhDC;
}

//--------------------------------------------------------
void TBackBuffer::ReleaseDC(void)
{
	if(FhDC==NULL) return ;
	FpD3DSurface->ReleaseDC(FhDC);
	FhDC = NULL;
}