
#ifndef __INPUT_H__
#define __INPUT_H__

//--------------------------------------------------------------------------------
#define KEY_UP      (1<<0)       // 上
#define KEY_DOWN    (1<<1)       // 下
#define KEY_LEFT    (1<<2)       // 左
#define KEY_RIGHT   (1<<3)       // 右
#define KEY_Z       (1<<4)       // Ｚ
#define KEY_X       (1<<5)       // Ｘ
#define KEY_SPACE   (1<<6)       // SPACE

#define MOUSE_L     (1<<0)       // マウス左ボタン
#define MOUSE_R     (1<<1)       // マウス右ボタン

//--------------------------------------------------------------------------------
// for debug mode
#define KEY_C		(1<<7)		 // C
#define KEY_V		(1<<8)		 // V
#define KEY_A		(1<<9)		 // A
#define KEY_S		(1<<10)		 // S
#define KEY_D		(1<<11)		 // D
#define KEY_F		(1<<12)		 // F

//---------------------------------------------------------------------
class TInput
{
private:
	HWND	FhWnd;
	WORD	FRapidBuff;				// 連射
	WORD	FHalfRapidBuff;			// 半自動連射
	BOOL	FHalfRapidFlag;			// 自動/半自動連射切り替えフラグ
	

private:
	TInput( void );

	TInput( const TInput & );
	TInput &operator =( const TInput & );

public:
	~TInput( void ) {}

	static TInput &GetInstance( void ) {
		static TInput instance;
		return instance;
	}

	void Update( void );
	
	void Initalize( HWND hWnd );

public:
	WORD	JoystickBuff;			// 現在のジョイスティックの状態
	WORD	KeyInputBuff;			// 現在のキーボード入力をまとめたもの
	WORD	InputBuff;				// 使用頻度の高いキーをまとめたもの
	WORD	DownInputBuff;			// キーＯＮ時にフラグが立つ
	WORD	UpInputBuff;			// キーＯＦＦ時にフラグが立つ
	POINT	MousePos;				// マウス位置
	BYTE	MouseButton;			// マウスのボタン

	

};

//---------------------------------------------------------------------
inline TInput &Input( void ) { return TInput::GetInstance(); }

//---------------------------------------------------------------------
#endif	// __INPUT_H__