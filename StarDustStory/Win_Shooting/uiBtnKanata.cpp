
#include "GameDef.h"
//-------------------------------------------
#include "objUi.h"
#include "uiBtnKanata.h"
#include "sceneStageSelect.h"

//----------------------------------------------
#define TRIMMING__IMAGE_LTX 0	// 
#define TRIMMING__IMAGE_LTY 0	// 
#define TRIMMING__IMAGE_RBX 512	// 
#define TRIMMING__IMAGE_RBY 256	// 

//----------------------------------------------
TuiBtnKanata::TuiBtnKanata( TsceneStageSelect *select, const Vector2D &pos, const Vector2D &velocity)
	:TobjUi(
	select,
	pos,						// position
	0,							// radius
	velocity,					// velocity
	0,							// max_speed
	Vec2DNormalize(velocity),	// heading
	0.,							// mass
	Vector2D(0.6, 0.6),			// scale
	0,							// turn_rate
	1,							// max_force
	1							// vitality
	),
	FiTimer(0),
	FiAlpha(1.0)
{
	iImageWidth=TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX;
	iImageHeight=TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY;
	FStgId= STAGE_1;
}

//----------------------------------------------
TuiBtnKanata::~TuiBtnKanata(void)
{
}

//----------------------------------------------
BOOL TuiBtnKanata::Update(double time_elapsed)
{
	FvVelocity.Normalize();
	FvVelocity *= FdMaxSpeed;

	if(FiAlpha <= 0 || !Move(time_elapsed))
		return false;

	return true;
}

//----------------------------------------------
void TuiBtnKanata::Render( void )
{
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// ビューポート変換
	FpStageSelect->ViewPortTransform( vec );
	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};						// 画像の中から切り取る座標
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);

	// 画像を表示する座標
	FpStageSelect->FpBtnKanata->RenderEx(
							&srcRec,
							pos,																// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),				// Scaling
							D3DXVECTOR3(0, 0, 0),												// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							FiAlpha,																// Alpha
							D3DCOLOR(1.0f));																// ColorKey
}

//---------------------------------------------------------------------
// Cgdi描画
void TuiBtnKanata::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}
