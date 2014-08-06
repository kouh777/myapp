
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
	TobjShot( const Vector2D &pos, const Vector2D &velocity );
	~TobjShot(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//-------------------------------------------
#endif	// __TOBJSHOT_H__
