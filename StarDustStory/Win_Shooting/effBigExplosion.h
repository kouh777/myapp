#ifndef  __EFFBIGEXPLOSION_H__
#define  __EFFBIGEXPLOSION_H__

#include "objEffect.h"

//-------------------------------------------
class TeffBigExplosion : public TobjEffect
{
private:
	double FiTimer;
	double FiAlpha;

public:
	TeffBigExplosion( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity);
	~TeffBigExplosion(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

#endif	// __EFFBIGEXPLOSION_H__