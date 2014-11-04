
#ifndef __ENEMFISH_H__
#define __ENEMFISH_H__

//-------------------------------------------
#include "objEnemy.h" 

class TbulOneWay;
class TbulHoming;
class TbulAiming;

//-------------------------------------------
class TenemFish:public TobjEnemy
{
private:
	int FdTimer;	// �e�̔��ˊԊu
	int FdPattern;	// �G�̍s���p�^�[��
	bool FmTurnFlag;

protected:
	// �摜�ǂݍ��ݗp
	D3DXVECTOR3 pos;
	TsceneGame	*FpGame;
	int FiImageWidth;
	int FiImageHeight;

	//	�O�p�֐��v�Z�p�ϐ�
	double FdTheta;
	double FdRadian;

public:
	TenemFish(TsceneGame *game, const int &pattern, const Vector2D &pos, const Vector2D &velocity);
	~TenemFish(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

#endif // __ENEMFISH_H__