#ifndef __GAMEWORLD_H_
#define __GAMEWORLD_H_

//---------------------
#include "SubSystem.h"

//---------------------
#define RECTSIZE 100
#define FONTSIZE 30

#define KEYLEFT 0
#define KEYRIGHT 1
#define KEYUP 2
#define KEYDOWN 3
#define NOKEY 4
#define GAMECLEAR 1

#define SHUFNUM 20


// ゲームを管理する唯一のクラス
class TGameWorld{
private:
	TGameWorld(void);
	TGameWorld(const TGameWorld &);
	TGameWorld operator = (const TGameWorld &);
	HWND FhWnd;
	int FiClientX;
	int FiClientY;
	int pos;

	// 計算
	int	Can_Move;		// 移動可能なマスの数字を格納
	int	up_judge;		// 上に移動できるかの判定
	int	down_judge;		// 下に移動できるかの判定
	int	right_judge;	// 右に移動できるかの判定
	int	left_judge;		// 左に移動できるかの判定
	int	move_direct;
	int	move_to;

	int	GetKey;
	int	cnt;
	int	count;

	bool shuf;			// シャッフルのフラグ
	int	 inv;			// 転倒値
	int	 CountSWap;		// スワップ制限を設ける

	TCHAR str[16];
	bool clear;

public:
	~TGameWorld(void);
	static TGameWorld &GetInstance(void){
		static TGameWorld instance;			// 唯一のインスタンス
		return instance;
	}
	bool Initialize(HWND hWnd,int cx, int cy);
	void Excute( double elapsed);			// 引数は経過時間
	void Draw(void);
	HRESULT MessageHandle( UINT message, WPARAM wParam, LPARAM lParam);

	//---------------------
	//-----------------------
	int data[16];
	bool GetClear(void){return clear;}
};

inline TGameWorld &GameWorld(void){return TGameWorld::GetInstance();} 

#endif //__GAMEWORLD_H_