
#ifndef	__TBULWAYAlONG_H__
#define	__TBULWAYAlONG_H__

//-------------------------------------------
#include "objBullet.h"
#include "WayPoint.h"

//-------------------------------------------
class TbulWayAlong : public TobjBullet
{
private:
	TWayPoint WayPoint[4];

	// �摜�ǂݍ��ݗp
	D3DXVECTOR3 pos;

protected:
	//	�O�p�֐��v�Z�p�ϐ�
	double FdTheta;
	double FdRadian;
	int FiImageWidth;
	int FiImageHeight;

public:
	TbulWayAlong( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity);
	~TbulWayAlong(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//-------------------------------------------
#endif	// __TBULWAYAlONG_H__ 