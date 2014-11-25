#include "DirectGraphics9.h"
#include <cassert>

//--------------------------------------------------------
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//--------------------------------------------------------
// constract
TDirectGraphics9::TDirectGraphics9(void)
	:FpD3dDevice(NULL),
	FpD3D(NULL),
	FpD3DXSprite(NULL),
	FpFont(NULL),
	FpBackBuffer(NULL),
	FhWnd(NULL)
{
}

//--------------------------------------------------------
// destract
TDirectGraphics9::~TDirectGraphics9(void)
{
	// release
	Release();
}

//--------------------------------------------------------
// initialize
bool TDirectGraphics9::Initialize(HWND hWnd, bool isWindowed){

	// cretate Direct3D object (this calls CoInitialize(NULL) and QueryInterface() method)
	FpD3D = Direct3DCreate9( D3D_SDK_VERSION);
	if(FpD3D == NULL){
		::OutputDebugString(TEXT("***Error - Direct3D9オブジェクトの生成に失敗しました。(TDirect3DGraphics::Initialize()\n)"));
		return false;
	}

	// presentation parameter(common)
	FPresentParams.BackBufferCount				= 1;									// number of backbuffer
	FPresentParams.MultiSampleType				= D3DMULTISAMPLE_NONE;					// multi sample type
	FPresentParams.MultiSampleQuality			= 0;									// multi sample quality
	FPresentParams.SwapEffect					= D3DSWAPEFFECT_DISCARD;				// swap effect
	FPresentParams.hDeviceWindow				= hWnd;									// target window
	FPresentParams.EnableAutoDepthStencil		= TRUE;									// depth buffer
	FPresentParams.AutoDepthStencilFormat		= D3DFMT_D16;							// depth buffer format
	FPresentParams.Flags						= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;	// flag
	FPresentParams.FullScreen_RefreshRateInHz	= 0;									// refresh rate

	// presentation parameter(identified)
	SetPresentParameters(isWindowed);

	// create Direct3DDevice object
	const DWORD Behavior[3] = {
		D3DCREATE_MIXED_VERTEXPROCESSING,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
	};
	HRESULT hr;
	for(int i=0; i<3 ; i++){
		hr = FpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
								hWnd, Behavior[i], &FPresentParams, &FpD3dDevice);
		if(SUCCEEDED(hr)){
			break;
		}
		if(FAILED(hr)){
			::OutputDebugString(TEXT("***Error - D3DDeviceオブジェクトの生成に失敗しました。(TDirectGraphics9::GetInstance();)"));
			return false;
		}
	}
	// create font object
	hr = D3DXCreateFont(FpD3dDevice, 0, 8, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,PROOF_QUALITY,FIXED_PITCH | FF_MODERN, TEXT("メイリオ"), &FpFont);
	if(FAILED(hr)){
		::OutputDebugString(TEXT("***Error - D3DXFontオブジェクトの生成に失敗しました。(TDirectGraphics9::GetInstance();)"));
		Release();
		return false;
	}
	// create sprite object
	hr = ::D3DXCreateSprite(FpD3dDevice, &FpD3DXSprite);
	if(FAILED(hr)){
		::OutputDebugString(TEXT("***Error - D3DXSpriteオブジェクトの生成に失敗しました。(TDirectGraphics9::GetInstance();)"));
		Release();
		return false;
	}

	FpBackBuffer = new TBackBuffer(FpD3dDevice);

	FhWnd = hWnd;

	return true;
}

//-------------------------------------------------
// device lost
bool TDirectGraphics9::Reset(void)
{
	assert( FpD3dDevice && TEXT("***Error - DxDevice9未初期化(TDirextGraphics9::Reset)"));

	HRESULT hr;

	// before reset
	if(FpBackBuffer) FpBackBuffer->OnLostDevice();
	if(FpD3DXSprite) FpD3DXSprite->OnLostDevice();
	if(FpFont) FpFont->OnLostDevice();

	// reset
	hr = FpD3dDevice->Reset(&FPresentParams);
	if( hr != D3D_OK)
	{
		::OutputDebugString(TEXT("***Error - シーンの開始に失敗(TDirextGraphics9::Reset)\n"));
		if ( hr == D3DERR_INVALIDCALL){
			::OutputDebugString(TEXT("***Error - D3DERR_INVALIDCALL メソッドの呼び出しが無効です。メソッドのパラメータに無効な値が含まれていないか確認して下さい。(TDirextGraphics9::Reset)\n"));
		}
		return false;
	}

	// after reset
	if(FpBackBuffer) FpBackBuffer->OnResetDevice();
	if(FpFont) FpFont->OnResetDevice();
	if(FpD3DXSprite) FpD3DXSprite->OnResetDevice();


	return true;
}

