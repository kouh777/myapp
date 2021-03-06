
#ifndef	__TBULONEWAY_H__
#define	__TBULONEWAY_H__

//-------------------------------------------
#include "objBullet.h"

//-------------------------------------------
class TbulOneWay : public TobjBullet
{
private:
	int bulletnum;			// 放射されている弾の数
	int timer;				// 弾を全部発射した後の待機時間
	int shotinterval;		// 弾の一つずつの発射間隔

	// 画像読み込み用
	D3DXVECTOR3 pos;

protected:
	//	三角関数計算用変数
	double FdTheta;
	double FdRadian;
	int FiImageWidth;
	int FiImageHeight;

public:
	TbulOneWay( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity);
	~TbulOneWay(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//-------------------------------------------
#endif	// __TBULONEWAY_H__ 