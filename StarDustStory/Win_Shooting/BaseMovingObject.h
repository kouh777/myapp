
#ifndef __BASEMOVINGOBJECT_H__
#define __BASEMOVINGOBJECT_H__
//---------------------------------------------------------------------
#include <Windows.h>
#include "Vector2D.h"
#include "BaseObject.h"

class TsceneGame;

//---------------------------------------------------------------------
class TBaseMovingObject : public TBaseObject
{
protected:
	Vector2D    FvVelocity;
	Vector2D    FvHeading;		// a normalized vector pointing in the direction the entity is heading. 
	Vector2D    FvSide;			// a vector perpendicular to the heading vector 
	double      FdMass;
	double		FdMaxSpeed;		// the maximum speed this entity may travel at.
	double      FdMaxForce;		// the maximum force this entity can produce to power itself (think rockets and thrust)
	double		FdMaxTurnRate;	// the maximum rate (radians per second)this vehicle can rotate
	double		FdVitality;
//	TsceneGame	*FpGame;

public:
	TBaseMovingObject(
//			TsceneGame *game,
			int type,
			Vector2D position,
            double   radius,
            Vector2D velocity,
            double   max_speed,
            Vector2D heading,
            double   mass,
            Vector2D scale,
            double   turn_rate,
            double   max_force,
			double   vitality) : TBaseObject(type, position, radius),
                                  FvHeading(heading),
                                  FvVelocity(velocity),
                                  FdMass(mass),
                                  FvSide(FvHeading.Perp()),
                                  FdMaxSpeed(max_speed),
                                  FdMaxTurnRate(turn_rate),
                                  FdMaxForce(max_force),
								  FdVitality(vitality)
	{
		FvScale = scale;
	}

	virtual ~TBaseMovingObject( void ) {} 

	virtual BOOL Move( double elasedtime );
	virtual void Render( void );
	virtual void RenderCgdi( void );
	virtual void ReactHit(double);
 
	
	__declspec( property( get=GetVelocity ) ) Vector2D vVelocity;
	Vector2D GetVelocity( void ) const { return FvVelocity; }  

	__declspec( property( get=GetVitality ) ) double dVitality;
	double GetVitality( void ) const { return FdVitality; }  

	/*
	__declspec( property( get=GetVitality, put=SetVitality ) ) double dVitality;
	double GetVitality( void ) const { return FdVitality; }  
	void SetVitality( double val ) { FdVitality = val; }  
	*/

	__declspec( property( get=GetBoundingRadius ) ) double dBoundingRadius;
	double GetBoundingRadius( void ) const { return FdBoundingRadius; }  

	BOOL RotateHeadingToFacePosition(Vector2D target);
	void SetHeading(Vector2D new_heading);
};

//---------------------------------------------------------------------
#endif	// __BASEMOVINGOBJECT_H__