//-------------------------------------------------
// change parameters
void TDirectGraphics9::SetPresentParameters(BOOL inWindowed)
{
	D3DDISPLAYMODE pMode;
	std::vector<D3DDISPLAYMODE>	FpModes;

	HRESULT hr;

	if(inWindowed){
		FPresentParams.Windowed				= true;			
		FPresentParams.BackBufferWidth		= 0;				
		FPresentParams.BackBufferHeight		= 0;				
		FPresentParams.BackBufferFormat		= D3DFMT_UNKNOWN;
		FPresentParams.PresentationInterval	= D3DPRESENT_INTERVAL_ONE;
	}else{
		// 何種類ディスプレイモードがあるか調べる
		int num = FpD3D->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8);
		// 使えるディスプレイモードをvectorに格納
		for(int i=0; i<num ; ++i){
			FpD3D->EnumAdapterModes(D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8, i, &pMode);
			FpModes.push_back(pMode);
		}
		// とりあえず800*600を指定 6
		pMode = FpModes[7];

		FPresentParams.Windowed				= false;			
		FPresentParams.BackBufferWidth		= pMode.Width;				
		FPresentParams.BackBufferHeight		= pMode.Height;
//		FPresentParams.BackBufferFormat		= D3DFMT_A8R8G8B8;
		FPresentParams.BackBufferFormat		= pMode.Format;
		// 使えるかチェック
		FPresentParams.PresentationInterval	= D3DPRESENT_INTERVAL_DEFAULT;
//		FPresentParams.PresentationInterval	= D3DPRESENT_INTERVAL_IMMEDIATE;
		FPresentParams.SwapEffect			= D3DSWAPEFFECT_DISCARD;
		FPresentParams.FullScreen_RefreshRateInHz = pMode.RefreshRate;
		FPresentParams.hDeviceWindow		= FhWnd;
	}
	// デバイスの生成
//	FpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, FhWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &FPresentParams, &FpD3dDevice);
//	FpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, FhWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &FPresentParams, &FpD3dDevice);
//	FpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, FhWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &FPresentParams, &FpD3dDevice);
//	FpD3D->Release();

}

//--------------------------------------------------------
// release
void TDirectGraphics9::Release(void)
{
	ClearAllSprite();
	ReleaseAllMeshes();
	ReleaseAllVertexBuffers();
	if(FpBackBuffer)FpBackBuffer ->OnLostDevice();FpBackBuffer = NULL;
	if(FpD3DXSprite)FpD3DXSprite -> Release(); FpD3DXSprite = NULL;
	if(FpFont)FpFont -> Release(); FpFont = NULL;
	if(FpD3dDevice) FpD3dDevice -> Release(); FpD3dDevice = NULL;
	if(FpD3D)FpD3D -> Release(); FpD3D = NULL;
	ReleaseAllMeshes();
}

//--------------------------------------------------------
// clear viewport
void TDirectGraphics9::Clear(DWORD inFlag, D3DCOLOR inColor)
{
	assert( FpD3dDevice && TEXT("***Error - DxDevice9未初期化(TDirextGraphics9::Clear)"));

	FpD3dDevice->Clear( 0, NULL, inFlag, inColor, 1.f, 0);
}

