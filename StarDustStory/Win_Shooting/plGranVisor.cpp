#include "GameDef.h"
#include "ObjPlayer.h"
#include "plGranVisor.h"

//---------------------------------------------------------------------
#define TRIMMING__IMAGE_LTX 9	// 
#define TRIMMING__IMAGE_LTY 9	// 
#define TRIMMING__IMAGE_RBX 51	// 
#define TRIMMING__IMAGE_RBY 51	// 


//----------
// TobjPlayer
//----------

//---------------------------------------------------------------------
// コンストラクタ
TplGranVisor::TplGranVisor( TsceneGame *game, Vector2D position, double radius )
	:TobjPlayer(
	game,
	position, 
	radius, 
	Vector2D(), 
	60., 
	Vector2D(0., -1.), 
	1., 
	Vector2D(0.9, 0.9), 
	10.,
	10.0,
	10 ),
	FiBeamPower(0),
	FiShotGauge(0),
	FiShotTime(0),
	FiBeamTime(0),
	pos(D3DXVECTOR3( (float)position.x, (float)position.y, 0)),
	FiImageWidth(TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX),
	FiImageHeight(TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY)

{
}

//---------------------------------------------------------------------
// デストラクタ
TplGranVisor::~TplGranVisor( void )
{
}

//---------------------------------------------------------------------
// 更新
BOOL TplGranVisor::Update(double time_elapsed)
{
	WORD inputBuff = Input().InputBuff;
	WORD DowninputBuff = Input().DownInputBuff;
	
	static const int MinBeamPower = 300;
	static const int ShotMaxGauge = 300;
	static const int MaxShotTime = 10;
	static const int MaxBeamTime = 5;


	// ショット
	if( inputBuff & KEY_Z ) {
		// パワーが足りないときは、ショットを発射
		if( FiBeamPower < MinBeamPower ) {
			FiBeamPower++;
			FiShotGauge = ShotMaxGauge;
			if( FiShotTime == 0 ){
				FpGame->CreateShot( 1, Vector2D( FvPosition.x, FvPosition.y), Vector2D(0,-1) );
			}
		} else {
			// パワーが足りていればビームを打つ
			FiShotGauge = 0;		
			if( FiBeamTime == 0 ) {
				FpGame->CreateShot( 2, FvPosition, Vector2D(0,-1.0) );
			}
		}
	} else {
		// ボタンを離したとき
		FiBeamPower = 0;

		// ゲージが残っている場合、ショットを打つ
		if(FiShotGauge > 0){
			//if(FiShotTime == 0)
			//	FpGame.CreateShot( 5, FvPosition , Vector2D(0,-1.0));
			FiShotGauge--;
		}
	}
	//-----------------
	// デバッグモード
	//-----------------

	// Xキーを押すと敵狙い弾を生成
	if( inputBuff & KEY_X ) {
		FiShotGauge = ShotMaxGauge;
		if( FiShotTime == 0 ){
			FpGame->CreateShot( 3, Vector2D(FvPosition.x ,FvPosition.y) , Vector2D(0,-1) );
			FpGame->CreateShot( 3, Vector2D(FvPosition.x-10 ,FvPosition.y), Vector2D(0,-1) );
			FpGame->CreateShot( 3, Vector2D(FvPosition.x+10 ,FvPosition.y), Vector2D(0,-1) );
		}
		else FiShotGauge = 0;
	}
	// Aキーを押すと敵ホーミング弾を生成
	if( inputBuff & KEY_A ) {
		FiShotGauge = ShotMaxGauge;
		if( FiShotTime == 0 ) FpGame->CreateShot( 4, FvPosition, Vector2D(0,-1) );
		else FiShotGauge = 0;
	}
	// Sキーを押すと分裂弾を生成
	if( inputBuff & KEY_S ) {
		FiShotGauge = ShotMaxGauge;
		if( FiShotTime == 0 ) FpGame->CreateShot( 5, FvPosition, Vector2D(0,-1) );
		else FiShotGauge = 0;
	}
	// Dキーを押すと爆発弾を生成
	if( inputBuff & KEY_D ) {
		FiShotGauge = ShotMaxGauge;
		if( FiShotTime == 0 ) FpGame->CreateShot( 7, FvPosition, Vector2D(0,-1) );
		else FiShotGauge = 0;
	}

	// ショットとビームの待機時間を更新
	FiShotTime = (FiShotTime+1) % MaxShotTime;
	FiBeamTime = (FiBeamTime+1) % MaxBeamTime;

	// 移動
	if( inputBuff & KEY_UP   )
		FvVelocity.y = -20.;	else
	if( inputBuff & KEY_DOWN ) FvVelocity.y =  20.; else
	FvVelocity.y = 0.0;
	if( inputBuff & KEY_LEFT ) FvVelocity.x = -20.;	else
	if( inputBuff & KEY_RIGHT) FvVelocity.x =  20.; else
	FvVelocity.x = 0.0;

	// 正規化
	FvVelocity.Normalize();
	FvVelocity *= this->FdMaxSpeed;

	// クランプを行う
	if( FvPosition.x < this->dBoundingRadius -50) FvPosition.x = this->dBoundingRadius -50;
	if( FvPosition.x > (50 - this->dBoundingRadius) ) FvPosition.x = 50 - this->dBoundingRadius;
	if( FvPosition.y < this->dBoundingRadius -50) FvPosition.y = this->dBoundingRadius -50;
	if( FvPosition.y > (50 - this->dBoundingRadius) ) FvPosition.y = 50 - this->dBoundingRadius;

	if(FdVitality <= 0){
		// 爆発エフェクトを表示させる
		FpGame->CreateEffect(EFF_EXPLOSION, FvPosition, FvVelocity);

		// 爆発音を再生する
		int ch = PlayDxSound( SND_SE_PL_DEATH);
		int bgm_vol = GetVolume(ch);
		SetVolume(ch, -300);

		return FALSE;
	}

	return TRUE;

}

//---------------------------------------------------------------------
// 描画
void TplGranVisor::Render( void )
{
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// ビューポート変換
	FpGame->ViewPortTransform( vec );
	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};		// 画像の中から切り取る座標
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);

	// 画像を表示する座標
	FpGame->FpPlayerVisorSprite->RenderEx(
							&srcRec,
							pos,													// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),					// Scaling
							D3DXVECTOR3(0, 0, 0),									// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							1.0,													// Alpha
							D3DCOLOR(1));													// ColorKey

}

//---------------------------------------------------------------------
// Cgdi描画
void TplGranVisor::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();

#ifdef _DEBUG
	TCHAR String[0xff];

	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// ビューポート変換
	FpGame->ViewPortTransform( vec );

	_stprintf_s(String, 0xFF, TEXT("HP=%f"),FdVitality);
	DxGraphics9().DrawString(String, (int)vec[0].x-30, (int)vec[0].y+15 ,D3DXCOLOR(1.0,1.0,1.0,1.0));
#endif

}

//--------------------------------------------------------------------