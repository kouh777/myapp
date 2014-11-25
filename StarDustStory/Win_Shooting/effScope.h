#ifndef  __EFFSCOPE_H__
#define  __EFFSCOPE_H__

#include "objEffect.h"

//-------------------------------------------
class TeffScope : public TobjEffect
{
private:
	double FiTimer;
	double FiAlpha;
	bool   FbBlinkEnd;		// ブリンクフラグ
	int    FiBlinkNum;		// ブリンク回数

public:
	TeffScope( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity);
	~TeffScope(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

#endif	// __EFFSCOPE_H__