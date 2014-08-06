
#ifndef __TOBJHOMINGSHOT_H__
#define __TOBJHOMINGSHOT_H__

//-------------------------------------------
#include "BaseMovingObject.h"
#include "objEnemy.h"

//-------------------------------------------
class TobjHomingShot : public TBaseMovingObject
{
private:
	// âÊëúì«Ç›çûÇ›óp
	D3DXVECTOR3 pos;

protected:
	int FiImageWidth;
	int FiImageHeight;

public:
	TobjHomingShot( const Vector2D &pos, const Vector2D &velocity );
	~TobjHomingShot(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//-------------------------------------------
#endif	// __TOBJHOMINGSHOT_H__
