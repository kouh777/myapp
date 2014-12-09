
#ifndef __ENEMBOSSSHWADOWSABER_H__
#define __ENEMBOSSSHWADOWSABER_H__

//-------------------------------------------
#include "observerEnemy.h" 

class TBaseObserverObject;
class TbulOneWay;
class TbulHoming;
class TbulAiming;

//-------------------------------------------
class TenemBossShadowSaber:public TobserverEnemy
{
private:
	int FdTimer;	// �e�̔��ˊԊu
	int FdPattern;	// �G�̍s���p�^�[��
	bool FmTurnFlag;
	bool FbInitializeFlg;	// �������t���O
	bool FbDamageFlg;		// �_���[�W�t���O
	int FiExplosionTimer;
	bool FbExplosionEnd;

protected:
	// �摜�ǂݍ��ݗp
	D3DXVECTOR3 pos;
	int FiImageWidth;
	int FiImageHeight;

	//	�O�p�֐��v�Z�p�ϐ�
	double FdTheta;
	double FdRadian;

public:
	TenemBossShadowSaber(TsceneGame *game, const int &pattern, const Vector2D &pos, const Vector2D &velocity);
	~TenemBossShadowSaber(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Initialize(void);
	virtual void Render( void );
	virtual void RenderCgdi( void );
	virtual void RecieveNotify( TBaseSubjectObject *sub );
	virtual void ReactHit(double damage);
};

#endif // __ENEMBOSSSHWADOWSABER_H__