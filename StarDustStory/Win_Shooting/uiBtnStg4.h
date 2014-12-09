#ifndef  __UIBTNSTG4_H__
#define  __UIBTNSTG4_H__

#include "objUi.h"

class TsceneStageSelect;

//-------------------------------------------
class TuiBtnStg4 : public TobjUi
{
private:
	double FiTimer;
	double FiAlpha;

public:
	TuiBtnStg4(  TsceneStageSelect *select, const Vector2D &pos, const Vector2D &velocity);
	~TuiBtnStg4(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
	// getter
	virtual STG_ID *GetStgId(void){ return &FStgId;}	
};

#endif	// __UIBTNSTG3_H__