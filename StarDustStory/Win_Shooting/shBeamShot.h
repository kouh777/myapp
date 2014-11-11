
#ifndef	__THSHBEAMSHOT_H__
#define	__THSHBEAMSHOT_H__

//-------------------------------------------
#include "objShot.h"

//-------------------------------------------
class TshBeamShot : public TobjShot
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
	TshBeamShot( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity);
	~TshBeamShot(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//-------------------------------------------
#endif	// __THSHBEAMSHOT_H__ 