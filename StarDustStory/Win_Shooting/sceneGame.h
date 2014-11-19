#ifndef __TSCENEGAME_H__
#define __TSCENEGAME_H__

//--------------------------------------------------------
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
// 敵
class TenemBox;
class TenemFish;
class TenemBossFortress;
class TenemBossSpaceShip;

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

//--------------------------------------------------------
// 背景
class TBackGround;

//--------------------------------------------------------
// ゲームスクリプト
class TGameScript;

//--------------------------------------------------------
class TsceneGame: public _Task
{
private:
	HWND FhWnd;
	int FiClientX;
	int FiClientY;
	double FiTimer;
	bool FbFadeFlg;
	bool FbOverFlg;

	TobjPlayer *FpPlayer;
	std::list< TBaseMovingObject * > FpShots;
	std::list< TBaseMovingObject * > FpBullets;
	std::list< TBaseMovingObject * > FpEnemies;
	int FiCollapsedTime;
	TGameScript *FpGameScript;

	TBackGround *FpBackGround;

public:
	TsceneGame( void );
	~TsceneGame( void );
	bool Execute( double ElapsedTime);
	void Draw( void );
	void DrawCgdi(void);

	bool Initialize( void );
	HRESULT MessageHandle( UINT message, WPARAM wParam, LPARAM lParam );
	void ViewPortTransform( std::vector<Vector2D> &vPoints );
	void CreateShot( const int &type, const Vector2D &pos, const Vector2D &velocity );
	void CreateEnemy( const int &type , const int &pattern , const Vector2D &pos, const Vector2D &velocity );
	void CreateBullet(const int &type, const Vector2D &pos, const Vector2D &velocity );

	void Collision (double elapsedtime);
	const TBaseMovingObject *GetNearestEnemy(void);

	// 3d test
	void Draw3D(void);

	// 画像リソース
	ISprite	*FpSprites;					// テスト用スプライト
	ISprite *FpBackGroundSprite;		// ゲーム背景
	ISprite *FpUiBackGround;			// UI背景
	ISprite *FpPlayerSprite;			// プレイヤー(テストで)
	ISprite *FpShotSprite;				// 弾
	ISprite *FpEnemySprite;				// 敵
	ISprite *FpPlayerVisorSprite;		// プレイヤー1
	ISprite *FpPlayerSaberSprite;		// プレイヤー2
	ISprite *FpBossSpaceshipSprite;		// ステージ2ボス

	// アクセサ
	__declspec( property(get=GetiClientX) ) int iClientX;
	int GetiClientX( void ) const { return FiClientX; }

	__declspec( property(get=GetiClientY) ) int iClientY;
	int GetiClientY( void ) const { return FiClientY; }

	__declspec( property(get=GetPlayer) ) TobjPlayer *pPlayer;
	const TobjPlayer *GetPlayer(void) const {return FpPlayer;}

};

#endif //__TSCENEGAME_H__