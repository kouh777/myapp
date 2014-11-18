
#ifndef	__THSHHOMINGSHOT_H__
#define	__THSHHOMINGSHOT_H__

//-------------------------------------------
#include "objShot.h"
#include "objEnemy.h"

//-------------------------------------------
class TshHomingShot : public TobjShot
{
private:
	// �摜�ǂݍ��ݗp
	D3DXVECTOR3 pos;
	const TBaseMovingObject *FpEnemy;

protected:
	//	�O�p�֐��v�Z�p�ϐ�
	double FdTheta;
	double FdRadian;
	int FiImageWidth;
	int FiImageHeight;

public:
	TshHomingShot( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity);
	~TshHomingShot(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//-------------------------------------------
#endif	// __THSHHOMINGSHOT_H__ 