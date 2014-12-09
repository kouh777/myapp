#ifndef  __UIBTNCURSOR_H__
#define  __UIBTNCURSOR_H__

#include "objUi.h"

class TsceneStageSelect;

//-------------------------------------------
class TuiCursor : public TobjUi
{
private:
	double FdTimer;
	double FiAlpha;
	int FiFrame;	// 表示画像変換用メンバー

public:
	TuiCursor(  TsceneStageSelect *select, const Vector2D &pos, const Vector2D &velocity);
	~TuiCursor(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );

};

#endif	// __UIBTNCURSOR_H__