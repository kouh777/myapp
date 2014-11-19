
#ifndef __ENEMBOSSFORTRESS_H__
#define __ENEMBOSSFORTRESS_H__

//-------------------------------------------
#include "subjectEnemy.h" 

class TbulOneWay;
class TbulHoming;
class TbulAiming;

//-------------------------------------------
class TenemBossFortress:public TsubjectEnemy
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

public:
	TenemBossFortress(TsceneGame *game, const int &pattern, const Vector2D &pos, const Vector2D &velocity);
	~TenemBossFortress(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

#endif // __ENEMBOSSFORTRESS_H__