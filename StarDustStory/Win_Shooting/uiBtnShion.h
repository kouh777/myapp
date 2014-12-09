#ifndef  __UIBTNSHION_H__
#define  __UIBTNSHION_H__

#include "objUi.h"

class TsceneStageSelect;

//-------------------------------------------
class TuiBtnShion : public TobjUi
{
private:
	double FiTimer;
	double FiAlpha;

public:
	TuiBtnShion(  TsceneStageSelect *select, const Vector2D &pos, const Vector2D &velocity);
	~TuiBtnShion(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

#endif	// __UIBTNSHION_H__