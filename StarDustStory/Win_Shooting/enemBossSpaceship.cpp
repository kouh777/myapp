
#include "GameDef.h"
#include "enemBossSpaceship.h"
#include "enemBossFortress.h"

#include "bulOneWay.h"
#include "bulHoming.h"
#include "bulAiming.h"

//---------------------------------------------------------------------
#define TRIMMING__IMAGE_LTX 9	// 
#define TRIMMING__IMAGE_LTY 9	// 
#define TRIMMING__IMAGE_RBX 295	// 
#define TRIMMING__IMAGE_RBY 151	// 

//----------------------------------------------
TenemBossSpaceship::TenemBossSpaceship( TsceneGame *game, const int &pattern, const Vector2D &pos, const Vector2D &velocity )
	:TobserverEnemy(
	game,
	pos,						// position
	2.0,						// radius
	velocity,					// velocity
	30,							// max_speed
	Vec2DNormalize(velocity),	// heading
	0.,							// mass
	Vector2D(1.,1.),			// scale
	0,							// turn_rate
	1,							// max_force
	70							// vitality
	),
	FdPattern(pattern),
	FdTimer(0),
	FmTurnFlag(false),
	FbInitializeFlg(false),
	FiExplosionTimer(0),
	FbExplosionEnd(false),
	FiImageWidth(TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX),
	FiImageHeight(TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY),
	FbDamageFlg(false)
{
	// �X�N���v�g���|�[�Y����
	FpGame->ScriptPause();
}

//----------------------------------------------
TenemBossSpaceship::~TenemBossSpaceship(void)
{
	// �X�N���v�g���ĊJ����
	FpGame->ScriptResume();
}

//----------------------------------------------
void TenemBossSpaceship::Initialize(void)
{
	// �E���𐶐�����
	FpGame->CreateEnemy( ENEM_BOSS_RIGHT_WING , 1 , Vector2D(FvPosition.x,FvPosition.y) , Vector2D(FvVelocity.x,FvVelocity.y) );
	// �����𐶐�����
	FpGame->CreateEnemy( ENEM_BOSS_LEFT_WING , 1 , Vector2D(FvPosition.x,FvPosition.y) , Vector2D(FvVelocity.x,FvVelocity.y) );
	// �{�̂𐶐�����
	FpGame->CreateEnemy( ENEM_BOSS_BODY , 1 , Vector2D(FvPosition.x,FvPosition.y) , Vector2D(FvVelocity.x,FvVelocity.y) );
	// �C��𐶐�����
	FpGame->CreateEnemy( ENEM_BOSS_FORTRESS , 1 , Vector2D(FvPosition.x-13,FvPosition.y-7) , Vector2D(FvVelocity.x,FvVelocity.y) );
	FpGame->CreateEnemy( ENEM_BOSS_FORTRESS , 1 , Vector2D(FvPosition.x+13,FvPosition.y-7) , Vector2D(FvVelocity.x,FvVelocity.y) );
}

