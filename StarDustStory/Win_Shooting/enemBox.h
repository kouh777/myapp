
#ifndef __ENEMBOX_H__
#define __ENEMBOX_H__

//-------------------------------------------
#include "objEnemy.h" 

class TbulOneWay;
class TbulHoming;
class TbulAiming;

//-------------------------------------------
class TenemBox:public TobjEnemy
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

public:
	TenemBox(TsceneGame *game, const int &pattern, const Vector2D &pos, const Vector2D &velocity);
	~TenemBox(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

#endif // __ENEMBOX_H__