
#ifndef	__TBULWAVE_H__
#define	__TBULWAVE_H__

//-------------------------------------------
#include "objBullet.h"

//-------------------------------------------
class TbulWave : public TobjBullet
{
private:
	// �摜�ǂݍ��ݗp
	D3DXVECTOR3 pos;
	TsceneGame	*FpGame;

protected:
	//	�O�p�֐��v�Z�p�ϐ�
	double FdTheta;
	double FdRadian;
	int FiImageWidth;
	int FiImageHeight;

public:
	TbulWave( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity);
	~TbulWave(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//-------------------------------------------
#endif	// __TBULONEWAY_H__ 