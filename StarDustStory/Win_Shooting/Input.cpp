
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
	static BYTE KeyboardBuff[256];    // ���݂̃L�[�{�[�h���
	JOYINFO joyinfo;
	WORD BeforeInputBuff;

	// �L�[�����擾
    BeforeInputBuff = InputBuff;        // �P�t���[���O�̃L�[��Ԃ�ۑ�
    GetKeyboardState( KeyboardBuff );     // �L�[�{�[�h���̎擾
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

    // �W���C�X�e�B�b�N�̏����擾
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

	// �W���C�X�e�B�b�N�ƃL�[�{�[�h�̓��͂�����
    InputBuff = JoystickBuff | KeyInputBuff;

    // ���͂�ON/OFF���Z�o
	DownInputBuff  =  InputBuff & ~BeforeInputBuff;
    UpInputBuff    = ~InputBuff &  BeforeInputBuff;

	// �}�E�X�����擾
	POINT mouse_pos; 
    GetCursorPos( &mouse_pos );
    ScreenToClient( FhWnd, &mouse_pos );         // �N���C�A���g���W�֕ϊ�

    MousePos.x = mouse_pos.x;
    MousePos.y = mouse_pos.y;

    MouseButton = 0;
    if( KeyboardBuff[VK_LBUTTON] & 0x80) MouseButton |= MOUSE_L;
    if( KeyboardBuff[VK_RBUTTON] & 0x80) MouseButton |= MOUSE_R;
}


//---------------------------------------------------------------------