#ifndef __GEGOMETRY_H__
#define __GEGOMETRY_H__

#include "Vector2D.h" 
#include "BaseMovingObject.h"

extern double CollisionCircle(
	const TBaseMovingObject *obj1,
	const TBaseMovingObject *obj2,
	double elapsedTime
	
);

extern BOOL CollisionCircleS(const TBaseMovingObject *obj1, const TBaseMovingObject *obj2);

#endif //__GEGOMETRY_H__