#ifndef  __UIPLAYERVITALITY_H__
#define  __UIPLAYERVITALITY_H__

#include "objUi.h"

class TsceneGame;

//-------------------------------------------
class TuiPlayerVitality : public TobjUi
{
private:
	double FiTimer;
	double FiAlpha;
	double FdPlayerPerLife;

public:
	TuiPlayerVitality(  TsceneGame *game, const Vector2D &pos, const Vector2D &velocity);
	~TuiPlayerVitality(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

#endif	// __UIPLAYERVITALITY_H__