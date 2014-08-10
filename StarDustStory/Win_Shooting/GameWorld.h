
#ifndef __GAMEWORLD_H__
#define __GAMEWORLD_H__

//--------------------------------------------------------
class TobjPlayer;
class TobjShot;
class TobjBullet;
class TobjEnemy;
class TenemBox;
class TBaseMovingObject;

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

//--------------------------------------------------------
class TGameWorld
{
private:
	TGameWorld( void );
	TGameWorld( const TGameWorld & );
	TGameWorld operator =( const TGameWorld & );

public:
	~TGameWorld( void );
	static TGameWorld &GetIsntance( void ) {
		static TGameWorld instance;
		return instance;
	}

private:
	HWND FhWnd;
	int FiClientX;
	int FiClientY;

	TobjPlayer *FpPlayer;
	std::list< TobjShot * > FpShots;
	std::list< TobjBullet * > FpBullets;
	std::list< TobjEnemy * > FpEnemies;
	int FiCollapsedTime;

public:
	bool Initialize( HWND hWnd, int cx, int cy );
	void Execute( double elapsed );
	void Draw( void );
	void DrawCgdi(void);

	HRESULT MessageHandle( UINT message, WPARAM wParam, LPARAM lParam );
	void ViewPortTransform( std::vector<Vector2D> &vPoints );
	void CreateShot( const int &type, const Vector2D &pos, const Vector2D &velocity );
	void CreateEnemy( const int &type , const int &pattern , const Vector2D &pos, const Vector2D &velocity );
	void CreateBullet(const int &type, const Vector2D &pos, const Vector2D &velocity );

	void Collision (double elapsedtime);
	const TobjEnemy *GetNearestEnemy(void);

	// アクセサ
	__declspec( property(get=GetiClientX) ) int iClientX;
	int GetiClientX( void ) const { return FiClientX; }
	__declspec( property(get=GetiClientY) ) int iClientY;
	int GetiClientY( void ) const { return FiClientY; }

	__declspec( property(get=GetPlayer) ) TobjPlayer *pPlayer;
	const TobjPlayer *GetPlayer(void) const {return FpPlayer;}

	// 画像リソース
	ISprite *FpSprites;			// テスト用スプライト
	ISprite *FpBackGround;		// ゲーム背景
	ISprite *FpUiBackGround;	// UI背景
	ISprite *FpPlayerSprite;	// プレイヤーテストで描画
	ISprite *FpShotSprite;	// 弾を描画
};
//--------------------------------------------------------
inline TGameWorld &GameWorld( void ) { return TGameWorld::GetIsntance(); }



//--------------------------------------------------------


#endif	// __GAMEWORLD_H__