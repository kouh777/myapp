
#include "GameDef.h"
//-------------------------------------------
#include "objUi.h"
#include "uiPlayerVitality.h"
#include "sceneGame.h"
#include "objPlayer.h"

//----------------------------------------------
#define TRIMMING__IMAGE_LTX 0	// 
#define TRIMMING__IMAGE_LTY 0	// 
#define TRIMMING__IMAGE_RBX 488	// 
#define TRIMMING__IMAGE_RBY 81	// 
#define TRIMMING__IMAGE_LTY_WAKU 81		//�@�̗̓Q�[�W�g�؂��� LeftTop
#define TRIMMING__IMAGE_RBY_WAKU 162	//  �̗̓Q�[�W�g�؂��� RightBottom
#define TRIMMING__IMAGE_LTY_EMP	162		//  �̗̓Q�[�W����ې؂��� LeftTop
#define TRIMMING__IMAGE_RBY_EMP	243		//  �̗̓Q�[�W����ې؂��� RightBottom

//----------------------------------------------
TuiPlayerVitality::TuiPlayerVitality( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity)
	:TobjUi(
	game,
	pos,						// position
	0,							// radius
	velocity,					// velocity
	0,							// max_speed
	Vec2DNormalize(velocity),	// heading
	0.,							// mass
	Vector2D(0.5, 0.5),			// scale
	0,							// turn_rate
	1,							// max_force
	1							// vitality
	),
	FiTimer(0),
	FiAlpha(1.0),
	FdPlayerPerLife(1.0)
{
	iImageWidth=TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX;
	iImageHeight=TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY;
}

//----------------------------------------------
TuiPlayerVitality::~TuiPlayerVitality(void)
{
}

//----------------------------------------------
BOOL TuiPlayerVitality::Update(double time_elapsed)
{
	// �ő�̗͂���݂����݂̃v���C���[�̗͂̊���
	if( FpGame->pPlayer ){
		FdPlayerPerLife = FpGame->pPlayer->dVitality / FpGame->pPlayer->dMaxVitality;
	}

	FvVelocity.Normalize();
	FvVelocity *= FdMaxSpeed;

	if(FiAlpha <= 0 || !Move(time_elapsed))
		return false;

	return true;
}

//----------------------------------------------
void TuiPlayerVitality::Render( void )
{
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// �r���[�|�[�g�ϊ�
	FpGame->ViewPortTransform( UI_VIEWPORT , vec );
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);

	// ����ۂ̃Q�[�W
	RECT EmpGaugeRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY_EMP, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY_EMP};	

	// �Q�[�W�̒��g
	RECT InGaugeRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX * FdPlayerPerLife, TRIMMING__IMAGE_RBY};						// �摜�̒�����؂�����W

	// �Q�[�W�̘g
	RECT WakuGaugeRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY_WAKU, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY_WAKU};	

	// ����ۂ̃Q�[�W
	FpGame->FpHpGauge->RenderEx(
							&EmpGaugeRec,
							pos,																// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),				// Scaling
							D3DXVECTOR3(0, 0, 0),												// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							FiAlpha,																// Alpha
							D3DCOLOR(1.0f));	// ColorKey

	// �Q�[�W�̒��g
	FpGame->FpHpGauge->RenderEx(
							&InGaugeRec,
							pos,																// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),				// Scaling
							D3DXVECTOR3(0, 0, 0),												// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							FiAlpha,																// Alpha
							D3DCOLOR(1.0f));	// ColorKey

	// �Q�[�W�̘g
	FpGame->FpHpGauge->RenderEx(
							&WakuGaugeRec,
							pos,																// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),				// Scaling
							D3DXVECTOR3(0, 0, 0),												// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							FiAlpha,																// Alpha
							D3DCOLOR(1.0f));	// ColorKey
}

//---------------------------------------------------------------------
// Cgdi�`��
void TuiPlayerVitality::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}
