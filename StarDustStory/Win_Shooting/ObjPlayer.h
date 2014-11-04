
#ifndef __OBJPLAYER_H__
#define __OBJPLAYER_H__

//---------------------------------------------------------------------
#include "BaseMovingObject.h"

//---------------------------------------------------------------------

//---------------------------------------------------------------------
// é©ã@Å@
class TobjPlayer : public TBaseMovingObject
{
protected:
	int FiBeamPower;
	int FiShotGauge;
	int FiShotTime;
	int FiBeamTime;

	// âÊëúì«Ç›çûÇ›óp
	D3DXVECTOR3 pos;
	TsceneGame	*FpGame;
	int FiImageWidth;
	int FiImageHeight;

public:
	TobjPlayer( TsceneGame *game, Vector2D position, double radius );
	virtual ~TobjPlayer( void );

	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//---------------------------------------------------------------------
#endif	// __OBJPLAYER_H__