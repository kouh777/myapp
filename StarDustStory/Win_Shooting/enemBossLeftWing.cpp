
#include "GameDef.h"
#include "enemBossLeftWing.h"
#include "BaseObserverObject.h"

#include "bulOneWay.h"
#include "bulHoming.h"
#include "bulAiming.h"

//---------------------------------------------------------------------
#define TRIMMING__IMAGE_LTX 9	// 
#define TRIMMING__IMAGE_LTY 169	// 
#define TRIMMING__IMAGE_RBX 133	// 
#define TRIMMING__IMAGE_RBY 279	//

//---------------------------------------------------------------------
// enemBossSpaceShip����ǂꂾ������Ă��邩�������`
#define FROM_SPACESHIP_X -17
#define FROM_SPACESHIP_Y 3

//----------------------------------------------
TenemBossLeftWing::TenemBossLeftWing( TsceneGame *game, const int &pattern, const Vector2D &pos, const Vector2D &velocity )
	:TsubjectEnemy(
	game,
	pos,						// position
	1.0,						// radius
	velocity,					// velocity
	0,							// max_speed
	Vec2DNormalize(velocity),	// heading
	0.,							// mass
	Vector2D(1.,1.),			// scale
	0,							// turn_rate
	1,							// max_force
	10							// vitality
	),
	FiTimer(0),
	FbExplosionEnd(false),
	FiImageWidth(TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX),
	FiImageHeight(TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY)
{
	bObserver = false;
	// ���̃I�u�W�F�N�g��enemBossSpaceShip�̃T�u�W�F�N�g�Ƃ��ēo�^����
	const TBaseMovingObject *obj = FpGame->GetNewestEnemy();
	TBaseObserverObject *observer = (TBaseObserverObject*)obj;
	AddObserver( observer );
	observer->AddSubject(this);

	// �I�u�W�F�N�g�����Ă���������󂯎��`�悷�邽�߂̌v�Z
	FdRadian = atan2(FvVelocity.y ,FvVelocity.x);
	FdRadian /= D3DX_PI;
	FdRadian -= 0.5;
	FdTheta = FdRadian * 180 ;

	// ��_�\���p�X�R�[�v��\��
	FpGame->CreateEffect( EFF_SCOPE, FvPosition, FvVelocity);
}

//----------------------------------------------
TenemBossLeftWing::~TenemBossLeftWing(void)
{

}

//---------------------------------------------
BOOL TenemBossLeftWing::Update(double time_elapsed)
{
	FvVelocity.Normalize();
	FvSide = FvVelocity.Perp();
	FvVelocity *= FdMaxSpeed;

	if(FdVitality <= 0){
		// �����̔����G�t�F�N�g��\��������
		const int RandRange = 15;		// �����̐����͈�
		const int ExplosionNum = 10;	// �����̐�
		const int ExplosionSpan = 5;	// �����̊Ԋu
		srand((unsigned)time(NULL));
		FiTimer++;
		if( FiTimer%ExplosionSpan == 0 ){
			double rw=rand()%RandRange;				// �����̐����͈͓��ŗ����𐶐�
			double rh=rand()%RandRange;
			// �����̐���

			for( int i=0; i < ExplosionNum; ++i ){
				rw=rand()%RandRange;				// �����̐����͈͓��ŗ����𐶐�
				rh=rand()%RandRange;
				FpGame->CreateEffect(EFF_EXPLOSION, Vector2D(FvPosition.x+(rw - (RandRange>>1)), FvPosition.y+(rh - (RandRange>>1) )) , FvVelocity);
			}
		}
		if( FiTimer > ExplosionNum*ExplosionSpan ){
			FbExplosionEnd = true;
		}
	}

	if( FbExplosionEnd != false ){
		// �{�X�ɏ�Ԃ�ʒm����
		NotifyObservers();
		/*
		// �{�X�Ɏ��S��ʒm����
		std::list<TBaseObserverObject *>::iterator it;
		for( it=FObservers.begin() ; it !=FObservers.end(); it++  ){
			(*it)->RecieveNotify(this);
			(*it)->RemoveSubject(this);
		}
		*/
		return FALSE;
	}

	return TRUE;
}

//---------------------------------------------
void TenemBossLeftWing::Render( void )
{
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// �r���[�|�[�g�ϊ�
	FpGame->ViewPortTransform( vec );
	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};						// �摜�̒�����؂�����W
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);

	// �摜��\��������W
	FpGame->FpBossSpaceshipSprite->RenderEx(
							&srcRec,
							pos,												// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),				// Scaling
							D3DXVECTOR3(0, 0, (float)-FdTheta),								// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							1.0,												// Alpha
							D3DCOLOR(1));												// ColorKey

}

//---------------------------------------------------------------------
// Cgdi�`��
void TenemBossLeftWing::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}

//---------------------------------------------
// Reccieve Notify
void TenemBossLeftWing::RecieveNotify( TBaseObserverObject *obs)
{
	// �I�u�U�[�o�[�̏ꏊ�ƌ����Ă���������󂯎��A���g�̏ꏊ�ƌ������v�Z����
	FvPosition.x = obs->vPosition.x + FROM_SPACESHIP_X;
	FvPosition.y = obs->vPosition.y + FROM_SPACESHIP_Y;

}