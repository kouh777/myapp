
#ifndef	__TBULAIMING_H__
#define	__TBULAIMING_H__

//-------------------------------------------
#include "objBullet.h"

//-------------------------------------------
class TbulAiming : public TobjBullet
{
private:
	Vector2D mAimingPos;	// 狙う位置
	// 画像読み込み用
	D3DXVECTOR3 pos;

protected:
	//	三角関数計算用変数
	double FdTheta;
	double FdRadian;
	int FiImageWidth;
	int FiImageHeight;

public:
	TbulAiming( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity);

	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//-------------------------------------------
#endif	// __TBULHOMING_H__ 