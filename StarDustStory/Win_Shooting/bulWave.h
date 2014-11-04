
#ifndef	__TBULWAVE_H__
#define	__TBULWAVE_H__

//-------------------------------------------
#include "objBullet.h"

//-------------------------------------------
class TbulWave : public TobjBullet
{
private:
	// 画像読み込み用
	D3DXVECTOR3 pos;
	TsceneGame	*FpGame;

protected:
	//	三角関数計算用変数
	double FdTheta;
	double FdRadian;
	int FiImageWidth;
	int FiImageHeight;

public:
	TbulWave( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity);
	~TbulWave(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//-------------------------------------------
#endif	// __TBULONEWAY_H__ 