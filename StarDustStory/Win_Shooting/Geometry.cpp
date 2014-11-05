#include "Geometry.h"

double CollisionCircle(
	const TBaseMovingObject *obj1,
	const TBaseMovingObject *obj2,
	double elapsedTime
)
{
	Vector2D A, B;
	double dotAB , d, bb_4ac, LenSqA, LenSqB;

	A = obj1->vPosition - obj2->vPosition;
	B = (obj1->vVelocity - obj2->vVelocity) * elapsedTime;
	d = obj1->dBoundingRadius + obj2->dBoundingRadius;
	dotAB = A.Dot(B);
	LenSqA = A.lengthSq();
	LenSqB = B.lengthSq();
	bb_4ac = dotAB * dotAB - LenSqB * (LenSqA - d*d);

	// ‡@
	if(B.isZero()) return 10.0;

	// ‡A
	if(bb_4ac < 0.) return 10.0;

	// ‡B
	double closestDist = LenSqA - (dotAB * dotAB) * (1.0 / LenSqB);
	if( d*d < closestDist) return 10.;

	// ‡C
	double t = (-dotAB- sqrt(bb_4ac)) * (1.0 / LenSqB);
	if(t < 0.0 || t > 1.0) return 10.0;

	return t;
}

// ’Pƒ“–‚½‚è”»’è
BOOL CollisionCircleS(	const TBaseMovingObject *obj1, const TBaseMovingObject *obj2)
{
	// obj1‚Æobj2‚Ì‚¢‚¸‚ê‚©‚ªNULL‚Ìê‡false‚ð‹­§“I‚É•Ô‚·
	if( !obj1 || !obj2 )
		return FALSE;

	Vector2D A;
	double R,d;

	A = obj1->vPosition - obj2->vPosition;
	R = obj1->dBoundingRadius + obj2->dBoundingRadius;

	d = A.lengthSq();
	if(d < R * R){
		return TRUE;
	}
	return FALSE;
}