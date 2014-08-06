#ifndef __DIRECTGRAPHICS9_H__
#define __DIRECTGRAPHICS9_H__

//--------------------------------------------------------
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <list>

#include "isprite.h"
#include "Mesh.h"
#include "VertexBuffer.h"

#include "Vector2D.h"

//--------------------------------------------------------
class TDirectGraphics9
{
private:
	TDirectGraphics9(void);

	// invalidate copy constract and =(equal) operator
	TDirectGraphics9(const TDirectGraphics9 &);
	TDirectGraphics9 operator = (const TDirectGraphics9 &);

	// general rule of directX
	LPDIRECT3D9				FpD3D;
	D3DPRESENT_PARAMETERS	FPresentParams;
	RECT					FRectWindow;		// ウィンドウモード時の位置と幅と高さを保持する
	LPDIRECT3DDEVICE9		FpD3dDevice;
	LPD3DXSPRITE			FpD3DXSprite;
	std::list<ISprite *>	FpSpriteList;
	std::list<IMesh *>		FpMesh;
	std::list<IVertexBuffer *> FVertextBuffer;

	LPD3DXFONT				FpFont;

	void Release(void);
	void SetPresentParameters(BOOL inWindowed);
	bool Reset(void);

public:
	~TDirectGraphics9(void);
	static TDirectGraphics9 &GetInstance(void){
		static TDirectGraphics9 instance;
		return instance;
	}
	// initailize
	bool Initialize(HWND hWnd, bool isWindowed);
	// clear viewport
	void Clear(DWORD inFlag, D3DCOLOR inColor);
	// begin scene
	bool BeginScene(void);
	// end scene
	void EndScene(void);
	// update frame
	void UpdateFrame(void);
	// change mode
	bool ChangeMode(bool inWindowed);
	
	//----------
	// Sprite
	//----------
	bool BeginSprite(DWORD Flags);
	void EndSprite(void);
	void ClearAllSprite(void);
	ISprite* CreateSpriteFormFile(LPCWSTR inFileName, D3DFORMAT inFormat, D3DCOLOR inColorKey);

	// font for debug
	void DrawString(LPCTSTR szStr, int iX, int iY, D3DXCOLOR col);

	//----------
	// Simple Shape
	//----------
	IMesh *CreateBox(const float inWidth, const float inHeight, const float inDepth );
	IMesh *CreateCylinder(const float inRadius1, const float inRadius2,
		const float inLength, const UINT inSlices, const UINT inStacks );
	IMesh *CreatePolygon(const float inLength, const UINT inSides);
	IMesh *CreateSphere(const float inRadius, const UINT inSlices, const UINT inStacks);
	IMesh *CreateTorus(const float inInnerRadius, const float inOuterRadius,
		const UINT inSlides, const UINT inRings);
	IMesh *CreateTeapot(void);

	void ReleaseMesh(IMesh* &pMesh);
	void ReleaseAllMeshes(void);

	IVertexBuffer *CreateVertexBuffer(const UINT inSize, const DWORD inFVF, const UINT inStride);
	void ReleaseVertexBuffer(IVertexBuffer* &pBuffer);
	void ReleaseAllVertexBuffers();


	// capsel
	LPDIRECT3DDEVICE9 &GetDevice(void){return FpD3dDevice;}
};

inline TDirectGraphics9 &DxGraphics9(void)
{
	return TDirectGraphics9::GetInstance();
}

#endif // __DIRECTGRAPHICS9_H__