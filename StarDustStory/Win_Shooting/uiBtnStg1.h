#ifndef  __UIBTNSTG1_H__
#define  __UIBTNSTG1_H__

#include "objUi.h"

class TsceneStageSelect;

//-------------------------------------------
class TuiBtnStg1 : public TobjUi
{
private:
	double FiTimer;
	double FiAlpha;

public:
	TuiBtnStg1(  TsceneStageSelect *select, const Vector2D &pos, const Vector2D &velocity);
	~TuiBtnStg1(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

#endif	// __UIBTNSTG1_H__