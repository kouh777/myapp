#ifndef __TMESH_H__
#define __TMESH_H__

//--------------------------------------------------------
#include <d3dx9.h>

//--------------------------------------------------------
class IMesh{
private:

public:
	IMesh(void){}
	virtual ~IMesh(void){}

	virtual void SetPosition(const float x, const float y, const float z)=0;
	virtual void SetScale(const float x, const float y, const float z)=0;
	virtual void SetRotation(const float x, const float y, const float z)=0;
	virtual void Render()=0;
};

class TMesh : public IMesh{
private:
	D3DXVECTOR3 FvPosition;
	D3DXVECTOR3 FvScale;
	D3DXVECTOR3 FvRotation;
	LPDIRECT3DDEVICE9 FpD3DDevice;
	LPD3DXMESH FpMesh;
	const DWORD FiSubsetCount;		// number of subset

public:
	TMesh(LPDIRECT3DDEVICE9 pD3DDevice, LPD3DXMESH pMesh, const DWORD inSubsetCount);
	~TMesh(void);
	virtual void SetPosition(const float x, const float y, const float z);
	virtual void SetScale(const float x, const float y, const float z);
	virtual void SetRotation(const float x, const float y, const float z);
	virtual void Render();
};

class TNullMesh:public IMesh{
private:

public:
	virtual ~TNullMesh(void){}
	virtual void SetPosition(const float x, const float y, const float z){}
	virtual void SetScale(const float x, const float y, const float z){}
	virtual void SetRotation(const float x, const float y, const float z){}
	virtual void Render(){}
};

#endif //__TMESH_H__