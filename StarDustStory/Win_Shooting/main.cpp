
#include "GameDef.h"
#include "GameWorld.h"
#include <TCHAR.h>

//--------------------------------------------------------------------------------
#include "DirectGraphics9.h"
#include "DirectWrite.h"
#include "BackBuffer.h"

//--------------------------------------------------------------------------------
#define WINDOW_W 800
#define WINDOW_H 600

BOOL g_inWindowed = true;

//--------------------------------------------------------------------------------
#pragma comment(lib, "winmm.lib")

TCHAR FpsString[0xFF]=TEXT("FPS=00");

//--------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, 
							WPARAM wParam, LPARAM lParam )
{
	static RECT clientRect;

	switch( message ) {

		case WM_CREATE:
			GetClientRect( hWnd, &clientRect );

			// DirectX　初期化
			DxGraphics9().Initialize(hWnd,true);
			// DirectWrite 初期化
			DxWrite().Initialize(hWnd,true);
			// ゲームワールド　初期化
			GameWorld().Initialize( hWnd, clientRect.right, clientRect.bottom );
			// インプット　初期化
			Input().Initalize( hWnd );
			return 0;

		case WM_SYSKEYDOWN:
			switch(wParam){
				case VK_RETURN:
					if(GetKeyState(VK_MENU)){
						g_inWindowed = !g_inWindowed;
						DxGraphics9().ChangeMode(g_inWindowed);
					}
			}
			return 0;

		case WM_KEYDOWN:
			if(wParam == VK_ESCAPE )
				PostMessage(hWnd,WM_CLOSE, 0, 0);
			return 0;

		case WM_DESTROY:
			// 終了処理
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProc( hWnd, message, wParam, lParam );
}

//--------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance, 
					HINSTANCE hPrevInstance,
					LPSTR szCmdLine,
					int CmdShow )
{
	WNDCLASS wndclass;
	static TCHAR szClassName[] = TEXT("WIN_WINDOW");
	HWND hWnd;
	MSG msg;
	

	//register window class 
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc	= WndProc;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= hInstance;
	wndclass.hIcon			= LoadIcon( hInstance, IDI_APPLICATION );
	wndclass.hCursor		= LoadCursor( NULL, IDC_ARROW );
	wndclass.hbrBackground	= (HBRUSH)GetStockObject( WHITE_BRUSH );
	wndclass.lpszMenuName	= NULL;
	wndclass.lpszClassName	= szClassName;

	if( !RegisterClass( &wndclass ) ) return 0;

	// create window	
	int fx = GetSystemMetrics(SM_CXFIXEDFRAME) * 2;									// フレームの大きさ
//	int fy = GetSystemMetrics(SM_CYFIXEDFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU);
	int fy = GetSystemMetrics(SM_CYFIXEDFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);
	int x = GetSystemMetrics(SM_CXFULLSCREEN);	// フルスクリーンの大きさ
	int y = GetSystemMetrics(SM_CYFULLSCREEN);

	hWnd = CreateWindow( szClassName, 											// クラス名
						TEXT("WIN_SPACEWAR"), 									// キャプション
						WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX|WS_THICKFRAME),	// ウィンドウスタイル
						(x-fx-WINDOW_W)/2,										// X位置
						(y-fy-WINDOW_H)/2,										// Y位置
						fx+WINDOW_W, 											// 幅	
						fy+WINDOW_H, 											// 高さ
						NULL, 													// 親ウィンドウ
						NULL, 													// メニュー
						hInstance, 												// インスタンス
						NULL );													// パラメータ

	// show window
	ShowWindow( hWnd, CmdShow );
	UpdateWindow( hWnd );


	// message loop
	do {
		if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) ) {
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		} else {
			// Idol
			const	double FPS = 1 / 60.0;
			static	DWORD frames = 1;
			static	DWORD beforeTime = timeGetTime();
			DWORD	nowTime, progress;
			DWORD	idealTime = (DWORD)(frames * (1000/60.0));

			// clear
			DxGraphics9().Clear(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x202020FF);
			if(DxGraphics9().BeginScene()){
				//--------------------------------------------------------
				// draw

				// sprite
				DxGraphics9().BeginSprite(D3DXSPRITE_ALPHABLEND);
				// draw sprite between BeginSprite() and EndSprite()
				GameWorld().Draw();

				DxGraphics9().EndSprite();
				
				// draw debug string
				DxGraphics9().DrawString(FpsString, 10, 10 ,D3DXCOLOR(1.0,1.0,1.0,1.0));

				// Input Update
				Input().Update();
				// Update GameWorld
				GameWorld().Execute(FPS);
				DxGraphics9().EndScene();
			}

			// この後にGetDCを入れてWINAPIの描画を入れる	RenderCgdi(void)を他の全クラスに追加した方がいいか？
			TBackBuffer *FpBackBuffer;					// instance
			FpBackBuffer = new TBackBuffer(DxGraphics9().GetDevice());
			HDC FhDC = FpBackBuffer->GetDC();			// HDCを取得

			Cgdi().StartDrawing(FhDC);
			GameWorld().DrawCgdi();
			Cgdi().StopDrawing(FhDC);
//			DxWrite().DrawD2DContent();
			FpBackBuffer->ReleaseDC();					// HDCを解放

			// updaate frame
			DxGraphics9().UpdateFrame();

			// sleep
			nowTime = timeGetTime();
			progress = nowTime-beforeTime;
			if(idealTime > progress) Sleep(idealTime-progress);
			if(progress >= 1000){
				// passed one second
				beforeTime = nowTime;

				// display only in debug mode
				_stprintf_s(FpsString, 0xFF, TEXT("FPS=%d\n"),frames);
#ifdef _DEBUG
				::OutputDebugString(FpsString);
#endif
				frames = 0;
			}

			frames++;
		}
	} while( msg.message != WM_QUIT );

	return 0;
}


//--------------------------------------------------------