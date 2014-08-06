
#ifndef __OBJBEAM_H__
#define __OBJBEAM_H__


//-------------------------------------------
#include "BaseMovingObject.h"

//-------------------------------------------
class TobjBeam : public TBaseMovingObject
{
private:
	// âÊëúì«Ç›çûÇ›óp
	D3DXVECTOR3 pos;

protected:
	int FiImageWidth;
	int FiImageHeight;

public:
	TobjBeam( const Vector2D &pos, const Vector2D &velocity );

	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};



#endif	// __OBJBEAM_H__