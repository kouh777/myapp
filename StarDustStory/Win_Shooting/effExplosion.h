#ifndef  __EFFEXPLOSION_H__
#define  __EFFEXPLOSION_H__

#include "objEffect.h"

//-------------------------------------------
class TeffExplosion : public TobjEffect
{
private:
	double FiTimer;
	double FiAlpha;

public:
	TeffExplosion( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity);
	~TeffExplosion(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

#endif	// __EFFEXPLOSION_H__