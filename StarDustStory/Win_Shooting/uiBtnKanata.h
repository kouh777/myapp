#ifndef  __UIBTNKANATA_H__
#define  __UIBTNKANATA_H__

#include "objUi.h"

class TsceneStageSelect;

//-------------------------------------------
class TuiBtnKanata : public TobjUi
{
private:
	double FiTimer;
	double FiAlpha;

public:
	TuiBtnKanata(  TsceneStageSelect *select, const Vector2D &pos, const Vector2D &velocity);
	~TuiBtnKanata(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

#endif	// __UIBTNKANATA_H__