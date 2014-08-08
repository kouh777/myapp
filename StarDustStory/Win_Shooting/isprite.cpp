
#include "isprite.h"

//--------------------------------------------------------
// constract
TSprite::TSprite(LPD3DXSPRITE pD3DXSprite , LPDIRECT3DTEXTURE9 pTexture)
	:FpD3DXSprite(pD3DXSprite), FpTexture9(pTexture)
{
	FpD3DXSprite->AddRef();
	FpTexture9->AddRef();

}

TSprite::~TSprite(void)
{
	FpD3DXSprite->Release();
	FpTexture9->Release();
}

//--------------------------------------------------------
// destract
void TSprite::Render(const RECT *pSrc, const D3DXVECTOR3 &inPos, FLOAT inAlpha)
{
	// set color
	const D3DCOLOR color = ((DWORD)(inAlpha*255.f) << 24) | 0x00FFFFFF;

	// set transformation matrix
	D3DXMATRIX mat;
	::D3DXMatrixIdentity(&mat);			// identity matrix
	FpD3DXSprite->SetTransform(&mat);	// set matrix	

	// draw
	FpD3DXSprite->Draw(FpTexture9, pSrc, NULL, &inPos, color);
}

//--------------------------------------------------------
 void TSprite::RenderEx(	const RECT *pSrc, const D3DXVECTOR3 &inPos,
							const D3DXVECTOR3 &inScale, const D3DXVECTOR3 &inRotation,
							D3DXVECTOR3 *pCenter , const FLOAT inAlpha, const D3DCOLOR inColor)
 {
	// set color

	const D3DCOLOR COLOR = ((DWORD)(inAlpha*255.f) << 24) | 0x00FFFFFF;
	//const D3DCOLOR COLOR = ((DWORD)(inAlpha * 255.f) << 24 )| (inColor & 0x00FFFFFF);

	// rotation vector change to quaternion
	D3DXQUATERNION qt;
	
	D3DXQuaternionRotationYawPitchRoll(	&qt,
										D3DXToRadian(inRotation.y),
										D3DXToRadian(inRotation.x),
										D3DXToRadian(inRotation.z));
	
	// set matrix
	D3DXMATRIX mat;
	D3DXMatrixTransformation(&mat, NULL, NULL, &inScale, NULL, &qt, &inPos);
	FpD3DXSprite->SetTransform(&mat);

	// draw
	FpD3DXSprite->Draw( FpTexture9, pSrc, pCenter, NULL, COLOR);
 }