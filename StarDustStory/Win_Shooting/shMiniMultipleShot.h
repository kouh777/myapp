
#ifndef	__THSHMINIMULTIPLESHOT_H__
#define	__THSHMINIMULTIPLESHOT_H__

//-------------------------------------------
#include "objShot.h"

//-------------------------------------------
class TshMiniMultipleShot : public TobjShot
{
private:
	// 画像読み込み用
	D3DXVECTOR3 pos;

protected:
	//	三角関数計算用変数
	double FdTheta;
	double FdRadian;
	int FiImageWidth;
	int FiImageHeight;
	int FiFlyingTime;	// 弾が分裂する時間

public:
	TshMiniMultipleShot( const Vector2D &pos, const Vector2D &velocity);
	~TshMiniMultipleShot(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//-------------------------------------------
#endif	// __THSHMINIMULTIPLESHOT_H__ 