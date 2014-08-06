
#ifndef	__TBULONEWAY_H__
#define	__TBULONEWAY_H__

//-------------------------------------------
#include "objBullet.h"

//-------------------------------------------
class TbulOneWay : public TobjBullet
{
private:
	int bulletnum;			// ���˂���Ă���e�̐�
	int timer;				// �e��S�����˂�����̑ҋ@����
	int shotinterval;		// �e�̈���̔��ˊԊu

	// �摜�ǂݍ��ݗp
	D3DXVECTOR3 pos;

protected:
	//	�O�p�֐��v�Z�p�ϐ�
	double FdTheta;
	double FdRadian;
	int FiImageWidth;
	int FiImageHeight;

public:
	TbulOneWay( const Vector2D &pos, const Vector2D &velocity);
	~TbulOneWay(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//-------------------------------------------
#endif	// __TBULONEWAY_H__ 