
#ifndef __ENEMBOSSRIGHTWING_H__
#define __ENEMBOSSRIGHTWING_H__

//-------------------------------------------
#include "subjectEnemy.h" 

//-------------------------------------------
class TenemBossRightWing:public TsubjectEnemy
{
private:
	int FiTimer;	// �e�̔��ˊԊu
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
	TenemBossRightWing(TsceneGame *game, const int &pattern, const Vector2D &pos, const Vector2D &velocity);
	~TenemBossRightWing(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
	virtual void RecieveNotify( TBaseObserverObject *obs);
};

#endif // __ENEMBOSSRIGHTWING_H__