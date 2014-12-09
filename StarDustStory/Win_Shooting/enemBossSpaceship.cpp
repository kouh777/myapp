
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
	// スクリプトをポーズする
	FpGame->ScriptPause();
}

//----------------------------------------------
TenemBossSpaceship::~TenemBossSpaceship(void)
{
	// スクリプトを再開する
	FpGame->ScriptResume();
}

//----------------------------------------------
void TenemBossSpaceship::Initialize(void)
{
	// 右翼を生成する
	FpGame->CreateEnemy( ENEM_BOSS_RIGHT_WING , 1 , Vector2D(FvPosition.x,FvPosition.y) , Vector2D(FvVelocity.x,FvVelocity.y) );
	// 左翼を生成する
	FpGame->CreateEnemy( ENEM_BOSS_LEFT_WING , 1 , Vector2D(FvPosition.x,FvPosition.y) , Vector2D(FvVelocity.x,FvVelocity.y) );
	// 本体を生成する
	FpGame->CreateEnemy( ENEM_BOSS_BODY , 1 , Vector2D(FvPosition.x,FvPosition.y) , Vector2D(FvVelocity.x,FvVelocity.y) );
	// 砲台を生成する
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

	// オブジェクト向いている方向を受け取り描画するための計算
	FdRadian = atan2(FvVelocity.y ,FvVelocity.x);
	FdRadian /= D3DX_PI;
	FdRadian -= 0.5;
	FdTheta = FdRadian * 180 ;

	// subjectとobserverの動きを連動させるためにサブジェクトにオブザーバーの現在情報を通知する
	{
		std::list<TBaseSubjectObject *>::iterator it;
		for(it = FSubjects.begin(); it!=FSubjects.end(); it++){
			(*it)->RecieveNotify(this);
		}
	}

	// サブジェクトが全て倒されたらダメージフラグをtrueにする
	if( FSubjects.empty() == true ){
		FbDamageFlg = true;
	}

	if(FdVitality <= 0){
		// 複数の爆発エフェクトを表示させる
		const int RandRange = 20;		// 爆発の生成範囲
		const int ExplosionNum = 10;	// 爆発の数
		const int ExplosionSpan = 5;	// 爆発の間隔
		srand((unsigned)time(NULL));
		FiExplosionTimer++;
		if( FiExplosionTimer%ExplosionSpan == 0 ){
			double rw=rand()%RandRange;				// 爆発の生成範囲内で乱数を生成
			double rh=rand()%RandRange;
			// 爆発の生成
			for( int i=0; i < ExplosionNum; ++i ){
				rw=rand()%RandRange;				// 爆発の生成範囲内で乱数を生成
				rh=rand()%RandRange;
				FpGame->CreateEffect(EFF_BIG_EXPLOSION, Vector2D(FvPosition.x+(rw - (RandRange>>1)), FvPosition.y+(rh - (RandRange>>1) )) , FvVelocity);
			}
		}
		if( FiExplosionTimer > ExplosionNum*ExplosionSpan ){
			FbExplosionEnd = true;
		}
	}

	if( FbExplosionEnd != false ){
		// サブジェクトに死亡を通知してサブジェクト内のオブザーバーリストから除外する(念のため)
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

	// ビューポート変換
	FpGame->ViewPortTransform( vec );
	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};						// 画像の中から切り取る座標
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);

	// 画像を表示する座標
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
// Cgdi描画
void TenemBossSpaceship::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}

//---------------------------------------------
void TenemBossSpaceship::RecieveNotify( TBaseSubjectObject *sub )
{
//	::OutputDebugString( TEXT("Success! (TBaseObserverObject::RecieveNotify())\n") );
//	FdPattern = 2;
	// もし受け取ったサブジェクトの体力が0以下なら
	if( sub->dVitality <= 0 ){
		// ボスのサブジェクトからこのオブジェクトを除外する
		RemoveSubject(sub);
	}
}


//---------------------------------------------------------------------
// 衝突処理
void TenemBossSpaceship::ReactHit(double damage){

	// 体力を減らす (ヒットしたものの攻撃力を受け取りたい)
	if( FbDamageFlg == true ){
		FdVitality -= 1;
	}else{
		FpGame->CreateEffect(EFF_BARRIER, Vector2D(FvPosition.x, FvPosition.y+10), FvVelocity);
//		::OutputDebugString(TEXT("\nダメージフラグがfalseだよ！\n"));	
	}
}