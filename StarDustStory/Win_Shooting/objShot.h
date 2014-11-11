
#ifndef __TOBJSHOT_H__
#define __TOBJSHOT_H__

//-------------------------------------------
#include "BaseMovingObject.h"

//-------------------------------------------
class TobjShot : public TBaseMovingObject
{
private:
	// âÊëúì«Ç›çûÇ›óp
	D3DXVECTOR3 pos;

protected:
	int FiImageWidth;
	int FiImageHeight;

public:
	TobjShot(
			TsceneGame *game,
			Vector2D position,
            double   radius,
            Vector2D velocity,
            double   max_speed,
            Vector2D heading,
            double   mass,
            Vector2D scale,
            double   turn_rate,
            double   max_force,
			double   vitality);

	~TobjShot(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//-------------------------------------------
#endif	// __TOBJSHOT_H__