//---------------------------------------------
BOOL TenemBossSpaceship::Update(double time_elapsed)
{
	if( !FbInitializeFlg){
		Initialize();
		FbInitializeFlg = true;
	}

	switch(FdPattern){	

		case 1:
			if (FdTimer < 20){
				FdTimer++;
				if(FdTimer >= 20){
					FpGame->CreateBullet( 1, FvPosition, Vector2D(0,10));	
					for(int i=0; i < 3; ++i){
						FpGame->CreateBullet( 1, FvPosition, Vector2D(0+i*5,10));	
					}
					for(int i=0; i < 3; ++i){
						FpGame->CreateBullet( 1, FvPosition, Vector2D(0+i*(-5),10));	
					}
					FdTimer = 0;
				}
			}
			break;

		case 2:
			if (FdTimer < 20){
				FdTimer++;
				if(FdTimer >= 20){
					FpGame->CreateBullet( 1, FvPosition, Vector2D(0,10));	
					for(int i=0; i < 3; ++i){
						FpGame->CreateBullet( 1, FvPosition, Vector2D(0+i*5,10));	
					}
					for(int i=0; i < 3; ++i){
						FpGame->CreateBullet( BUL_HOMING, Vector2D( FvPosition.x + i* 5, FvPosition.y ), Vector2D(0+i*(-5),10));	
					}
//					FpGame->CreateBullet( 5, FvPosition, Vector2D(0 ,10));
					FdTimer = 0;
				}
			}
			if(!FmTurnFlag && FvPosition.y > 0){
				FpGame->CreateBullet( 5, FvPosition, Vector2D(0 ,1));
				FvVelocity *= -1;
				FmTurnFlag = true;

			}
			if(FmTurnFlag == true && FvPosition.y < -40){
				FvVelocity *= -1;
				FmTurnFlag = false;				
			}
			break;
	}

	FvVelocity.Normalize();
	FvSide = FvVelocity.Perp();
	FvVelocity *= FdMaxSpeed;

	// �I�u�W�F�N�g�����Ă���������󂯎��`�悷�邽�߂̌v�Z
	FdRadian = atan2(FvVelocity.y ,FvVelocity.x);
	FdRadian /= D3DX_PI;
	FdRadian -= 0.5;
	FdTheta = FdRadian * 180 ;

	// subject��observer�̓�����A�������邽�߂ɃT�u�W�F�N�g�ɃI�u�U�[�o�[�̌��ݏ���ʒm����
	{
		std::list<TBaseSubjectObject *>::iterator it;
		for(it = FSubjects.begin(); it!=FSubjects.end(); it++){
			(*it)->RecieveNotify(this);
		}
	}

	// �T�u�W�F�N�g���S�ē|���ꂽ��_���[�W�t���O��true�ɂ���
	if( FSubjects.empty() == true ){
		FbDamageFlg = true;
	}

	if(FdVitality <= 0){
		// �����̔����G�t�F�N�g��\��������
		const int RandRange = 20;		// �����̐����͈�
		const int ExplosionNum = 10;	// �����̐�
		const int ExplosionSpan = 5;	// �����̊Ԋu
		srand((unsigned)time(NULL));
		FiExplosionTimer++;
		if( FiExplosionTimer%ExplosionSpan == 0 ){
			double rw=rand()%RandRange;				// �����̐����͈͓��ŗ����𐶐�
			double rh=rand()%RandRange;
			// �����̐���
			for( int i=0; i < ExplosionNum; ++i ){
				rw=rand()%RandRange;				// �����̐����͈͓��ŗ����𐶐�
				rh=rand()%RandRange;
				FpGame->CreateEffect(EFF_BIG_EXPLOSION, Vector2D(FvPosition.x+(rw - (RandRange>>1)), FvPosition.y+(rh - (RandRange>>1) )) , FvVelocity);
			}
		}
		if( FiExplosionTimer > ExplosionNum*ExplosionSpan ){
			FbExplosionEnd = true;
		}
	}

	if( FbExplosionEnd != false ){
		// �T�u�W�F�N�g�Ɏ��S��ʒm���ăT�u�W�F�N�g���̃I�u�U�[�o�[���X�g���珜�O����(�O�̂���)
		std::list<TBaseSubjectObject *>::iterator it;
		for( it=FSubjects.begin() ; it !=FSubjects.end(); it++  ){
			(*it)->RemoveObserver(this);
		}
		return FALSE;
	}

	return TRUE;
}

//---------------------------------------------
void TenemBossSpaceship::Render( void )
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
void TenemBossSpaceship::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}

//---------------------------------------------
void TenemBossSpaceship::RecieveNotify( TBaseSubjectObject *sub )
{
//	::OutputDebugString( TEXT("Success! (TBaseObserverObject::RecieveNotify())\n") );
//	FdPattern = 2;
	// �����󂯎�����T�u�W�F�N�g�̗̑͂�0�ȉ��Ȃ�
	if( sub->dVitality <= 0 ){
		// �{�X�̃T�u�W�F�N�g���炱�̃I�u�W�F�N�g�����O����
		RemoveSubject(sub);
	}
}


//---------------------------------------------------------------------
// �Փˏ���
void TenemBossSpaceship::ReactHit(double damage){

	// �̗͂����炷 (�q�b�g�������̂̍U���͂��󂯎�肽��)
	if( FbDamageFlg == true ){
		FdVitality -= 1;
	}else{
		FpGame->CreateEffect(EFF_BARRIER, Vector2D(FvPosition.x, FvPosition.y+10), FvVelocity);
//		::OutputDebugString(TEXT("\n�_���[�W�t���O��false����I\n"));	
	}
}