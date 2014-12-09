
#ifndef __ENEMCOMMET_H__
#define __ENEMCOMMET_H__

//-------------------------------------------
#include "observerEnemy.h" 

class TbulOneWay;
class TbulHoming;
class TbulAiming;

//-------------------------------------------
class TenemCommet:public TobserverEnemy
{
private:
	int FdTimer;	// �e�̔��ˊԊu
	int FdPattern;	// �G�̍s���p�^�[��
	bool FmTurnFlag;

protected:
	// �摜�ǂݍ��ݗp
	D3DXVECTOR3 pos;
	int FiImageWidth;
	int FiImageHeight;

	//	�O�p�֐��v�Z�p�ϐ�
	double FdTheta;
	double FdRadian;

	// ��]�A�j���[�V�����p�ϐ�
	double FdRotate;

public:
	TenemCommet(TsceneGame *game, const int &pattern, const Vector2D &pos, const Vector2D &velocity);
	~TenemCommet(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
	virtual void RecieveNotify( TBaseSubjectObject *sub );
};

#endif // __ENEMCOMMET_H__