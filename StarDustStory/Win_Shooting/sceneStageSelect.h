#ifndef __TSCENNSTAGESELECT_H__
#define __TSCENNSTAGESELECT_H__

//--------------------------------------------------------
#include "TaskManager.h"

//--------------------------------------------------------
class TBaseMovingObject;
class ISprite;

//--------------------------------------------------------
class TuibtnStg1;
class TuibtnStg2;
class TuibtnStg3;
class TuibtnStg4;
class TuibtnStg5;

//--------------------------------------------------------
class TsceneStageSelect: public _Task
{
private:
	HWND FhWnd;
	int FiClientX;
	int FiClientY;
	double FiTimer;		// �V�[���I���p�A�j���[�V�����l�Ԃ��[
	bool FbFadeFlg;		// �t�F�C�h�t���O
	bool FbSceneEndFlg;	// �V�[���I���A�j���[�V�����J�n�t���O
	bool FbButtonFlg;	// �A�����͖h�~�t���O
	bool FbCursorFlg;	// �J�[�\���o���t���O

	std::vector< TBaseMovingObject * > FpButtons;
	std::vector< TBaseMovingObject * > FpUis;

public:
	TsceneStageSelect();
	~TsceneStageSelect( void );
	bool Execute( double ElapsedTime);
	void Draw( void );
	void DrawCgdi(void);

	bool Initialize( void );
	HRESULT MessageHandle( UINT message, WPARAM wParam, LPARAM lParam );
	void ViewPortTransform( std::vector<Vector2D> &vPoints );
	void CreateButton( const int &type, const Vector2D &pos, const Vector2D &velocity );
	void CreateUi( const int &type, const Vector2D &pos, const Vector2D &velocity );
	void ButtonDownSelect(void);	// [��]�L�[����
	void ButtonUpSelect(void);		// [��]�L�[����
	TBaseMovingObject *GetSelectingBtn(void);	// �I�𒆂̃{�^���̃|�W�V������Ԃ�

	// �摜���\�[�X
	ISprite *FpBackGround;
	ISprite *FpLogo;
	ISprite	*FpBtnStg1;		// �X�e�[�W1�{�^��
	ISprite	*FpBtnStg2;		// �X�e�[�W2�{�^��
	ISprite	*FpBtnStg3;		// �X�e�[�W3�{�^��
	ISprite	*FpBtnStg4;		// �X�e�[�W4�{�^��
	ISprite	*FpBtnStg5;		// �X�e�[�W5�{�^��
	ISprite	*FpBtnReward;	// ��ʕ�V�{�^��
	ISprite *FpBtnCursor;	// �J�[�\��
	ISprite *FpBtnShion;	// �j��l���{�^��
	ISprite *FpBtnShionS;	// �j��l���{�^��(�I��)
	ISprite *FpBtnKanata;	// ����l���{�^��
	ISprite *FpBtnKanataS;	// ����l���{�^��(�I��)

	// �A�N�Z�T
	__declspec( property(get=GetiClientX) ) int iClientX;
	int GetiClientX( void ) const { return FiClientX; }

	__declspec( property(get=GetiClientY) ) int iClientY;
	int GetiClientY( void ) const { return FiClientY; }

};

#endif //__TSCENNSTAGESELECT_H__