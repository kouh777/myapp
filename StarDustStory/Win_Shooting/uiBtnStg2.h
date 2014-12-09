#ifndef  __UIBTNSTG2_H__
#define  __UIBTNSTG2_H__

#include "objUi.h"

class TsceneStageSelect;

//-------------------------------------------
class TuiBtnStg2 : public TobjUi
{
private:
	double FiTimer;
	double FiAlpha;

public:
	TuiBtnStg2(  TsceneStageSelect *select, const Vector2D &pos, const Vector2D &velocity);
	~TuiBtnStg2(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
	// getter
	virtual STG_ID *GetStgId(void){ return &FStgId;}
};

#endif	// __UIBTNSTG2_H__