
#ifndef __ENEMCOMMET_H__
#define __ENEMCOMMET_H__

//-------------------------------------------
#include "observerEnemy.h" 

class TbulOneWay;
class TbulHoming;
class TbulAiming;

//-------------------------------------------
class TenemCommet:public TobserverEnemy
{
private:
	int FdTimer;	// 弾の発射間隔
	int FdPattern;	// 敵の行動パターン
	bool FmTurnFlag;

protected:
	// 画像読み込み用
	D3DXVECTOR3 pos;
	int FiImageWidth;
	int FiImageHeight;

	//	三角関数計算用変数
	double FdTheta;
	double FdRadian;

	// 回転アニメーション用変数
	double FdRotate;

public:
	TenemCommet(TsceneGame *game, const int &pattern, const Vector2D &pos, const Vector2D &velocity);
	~TenemCommet(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
	virtual void RecieveNotify( TBaseSubjectObject *sub );
};

#endif // __ENEMCOMMET_H__