
#ifndef	__THSHAIMINGSHOT_H__
#define	__THSHAIMINGSHOT_H__

//-------------------------------------------
#include "objShot.h"
#include "objEnemy.h"

//-------------------------------------------
class TshAimingShot : public TobjShot
{
private:
	// �摜�ǂݍ��ݗp
	D3DXVECTOR3 pos;

protected:
	//	�O�p�֐��v�Z�p�ϐ�
	double FdTheta;
	double FdRadian;
	int FiImageWidth;
	int FiImageHeight;

public:
	TshAimingShot( const Vector2D &pos, const Vector2D &velocity);
	~TshAimingShot(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//-------------------------------------------
#endif	// __THSHAIMINGSHOT_H__ 