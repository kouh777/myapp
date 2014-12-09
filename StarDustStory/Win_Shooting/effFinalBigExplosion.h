#ifndef  __EFFFINALBIGEXPLOSION_H__
#define  __EFFFINALBIGEXPLOSION_H__

#include "objEffect.h"

//-------------------------------------------
class TeffFinalBigExplosion : public TobjEffect
{
private:
	double FiTimer;
	double FiAlpha;
	DWORD FiFrame;

public:
	TeffFinalBigExplosion( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity);
	~TeffFinalBigExplosion(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

#endif	// __EFFFINALBIGEXPLOSION_H__