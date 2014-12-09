
#include "GameDef.h"
//-------------------------------------------
#include "objUi.h"
#include "uiCursor.h"
#include "sceneStageSelect.h"

//----------------------------------------------
// ���摜�T�C�Y��`
#define ORIGINAL_IMAGE_LTX 0	
#define ORIGINAL_IMAGE_LTY 0	
#define ORIGINAL_IMAGE_RBX 600
#define ORIGINAL_IMAGE_RBY 120	

//----------------------------------------------
// �摜�؂���T�C�Y��`
#define TRIMMING_WIDTH	120
#define TRIMMING_HEIGHT 120

/*
#define TRIMMING__IMAGE_LTX 0	// 
#define TRIMMING__IMAGE_LTY 0	// 
#define TRIMMING__IMAGE_RBX 120	// 
#define TRIMMING__IMAGE_RBY 120	// 
*/

//----------------------------------------------
TuiCursor::TuiCursor( TsceneStageSelect *select, const Vector2D &pos, const Vector2D &velocity)
	:TobjUi(
	select,
	pos,						// position
	0,							// radius
	velocity,					// velocity
	0,							// max_speed
	Vec2DNormalize(velocity),	// heading
	0.,							// mass
	Vector2D(0.3, 0.3),			// scale
	0,							// turn_rate
	1,							// max_force
	1							// vitality
	),
	FdTimer(0),
	FiAlpha(1.0),
	FiFrame(1)
{
	iImageWidth=TRIMMING_WIDTH;
	iImageHeight=TRIMMING_HEIGHT;
}

//----------------------------------------------
TuiCursor::~TuiCursor(void)
{
}

//----------------------------------------------
BOOL TuiCursor::Update(double time_elapsed)
{
//	FvVelocity.Normalize();
//	FvVelocity *= FdMaxSpeed;
	const int iMaxFrame = 4;			// �摜��5��������
	const double dMaxTimer = 0.075;		// �摜��؂�ւ��鑬�x(�l���������قǐ؂�ւ�������)
	const double dFromBtnLeft = 3;

	FdTimer += time_elapsed;
	if( FdTimer > dMaxTimer ){
		FdTimer = 0;
		FiFrame++;
	}
	if( FiFrame > iMaxFrame ){
		FiFrame = 0;
	}

	// �I�𒆂̃{�^�����󂯎��A�{�^���̍��[����dFromBtnLeft�̒l�������炵���ꏊ�ɃJ�[�\����z�u����
	if( FpStageSelect->GetSelectingBtn() ){
		TobjUi *ui = (TobjUi*)FpStageSelect->GetSelectingBtn();
		// width���擾
		double mx = ui->iImageWidth * ui->vScale.x;
		mx = mx * 100 / FpStageSelect->iClientX;

		Vector2D c_pos = ui->vPosition;
		Vector2D lpos = Vector2D( c_pos.x - ( (int)mx >> 1 ) + dFromBtnLeft, c_pos.y);
		FvPosition = lpos;
	}
	if(FiAlpha <= 0 || !Move(time_elapsed))
		return false;

	return true;
}

//----------------------------------------------
void TuiCursor::Render( void )
{
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// �r���[�|�[�g�ϊ�
	FpStageSelect->ViewPortTransform( vec );
	// �摜�̒�����؂�����W��ݒ肷��
	RECT srcRec = { 
					ORIGINAL_IMAGE_LTX + (FiFrame * TRIMMING_WIDTH),
					ORIGINAL_IMAGE_LTY,
					ORIGINAL_IMAGE_LTX + ( (FiFrame+1) * TRIMMING_WIDTH),
					TRIMMING_HEIGHT
					};
//	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};						// �摜�̒�����؂�����W
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);

	// �摜��\��������W
	FpStageSelect->FpBtnCursor->RenderEx(
							&srcRec,
							pos,																// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),				// Scaling
							D3DXVECTOR3(0, 0, 0),												// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							FiAlpha,																// Alpha
							D3DCOLOR(1.f));																// ColorKey
}

//---------------------------------------------------------------------
// Cgdi�`��
void TuiCursor::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}
