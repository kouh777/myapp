#include <Windows.h>
#include <stdio.h>
#include <TCHAR.h>
#include <time.h>

//---------------------------------------------
#include "Cgdi.h"
#include "GameWorld.h"

//---------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static HDC BackBufferDC;	//�@���񃁃�����������Ȃ�����
	static HBITMAP hBitmap, hOldBitmap;
	static RECT rect;

	switch(message){

		case WM_CREATE:
			GetClientRect( hWnd, &rect);

			hdc = GetDC(hWnd);
			BackBufferDC = ::CreateCompatibleDC(hdc);

			hBitmap = ::CreateCompatibleBitmap( hdc, rect.right,rect.bottom);
			hOldBitmap = (HBITMAP)SelectObject( BackBufferDC, hBitmap);

			::ReleaseDC( hWnd, hdc);
			GameWorld().Initialize(hWnd, rect.right, rect.bottom);

			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hWnd,&ps);
			BitBlt( BackBufferDC,0,0,rect.right,rect.bottom,NULL,0,0,BLACKNESS);	//�@�o�b�N�o�b�n���N���A����
			Cgdi().StartDrawing(BackBufferDC);
			GameWorld().Draw();														// �`��
			Cgdi().StopDrawing(BackBufferDC);

			//�@�E�B���h�E�ɓ]��
			BitBlt( hdc,0,0,rect.right,rect.bottom,BackBufferDC,0,0,SRCCOPY);
			EndPaint(hWnd,&ps);

			return 0;

		case WM_DESTROY:
			SelectObject(BackBufferDC,hOldBitmap);
			DeleteObject(hBitmap);
			::PostQuitMessage(0);
			return 0;

	}
	GameWorld().MessageHandle(message, wParam, lParam);
	return DefWindowProc(hWnd, message,wParam,lParam);
}

//---------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR szCmdLine,
					int CmdShow)
{
	WNDCLASS wndclass;
	static TCHAR szClassName[]=TEXT("WINWINDOW");
	HWND hWnd;
	MSG msg;

	// register window class
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0 ;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject( WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szClassName;

	if(!RegisterClass(&wndclass)){
		return 0;
	} 
	

	// create window
	hWnd = CreateWindow( szClassName,			// �N���X��
						TEXT("WIN_15PUZZLE"),	// �L���v�V����
						WS_OVERLAPPEDWINDOW,	// �E�B��ǂ��X�^�C��
						0,			// X�ʒu
						0,			// Y�ʒu
						640,		// ��
						480,		// ����
						NULL,		// �e�E�B���h�E
						NULL,		// ���j���[
						hInstance,	// �C���X�^���X
						NULL);		// �p�����[�^

	// show window
	ShowWindow(hWnd,CmdShow);
	UpdateWindow(hWnd);

	// message loop
	do{
		if(PeekMessage(&msg,0,0,0,PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}else{
			// Idol
			// �Q�[�����[���h�@�X�V
			GameWorld().Excute(1);
			if(GameWorld().GetClear()){
				MessageBox(hWnd,
					TEXT("Congratulation!You Clear!"),
					TEXT("�I��"), MB_OK | MB_ICONINFORMATION);
				DestroyWindow(hWnd);  // �E�B���h�E��j��
			}
			::InvalidateRect( hWnd, NULL, FALSE);
		}
	}while(msg.message != WM_QUIT);{
	
	}

	return 0;
}