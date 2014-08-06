#ifndef __ISPRITE_H__
#define __ISPRITE_H__

// This cord is created by 'NULL Object' Design Patern

//--------------------------------------------------------
#include <d3dx9.h>

//--------------------------------------------------------
// sprite interface class
class ISprite
{
public:
	virtual ~ISprite(void){}
	virtual void Render(const RECT *pSrc, const D3DXVECTOR3 &inPos, FLOAT inAlpha) = 0;
	virtual void RenderEx(	const RECT *pSrc, const D3DXVECTOR3 &inPos,
							const D3DXVECTOR3 &inScale, const D3DXVECTOR3 &inRotation,
							D3DXVECTOR3 *Center , const FLOAT inAlpha, const D3DCOLOR inColor) = 0;

};

class TSprite : public ISprite
{
private:
	LPD3DXSPRITE		FpD3DXSprite;
	LPDIRECT3DTEXTURE9	FpTexture9;

public:
	TSprite(LPD3DXSPRITE pD3DXSprite , LPDIRECT3DTEXTURE9 pTexture);
	~TSprite(void);

	virtual void Render(const RECT *pSrc, const D3DXVECTOR3 &inPos, FLOAT inAlpha);
	virtual void RenderEx(	const RECT *pSrc, const D3DXVECTOR3 &inPos,
							const D3DXVECTOR3 &inScale, const D3DXVECTOR3 &inRotation,
							D3DXVECTOR3 *pCenter, const FLOAT inAlpha, const D3DCOLOR inColor);
};

class TNullSprite : public ISprite
{
	virtual void Render(const RECT *pSrc, const D3DXVECTOR3 &inPos, FLOAT inAlpha){}
	virtual void RenderEx(	const RECT *pSrc, const D3DXVECTOR3 &inPos,
							const D3DXVECTOR3 &inScale, const D3DXVECTOR3 &inRotation,
							D3DXVECTOR3 *pCenter , const FLOAT inAlpha, const D3DCOLOR inColor){}
};



#endif //__ISPRITE_H__