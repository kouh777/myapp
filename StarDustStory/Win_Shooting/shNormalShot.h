
#ifndef	__THSHNORMASHOT_H__
#define	__THSHNORMASHOT_H__

//-------------------------------------------
#include "objShot.h"

//-------------------------------------------
class TshNormalShot : public TobjShot
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
	TshNormalShot( const Vector2D &pos, const Vector2D &velocity);
	~TshNormalShot(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//-------------------------------------------
#endif	// __TBULONEWAY_H__ 