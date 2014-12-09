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
	double FiTimer;		// シーン終了用アニメーション様態あー
	bool FbFadeFlg;		// フェイドフラグ
	bool FbSceneEndFlg;	// シーン終了アニメーション開始フラグ
	bool FbButtonFlg;	// 連続入力防止フラグ
	bool FbCursorFlg;	// カーソル出現フラグ

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
	void ButtonDownSelect(void);	// [↑]キー処理
	void ButtonUpSelect(void);		// [↓]キー処理
	TBaseMovingObject *GetSelectingBtn(void);	// 選択中のボタンのポジションを返す

	// 画像リソース
	ISprite *FpBackGround;
	ISprite *FpLogo;
	ISprite	*FpBtnStg1;		// ステージ1ボタン
	ISprite	*FpBtnStg2;		// ステージ2ボタン
	ISprite	*FpBtnStg3;		// ステージ3ボタン
	ISprite	*FpBtnStg4;		// ステージ4ボタン
	ISprite	*FpBtnStg5;		// ステージ5ボタン
	ISprite	*FpBtnReward;	// 戦果報酬ボタン
	ISprite *FpBtnCursor;	// カーソル
	ISprite *FpBtnShion;	// 男主人公ボタン
	ISprite *FpBtnShionS;	// 男主人公ボタン(選択中)
	ISprite *FpBtnKanata;	// 女主人公ボタン
	ISprite *FpBtnKanataS;	// 女主人公ボタン(選択中)

	// アクセサ
	__declspec( property(get=GetiClientX) ) int iClientX;
	int GetiClientX( void ) const { return FiClientX; }

	__declspec( property(get=GetiClientY) ) int iClientY;
	int GetiClientY( void ) const { return FiClientY; }

};

#endif //__TSCENNSTAGESELECT_H__