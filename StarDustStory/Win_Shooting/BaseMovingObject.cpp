
#include "GameDef.h"
#include "BaseMovingObject.h"
#include "sceneGame.h"

//---------------------------------------------------------------------
// �ړ��֐�
BOOL TBaseMovingObject::Move( double elapsedtime )
{
	FvPosition += FvVelocity * elapsedtime;

	// ��ʊO�ɏo��
	if( FvPosition.x < -55. ) return FALSE;
	if( FvPosition.x >  55. ) return FALSE;
	if( FvPosition.y < -55. ) return FALSE;
	if( FvPosition.y >  55. ) return FALSE;

	return TRUE;
}

//---------------------------------------------------------------------
// �`��֐�
void TBaseMovingObject::Render( void )
{

}

//---------------------------------------------------------------------
// Cgdi�`��֐�
void TBaseMovingObject::RenderCgdi( void )
{
	std::vector<Vector2D> vec;
	vec.push_back( FvPosition );
	// �r���[�|�[�g�ϊ��E�Q�[���V�[�������󂯎��K�v������
	FpGame->ViewPortTransform( vec );
	double scale = FpGame->iClientX / 100;

	// �Փ˔���p�̉~��`��
	Cgdi().BluePen();
	Cgdi().BlueBrush();
	Cgdi().Circle(vec[0], dBoundingRadius*scale);
}

//---------------------------------------------------------------------
// �Փˏ���
void TBaseMovingObject::ReactHit(double){

	// �̗͂����炷 (�q�b�g�������̂̍U���͂��󂯎�肽��)
	FdVitality -= 1;

#ifdef _DEBUG
				::OutputDebugString(TEXT("Hit!"));				
#endif

}