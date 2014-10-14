
#include "WayPoint.h"

/*
//--------------------------------------------------------------------
// obj1‚ÆWayPoint‚Ì‚ ‚½‚è”»’è
BOOL TWayPoint::CollisionCircleS(	const TBaseMovingObject *obj1)
{
	Vector2D A;
	double R,d;

	A = obj1->vPosition - Vector2D(x ,y);
	R = obj1->dBoundingRadius + r;

	d = A.lengthSq();
	if(d < R * R){
		return TRUE;
	}
	return FALSE;
}
*/