#ifndef  __EFFHIT_H__
#define  __EFFHIT_H__

#include "objEffect.h"

//-------------------------------------------
class TeffHit : public TobjEffect
{
private:
	double FiTimer;
	double FiAlpha;

public:
	TeffHit( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity);
	~TeffHit(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

#endif	// __EFFHIT_H__