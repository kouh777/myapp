#ifndef __TVERTEXBUFFER_H__
#define __TVERTEXBUFFER_H__

#include <d3dx9.h>

// トランスフォーム済みライティング済みの頂点
struct DXGTLVERTEX{
	float x, y, z, rhw;	// 頂点座標
	D3DCOLOR color;		//　頂点色
	float tu, tv;

	// constract
	DXGTLVERTEX():x(0.0f),y(0.0f),z(0.0f),rhw(0.0f),color(0),tu(0.0f),tv(0.0f){}

};

// 未トランスフォームライティング済みの頂点
struct DXGLVERTEX{
	float x, y, z;
	D3DCOLOR color;
	D3DCOLOR colsp;	// スペキュラー色
	float tu, tv;

	// constract
	DXGLVERTEX():x(0.0f),y(0.0f),z(0.0f),color(0),colsp(0),tu(0.0f),tv(0.0f){}
};

// 未トランスフォーム未ライティングの頂点
struct DXGVERTEX{
	float x, y, z;
	float nx, ny, nz;	//　法線ベクトル
	float tu, tv;

	// constract
	DXGVERTEX():x(0.0f),y(0.0f),z(0.0f),nx(0.0f),ny(0.0f),nz(0.0f),tu(0.0f),tv(0.0f){}

};

enum{
	DXGFVF_TLVERTEX = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1,
	DXFVF_LVERTEX = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1,
	DXFVF_VERTEX = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1,
};

class IVertexBuffer{
private:

public:
	virtual ~IVertexBuffer(void){}

	virtual void SetPosition(const float x, const float y, const float z)=0;
	virtual void SetScale(const float x, const float y, const float z)=0;
	virtual void SetRotation(const float x, const float y, const float z)=0;

	virtual LPVOID Lock(void) = 0;
	virtual void Unlock(void) = 0;
	virtual void Render(D3DPRIMITIVETYPE inType, const UINT inStart, const UINT inCount) = 0;
	virtual void SetMaterial(D3DMATERIAL9 & inMaterial) = 0;
};

class TVertexBuffer : public IVertexBuffer{
private:
	LPDIRECT3DDEVICE9		FpD3DDevice;
	LPDIRECT3DVERTEXBUFFER9	FpVertexBuffer;
	const DWORD				FFVF;				// flag of fvf
	const UINT				FStride;			// 次の頂点までのバイト数

	D3DXVECTOR3 FvPosition;
	D3DXVECTOR3 FvScale;
	D3DXVECTOR3 FvRotation;

	D3DMATERIAL9 FMaterial;

public:
	TVertexBuffer(LPDIRECT3DDEVICE9 pD3DDevice,
		LPDIRECT3DVERTEXBUFFER9 pVertexBuffer,
		const DWORD FVF,
		const UINT	Stride);
	virtual ~TVertexBuffer(void);

	virtual void SetPosition(const float x, const float y, const float z);
	virtual void SetScale(const float x, const float y, const float z);
	virtual void SetRotation(const float x, const float y, const float z);

	virtual LPVOID Lock(void);
	virtual void Unlock(void);
	virtual void Render(D3DPRIMITIVETYPE inType, const UINT inStart, const UINT inCount);
	virtual void SetMaterial(D3DMATERIAL9 & inMaterial);
};

class TNullVertexBuffer : public IVertexBuffer{
private:

public:
	virtual ~TNullVertexBuffer(void){}
	virtual void SetPosition(const float x, const float y, const float z){}
	virtual void SetScale(const float x, const float y, const float z){}
	virtual void SetRotation(const float x, const float y, const float z){}
	virtual LPVOID Lock(void){return false;}
	virtual void Unlock(void){}
	virtual void Render(D3DPRIMITIVETYPE inType, const UINT inStart, const UINT inCount){}
	virtual void SetMaterial(D3DMATERIAL9 & inMaterial){}
};


#endif //__TVERTEXBUFFER_H__