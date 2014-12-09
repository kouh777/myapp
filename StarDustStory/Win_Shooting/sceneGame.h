#ifndef __TSCENEGAME_H__
#define __TSCENEGAME_H__

//--------------------------------------------------------
#include "GameDef.h"
#include "TaskManager.h"
#include <vector>

//--------------------------------------------------------
class TobjPlayer;
class TobjShot;
class TobjBullet;
class TobserverEnemy;
class TBaseMovingObject;

class ISprite;

//--------------------------------------------------------
// プレイヤー
class TplGranVisor;
class TplGransaber;

//--------------------------------------------------------
// 敵
class TenemBox;
class TenemFish;
class TenemBossFortress;
class TenemBossSpaceShip;
class TenemBossRightWing;
class TenemBossLeftWing;
class TenemBossBody;
class TenemBossDegin;
class TenemBossUnderson;
class TenemBossShadowSaber;
class TenemBossShadowVisor;
class TenemBossAlbert;
class TenemCommet;

//--------------------------------------------------------
// プレイヤー弾
class TshNormalShot;
class TshBeamShot;
class TshAimingShot;
class TshHomingShot;
class TshMultipleShot;
class TshMiniMultipleShot;
class TshBlastShot;
class TshBlast;

//--------------------------------------------------------
// 敵弾
class TbulOneWay;
class TbulHoming;
class TbulAiming;
class TbulWave;
class TbulWayAlong;

//------------------------------------------
// エフェクト
class TeffExplosion;
class TeffBarrier;
class TeffScope;
class TeffBigExplosion;
class TeffHit;
class TeffFInalBigExplosion;

//------------------------------------------
// 障害物

//------------------------------------------
// アイテム

//------------------------------------------
// Ui
class TuiCharacter;
class TuiPlayerVitality;
class TuiPlayerLife;

//--------------------------------------------------------
// 背景
class TBackGround;

//--------------------------------------------------------
// ゲームスクリプト
class TGameScript;

//--------------------------------------------------------
// ViewPort種類
enum VIEWPORT_KIND{
	GAME_VIEWPORT,
	STAGE_VIEWPORT,
	UI_VIEWPORT,
};

//--------------------------------------------------------
class TsceneGame: public _Task
{
private:
	HWND FhWnd;
	int FiClientX;
	int FiClientY;
	double FiTimer;
	STG_ID FStageId;
	int FiPlayerId;
	bool FbFadeFlg;
	bool FbOverFlg;
	DWORD FiLife;	// プレイヤー残機

	TobjPlayer *FpPlayer;
	std::list< TBaseMovingObject * > FpShots;
	std::list< TBaseMovingObject * > FpBullets;
	std::list< TBaseMovingObject * > FpEnemies;
	std::list< TBaseMovingObject * > FpEffects;
	std::list< TBaseMovingObject * > FpGimmicks;
	std::list< TBaseMovingObject * > FpItems;
	std::list< TBaseMovingObject * > FpUis;

	int FiCollapsedTime;
	TGameScript *FpGameScript;

	TBackGround *FpBackGround;

public:
	TsceneGame( int player_id, STG_ID stage_id );
	~TsceneGame( void );
	bool Execute( double ElapsedTime);
	void Draw( void );
	void DrawCgdi(void);

	bool Initialize( void );
	HRESULT MessageHandle( UINT message, WPARAM wParam, LPARAM lParam );
	void ViewPortTransform( std::vector<Vector2D> &vPoints );
	void ViewPortTransform( VIEWPORT_KIND kind, std::vector<Vector2D> &vPoints );
	//-----------------------
	// Create BaseMovingObject
	//-----------------------
	void CreateShot( const int &type, const Vector2D &pos, const Vector2D &velocity );
	void CreateEnemy( const int &type , const int &pattern , const Vector2D &pos, const Vector2D &velocity );
	void CreateBullet(const int &type, const Vector2D &pos, const Vector2D &velocity );
	void CreateEffect(const int &type, const Vector2D &pos, const Vector2D &velocity );
	void CreateGimmick(const int &type, const Vector2D &pos, const Vector2D &velocity );
	void CreateItem(const int &type, const Vector2D &pos, const Vector2D &velocity );
	void CreateUi(const int &type, const Vector2D &pos, const Vector2D &velocity );
	//-----------------------
	// Control GameScript
	//-----------------------
	void ScriptPause(void);			// スクリプトをポーズする
	void ScriptResume(void);		// スクリプトを再開する

	void Collision (double elapsedtime);
	const TBaseMovingObject *GetNearestEnemy(void);
	const TBaseMovingObject *GetNewestEnemy(void);	// return the newest Enemy
	// 3d test
	void Draw3D(void);

	// 画像リソース
	ISprite	*FpSprites;					// テスト用スプライト
	ISprite *FpBackGroundSprite;		// ゲーム背景
	ISprite *FpUiBackGround;			// UI背景
	ISprite *FpPlayerSprite;			// プレイヤー(テストで)
	ISprite *FpShotSprite;				// 弾
	ISprite *FpEnemySprite;				// 敵
	ISprite *FpPlayerVisorSprite;		// 男性主人公機
	ISprite *FpPlayerSaberSprite;		// 女性主人公機
	ISprite *FpBossSpaceshipSprite;		// ステージ2ボス
	ISprite *FpBossDegin;				// ジークザデギン(ステージ1,ステージ3ボス)
	ISprite *FpBossUnderson;			// エルダアンダーソン(ステージ4ボス)
	ISprite *FpBossShadowVisor;			// 闇男主人公機(ステージ5ボス)
	ISprite *FpBossShadowSaber;			// 闇女主人公機(ステージ5ボス)
	ISprite *FpBossAlbert;				// アルバートロイアデウス(ステージ6ラスボス)
	ISprite *FpCharacterSeiya;			// 男性立ち絵
	ISprite *FpCharacterKanata;			// 女性立ち絵
	ISprite *FpHpGauge;					// HPゲージ

	ISprite *FpBarrier;					// バリアエフェクト
	ISprite *FpScope;					// ボス弱点表示用スコープ
	ISprite *FpHit;						// ヒットエフェクト
	ISprite *FpExplosionSprite;			// 超大爆発エフェクト
	ISprite *FpAsteroid;				// 障害物(隕石)

	

	// アクセサ
	__declspec( property(get=GetiClientX) ) int iClientX;
	int GetiClientX( void ) const { return FiClientX; }

	__declspec( property(get=GetiClientY) ) int iClientY;
	int GetiClientY( void ) const { return FiClientY; }

	__declspec( property(get=GetPlayer) ) TobjPlayer *pPlayer;
	const TobjPlayer *GetPlayer(void) const {return FpPlayer;}

	__declspec( property(get=GetPlayerLife) ) DWORD iLife;
	const DWORD GetPlayerLife(void) const {return FiLife;}

};

#endif //__TSCENEGAME_H__