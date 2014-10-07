#include "Mesh.h"
#include <cassert>

//--------------------------------------------------------
// constract
TMesh::TMesh(LPDIRECT3DDEVICE9 pD3DDevice, LPD3DXMESH pMesh, const DWORD inSubsetCount)
	:FpD3DDevice(pD3DDevice),
	FpMesh(pMesh),
	FiSubsetCount(inSubsetCount),
	FvPosition(D3DXVECTOR3(0,0,0)),
	FvScale(D3DXVECTOR3(1,1,1)),
	FvRotation(D3DXVECTOR3(0,0,0)),
	FMaterial(inSubsetCount)
{
	assert(FpD3DDevice!=NULL && FpMesh != NULL);

	FpD3DDevice->AddRef();
	FpMesh->AddRef();

	for(DWORD i=0; i < FMaterial.size() ; ++i)
	{
		ZeroMemory(&FMaterial[i],sizeof FMaterial[i]);
	}
}

//--------------------------------------------------------
// destract
TMesh::~TMesh(void)
{
	FpD3DDevice->Release();
	FpMesh->Release();
}

//--------------------------------------------------------
// 
void TMesh::SetPosition(const float x, const float y, const float z)
{
	FvPosition.x = x;
	FvPosition.y = y;
	FvPosition.z = z;
}

//--------------------------------------------------------
// 
void TMesh::SetScale(const float x, const float y, const float z)
{
	FvScale.x = x;
	FvScale.y = y;
	FvScale.z = z;
}

//--------------------------------------------------------
// 
void TMesh::SetRotation(const float x, const float y, const float z)
{
	FvRotation.x = x;
	FvRotation.y = y;
	FvRotation.z = z;
}

//--------------------------------------------------------
// destract
void TMesh::Render(void)
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

	// fusion of matrixs
	D3DXMATRIX world = rot * scale * trans;

	FpD3DDevice->SetTransform(D3DTS_WORLD, &world);
	for(DWORD i=0; i < FiSubsetCount; ++i){
		FpD3DDevice->SetMaterial(&FMaterial[i]);
		FpMesh->DrawSubset(i);
	}
}

//--------------------------------------------------------
// 
void TMesh::SetMaterial(const DWORD inSubset, const D3DMATERIAL9 & inMaterial)
{
	FMaterial[inSubset] = inMaterial;
}