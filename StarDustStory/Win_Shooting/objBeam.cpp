
#include "GameDef.h"
#include "objBeam.h"
#include "GameWorld.h"

//---------------------------------------------------------------------
#define TRIMMING__IMAGE_LTX 80	// 
#define TRIMMING__IMAGE_LTY 20	// 
#define TRIMMING__IMAGE_RBX 100	// 
#define TRIMMING__IMAGE_RBY 40	// 

//----------------------------------------------
TobjBeam::TobjBeam( const Vector2D &pos, 
	const Vector2D &velocity )
	:TBaseMovingObject( TBaseObject::beam, 
						Vector2D(pos.x,pos.y-5.0),	// �r�[�����ˈʒu�������
						1.3, 
						velocity, 
						0.1, 
						Vec2DNormalize(velocity), 
						1., 
						Vector2D(0.5, 1.), 
						10., 
						10.0, 
						0.6 ),
						FiImageWidth(TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX),
						FiImageHeight(TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY)
{
	FdBoundingRadius *= FvScale.length();
}

//----------------------------------------------
BOOL TobjBeam::Update(double time_elapsed)
{
	if(FdVitality <= 0)
		return FALSE;
	return TRUE;
}

//----------------------------------------------
void TobjBeam::Render( void )
{
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// �r���[�|�[�g�ϊ�
	GameWorld().ViewPortTransform( vec );
	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};						// �摜�̒�����؂�����W

	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);
	
	// �e�̌��ɂڂ���������
	GameWorld().FpSprites->RenderEx(
							&srcRec,
							pos,																// DrawPosition
							D3DXVECTOR3((float)(FvScale.x*1.5) , (float)(FvScale.y*1.5), 1),				// Scaling
							D3DXVECTOR3(0, 0, 0),												// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							0.4,																// Alpha
							D3DCOLOR(1.f));	


	// �摜��\��������W
	GameWorld().FpSprites->RenderEx(
							&srcRec,
							pos,												// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),				// Scaling
							D3DXVECTOR3(0, 0, 0),								// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							1.0,												// Alpha
							D3DCOLOR(1));												// ColorKey
}

//---------------------------------------------------------------------
// Cgdi�`��
void TobjBeam::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}
