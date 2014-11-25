#ifndef  __EFFBARRIER_H__
#define  __EFFBARRIER_H__

#include "objEffect.h"

//-------------------------------------------
class TeffBarrier : public TobjEffect
{
private:
	double FiTimer;
	double FiAlpha;

public:
	TeffBarrier( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity);
	~TeffBarrier(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

#endif	// __EFFBARRIER_H__