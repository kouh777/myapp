
#ifndef __ENEMBOSSLEFTWING_H__
#define __ENEMBOSSLEFTWING_H__

//-------------------------------------------
#include "subjectEnemy.h" 

//-------------------------------------------
class TenemBossLeftWing:public TsubjectEnemy
{
private:
	int FiTimer;			// �����x���^�C�}�[
	bool FbExplosionEnd;	// �����G���h�t���O


protected:
	// �摜�ǂݍ��ݗp
	D3DXVECTOR3 pos;
	int FiImageWidth;
	int FiImageHeight;

	//	�O�p�֐��v�Z�p�ϐ�
	double FdTheta;
	double FdRadian;

public:
	TenemBossLeftWing(TsceneGame *game, const int &pattern, const Vector2D &pos, const Vector2D &velocity);
	~TenemBossLeftWing(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
	virtual void RecieveNotify( TBaseObserverObject *obs);
};

#endif // __ENEMBOSSLEFTWING_H__