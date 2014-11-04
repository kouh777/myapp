#ifndef __TSCENEGAME_H__
#define __TSCENEGAME_H__

//--------------------------------------------------------
#include "TaskManager.h"
#include <vector>

//--------------------------------------------------------
class TobjPlayer;
class TobjShot;
class TobjBullet;
class TobjEnemy;
class TenemBox;
class TenemFish;
class TBaseMovingObject;

class ISprite;

//--------------------------------------------------------
// vC[e
class TshNormalShot;
class TshBeamShot;
class TshAimingShot;
class TshHomingShot;
class TshMultipleShot;
class TshMiniMultipleShot;
class TshBlastShot;
class TshBlast;

//--------------------------------------------------------
// Ge
class TbulOneWay;
class TbulHoming;
class TbulAiming;
class TbulWave;
class TbulWayAlong;

//--------------------------------------------------------
// wi
class TBackGround;

//--------------------------------------------------------
// Q[XNvg
class TGameScript;

//--------------------------------------------------------
class TsceneGame: public _Task
{
private:
	HWND FhWnd;
	int FiClientX;
	int FiClientY;
	double FiTimer;

	TobjPlayer *FpPlayer;
	std::list< TobjShot * > FpShots;
	std::list< TobjBullet * > FpBullets;
	std::list< TobjEnemy * > FpEnemies;
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
	const TobjEnemy *GetNearestEnemy(void);

	// 3d test
	void Draw3D(void);

	// æ\[X
	ISprite	*FpSprites;					// eXgpXvCg
	ISprite *FpBackGroundSprite;		// Q[wi
	ISprite *FpUiBackGround;			// UIwi
	ISprite *FpPlayerSprite;			// vC[(eXgÅ)
	ISprite *FpShotSprite;				// e
	ISprite *FpEnemySprite;				// G

	// ANZT
	__declspec( property(get=GetiClientX) ) int iClientX;
	int GetiClientX( void ) const { return FiClientX; }

	__declspec( property(get=GetiClientY) ) int iClientY;
	int GetiClientY( void ) const { return FiClientY; }

	__declspec( property(get=GetPlayer) ) TobjPlayer *pPlayer;
	const TobjPlayer *GetPlayer(void) const {return FpPlayer;}

};

#endif //__TSCENEGAME_H__