//--------------------------------------------------------
// begin scene
bool TDirectGraphics9::BeginScene(void)
{
	HRESULT hr;
	assert( FpD3dDevice && TEXT("***Error - DxDevice9未初期化(TDirextGraphics9::BeginScene)"));

	hr = FpD3dDevice -> BeginScene();
	if(FAILED(hr)){
		::OutputDebugString(TEXT("***Error - シーンの開始に失敗(TDirextGraphics9::BeginScene)"));
			return false;
	}

	// set camera
	D3DXMATRIX viewMat;
	D3DXVECTOR3 eyepos = D3DXVECTOR3(0,1,-5);
	D3DXVECTOR3 target = D3DXVECTOR3(0,0,0);
	D3DXVECTOR3 up = D3DXVECTOR3(0,1,0);
	
	::D3DXMatrixLookAtLH(&viewMat, &eyepos, &target, &up);
	FpD3dDevice->SetTransform(D3DTS_VIEW ,&viewMat);

	// set projection
	D3DXMATRIX projMat;
	RECT rec;
	::GetClientRect(FPresentParams.hDeviceWindow, &rec);
	::D3DXMatrixPerspectiveFovLH(&projMat,D3DXToRadian(60.f), (float)rec.right/ (float)rec.bottom,0.1f,100.0);
	FpD3dDevice->SetTransform(D3DTS_PROJECTION ,&projMat);

	// set Light
	D3DLIGHT9 light;
	light.Diffuse.r = 1.0f;
	light.Ambient.r = 1.0f;
	light.Specular.r = 1.0f;
	light.Type = D3DLIGHT_DIRECTIONAL;
	FpD3dDevice->SetLight( 0 , &light);
	FpD3dDevice->LightEnable( 0,TRUE);

	/*
	// set camera
	D3DXMATRIX viewmat;
	::D3DXMatrixLookAtLH(&viewmat,&D3DXVECTOR3(0,0,5),&D3DXVECTOR3(0,0,0),&D3DXVECTOR3(0,1,0));
	FpD3dDevice->SetTransform(D3DTS_VIEW, &viewmat);
	*/

	return true;
}


//--------------------------------------------------------
// end scene
void TDirectGraphics9::EndScene(void)
{
	assert( FpD3dDevice && TEXT("***Error - DxDevice9未初期化(TDirextGraphics9::EndScene)"));

	FpD3dDevice->EndScene();
}

//--------------------------------------------------------
// update frame
void TDirectGraphics9::UpdateFrame(void)
{
	assert( FpD3dDevice && TEXT("***Error - DxDevice9未初期化(TDirextGraphics9::UpdateFrame)"));

	HRESULT hr = FpD3dDevice ->  Present( NULL, NULL, NULL, NULL);
	if(FAILED(hr)){
		if(hr == D3DERR_DEVICENOTRESET){
			// if failed to update frame , reset device and try to recovery
			// write cord 
			this->Reset();
		}
	}
}

//--------------------------------------------------------
// change mode
bool TDirectGraphics9::ChangeMode(bool inWindowed)
{
	if(inWindowed){
		SetWindowLong(FPresentParams.hDeviceWindow, GWL_STYLE,
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE);
		::SetWindowPos(
			FPresentParams.hDeviceWindow,
			HWND_NOTOPMOST,
			FRectWindow.left,
			FRectWindow.top,
			FRectWindow.right-FRectWindow.left,
			FRectWindow.bottom-FRectWindow.top,
			SWP_SHOWWINDOW);
	}else{
		// ウィンドウの位置と大きさを保持する
		GetWindowRect(FPresentParams.hDeviceWindow, &FRectWindow);
		// ウィンドウのスタイルを設定する
		SetWindowLong(FPresentParams.hDeviceWindow, GWL_STYLE, WS_POPUP | WS_VISIBLE);
	}
	// プレゼンテーションパラメータを設定
	SetPresentParameters(inWindowed);

	return Reset();
}

//--------------------------------------------------------
// font for debug
void TDirectGraphics9::DrawString(LPCTSTR szStr, int iX, int iY, D3DXCOLOR col)
{
	RECT rect = { iX , iY , 0 , 0 };
	// calculate string size
	FpFont->DrawText(NULL, szStr, -1, &rect, DT_CALCRECT, NULL);
	// rendering
	RECT rectShadow = {rect.left+2, rect.top+2, rect.right+2, rect.bottom+2};
	FpFont->DrawText(NULL, szStr, -1, &rectShadow, DT_LEFT| DT_BOTTOM, D3DXCOLOR(0,0,0,1));
	FpFont->DrawText(NULL, szStr, -1, &rect, DT_LEFT| DT_BOTTOM, col);
}

