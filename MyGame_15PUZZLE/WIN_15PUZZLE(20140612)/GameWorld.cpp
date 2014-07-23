#include <Windows.h>
#include <TCHAR.h>
#include <time.h>

#include "GameWorld.h"
#include "Cgdi.h"
#include "Vector2D.h"

//---------------------------
// コンストラクタ
TGameWorld::TGameWorld(void)
	:FhWnd(NULL),
	 FiClientX(0),
	 FiClientY(0),
	 inv(0),
	 shuf(false),
	 move_direct(0),
	 Can_Move(0),		// 移動可能なマスの数字を格納
	 up_judge(0),		// 上に移動できるかの判定
	 down_judge(0),		// 下に移動できるかの判定
	 right_judge(0),	// 右に移動できるかの判定
	 left_judge(0),		// 左に移動できるかの判定
	 move_to(0),		// 移動先のマスの場所
	 GetKey(NOKEY),
	 cnt(0),
	 count(0)
{
}

//---------------------------
// デストラクタ
TGameWorld::~TGameWorld(void){}

//---------------------------
// 初期化関数
bool TGameWorld::Initialize(HWND hWnd,int cx, int cy)
{
	FhWnd = hWnd;
	FiClientX = cx;
	FiClientY = cy;
	for(int i=0; i<16;++i){
		data[i]=i;
	}
	return true;
}

//---------------------------
// 実行関数
void TGameWorld::Excute( double elapsed)
{
	Can_Move=SpaceNum(data);			// 移動可能なマスの数字の位置を格納
	up_judge=Up_Judge(Can_Move);		// 上に移動できるかの判定
	down_judge=Down_Judge(Can_Move);	// 下に移動できるかの判定
	right_judge=Right_Judge(Can_Move);	// 右に移動できるかの判定
	left_judge=Left_Judge(Can_Move);	// 左に移動できるかの判定

	// キーボードでの移動判定
	if (GetKey != NOKEY){
		move_direct = Move_Judge(left_judge,right_judge,up_judge,down_judge,GetKey);
		move_to=Move_To(Can_Move,move_direct);
		Swap(Can_Move,move_to,data);	// 入れ替え処理
		GetKey = NOKEY;					// キー情報をクリア				
	}
	if(Clear_Judge(data,Can_Move)==GAMECLEAR){
		clear=true;						// ゲームクリア
	}
}

//---------------------------
// 描画関数
void TGameWorld::Draw(void)
{

	// 初期データを計算
	srand((unsigned)time(NULL));

	// ゲーム開始時にシャッフル
	while(shuf==false){
		for (int i=0; i < SHUFNUM; ++i){	// テストで10回シャッフル
			DoubleRand();
			RandSwap(data);
		}
		shuf=true;
	}

	//　描画
	for(int j=0; j<4; ++j){
		for(int i=0; i<4; ++i){
			cnt=i*4+j;
			if(data[cnt]==15){
				Cgdi().RedBrush();
			}else{
				Cgdi().BlueBrush();
			}
			// int型のdataの値を、tchar型の文字列に格納する
			//① sprintfを用い、int型のデータを文字列に変換(sprintfだとchar型の文字が返されうまくいかなかった)
			_stprintf_s(str,16,TEXT("%d"),data[cnt]);

			// 四角形描画
			Cgdi().Rectangle(RECTSIZE*j,RECTSIZE*i,RECTSIZE+RECTSIZE*j,RECTSIZE+RECTSIZE*i);

			// 文字の背景を透明に
			Cgdi().TransparentText();

			// 白抜きの文字にする
			if(data[cnt]==15){
				Cgdi().TextColor(255 , 255 , 255);
			}else{
				Cgdi().TextColor(0 , 0 , 0);
			}

			// 文字描画 一定座標の中にdata[i][j]の数字を表示
			Cgdi().TextOutAtPos(
				(j*RECTSIZE+j*RECTSIZE+RECTSIZE-FONTSIZE)/2,	// 描画開始位置(x座標)
				(i*RECTSIZE+i*RECTSIZE+RECTSIZE-FONTSIZE)/2,	
				str);
		}
	}
}

HRESULT TGameWorld::MessageHandle( UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message){
		case WM_LBUTTONDOWN:
			return 0;

		case WM_KEYDOWN:
			if (wParam == VK_LEFT){		// ← キー
				GetKey=KEYLEFT;
			}
			if(wParam == VK_RIGHT){	// → キー
				GetKey=KEYRIGHT;
			}
			if(wParam == VK_UP){		// ↑ キー
				GetKey=KEYUP;
			}
			if(wParam == VK_DOWN){		// ↓ キー
				GetKey=KEYDOWN;
			}
			return 0;

	}
	return 0;
}