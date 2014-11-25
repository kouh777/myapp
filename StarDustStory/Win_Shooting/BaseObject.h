
#ifndef __BASEOBJECT_H__
#define __BASEOBJECT_H__

//---------------------------------------------------------------------
#include "windows.h"
#include "Vector2D.h"
#include "sceneGame.h"

//---------------------------------------------------------------------
class TBaseObject
{
public:
	enum {
		default_entity_type = -1,
		player = 0,
		bit,
		shot,
		beam,
		enemy,
		bullet,
		effect,
		gimmick,
		item,
		board,
	};

private:
	int         FID;			// each entity has a unique ID
	int         FObjectType;	// every entity has a type associated with it (health, troll, ammo etc)
	bool        FbTag;			// this is a generic flag. 

	// used by the constructor to give each entity a unique ID
	int NextValidID( void ){ static int NextID = 0; return NextID++; }

protected:
	// its location in the environment
	Vector2D	FvPosition;
	Vector2D	FvScale;
	// the length of this object's bounding radius
	double		FdBoundingRadius;


	TBaseObject( void ) 
		:	FID(NextValidID()), 
			FObjectType(default_entity_type),
			FdBoundingRadius(0.0),
			FvPosition(Vector2D()),
			FvScale(Vector2D(1., 1.)),
			FbTag(false)
	{}

	TBaseObject(int entity_type, Vector2D pos, double r)
		:	FID(NextValidID()), 
			FObjectType(entity_type),
			FdBoundingRadius(r),
			FvPosition(pos),
			FvScale(Vector2D(1., 1.)),
			FbTag(false)
	{}

	
                                      
public:
	virtual ~TBaseObject( void ) {}

	__declspec( property( get=GetPosition, put=SetPosition ) ) Vector2D vPosition;
	Vector2D GetPosition( void ) const { return FvPosition; }  
	void SetPosition( Vector2D new_pos ) { FvPosition = new_pos; }

	__declspec( property( get=GetBRadius, put=SetBRadius ) ) double dBoundingRadius;
	double GetBRadius( void ) const { return FdBoundingRadius; }
	void SetBRadius(double r) { FdBoundingRadius = r; }

	__declspec( property( get=GetID ) ) int ID;
	int GetID( void ) const { return FID; }

	__declspec( property( get=GetTagged, put=SetTag ) ) bool bTag;
	bool GetTagged( void ) const { return FbTag; }
	void SetTag( bool flg ) { FbTag = flg; }

	__declspec( property( get=GetObjectType ) ) int ObjectType;
	int GetObjectType( void ) const { return FObjectType; }

	virtual BOOL Update(double time_elapsed) = 0;
	virtual void Render( void ) = 0;
};


//---------------------------------------------------------------------
#endif	// __BASEOBJECT_H__