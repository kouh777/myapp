#include "GameDef.h"
#include "TaskManager.h"

#include "sceneGame.h"
#include "sceneGameOver.h"
#include "sceneFade.h"

#include "ObjPlayer.h"
#include "objShot.h"
#include "objEnemy.h"
#include "objBullet.h"
#include "Geometry.h"
#include "BaseMovingObject.h"
#include "BackGround.h"
#include "VertexBuffer.h"

//------------------------------------------
// テストでプレイヤーの体力が0になればタイトルに移動
#include "sceneTitle.h"

//------------------------------------------
// プレイヤー自機
#include "plGranVisor.h"

//------------------------------------------
// 敵
#include "enemBox.h"
#include "enemFish.h"
#include "enemBossFortress.h"

//------------------------------------------
// プレイヤー弾
#include "shNormalShot.h"
#include "shBeamShot.h"
#include "shAimingShot.h"
#include "shHomingShot.h"
#include "shMultipleShot.h"
#include "shMiniMultipleShot.h"
#include "shBlastShot.h"
#include "shBlast.h"

//------------------------------------------
// 敵弾
#include "bulOneWay.h"
#include "bulHoming.h"
#include "bulAiming.h"
#include "bulWave.h"
#include "bulWayAlong.h"

//------------------------------------------
// ゲームスクリプト
#include "GameScript.h"

//------------------------------------------
// 敵ID定義
#define ENEM_BOX					1
#define ENEM_FISH					2
#define ENEM_BOSS_SPACESHITP		10	//	ステージ2ボス
#define ENEM_BOSS_FORTRESS			11	//	ステージ2ボス砲台
#define ENEM_BOSS_RIGHT_WING		12	//	ステージ2ボス右翼
#define ENEM_BOSS_LEFT_WING			13	//	ステージ2ボス左翼

//------------------------------------------
// コンストラクタ
TsceneGame::TsceneGame( void )
	: _Task(12),
	  FiTimer(1),
	  FbFadeFlg(false),
	  FbOverFlg(false),
	  FhWnd(NULL),
	  FiClientX(0),
	  FiClientY(0),
	  FpPlayer(NULL),
	  FpBackGround(NULL),
	  FiCollapsedTime(0)
{
	Initialize();
}

//------------------------------------------
// デストラクタ
TsceneGame::~TsceneGame( void )
{
	int test = 0;

	// 自機
	if( FpPlayer )
		delete FpPlayer;

	{
		// ショット
		std::list< TobjShot * >::iterator it;
		for( it=FpShots.begin(); it!=FpShots.end(); it++ ) {
			delete *it;
		}
		FpShots.clear();
	}

	// enemy
	{
		std::list< TobjEnemy * >::iterator it;
		for( it=FpEnemies.begin(); it!=FpEnemies.end(); it++ ) {
			delete *it;
		}
		FpEnemies.clear();
	}
	// 敵弾
	{
		std::list< TobjBullet * >::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end(); it++) {
			delete *it;
		}
		FpBullets.clear();
	}
	if( FpBackGround ) delete FpBackGround;
//	if( FpGameScript ) delete FpGameScript;
}

