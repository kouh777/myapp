
//--------------------------------------------------------
#include "GameDef.h"
#include "sceneStageSelect.h"
#include "cgdi.h"
#include "sceneGame.h"
#include "sceneFade.h"
#include "BaseMovingObject.h"

//--------------------------------------------------------
// �X�e�[�W�{�^��
#include "uiBtnStg1.h"		// �X�e�[�W1�{�^��
#include "uiBtnStg2.h"		// �X�e�[�W2�{�^��
#include "uiBtnStg3.h"		// �X�e�[�W3�{�^��
#include "uiBtnStg4.h"		// �X�e�[�W4�{�^��
#include "uiBtnStg5.h"		// �X�e�[�W5�{�^��
#include "uiBtnShion.h"		// �j��l���{�^��
#include "uiBtnKanata.h"	// ����l���{�^��

//--------------------------------------------------------
// UI�I�u�W�F�N�g
#include "uiCursor.h"	// �J�[�\��

//--------------------------------------------------------
#define BACKGROUND_X 0			// �w�i�摜�z�uX���W
#define BACKGROUND_Y 0			// �w�i�摜�z�uY���W
#define BACKGROUND_WIDTH 800	// �w�i�摜�؂���T�C�Y ��
#define BACKGROUND_HEIGHT 600	// �w�i�摜�؂���T�C�Y �c

//--------------------------------------------------------
TsceneStageSelect::TsceneStageSelect(void):
	_Task(6),
	FiTimer(1),
	FbFadeFlg(FALSE),
	FiClientX(0),
	FiClientY(0),
	FbButtonFlg(FALSE),
	FbSceneEndFlg(FALSE),
	FbCursorFlg(FALSE)
{
	Initialize();
}

//--------------------------------------------------------
TsceneStageSelect::~TsceneStageSelect(void)
{
	{
		// �{�^��
		std::vector< TBaseMovingObject * >::iterator it;
		for( it=FpButtons.begin(); it!=FpButtons.end(); it++ ) {
			delete *it;
		}
		FpButtons.clear();
	}

	{
		// UI
		std::vector< TBaseMovingObject * >::iterator it;
		for( it=FpUis.begin(); it!=FpUis.end(); it++ ) {
			delete *it;
		}
		FpUis.clear();
	}
}


