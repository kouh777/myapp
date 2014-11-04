
#ifndef __INPUT_H__
#define __INPUT_H__

//--------------------------------------------------------------------------------
#define KEY_UP      (1<<0)       // ��
#define KEY_DOWN    (1<<1)       // ��
#define KEY_LEFT    (1<<2)       // ��
#define KEY_RIGHT   (1<<3)       // �E
#define KEY_Z       (1<<4)       // �y
#define KEY_X       (1<<5)       // �w
#define KEY_SPACE   (1<<6)       // SPACE

#define MOUSE_L     (1<<0)       // �}�E�X���{�^��
#define MOUSE_R     (1<<1)       // �}�E�X�E�{�^��

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
	WORD	FRapidBuff;				// �A��
	WORD	FHalfRapidBuff;			// �������A��
	BOOL	FHalfRapidFlag;			// ����/�������A�ː؂�ւ��t���O
	

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
	WORD	JoystickBuff;			// ���݂̃W���C�X�e�B�b�N�̏��
	WORD	KeyInputBuff;			// ���݂̃L�[�{�[�h���͂��܂Ƃ߂�����
	WORD	InputBuff;				// �g�p�p�x�̍����L�[���܂Ƃ߂�����
	WORD	DownInputBuff;			// �L�[�n�m���Ƀt���O������
	WORD	UpInputBuff;			// �L�[�n�e�e���Ƀt���O������
	POINT	MousePos;				// �}�E�X�ʒu
	BYTE	MouseButton;			// �}�E�X�̃{�^��

	

};

//---------------------------------------------------------------------
inline TInput &Input( void ) { return TInput::GetInstance(); }

//---------------------------------------------------------------------
#endif	// __INPUT_H__