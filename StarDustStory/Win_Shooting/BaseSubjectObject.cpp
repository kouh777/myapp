#include "GameDef.h"
#include "BaseSubjectObject.h"
#include "BaseObserverObject.h"
#include "sceneGame.h"

// destructer
TBaseSubjectObject::~TBaseSubjectObject(void)
{

}

// Update
BOOL TBaseSubjectObject::Update(double time_elapsed)
{
	return false;
}

// Render
// Draw Sprite	
void TBaseSubjectObject::Render(void)
{

}

// Draw Cgdi
void TBaseSubjectObject::RenderCgdi(void)
{
	TBaseMovingObject::RenderCgdi();
}

// Relation to Observer Design Pattern
// Add Subject
void TBaseSubjectObject::AddObserver(TBaseObserverObject *obs)
{
	if(obs){
		FObservers.push_back(obs);
	}else{
		::OutputDebugString( TEXT("***Error - Try to add Null Observer Object(TBaseSubjectObject::AddObserver())\n") );
	}
}

// Notity this status to Observer
void TBaseSubjectObject::NotifyObservers(void)
{
	std::list<TBaseObserverObject * >::iterator it;
	for( it = FObservers.begin(); it != FObservers.end() ; it++ ){
		// Object recieve this status
		(*it)->RecieveNotify(this);
	}
}

// Remove Observer
void TBaseSubjectObject::RemoveObserver( TBaseObserverObject *obs )
{
	// FObserversì‡ÇÃobbÇçÌèúÇ∑ÇÈ
	std::list<TBaseObserverObject *>::iterator it;
	for( it = FObservers.begin(); it != FObservers.end() ; ){
		if( (*it)== obs){
			it = FObservers.erase(it);
		}else{
			it++;
		}
	}	
}

/*
// setter
// set Status
void TBaseSubjectObject::SetStatus(int &status)
{
	FiSubjectStatus = status;
}
*/