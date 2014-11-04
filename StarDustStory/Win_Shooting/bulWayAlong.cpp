
#include "GameDef.h"
#include "bulWayAlong.h"
#include "GameWorld.h"

#define TRIMMING__IMAGE_LTX 160	// 
#define TRIMMING__IMAGE_LTY 120	// 
#define TRIMMING__IMAGE_RBX 170	// 
#define TRIMMING__IMAGE_RBY 130	// 

//----------------------------------------------
TbulWayAlong::TbulWayAlong( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity)
	:TobjBullet(
	pos,						// position
	0.5,						// radius
	velocity,					// velocity
	30,							// max_speed
	Vec2DNormalize(velocity),	// heading
	0.,							// mass
	Vector2D(1., 0.5),			// scale
	0,							// turn_rate
	1,							// max_force
	1							// vitality
	),
	FpGame(game),
	FiImageWidth(TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX),
	FiImageHeight(TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY)
{
	/*
	WayPoint[0] = TWayPoint(0, 0, 10);
	WayPoint[1] = TWayPoint(100, 0, 10);
	WayPoint[2] = TWayPoint(100, 100, 10);
	WayPoint[3] = TWayPoint(100, 0, 10);
	*/
}

//----------------------------------------------
TbulWayAlong::~TbulWayAlong(void)
{
}

//----------------------------------------------
BOOL TbulWayAlong::Update(double time_elapsed)
{
	//----------
	// Œo˜H’Ç]’e(”ò‚Ô•ûŒü‚ÍÝ’è‚µ‚½Œo˜H‚É‰ˆ‚¤)
	//----------

	/*
	for(int i=0; i > sizeof WayPoint / sizeof WayPoint[0]; ){
		while(FvPosition != WayPoint[i]){
			FvVelocity = WayPoint[i]-WayPoint[i+1];
			FvVelocity.Normalize();
			FvVelocity *= FdMaxSpeed;
		
			if(FvPosition==WayPoint[i]){
				++i;
				break;
			}

			if(FdVitality <= 0 || !Move(time_elapsed))
				return false;
		}
	}
	*/
	
	FvVelocity.Normalize();
	FvVelocity *= FdMaxSpeed;
	
	return true;
}

//----------------------------------------------
void TbulWayAlong::Render( void )
{
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// ƒrƒ…[ƒ|[ƒg•ÏŠ·
	FpGame->ViewPortTransform( vec );
	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};						// ‰æ‘œ‚Ì’†‚©‚çØ‚èŽæ‚éÀ•W
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);

	// ‰æ‘œ‚ð•\Ž¦‚·‚éÀ•W
	FpGame->FpSprites->RenderEx(
							&srcRec,
							pos,																// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),				// Scaling
							D3DXVECTOR3(0, 0, 0),												// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							1.0,																// Alpha
							D3DCOLOR(1));																// ColorKey
}

//---------------------------------------------------------------------
// Cgdi•`‰æ
void TbulWayAlong::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}

//----------------------------------------------