//--------------------------------------------------------
// set viewport
void TDirectGraphics9::SetViewport ( const D3DVIEWPORT9 *pviewport )
{
#ifdef _DEBUG
	if(FpD3dDevice==NULL){
		::OutputDebugString(TEXT("***Error - Direct3DDevice9未初期化(SetViewport)"));
		return;
	}
#endif
	FpD3dDevice->SetViewport( pviewport);
}

//--------------------------------------------------------
// Sprite
bool TDirectGraphics9::BeginSprite(DWORD Flags)
{
	assert( FpD3dDevice && TEXT("***Error - DxDevice9未初期化(TDirextGraphics9::BeginSprite)"));
	assert( FpD3DXSprite && TEXT("***Error - FpD3DXSprite未初期化(TDirextGraphics9::BeginSprite)"));

	FpD3DXSprite->Begin(Flags);

	return true;
}
void TDirectGraphics9::EndSprite(void)
{
	FpD3DXSprite->End();
}

//--------------------------------------------------------
// clear all sprite
void TDirectGraphics9::ClearAllSprite(void)
{
	std::list<ISprite *>::iterator it;
	for(it=FpSpriteList.begin(); it!=FpSpriteList.end(); ++it){
		delete *it;
	}
	FpSpriteList.clear();
}

//--------------------------------------------------------
// create sprite
ISprite* TDirectGraphics9::CreateSpriteFormFile(LPCWSTR inFileName, D3DFORMAT inFormat, D3DCOLOR inColorKey)
{
	ISprite *pSprite;

	try{
		if(FpD3dDevice == NULL)
			throw TEXT("***Error - Direct3DDevice9未初期化");

		// create texture
		LPDIRECT3DTEXTURE9 pTexture = NULL;

		HRESULT hr = ::D3DXCreateTextureFromFileEx(
											FpD3dDevice,
											inFileName,
											D3DX_DEFAULT,
											D3DX_DEFAULT,
											1,
											0,
											inFormat,
											D3DPOOL_MANAGED,
											D3DX_FILTER_NONE,
											D3DX_DEFAULT,
											inColorKey,
											NULL,
											NULL,
											&pTexture);
		if(FAILED(hr)){
			throw TEXT("***Error - ファイルの読み込みに失敗");
		}
		pSprite = new TSprite( FpD3DXSprite, pTexture);
		pTexture->Release();

	}catch(...){
		::OutputDebugString(TEXT("***Error - Spriteの生成に失敗しました。(CreateSpriteFormFile"));	

		// if some exception happens, create null object
		pSprite = new TNullSprite();
	}
	FpSpriteList.push_back(pSprite);		// add to sprite list
	return pSprite;
}

//--------------------------------------------------------
// create simple shape
IMesh* TDirectGraphics9::CreateBox(const float inWidth, const float inHeight, const float inDepth )
{
#ifdef _DEBUG
	if(FpD3dDevice==NULL){
		::OutputDebugString(TEXT("***Error - Direct3DDevice9未初期化(CreateBox)"));
		return NULL;
	}
#endif
	IMesh* pShape;
	ID3DXMesh* pMesh = NULL;
	if(::D3DXCreateBox(FpD3dDevice, inWidth, inHeight, inDepth, &pMesh, NULL) == D3D_OK){
		pShape = new TMesh(FpD3dDevice, pMesh, 1);
	}else{
		::OutputDebugString(TEXT("***Error - 立方体の生成に失敗しました(CreateBox)"));
		pShape = new TNullMesh();
	}
	if(pMesh){
		pMesh->Release();
		pMesh = NULL;
	}
	FpMesh.push_back(pShape);
	return pShape;
}

