
#ifndef	__THSHBLASTSHOT_H__
#define	__THSHBLASTSHOT_H__

//-------------------------------------------
#include "objShot.h"

//-------------------------------------------
class TshBlastShot : public TobjShot
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
	TshBlastShot( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity);
	~TshBlastShot(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//-------------------------------------------
#endif	// __THSHBLASTSHOT_H__ 