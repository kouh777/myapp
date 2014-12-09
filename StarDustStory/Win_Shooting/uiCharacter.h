#ifndef  __UICHARACTER_H__
#define  __UICHARACTER_H__

#include "objUi.h"

class TsceneGame;

//-------------------------------------------
class TuiCharacter : public TobjUi
{
private:
	double FiTimer;
	double FiAlpha;

public:
	TuiCharacter(  TsceneGame *game, const Vector2D &pos, const Vector2D &velocity);
	~TuiCharacter(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

#endif	// __UICHARACTER_H__