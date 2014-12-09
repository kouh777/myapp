#ifndef  __UIBTNSTG5_H__
#define  __UIBTNSTG5_H__

#include "objUi.h"

class TsceneStageSelect;

//-------------------------------------------
class TuiBtnStg5 : public TobjUi
{
private:
	double FiTimer;
	double FiAlpha;

public:
	TuiBtnStg5(  TsceneStageSelect *select, const Vector2D &pos, const Vector2D &velocity);
	~TuiBtnStg5(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
	// getter
	virtual STG_ID *GetStgId(void){ return &FStgId;}
};

#endif	// __UIBTNSTG5_H__