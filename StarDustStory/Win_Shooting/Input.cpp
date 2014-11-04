
#include "GameDef.h"

//---------------------------------------------------------------------
TInput::TInput( void )
	: FhWnd(NULL)
{
}

//---------------------------------------------------------------------
void TInput::Initalize( HWND hWnd )
{
	FhWnd = hWnd; 
}

//---------------------------------------------------------------------
void TInput::Update( void )
{
	static DWORD rapidCnt[6] = {0};
	static BYTE KeyboardBuff[256];    // 現在のキーボード状態
	JOYINFO joyinfo;
	WORD BeforeInputBuff;

	// キー情報を取得
    BeforeInputBuff = InputBuff;        // １フレーム前のキー状態を保存
    GetKeyboardState( KeyboardBuff );     // キーボード情報の取得
    KeyInputBuff = 0;
    if( KeyboardBuff[VK_UP]   & 0x80 ) KeyInputBuff |= KEY_UP;
    if( KeyboardBuff[VK_DOWN] & 0x80 ) KeyInputBuff |= KEY_DOWN;
    if( KeyboardBuff[VK_LEFT] & 0x80 ) KeyInputBuff |= KEY_LEFT;
    if( KeyboardBuff[VK_RIGHT]& 0x80 ) KeyInputBuff |= KEY_RIGHT;
    if( KeyboardBuff[ 'Z' ]   & 0x80 ) KeyInputBuff |= KEY_Z;
    if( KeyboardBuff[ 'X' ]   & 0x80 ) KeyInputBuff |= KEY_X;
	//----------------
	// for debug
	//----------------
	if( KeyboardBuff[ 'C' ]   & 0x80 ) KeyInputBuff |= KEY_C;
	if( KeyboardBuff[ 'V' ]   & 0x80 ) KeyInputBuff |= KEY_V;
	if( KeyboardBuff[ 'A' ]   & 0x80 ) KeyInputBuff |= KEY_A;
	if( KeyboardBuff[ 'S' ]   & 0x80 ) KeyInputBuff |= KEY_S;
	if( KeyboardBuff[ 'D' ]   & 0x80 ) KeyInputBuff |= KEY_D;
	if( KeyboardBuff[ 'F' ]   & 0x80 ) KeyInputBuff |= KEY_F;

	//---------------
	if( KeyboardBuff[VK_SPACE]& 0x80 ) KeyInputBuff |= KEY_SPACE;

    // ジョイスティックの情報を取得
    JoystickBuff = 0;
    if( !joyGetPos( JOYSTICKID1, &joyinfo) ) {
        if( joyinfo.wYpos   == 0     ) JoystickBuff |= KEY_UP;
        if( joyinfo.wYpos   == 65535 ) JoystickBuff |= KEY_DOWN;
        if( joyinfo.wXpos   == 0     ) JoystickBuff |= KEY_LEFT;
        if( joyinfo.wXpos   == 65535 ) JoystickBuff |= KEY_RIGHT;
        if( joyinfo.wButtons & 0x01  ) JoystickBuff |= KEY_Z;
        if( joyinfo.wButtons & 0x02  ) JoystickBuff |= KEY_X;
		if( joyinfo.wButtons & 0x200 ) JoystickBuff |= KEY_SPACE;
    }

	// ジョイスティックとキーボードの入力を合成
    InputBuff = JoystickBuff | KeyInputBuff;

    // 入力のON/OFFを算出
	DownInputBuff  =  InputBuff & ~BeforeInputBuff;
    UpInputBuff    = ~InputBuff &  BeforeInputBuff;

	// マウス情報を取得
	POINT mouse_pos; 
    GetCursorPos( &mouse_pos );
    ScreenToClient( FhWnd, &mouse_pos );         // クライアント座標へ変換

    MousePos.x = mouse_pos.x;
    MousePos.y = mouse_pos.y;

    MouseButton = 0;
    if( KeyboardBuff[VK_LBUTTON] & 0x80) MouseButton |= MOUSE_L;
    if( KeyboardBuff[VK_RBUTTON] & 0x80) MouseButton |= MOUSE_R;
}


//---------------------------------------------------------------------