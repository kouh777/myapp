
#ifndef	__THSHNORMASHOT_H__
#define	__THSHNORMASHOT_H__

//-------------------------------------------
#include "objShot.h"

//-------------------------------------------
class TshNormalShot : public TobjShot
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

public:
	TshNormalShot( const Vector2D &pos, const Vector2D &velocity);
	~TshNormalShot(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//-------------------------------------------
#endif	// __TBULONEWAY_H__ 