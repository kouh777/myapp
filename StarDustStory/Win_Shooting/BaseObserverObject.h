#ifndef __BASEOBSERVEROBJECT_H__
#define __BASEOBSERVEROBJECT_H__

#include "BaseMovingObject.h"

class TBaseSubjectObject;

//------------------------------------------------------
// this class os designed by "Observer Design Pattern"
//------------------------------------------------------

class TBaseObserverObject : public TBaseMovingObject{

private:

	// Rellation to Observer Design Pattern
	int FiObserverStatus;							// Observer Status
//	int FiSubjectStatus;							// Subject Status

protected:
	std::list<TBaseSubjectObject *>	FSubjects;		// Subjects

public:

	// constucter
	TBaseObserverObject( 
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

	~TBaseObserverObject(void);																	// destructer

	// Update
	virtual BOOL Update(double time_elapsed);				// Update

	// Render
	virtual void Render( void );							// Draw Sprite	
	virtual void RenderCgdi( void );						// Draw Cgdi

	// Relation to Observer Design Pattern
	virtual void AddSubject( TBaseSubjectObject *sub );			// Add Subject
	virtual void NotifySubject( void );							// Notity this status to Subject
	virtual void RemoveSubject( TBaseSubjectObject *sub );		// Remove Subject
	virtual void RecieveNotify( TBaseSubjectObject *sub ) = 0;	// Recieve Subject

	// setter
//	virtual void SetStatus( int &status );					// set Status

	// getter
	virtual int GetStatus(void) const { return FiObserverStatus; }			// getStatus

};

#endif // __BASEOBSERVEROBJECT_H__