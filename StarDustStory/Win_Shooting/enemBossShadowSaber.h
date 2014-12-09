
#ifndef __ENEMBOSSSHWADOWSABER_H__
#define __ENEMBOSSSHWADOWSABER_H__

//-------------------------------------------
#include "observerEnemy.h" 

class TBaseObserverObject;
class TbulOneWay;
class TbulHoming;
class TbulAiming;

//-------------------------------------------
class TenemBossShadowSaber:public TobserverEnemy
{
private:
	int FdTimer;	// 弾の発射間隔
	int FdPattern;	// 敵の行動パターン
	bool FmTurnFlag;
	bool FbInitializeFlg;	// 初期化フラグ
	bool FbDamageFlg;		// ダメージフラグ
	int FiExplosionTimer;
	bool FbExplosionEnd;

protected:
	// 画像読み込み用
	D3DXVECTOR3 pos;
	int FiImageWidth;
	int FiImageHeight;

	//	三角関数計算用変数
	double FdTheta;
	double FdRadian;

public:
	TenemBossShadowSaber(TsceneGame *game, const int &pattern, const Vector2D &pos, const Vector2D &velocity);
	~TenemBossShadowSaber(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Initialize(void);
	virtual void Render( void );
	virtual void RenderCgdi( void );
	virtual void RecieveNotify( TBaseSubjectObject *sub );
	virtual void ReactHit(double damage);
};

#endif // __ENEMBOSSSHWADOWSABER_H__