
#ifndef __ENEMBOSSLEFTWING_H__
#define __ENEMBOSSLEFTWING_H__

//-------------------------------------------
#include "subjectEnemy.h" 

//-------------------------------------------
class TenemBossLeftWing:public TsubjectEnemy
{
private:
	int FiTimer;			// 爆発遅延タイマー
	bool FbExplosionEnd;	// 爆発エンドフラグ


protected:
	// 画像読み込み用
	D3DXVECTOR3 pos;
	int FiImageWidth;
	int FiImageHeight;

	//	三角関数計算用変数
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