
#ifndef	__THSHMINIMULTIPLESHOT_H__
#define	__THSHMINIMULTIPLESHOT_H__

//-------------------------------------------
#include "objShot.h"

//-------------------------------------------
class TshMiniMultipleShot : public TobjShot
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
	int FiFlyingTime;	// �e�����􂷂鎞��

public:
	TshMiniMultipleShot( const Vector2D &pos, const Vector2D &velocity);
	~TshMiniMultipleShot(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//-------------------------------------------
#endif	// __THSHMINIMULTIPLESHOT_H__ 