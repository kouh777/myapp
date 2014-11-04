
#ifndef	__THSHBLAST_H__
#define	__THSHBLAST_H__

//-------------------------------------------
#include "objShot.h"

//-------------------------------------------
class TshBlast : public TobjShot
{
private:
	// �摜�ǂݍ��ݗp
	D3DXVECTOR3 pos;
	TsceneGame *FpGame;
	double FdTimer;					// �������ԊǗ�
	const double FdInitialRadius;

protected:
	//	�O�p�֐��v�Z�p�ϐ�
	double FdTheta;
	double FdRadian;
	int FiImageWidth;
	int FiImageHeight;

public:
	TshBlast( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity);
	~TshBlast(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//-------------------------------------------
#endif	// __THSHBLAST_H__ 