#include "GameDef.h"
#include "BaseObserverObject.h"
#include "BaseSubjectObject.h"
#include "sceneGame.h"

// destructer
TBaseObserverObject::~TBaseObserverObject(void)
{

}																	

// Update
BOOL TBaseObserverObject::Update(double time_elapsed)
{
	return false;
}

//------------------------------------
// Render
//------------------------------------

// Draw Sprite
void TBaseObserverObject::Render( void )
{

}
// Draw Cgdi
void TBaseObserverObject::RenderCgdi( void )
{
	TBaseMovingObject::RenderCgdi();
}

//------------------------------------
// Relation to Observer Design Pattern
//------------------------------------

// Add Subject
void TBaseObserverObject::AddSubject( TBaseSubjectObject *sub )
{
	if(sub){
		FSubjects.push_back(sub);
	}else{
		::OutputDebugString( TEXT("***Error - Try to add Null Subject Object(TBaseObserverObject::AddSubject())\n") );
	}
}

// Notity this status to Subject
void TBaseObserverObject::NotifySubject(void)
{
	std::list<TBaseSubjectObject * >::iterator it;
	for( it = FSubjects.begin(); it != FSubjects.end() ; it++ ){
		// Subjects recieve this status
		(*it)->RecieveNotify(FiObserverStatus);
	}	
}

// Remove Subject
void TBaseObserverObject::RemoveSubject(void)
{
}

// Reccieve Notify. This method is called int Update method
void TBaseObserverObject::RecieveNotify(int &subject_status)
{
	FiSubjectStatus = subject_status;
}

//------------------------------------
// Setter
//------------------------------------

// set Status
void TBaseObserverObject::SetStatus( int &status )
{
	FiObserverStatus = status;
}					
