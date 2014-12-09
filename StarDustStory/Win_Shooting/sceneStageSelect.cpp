
//--------------------------------------------------------
#include "GameDef.h"
#include "sceneStageSelect.h"
#include "cgdi.h"
#include "sceneGame.h"
#include "sceneFade.h"
#include "BaseMovingObject.h"

//--------------------------------------------------------
// ステージボタン
#include "uiBtnStg1.h"		// ステージ1ボタン
#include "uiBtnStg2.h"		// ステージ2ボタン
#include "uiBtnStg3.h"		// ステージ3ボタン
#include "uiBtnStg4.h"		// ステージ4ボタン
#include "uiBtnStg5.h"		// ステージ5ボタン
#include "uiBtnShion.h"		// 男主人公ボタン
#include "uiBtnKanata.h"	// 女主人公ボタン

//--------------------------------------------------------
// UIオブジェクト
#include "uiCursor.h"	// カーソル

//--------------------------------------------------------
#define BACKGROUND_X 0			// 背景画像配置X座標
#define BACKGROUND_Y 0			// 背景画像配置Y座標
#define BACKGROUND_WIDTH 800	// 背景画像切り取りサイズ 横
#define BACKGROUND_HEIGHT 600	// 背景画像切り取りサイズ 縦

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
		// ボタン
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
// 初期化関数
bool TsceneStageSelect::Initialize( void )
{

	FhWnd = TaskManager().GethWnd();
	FiClientX = TaskManager().GetiClientX();
	FiClientY = TaskManager().GetiClientY();

	// 画像をメモリに読み込む
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

	// ボタン作成
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

	// [↓]
	if( inputBuff & KEY_DOWN && !FbButtonFlg ){
		ButtonDownSelect();
		FbButtonFlg = TRUE;

		if( !FbCursorFlg ){
			// カーソルの作成
			CreateUi(UI_CUR,Vector2D(-20,-20),Vector2D(0,0));
			FbCursorFlg = TRUE;
		}
	}
	// [↑]
	if( inputBuff & KEY_UP && !FbButtonFlg ){
		ButtonUpSelect();
		FbButtonFlg = TRUE;

		if( !FbCursorFlg ){
			// カーソルの作成
			CreateUi(UI_CUR,Vector2D(-20,-20),Vector2D(0,0));
			FbCursorFlg = TRUE;
		}

	}
	// キーの連続入力の防止
	if( UpInputBuff && FbButtonFlg ){
		FbButtonFlg = FALSE;
	}

	{	// ボタン
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
	// シーンエンド条件:Zキーで決定する
	if( inputBuff & KEY_Z && !FbSceneEndFlg ){
		FbSceneEndFlg = TRUE;
	}
	// シーンエンド処理
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
	// 背景描画 全体を埋め撃つくす
	RECT FrSrcRec = {0 , 0 , BACKGROUND_WIDTH , BACKGROUND_HEIGHT}; 	// 画像の中から切り取る座標
	FpBackGround->Render(&FrSrcRec, D3DXVECTOR3( (float)BACKGROUND_X,(float)BACKGROUND_Y, 0), 1.f);

	{	// ボタン
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
	{	// ボタン
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
// メッセージ処理
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
// ボタン作成
void TsceneStageSelect::CreateButton( const int &type, const Vector2D &pos, const Vector2D &velocity )
{
	TBaseMovingObject	*button;
	switch(type)
	{
		// ステージ1ボタン
		case UI_BTN_STG_1:
			button = new TuiBtnStg1( this, pos, velocity );
			break;

		// ステージ2ボタン
		case UI_BTN_STG_2:
			button = new TuiBtnStg2( this, pos, velocity );
			break;

		// ステージ3ボタン
		case UI_BTN_STG_3:
			button = new TuiBtnStg3( this, pos, velocity );
			break;

		// ステージ4ボタン
		case UI_BTN_STG_4:
			button = new TuiBtnStg4( this, pos, velocity );
			break;

		// ステージ5ボタン
		case UI_BTN_STG_5:
			button = new TuiBtnStg5( this, pos, velocity );
			break;

		// 戦果報酬ボタン
		case UI_BTN_REW:
			button = new TuiBtnStg1( this, pos, velocity );
			break;


		// 男主人公ボタン
		case UI_BTN_SHION:
			button = new TuiBtnShion( this, pos, velocity );
			break;

		// 女主人公ボタン
		case UI_BTN_KANATA:
			button = new TuiBtnKanata( this, pos, velocity );
			break;
	}
	FpButtons.push_back(button);
}

//------------------------------------------
// UIオブジェクト作成
void TsceneStageSelect::CreateUi( const int &type, const Vector2D &pos, const Vector2D &velocity )
{
	TBaseMovingObject	*ui;
	switch( type ){
		// ボタンカーソル
		case UI_CUR:
			ui = new TuiCursor( this, pos, velocity );
			break;
	}
	FpUis.push_back(ui);
}

//------------------------------------------
// 「↓」キー処理
void TsceneStageSelect::ButtonDownSelect(void)
{
	// 何かボタンが選択されていれば、次の要素を選択し、前の要素は選択していないことにする
	{	// ボタン
		std::vector< TBaseMovingObject * >::iterator it;
		for( it=FpButtons.begin(); it!=FpButtons.end();) {
			// もしボタンが選択されていれば
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
				// 全てのボタンが選択されていなければ
				if( it == FpButtons.end() ){
					// ステージ1のボタンを選択する
					it = FpButtons.begin();
					(*it)->bSelected = TRUE;
					break;
				}
			}
		}
	}
}

//------------------------------------------
// 「↑」キー処理
void TsceneStageSelect::ButtonUpSelect(void)
{
	// 何かボタンが選択されていれば、次の要素を選択し、前の要素は選択していないことにする
	{	// ボタン
		std::vector< TBaseMovingObject * >::reverse_iterator it;
		for( it=FpButtons.rbegin(); it!=FpButtons.rend();) {
			// もしボタンが選択されていれば
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
				// 全てのボタンが選択されていなければ
				if( it == FpButtons.rend() ){
					// ステージ5のボタンを選択する
					it = FpButtons.rbegin();
					(*it)->bSelected = TRUE;
					break;
				}
			}
		}
	}
}

// 選択中のボタンを返す
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