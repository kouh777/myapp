#include "GameDef.h"
#include "shHomingShot.h"
#include "GameWorld.h"

//----------------------------------------------
#define TRIMMING__IMAGE_LTX 40	// 
#define TRIMMING__IMAGE_LTY 20	// 
#define TRIMMING__IMAGE_RBX 60	// 
#define TRIMMING__IMAGE_RBY 30	//

//----------------------------------------------
TshHomingShot::TshHomingShot( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity)
	:TobjShot(
	game,
	Vector2D(pos.x,pos.y-2),	// position
	1.5,							// radius
	velocity,					// velocity
	60,							// max_speed
	Vec2DNormalize(velocity),	// heading
	1.,							// mass
	Vector2D(2.0, 2.0),			// scale
	10,							// turn_rate
	10,							// max_force
	1							// vitality
	),
	FiImageWidth(TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX),
	FiImageHeight(TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY),
	FpEnemy(NULL)
{
	// When this shots create, get nearset enemy.
	if(FpGame->GetNearestEnemy() != NULL)
		FpEnemy = FpGame->GetNearestEnemy();
}

//----------------------------------------------
TshHomingShot::~TshHomingShot(void)
{
}

//----------------------------------------------
BOOL TshHomingShot::Update(double time_elapsed)
{

	//----------
	// �ǐՒe(�e�̐������Ƀv���C���[�̈�ԋ߂��ɂ����G�����������ǐՂ���B)
	//---------
	if(FpEnemy){
		FvVelocity = FpEnemy->vPosition - FvPosition;
		// �^�[�Q�b�g��HP��0�ɂȂ�����FpEnemy��NULL������
		if(FpEnemy->dVitality <= 0)
			FpEnemy = NULL;
	}
	// �����e�̑��x��0�ɂȂ�����AFvVelocity��Vector2D(0,1)��������
	if(FvVelocity.isZero())
		FvVelocity = Vector2D(0,1);

	FvVelocity.Normalize();
	FvVelocity *= FdMaxSpeed;

	if(FdVitality <= 0 || !Move(time_elapsed))
		return false;

	return true;
}

//----------------------------------------------
void TshHomingShot::Render( void )
{
	
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// �r���[�|�[�g�ϊ�
	FpGame->ViewPortTransform( vec );
	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};						// �摜�̒�����؂�����W
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);

	// �摜��\��������W
	FpGame->FpSprites->RenderEx(
							&srcRec,
							pos,																	// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),					// Scaling
							D3DXVECTOR3(0, 0, 0),													// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							1.0,																	// Alpha
							D3DCOLOR(1));															// ColorKey

}

//---------------------------------------------------------------------
// Cgdi�`��
void TshHomingShot::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}