//------------------------------------------
// �������֐�
bool TsceneStageSelect::Initialize( void )
{

	FhWnd = TaskManager().GethWnd();
	FiClientX = TaskManager().GetiClientX();
	FiClientY = TaskManager().GetiClientY();

	// �摜���������ɓǂݍ���
	FpBackGround = DxGraphics9().CreateSpriteFormFile(TEXT("stage_select_back.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 255, 0, 0));
	FpBtnStg1 = DxGraphics9().CreateSpriteFormFile(TEXT("btn_stg1.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 255, 0, 0));
	FpBtnStg2 = DxGraphics9().CreateSpriteFormFile(TEXT("btn_stg2.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 255, 0, 0));
	FpBtnStg3 = DxGraphics9().CreateSpriteFormFile(TEXT("btn_stg3.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 255, 0, 0));
	FpBtnStg4 = DxGraphics9().CreateSpriteFormFile(TEXT("btn_stg4.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 255, 0, 0));
	FpBtnStg5 = DxGraphics9().CreateSpriteFormFile(TEXT("btn_stg5.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 255, 0, 0));
	FpBtnReward = DxGraphics9().CreateSpriteFormFile(TEXT("btn_rewards.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 255, 0, 0));
	FpBtnCursor = DxGraphics9().CreateSpriteFormFile(TEXT("btn_cursor.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 255, 0, 0));
	FpBtnKanata = DxGraphics9().CreateSpriteFormFile(TEXT("kanata_btn_selected.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 255, 0, 0));
	FpBtnKanataS = DxGraphics9().CreateSpriteFormFile(TEXT("kanata_btn_selected.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 255, 0, 0));
	FpBtnShion = DxGraphics9().CreateSpriteFormFile(TEXT("shion_btn_normal.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 255, 0, 0));
	FpBtnShionS = DxGraphics9().CreateSpriteFormFile(TEXT("shion_btn_selected.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 255, 0, 0));

	// �{�^���쐬
	CreateButton(UI_BTN_STG_1,Vector2D(-20,-20),Vector2D(0,0));
	CreateButton(UI_BTN_STG_2,Vector2D(-20,-10),Vector2D(0,0));
	CreateButton(UI_BTN_STG_3,Vector2D(-20,0),Vector2D(0,0));
	CreateButton(UI_BTN_STG_4,Vector2D(-20,10),Vector2D(0,0));
	CreateButton(UI_BTN_STG_5,Vector2D(-20,20),Vector2D(0,0));
	CreateButton(UI_BTN_SHION,Vector2D(20,-20),Vector2D(0,0));
	CreateButton(UI_BTN_KANATA,Vector2D(20,20),Vector2D(0,0));
	return true;
}

//--------------------------------------------------------
bool TsceneStageSelect::Execute( double ElapsedTime)
{
	
	WORD inputBuff = Input().InputBuff;
	WORD DowninputBuff = Input().DownInputBuff;
	WORD UpInputBuff = Input().UpInputBuff;

	// [��]
	if( inputBuff & KEY_DOWN && !FbButtonFlg ){
		ButtonDownSelect();
		FbButtonFlg = TRUE;

		if( !FbCursorFlg ){
			// �J�[�\���̍쐬
			CreateUi(UI_CUR,Vector2D(-20,-20),Vector2D(0,0));
			FbCursorFlg = TRUE;
		}
	}
	// [��]
	if( inputBuff & KEY_UP && !FbButtonFlg ){
		ButtonUpSelect();
		FbButtonFlg = TRUE;

		if( !FbCursorFlg ){
			// �J�[�\���̍쐬
			CreateUi(UI_CUR,Vector2D(-20,-20),Vector2D(0,0));
			FbCursorFlg = TRUE;
		}

	}
	// �L�[�̘A�����̖͂h�~
	if( UpInputBuff && FbButtonFlg ){
		FbButtonFlg = FALSE;
	}

	{	// �{�^��
		std::vector< TBaseMovingObject * >::iterator it;

		for( it=FpButtons.begin(); it!=FpButtons.end(); it++ ) {
			(*it)->Update(ElapsedTime);
		}
	}

	{	// UI
		std::vector< TBaseMovingObject * >::iterator it;
		for( it=FpUis.begin(); it!=FpUis.end(); it++ ) {
			(*it)->Update(ElapsedTime);
		}
	}
	// �V�[���G���h����:Z�L�[�Ō��肷��
	if( inputBuff & KEY_Z && !FbSceneEndFlg ){
		FbSceneEndFlg = TRUE;
	}
	// �V�[���G���h����
	if(FbSceneEndFlg){
		FiTimer -= ElapsedTime;
		if(FiTimer <= 0){
			if(FbFadeFlg == FALSE){
				new TsceneFade();
				FbFadeFlg = TRUE;
				::OutputDebugString(TEXT("new fade\n"));
			}
		}
		if(FiTimer <= -2.0){
			TobjUi *ui = NULL;
			ui = (TobjUi*)GetSelectingBtn();
			new TsceneGame( PL_GRANDVISOR, ui->StgId );
			return false;
		}
	}
	return true;
}

//--------------------------------------------------------
void TsceneStageSelect::Draw(void)
{
	// �w�i�`�� �S�̂𖄂ߌ�����
	RECT FrSrcRec = {0 , 0 , BACKGROUND_WIDTH , BACKGROUND_HEIGHT}; 	// �摜�̒�����؂�����W
	FpBackGround->Render(&FrSrcRec, D3DXVECTOR3( (float)BACKGROUND_X,(float)BACKGROUND_Y, 0), 1.f);

	{	// �{�^��
		std::vector< TBaseMovingObject * >::iterator it;
		for( it=FpButtons.begin(); it!=FpButtons.end(); it++ ) {
			(*it)->Render();
		}
	}

	{	// UI
		std::vector< TBaseMovingObject * >::iterator it;
		for( it=FpUis.begin(); it!=FpUis.end(); it++ ) {
			(*it)->Render();
		}
	}
}

//--------------------------------------------------------
void TsceneStageSelect::DrawCgdi(void)
{
	{	// �{�^��
		std::vector< TBaseMovingObject * >::iterator it;
		for( it=FpButtons.begin(); it!=FpButtons.end(); it++ ) {
			(*it)->RenderCgdi();
		}
	}

	{	// UI
		std::vector< TBaseMovingObject * >::iterator it;
		for( it=FpUis.begin(); it!=FpUis.end(); it++ ) {
			(*it)->RenderCgdi();
		}
	}
}

//------------------------------------------
// ���b�Z�[�W����
HRESULT TsceneStageSelect::MessageHandle( UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message ) {

		case WM_LBUTTONDOWN:

			return 0;
	}

	return 0;
}

//------------------------------------------
void TsceneStageSelect::ViewPortTransform( std::vector<Vector2D> &vPoints )
{
	double xs = FiClientX / 100.;
	double ys = FiClientY / 100.;

	// (   w/100      0  0 )
	// (   0      h/100  0 )
	// (   w/2      h/2  1 )
	for( DWORD i=0; i<vPoints.size(); i++ ) {
		vPoints[i].x = vPoints[i].x * xs + FiClientX/2.;  
		vPoints[i].y = vPoints[i].y * ys + FiClientY/2.;  
	}
}

//------------------------------------------
// �{�^���쐬
void TsceneStageSelect::CreateButton( const int &type, const Vector2D &pos, const Vector2D &velocity )
{
	TBaseMovingObject	*button;
	switch(type)
	{
		// �X�e�[�W1�{�^��
		case UI_BTN_STG_1:
			button = new TuiBtnStg1( this, pos, velocity );
			break;

		// �X�e�[�W2�{�^��
		case UI_BTN_STG_2:
			button = new TuiBtnStg2( this, pos, velocity );
			break;

		// �X�e�[�W3�{�^��
		case UI_BTN_STG_3:
			button = new TuiBtnStg3( this, pos, velocity );
			break;

		// �X�e�[�W4�{�^��
		case UI_BTN_STG_4:
			button = new TuiBtnStg4( this, pos, velocity );
			break;

		// �X�e�[�W5�{�^��
		case UI_BTN_STG_5:
			button = new TuiBtnStg5( this, pos, velocity );
			break;

		// ��ʕ�V�{�^��
		case UI_BTN_REW:
			button = new TuiBtnStg1( this, pos, velocity );
			break;


		// �j��l���{�^��
		case UI_BTN_SHION:
			button = new TuiBtnShion( this, pos, velocity );
			break;

		// ����l���{�^��
		case UI_BTN_KANATA:
			button = new TuiBtnKanata( this, pos, velocity );
			break;
	}
	FpButtons.push_back(button);
}

//------------------------------------------
// UI�I�u�W�F�N�g�쐬
void TsceneStageSelect::CreateUi( const int &type, const Vector2D &pos, const Vector2D &velocity )
{
	TBaseMovingObject	*ui;
	switch( type ){
		// �{�^���J�[�\��
		case UI_CUR:
			ui = new TuiCursor( this, pos, velocity );
			break;
	}
	FpUis.push_back(ui);
}

//------------------------------------------
// �u���v�L�[����
void TsceneStageSelect::ButtonDownSelect(void)
{
	// �����{�^�����I������Ă���΁A���̗v�f��I�����A�O�̗v�f�͑I�����Ă��Ȃ����Ƃɂ���
	{	// �{�^��
		std::vector< TBaseMovingObject * >::iterator it;
		for( it=FpButtons.begin(); it!=FpButtons.end();) {
			// �����{�^�����I������Ă����
			if( (*it)->bSelected != FALSE ){
				(*it)->bSelected = FALSE;
				it++;
				if( it != FpButtons.end() ){
					(*it)->bSelected = TRUE;
					break;
				}else{
					it = FpButtons.begin();
					(*it)->bSelected = TRUE;
					break;
				}
			}else{
				it++;
				// �S�Ẵ{�^�����I������Ă��Ȃ����
				if( it == FpButtons.end() ){
					// �X�e�[�W1�̃{�^����I������
					it = FpButtons.begin();
					(*it)->bSelected = TRUE;
					break;
				}
			}
		}
	}
}

//------------------------------------------
// �u���v�L�[����
void TsceneStageSelect::ButtonUpSelect(void)
{
	// �����{�^�����I������Ă���΁A���̗v�f��I�����A�O�̗v�f�͑I�����Ă��Ȃ����Ƃɂ���
	{	// �{�^��
		std::vector< TBaseMovingObject * >::reverse_iterator it;
		for( it=FpButtons.rbegin(); it!=FpButtons.rend();) {
			// �����{�^�����I������Ă����
			if( (*it)->bSelected != FALSE ){
				(*it)->bSelected = FALSE;
				it++;
				if( it != FpButtons.rend() ){
					(*it)->bSelected = TRUE;
					break;
				}else{
					it = FpButtons.rbegin();
					(*it)->bSelected = TRUE;
					break;
				}
			}else{
				it++;
				// �S�Ẵ{�^�����I������Ă��Ȃ����
				if( it == FpButtons.rend() ){
					// �X�e�[�W5�̃{�^����I������
					it = FpButtons.rbegin();
					(*it)->bSelected = TRUE;
					break;
				}
			}
		}
	}
}

// �I�𒆂̃{�^����Ԃ�
TBaseMovingObject* TsceneStageSelect::GetSelectingBtn(void)
{
	TBaseMovingObject *select_btn = NULL;
	if( FpButtons.empty() ){
		return select_btn;
	}else{
		std::vector<TBaseMovingObject *>::iterator it;
		for( it=FpButtons.begin(); it!=FpButtons.end(); it++ ){
			if( (*it)->bSelected ){
				select_btn = (*it);
			}
		}
	}
	return select_btn;
}