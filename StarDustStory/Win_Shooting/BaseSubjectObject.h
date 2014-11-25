#ifndef __BASESUBJECTOBJECT_H__
#define __BASESUBJECTOBJECT_H__

#include "BaseMovingObject.h"

class TBaseObserverObject;

//------------------------------------------------------
// this class os designed by "Observer Design Pattern"
//------------------------------------------------------

class TBaseSubjectObject : public TBaseMovingObject{

protected:

	// Rellation to Observer Design Pattern
	std::list<TBaseObserverObject *>	FObservers;			// Observers
//	int									FiObserverStatus;	// Observer status
	int									FiSubjectStatus;	// Subject Status

public:
	
	TBaseSubjectObject( 
		TsceneGame	*game,
		int			type,
		Vector2D	position,
		double		radius,
		Vector2D	velocity,
		double		max_speed,
		Vector2D	heading,
		double		mass,
		Vector2D	scale,
		double		turn_rate,
		double		max_force,
		double		vitality)
		:TBaseMovingObject(game,type,position,radius,velocity,max_speed,heading,mass,scale,turn_rate,max_force,vitality)
	{
	}

	~TBaseSubjectObject(void);										// destructer

	// Update
	virtual BOOL Update(double time_elapsed);						// Update

	// Render
	virtual void Render( void );									// Draw Sprite	
	virtual void RenderCgdi( void );								// Draw Cgdi

	// Relation to Observer Design Pattern
	virtual void AddObserver( TBaseObserverObject *obs );			// Add Subject
	virtual void NotifyObservers(void);								// Notity this status to Observers
	virtual void RemoveObserver( TBaseObserverObject *obs );		// Remove Subject
	virtual void RecieveNotify( TBaseObserverObject *obs) = 0;		// Reccieve Observer Notify

	// setter
//	virtual void SetStatus(int &status);							// set Status

	// getter
	virtual int GetStatus(void) const { return FiSubjectStatus; }	// getStatus
};

#endif //__BASESUBJECTOBJECT_H__