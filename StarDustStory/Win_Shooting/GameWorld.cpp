
#include "GameDef.h"
#include "ObjPlayer.h"

#include "objShot.h"
#include "objEnemy.h"
#include "objBullet.h"
#include "GameWorld.h"
#include "Geometry.h"
#include "BaseMovingObject.h"
#include "BackGround.h"
#include "VertexBuffer.h"

//------------------------------------------
// 敵
#include "enemBox.h"
#include "enemFish.h"

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
#define ENEM_BOX	1
#define ENEM_FISH	2


//------------------------------------------
// コンストラクタ
TGameWorld::TGameWorld( void )
	: FhWnd(NULL),
	  FiClientX(0),
	  FiClientY(0),
	  FpPlayer(NULL),
	  FiCollapsedTime(0),
  	  FpTeaPot(NULL),
	  FRotation(0)
{
}

//------------------------------------------
// デストラクタ
TGameWorld::~TGameWorld( void )
{
	// 自機
	if( FpPlayer ) delete FpPlayer;

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
}

//------------------------------------------
// 初期化関数
bool TGameWorld::Initialize( HWND hWnd, int cx, int cy )
{
	FhWnd = hWnd;
	FiClientX = cx-270;
	FiClientY = cy;



	// 画像をメモリに読み込む
	FpSprites = DxGraphics9().CreateSpriteFormFile(TEXT("sprites2.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 0));
	FpBackGround = DxGraphics9().CreateSpriteFormFile(TEXT("background2.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 0)); 
	FpUiBackGround = DxGraphics9().CreateSpriteFormFile(TEXT("uiback.png"),D3DFMT_A8R8G8B8 , 0);
	FpPlayerSprite = DxGraphics9().CreateSpriteFormFile(TEXT("player01.png"),D3DFMT_A8R8G8B8 , 0);
	FpShotSprite = DxGraphics9().CreateSpriteFormFile(TEXT("ef001.png"),D3DFMT_A8R8G8B8 , 0);

	FpEnemySprite = DxGraphics9().CreateSpriteFormFile(TEXT("chantougoke.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 0));



	// 自機作成
	FpPlayer = new TobjPlayer( Vector2D(-50,0), 1.6 ); 

	FpGameScript = new TGameScript(this);
	FpGameScript->ReadScriptFile(TEXT("test_script.txt"));

	// ティーポッド表示
	FpTeaPot = DxGraphics9().CreateTeapot();
	// マテリアルを設定する
	D3DMATERIAL9 material;
	ZeroMemory(&material, sizeof material);
	material.Ambient.r=0.2f;
	FpTeaPot->SetMaterial(0, material);

	return true;
}
//------------------------------------------
// 実行関数
void TGameWorld::Execute( double elapsed )
{
	BackGround().Update(elapsed);
	if( FpPlayer )
		FpPlayer->Update( elapsed );

	{	// ショット
		std::list< TobjShot * >::iterator it;
		for( it=FpShots.begin(); it!=FpShots.end();  ) {
			if( !((*it)->Update(elapsed)) ) {
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
			if( !((*it)->Update(elapsed)) ) {
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
			if( !(*it)->Update(elapsed)){
				delete *it;
				// リスト削除
				it = FpBullets.erase(it);
			} else
				it++;
		}
	}
	// 衝突判定
	Collision(elapsed);

	// 移動
	if(FpPlayer)FpPlayer->Move(elapsed);

	{	// ショット
		std::list< TobjShot * >::iterator it;
		for( it=FpShots.begin(); it!=FpShots.end();  ) {
			if( !((*it)->Move(elapsed)) ) {
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
			if( !((*it)->Move(elapsed)) ) {
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
			if( !((*it)->Move(elapsed)) ) {
				delete *it;
				// リスト削除
				it = FpBullets.erase(it);

			} else
				it++;
		}
	}

	FiCollapsedTime++;

	// ティーポッド
	FpTeaPot->SetRotation( FRotation , 0 , 0);
	FRotation += 0.05f;

	// GameScriptから敵出現情報を読み取る
	FpGameScript->Excute(elapsed);
}

//------------------------------------------
// 描画関数
void TGameWorld::Draw( void )
{
	BackGround().Render();

	// Ui描画
	RECT srcRec2 = { 0, 0, 250, 600};	// 画像の中から切り取る座標
	FpUiBackGround->Render(&srcRec2, D3DXVECTOR3( 550, 0, 0), 0.6f);

	if( FpPlayer ) FpPlayer->Render();

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
void TGameWorld::Draw3D(void)
{
	// ティーポッド
	FpTeaPot->Render();
}

//------------------------------------------
// 描画関数
void TGameWorld::DrawCgdi( void )
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
HRESULT TGameWorld::MessageHandle( UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message ) {

		case WM_LBUTTONDOWN:

			return 0;
	}

	return 0;
}

//------------------------------------------
void TGameWorld::ViewPortTransform( std::vector<Vector2D> &vPoints )
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
void TGameWorld::CreateShot( const int &type, const Vector2D &pos, const Vector2D &velocity )
{
	TobjShot *pshot;
	switch(type){
		// 方向弾
		case 1:
			pshot = new TshNormalShot( pos, velocity );
			break;
		// ビーム
		case 2:
			pshot = new TshBeamShot( pos, velocity );
			break;
		// 狙い撃ち弾
		case 3:
			pshot = new TshAimingShot( pos, velocity );
			break;
		// ホーミング弾
		case 4:
			pshot = new TshHomingShot( pos, velocity);
			break;
		// 分裂弾(分裂前)
		case 5:
			pshot = new TshMultipleShot( pos, velocity);
			break;
		// 分裂弾(分裂後)
		case 6:
			pshot = new TshMiniMultipleShot( pos, velocity);
			break;
		// 爆発弾
		case 7:
			pshot = new TshBlastShot( pos, velocity);
			break;
		// 爆発弾(爆風)
		case 8:
			pshot = new TshBlast( pos, velocity);
			break;
	}
	FpShots.push_back( pshot );

}

//------------------------------------------
// enemyを作成する
void TGameWorld::CreateEnemy( const int &type , const int &pattern ,const Vector2D &pos, const Vector2D &velocity )
{
	TobjEnemy *penemy;
	switch(type){
		case 0:
			break;

		// 雑魚敵　ボックス
		case ENEM_BOX:
			penemy = new TenemBox( pattern, pos, velocity );
			break;

		// 雑魚的　フィッシュ
		case ENEM_FISH:
			penemy = new TenemFish( pattern, pos, velocity );
			break;

	}
	FpEnemies.push_back( penemy );
}

//------------------------------------------
void TGameWorld::CreateBullet( const int &type , const Vector2D &pos, const Vector2D &velocity)
{
	TobjBullet *pbullet;
	switch(type){
		// 方向弾
		case 1:
			pbullet = new TbulOneWay(pos, velocity);
			break;
		// ホーミング弾
		case 2:
			pbullet = new TbulHoming(pos, velocity);
			break;
		// 狙い撃ち弾
		case 3:
			pbullet = new TbulAiming(pos, velocity);
			break;
		// 波打ち弾
		case 4:
			pbullet = new TbulWave(pos, velocity);
			break;
		// 経路追従弾
		case 5:
			pbullet = new TbulWayAlong(pos,velocity);
			break;
	}
	FpBullets.push_back( pbullet );
}

void TGameWorld::Collision (double elapsedtime)
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
const TobjEnemy* TGameWorld::GetNearestEnemy(void)
{
	std::list< TobjEnemy * >::iterator it;
	TobjEnemy *ReturnEnemy = NULL;
	int length = (FiClientX*FiClientX)+(FiClientY*FiClientY);	// 画面の斜めの長さの2乗を入れておく
	for(it = FpEnemies.begin(); it != FpEnemies.end(); it++){
		if(length > ((*it)->vPosition - FpPlayer->vPosition).lengthSq() ){
			length = ((*it)->vPosition - FpPlayer->vPosition).lengthSq();
			ReturnEnemy = (*it);
		}
	}
	return ReturnEnemy;
}