//--------------------------------------------------------
IMesh* TDirectGraphics9::CreateCylinder(const float inRadius1, const float inRadius2,
	const float inLength, const UINT inSlices, const UINT inStacks )
{
#ifdef _DEBUG
	if(FpD3dDevice==NULL){
		::OutputDebugString(TEXT("***Error - Direct3DDevice9未初期化(CreateCylinder)"));
		return NULL;
	}
#endif
	IMesh* pShape;
	ID3DXMesh* pMesh = NULL;
	if(::D3DXCreateCylinder(FpD3dDevice, inRadius1, inRadius2, inLength, inSlices, inStacks, &pMesh, NULL) == D3D_OK){
		pShape = new TMesh(FpD3dDevice, pMesh, 1);
	}else{
		::OutputDebugString(TEXT("***Error - 円柱の生成に失敗しました(CreateCylinder)"));
		pShape = new TNullMesh();
	}
	if(pMesh){
		pMesh->Release();
		pMesh = NULL;
	}
	FpMesh.push_back(pShape);
	return pShape;
}

//--------------------------------------------------------
IMesh* TDirectGraphics9::CreatePolygon(const float inLength, const UINT inSlides)
{
#ifdef _DEBUG
	if(FpD3dDevice==NULL){
		::OutputDebugString(TEXT("***Error - Direct3DDevice9未初期化(CreatePolygon)"));
		return NULL;
	}
#endif
	IMesh* pShape;
	ID3DXMesh* pMesh = NULL;
	if(::D3DXCreatePolygon(FpD3dDevice, inLength, inSlides, &pMesh, NULL) == D3D_OK){
		pShape = new TMesh(FpD3dDevice, pMesh, 1);
	}else{
		::OutputDebugString(TEXT("***Error - ポリゴンの生成に失敗しました(CreatePolygon)"));
		pShape = new TNullMesh();
	}
	if(pMesh){
		pMesh->Release();
		pMesh = NULL;
	}
	FpMesh.push_back(pShape);
	return pShape;
}

//--------------------------------------------------------
IMesh* TDirectGraphics9::CreateSphere(const float inRadius, const UINT inSlices, const UINT inStacks)
{
#ifdef _DEBUG
	if(FpD3dDevice==NULL){
		::OutputDebugString(TEXT("***Error - Direct3DDevice9未初期化(CreateSphere)"));
		return NULL;
	}
#endif
	IMesh* pShape;
	ID3DXMesh* pMesh = NULL;
	if(::D3DXCreateSphere(FpD3dDevice, inRadius, inSlices, inStacks, &pMesh, NULL) == D3D_OK){
		pShape = new TMesh(FpD3dDevice, pMesh, 1);
	}else{
		::OutputDebugString(TEXT("***Error - 球の生成に失敗しました(CreateSphere)"));
		pShape = new TNullMesh();
	}
	if(pMesh){
		pMesh->Release();
		pMesh = NULL;
	}
	FpMesh.push_back(pShape);
	return pShape;
}

//--------------------------------------------------------
IMesh* TDirectGraphics9::CreateTorus(const float inInnerRadius, const float inOuterRadius,
	const UINT inSlides, const UINT inRings)
{
#ifdef _DEBUG
	if(FpD3dDevice==NULL){
		::OutputDebugString(TEXT("***Error - Direct3DDevice9未初期化(CreateTorus)"));
		return NULL;
	}
#endif
	IMesh* pShape;
	ID3DXMesh* pMesh = NULL;
	if(::D3DXCreateTorus(FpD3dDevice, inInnerRadius, inOuterRadius, inSlides, inRings, &pMesh, NULL) == D3D_OK){
		pShape = new TMesh(FpD3dDevice, pMesh, 1);
	}else{
		::OutputDebugString(TEXT("***Error - Torusの生成に失敗しました(CreateTorus)"));
		pShape = new TNullMesh();
	}
	if(pMesh){
		pMesh->Release();
		pMesh = NULL;
	}
	FpMesh.push_back(pShape);
	return pShape;
}