//------------------------------------------
// 初期化関数
bool TsceneGame::Initialize( void )
{

	FhWnd = TaskManager().GethWnd();
	FiClientX = TaskManager().GetiClientX()-270;
	FiClientY = TaskManager().GetiClientY();

	// 画像をメモリに読み込む
	FpSprites = DxGraphics9().CreateSpriteFormFile(TEXT("sprites2.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 0));
	FpBackGroundSprite = DxGraphics9().CreateSpriteFormFile(TEXT("space3.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 0)); 
	FpUiBackGround = DxGraphics9().CreateSpriteFormFile(TEXT("uiback.png"),D3DFMT_A8R8G8B8 , 0);
	FpPlayerSprite = DxGraphics9().CreateSpriteFormFile(TEXT("player01.png"),D3DFMT_A8R8G8B8 , 0);
	FpShotSprite = DxGraphics9().CreateSpriteFormFile(TEXT("ef001.png"),D3DFMT_A8R8G8B8 , 0);
	FpEnemySprite = DxGraphics9().CreateSpriteFormFile(TEXT("chantougoke.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 0));
	FpBossSpaceshipSprite = DxGraphics9().CreateSpriteFormFile(TEXT("chantougoke.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 255));

	FpPlayerSaberSprite = DxGraphics9().CreateSpriteFormFile(TEXT("player001a.png"),D3DFMT_A8R8G8B8 , 0);
	FpPlayerVisorSprite = DxGraphics9().CreateSpriteFormFile(TEXT("player002a.png"),D3DFMT_A8R8G8B8 , 0);

	// 背景インスタンス作成
	FpBackGround = new TBackGround( *this );

	// 自機作成
	FpPlayer = new TplGranVisor( this, Vector2D(-50,0), 1.6 ); 

	// ゲームスクリプト作成
	FpGameScript = new TGameScript(this);
	FpGameScript->ReadScriptFile(TEXT("test_script.txt"));

	return true;
}
//------------------------------------------
// 実行関数
bool TsceneGame::Execute( double ElapsedTime )
{

	FpBackGround->Update(ElapsedTime);
	if( FpPlayer )
		FpPlayer->Update( ElapsedTime );
	if( !FpPlayer)
		int test = 0;

	{	// ショット
		std::list< TobjShot * >::iterator it;
		for( it=FpShots.begin(); it!=FpShots.end();  ) {
			if( !((*it)->Update(ElapsedTime)) ) {
				delete *it;
				// リスト削除
				it = FpShots.erase(it);

			} else
				it++;
		}
	}

	{	// enemy
		std::list< TobjEnemy * >::iterator it;
		for( it=FpEnemies.begin(); it!=FpEnemies.end();  ) {
			if( !((*it)->Update(ElapsedTime)) ) {
				delete *it;
				// リスト削除
				it = FpEnemies.erase(it);

			} else
				it++;
		}
	}

	{	// 敵弾
		std::list< TobjBullet *>::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end(); ){
			if( !(*it)->Update(ElapsedTime)){
				delete *it;
				// リスト削除
				it = FpBullets.erase(it);
			} else
				it++;
		}
	}
	// 衝突判定
	Collision(ElapsedTime);

	// 移動
	if(FpPlayer)
		FpPlayer->Move(ElapsedTime);

	{	// ショット
		std::list< TobjShot * >::iterator it;
		for( it=FpShots.begin(); it!=FpShots.end();  ) {
			if( !((*it)->Move(ElapsedTime)) ) {
				delete *it;
				// リスト削除
				it = FpShots.erase(it);

			} else
				it++;
		}
	}

	{	// 敵
		std::list< TobjEnemy * >::iterator it;
		for( it=FpEnemies.begin(); it!=FpEnemies.end();  ) {
			if( !((*it)->Move(ElapsedTime)) ) {
				delete *it;
				// リスト削除
				it = FpEnemies.erase(it);

			} else
				it++;
		}
	}

	{	// 敵の弾
		std::list< TobjBullet * >::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end();  ) {
			if( !((*it)->Move(ElapsedTime)) ) {
				delete *it;
				// リスト削除
				it = FpBullets.erase(it);

			} else
				it++;
		}
	}

	FiCollapsedTime++;

	// GameScriptから敵出現情報を読み取る
	FpGameScript->Excute(ElapsedTime);

	// FpPlayerがnullでなければ
	if(FpPlayer){
		if(FpPlayer->Update(ElapsedTime) == FALSE && FbOverFlg == FALSE){
			delete FpPlayer;
			FpPlayer = NULL;
			FbOverFlg = TRUE;
		}
	}
	if(FbOverFlg == TRUE){
		FiTimer -= ElapsedTime;
		if(FiTimer <= 0){
			if(FbFadeFlg == FALSE){
				new TsceneFade();
				FbFadeFlg = TRUE;
			}

			// -2.0はfadeを始めてから次をnewするまでの遅延時間
			if(FiTimer <= -2.0){
				new TsceneTitle();
				return false;
			}
		}
	}
	return true;
}

//------------------------------------------
// 描画関数
void TsceneGame::Draw( void )
{
	FpBackGround->Render();

	// Ui描画
	RECT srcRec2 = { 0, 0, 250, 600};	// 画像の中から切り取る座標
//	FpUiBackGround->Render(&srcRec2, D3DXVECTOR3( 550, 0, 0), 0.6f);

	if( FpPlayer )
		FpPlayer->Render();

	{	// ショット
		std::list< TobjShot * >::iterator it;
		for( it=FpShots.begin(); it!=FpShots.end(); it++ ) {
			(*it)->Render();
		}
	}

	{	// enemy
		std::list< TobjEnemy * >::iterator it;
		for( it=FpEnemies.begin(); it!=FpEnemies.end(); it++ ) {
			(*it)->Render();
		}
	}

	{	// 敵弾
		std::list< TobjBullet *>::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end(); it++){
			(*it)->Render();
		}
	}
}

//------------------------------------------
// 3d描画関数
void TsceneGame::Draw3D(void)
{
}

//------------------------------------------
// 描画関数
void TsceneGame::DrawCgdi( void )
{
	if( FpPlayer ) FpPlayer->RenderCgdi();

	{	// ショット
		std::list< TobjShot * >::iterator it;
		for( it=FpShots.begin(); it!=FpShots.end(); it++ ) {
			(*it)->RenderCgdi();
		}
	}

	{	// enemy
		std::list< TobjEnemy * >::iterator it;
		for( it=FpEnemies.begin(); it!=FpEnemies.end(); it++ ) {
			(*it)->RenderCgdi();
		}
	}

	{	// 敵弾
		std::list< TobjBullet *>::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end(); it++){
			(*it)->RenderCgdi();
		}
	}
}


//------------------------------------------
// メッセージ処理
HRESULT TsceneGame::MessageHandle( UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message ) {

		case WM_LBUTTONDOWN:

			return 0;
	}

	return 0;
}

//------------------------------------------
void TsceneGame::ViewPortTransform( std::vector<Vector2D> &vPoints )
{
	double xs = FiClientX / 100.;
	double ys = FiClientY / 100.;

	// (   w/100      0  0 )
	// (   0      h/100  0 )
	// (   w/2      h/2  1 )
	for( DWORD i=0; i<vPoints.size(); i++ ) {
		vPoints[i].x = vPoints[i].x * xs + FiClientX/2.;  
		vPoints[i].y = vPoints[i].y * ys + FiClientY/2.;  
	}
}

//------------------------------------------
// ショットを作成する
void TsceneGame::CreateShot( const int &type, const Vector2D &pos, const Vector2D &velocity )
{
	TobjShot *pshot;
	switch(type){
		// 方向弾
		case 1:
			pshot = new TshNormalShot( this, pos, velocity );
			break;
		// ビーム
		case 2:
			pshot = new TshBeamShot( this, pos, velocity );
			break;
		// 狙い撃ち弾
		case 3:
			pshot = new TshAimingShot( this, pos, velocity );
			break;
		// ホーミング弾
		case 4:
			pshot = new TshHomingShot( this, pos, velocity);
			break;
		// 分裂弾(分裂前)
		case 5:
			pshot = new TshMultipleShot( this, pos, velocity);
			break;
		// 分裂弾(分裂後)
		case 6:
			pshot = new TshMiniMultipleShot( this, pos, velocity);
			break;
		// 爆発弾
		case 7:
			pshot = new TshBlastShot( this, pos, velocity);
			break;
		// 爆発弾(爆風)
		case 8:
			pshot = new TshBlast( this, pos, velocity);
			break;
	}
	FpShots.push_back( pshot );
}

//------------------------------------------
// enemyを作成する
void TsceneGame::CreateEnemy( const int &type , const int &pattern ,const Vector2D &pos, const Vector2D &velocity )
{
	TobjEnemy *penemy;
	switch(type){
		case 0:
			break;

		// 雑魚敵　ボックス
		case ENEM_BOX:
			penemy = new TenemBox( this, pattern, pos, velocity );
			break;

		// 雑魚的　フィッシュ
		case ENEM_FISH:
			penemy = new TenemFish( this, pattern, pos, velocity );
			break;

		// ステージ2ボス
		case ENEM_BOSS_SPACESHITP:
			break;

		// ステージ2ボス砲台
		case ENEM_BOSS_FORTRESS:
			penemy = new TenemBossFortress( this, pattern, pos, velocity );
			break;

		// ステージ2ボス右翼
		case ENEM_BOSS_RIGHT_WING:
			break;

		// ステージ2ボス左翼
		case ENEM_BOSS_LEFT_WING:
			break;
	}
	FpEnemies.push_back( penemy );
}

//------------------------------------------
void TsceneGame::CreateBullet( const int &type , const Vector2D &pos, const Vector2D &velocity)
{
	TobjBullet *pbullet;
	switch(type){
		// 方向弾
		case 1:
			pbullet = new TbulOneWay( this, pos, velocity);
			break;
		// ホーミング弾
		case 2:
			pbullet = new TbulHoming( this, pos, velocity);
			break;
		// 狙い撃ち弾
		case 3:
			pbullet = new TbulAiming( this, pos, velocity);
			break;
		// 波打ち弾
		case 4:
			pbullet = new TbulWave( this, pos, velocity);
			break;
		// 経路追従弾 未実装
		case 5:
			pbullet = new TbulWayAlong( this, pos,velocity);
			break;
	}
	FpBullets.push_back( pbullet );
}

void TsceneGame::Collision (double elapsedtime)
{
	{	// プレイヤーと敵の弾
		std::list< TobjBullet * >::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end(); it++ ) {
			if(CollisionCircleS(FpPlayer, *it))
			// 当たり判定の計算がおかしいようなのでコメントアウト
			//if(CollisionCircle(FpPlayer, *it,elapsedtime) <= 1.0 )
			{
				(*it)->ReactHit(elapsedtime);
				FpPlayer->ReactHit(elapsedtime);	// Playerのhpが0になったときの処理を入れれてないので一旦コメントアウト
			}
		}
	}

	{	// プレイヤーの弾と敵
		std::list< TobjShot * >::iterator sit;
		std::list< TobjEnemy * >::iterator eit;
		for( sit=FpShots.begin(); sit!=FpShots.end(); sit++ ) {
			for( eit=FpEnemies.begin(); eit!=FpEnemies.end(); eit++ ){
				if(CollisionCircleS(*sit, *eit)){
					(*sit)->ReactHit(elapsedtime);
					(*eit)->ReactHit(elapsedtime);
				}
			}
		}
	}
}

// プレイヤーとEnemyの距離を測り、一番距離が近いEnemyを返す
const TobjEnemy* TsceneGame::GetNearestEnemy(void)
{
	std::list< TobjEnemy * >::iterator it;
	TobjEnemy *ReturnEnemy = NULL;
	// プレイヤーがNULLならばNULLを返す
	if(FpPlayer == NULL)
		return ReturnEnemy;
	// プレイヤーがNULLでなければ一番近くの敵を返す
	else{
		int length = (FiClientX*FiClientX)+(FiClientY*FiClientY);	// 画面の斜めの長さの2乗を入れておく
		for(it = FpEnemies.begin(); it != FpEnemies.end(); it++){
			if(length > ((*it)->vPosition - FpPlayer->vPosition).lengthSq() ){
				length = (int)( ((*it)->vPosition - FpPlayer->vPosition).lengthSq() );
				ReturnEnemy = (*it);
			}
		}
	}
	return ReturnEnemy;
}