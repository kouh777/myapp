#include "VertexBuffer.h"
#include <cassert>

//--------------------------------------------------------
// constract
TVertexBuffer::TVertexBuffer(LPDIRECT3DDEVICE9 pD3DDevice,
		LPDIRECT3DVERTEXBUFFER9 pVertexBuffer,
		const DWORD FVF,
		const UINT	Stride)
		:FpD3DDevice(pD3DDevice),
		FpVertexBuffer(pVertexBuffer),
		FFVF(FVF),
		FStride(Stride),
		FvPosition(D3DXVECTOR3(0,0,0)),
		FvScale(D3DXVECTOR3(1,1,1)),
		FvRotation(D3DXVECTOR3(0,0,0))
{
	assert(FpD3DDevice!=NULL && FpVertexBuffer != NULL);
	FpD3DDevice->AddRef();
	FpVertexBuffer->AddRef();
	ZeroMemory(&FMaterial,sizeof (FMaterial));
}

//--------------------------------------------------------
// destract
TVertexBuffer::~TVertexBuffer(void)
{
	FpD3DDevice->Release();
	FpVertexBuffer->Release();
}

//--------------------------------------------------------
// 
void TVertexBuffer::SetPosition(const float x, const float y, const float z)
{
	FvPosition.x = x;
	FvPosition.y = y;
	FvPosition.z = z;
}

//--------------------------------------------------------
// 
void TVertexBuffer::SetScale(const float x, const float y, const float z)
{
	FvScale.x = x;
	FvScale.y = y;
	FvScale.z = z;
}

//--------------------------------------------------------
// 
void TVertexBuffer::SetRotation(const float x, const float y, const float z)
{
	FvRotation.x = x;
	FvRotation.y = y;
	FvRotation.z = z;
}

//--------------------------------------------------------
// 
LPVOID TVertexBuffer::Lock(void)
{
	LPVOID pBuffer;
	FpVertexBuffer->Lock(0,0,&pBuffer,0);
	return pBuffer;
}

//--------------------------------------------------------
// 
void TVertexBuffer::Unlock(void)
{
	LPVOID pBuffer;
	FpVertexBuffer->Unlock();
}

//--------------------------------------------------------
// 
void TVertexBuffer::Render(D3DPRIMITIVETYPE inType, const UINT inStart, const UINT inCount)
{
	// set world transforamtion matrix
	// rotation
	D3DXMATRIX rot;
	D3DXMatrixRotationYawPitchRoll(&rot,FvRotation.x, FvRotation.y, FvRotation.z);

	// scaling
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, FvScale.x, FvScale.y, FvScale.z);

	// •½sˆÚ“®
	D3DXMATRIX trans;
	D3DXMatrixTranslation(&trans, FvPosition.x, FvPosition.y,FvPosition.z);

	// fustion of matrixs
	D3DXMATRIX world = rot * scale * trans;

	FpD3DDevice->SetTransform(D3DTS_WORLD, &world);

	FpD3DDevice->SetFVF(FFVF);

	if( (FFVF & D3DFVF_NORMAL) != 0 )
		FpD3DDevice->SetMaterial( &FMaterial);

	FpD3DDevice->SetStreamSource(0, FpVertexBuffer, 0, FStride);
	FpD3DDevice->DrawPrimitive(inType,inStart, inCount);
}

//--------------------------------------------------------
// 
void TVertexBuffer::SetMaterial(D3DMATERIAL9 & inMaterial)
{
	FMaterial = inMaterial;
}