#ifndef  __UIPLAYERLIFE_H__
#define  __UIPLAYERLIFE_H__

#include "objUi.h"

class TsceneGame;

//-------------------------------------------
class TuiPlayerLife : public TobjUi
{
private:
	double FiTimer;
	double FiAlpha;

public:
	TuiPlayerLife(  TsceneGame *game, const Vector2D &pos, const Vector2D &velocity);
	~TuiPlayerLife(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

#endif	// __UIPLAYERLIFE_H__