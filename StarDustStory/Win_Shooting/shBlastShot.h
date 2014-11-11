
#ifndef	__THSHBLASTSHOT_H__
#define	__THSHBLASTSHOT_H__

//-------------------------------------------
#include "objShot.h"

//-------------------------------------------
class TshBlastShot : public TobjShot
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
	TshBlastShot( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity);
	~TshBlastShot(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//-------------------------------------------
#endif	// __THSHBLASTSHOT_H__ 