//--------------------------------------------------------
IMesh* TDirectGraphics9::CreateTeapot(void)
{
#ifdef _DEBUG
	if(FpD3dDevice==NULL){
		::OutputDebugString(TEXT("***Error - Direct3DDevice9未初期化(CreateTeapot)"));
		return NULL;
	}
#endif
	IMesh* pShape;
	ID3DXMesh* pMesh = NULL;
	if(::D3DXCreateTeapot(FpD3dDevice, &pMesh, NULL) == D3D_OK){
		pShape = new TMesh(FpD3dDevice, pMesh, 1);
	}else{
		::OutputDebugString(TEXT("***Error - Torusの生成に失敗しました(CreateTeapot)"));
		pShape = new TNullMesh();
	}
	if(pMesh){
		pMesh->Release();
		pMesh = NULL;
	}
	FpMesh.push_back(pShape);
	return pShape;
}

//--------------------------------------------------------
void TDirectGraphics9::ReleaseMesh(IMesh* &pMesh)
{
	if(pMesh){
		FpMesh.remove(pMesh);
		delete pMesh;
		pMesh = NULL;
	}
}

//--------------------------------------------------------
void TDirectGraphics9::ReleaseAllMeshes(void)
{
	for(std::list<IMesh*>::iterator it = FpMesh.begin(); it!= FpMesh.end(); it++){
		delete (*it);
	}
	FpMesh.clear();
}

IVertexBuffer* TDirectGraphics9::CreateVertexBuffer(const UINT inSize, const DWORD inFVF, const UINT inStride)
{
#ifdef _DEBUG
	if(FpD3dDevice == NULL){
		::OutputDebugString(TEXT("***Error - Direct3DDevice9未初期化(CreateVertexBuffer)"));
		return NULL;
	}
#endif
	// create vertext buffer
	IVertexBuffer *pVertex;
	LPDIRECT3DVERTEXBUFFER9 pBuffer;

	if(FpD3dDevice->CreateVertexBuffer(inSize, 0, inFVF, D3DPOOL_MANAGED, &pBuffer, NULL)==D3D_OK){
		pVertex = new TVertexBuffer(FpD3dDevice, pBuffer, inFVF, inStride);
	}else{
		::OutputDebugString(TEXT("***Error - 頂点バッファ生成に失敗(CreateVertexBuffer)"));
		pVertex = new TNullVertexBuffer();
	}
	if(pBuffer) pBuffer->Release(); pBuffer = NULL;
	FVertextBuffer.push_back(pVertex);
	return pVertex;
}


void TDirectGraphics9::ReleaseVertexBuffer(IVertexBuffer* &pBuffer)
{
	if(pBuffer){
		FVertextBuffer.remove(pBuffer);
		delete pBuffer;
		pBuffer = NULL;
	}
}

void TDirectGraphics9::ReleaseAllVertexBuffers()
{
	for(std::list<IVertexBuffer*>::iterator it = FVertextBuffer.begin(); it!= FVertextBuffer.end(); it++){
		delete (*it);
	}
	FVertextBuffer.clear();
}

void TDirectGraphics9::SetLight(DWORD inIndex, const D3DLIGHT9 & inLight, BOOL inEnable)
{
#ifdef DEBUG
	if(FpD3dDevice == NULL)
	{
		::OutputDebugString(TEXT("***Error - Direct3DDeveice初期化に失敗(SetLight)");
		return;
	}
#endif
	FpD3dDevice-> SetLight(inIndex, &inLight);
	FpD3dDevice-> LightEnable(inIndex, inEnable);
	FLightIndex.insert(inIndex);
}

void TDirectGraphics9::ClearAllLights(void)
{
#ifdef DEBUG
	if(FpD3dDevice == NULL)
	{
		return;
	}
#endif
	D3DLIGHT9 light;
	::ZeroMemory(&light,sizeof(light));

	std::set<DWORD>::iterator it;
	for(it = FLightIndex.begin(); it != FLightIndex.end(); it++)
	{
		FpD3dDevice-> LightEnable(*it, FALSE);
		FpD3dDevice-> SetLight(*it, &light);
	}
	FLightIndex.clear();
}

void TDirectGraphics9::LightEnable(DWORD inIndex, BOOL inEnable)
{
#ifdef DEBUG
	if(FpD3dDevice == NULL)
	{
		::OutputDebugString(TEXT("***Error - Direct3DDeveice初期化に失敗(SetLight)");
		return;
	}
#endif
	FpD3dDevice-> LightEnable(inIndex, inEnable);
}
