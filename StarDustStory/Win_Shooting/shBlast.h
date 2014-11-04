
#ifndef	__THSHBLAST_H__
#define	__THSHBLAST_H__

//-------------------------------------------
#include "objShot.h"

//-------------------------------------------
class TshBlast : public TobjShot
{
private:
	// 画像読み込み用
	D3DXVECTOR3 pos;
	TsceneGame *FpGame;
	double FdTimer;					// 爆発時間管理
	const double FdInitialRadius;

protected:
	//	三角関数計算用変数
	double FdTheta;
	double FdRadian;
	int FiImageWidth;
	int FiImageHeight;

public:
	TshBlast( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity);
	~TshBlast(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//-------------------------------------------
#endif	// __THSHBLAST_H__ 