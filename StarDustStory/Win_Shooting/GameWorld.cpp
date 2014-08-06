
#include "GameDef.h"
#include "ObjPlayer.h"
#include "objShot.h"
#include "objBeam.h"
#include "objHomingShot.h"
#include "objEnemy.h"
#include "objBullet.h"
#include "enemBox.h"
#include "GameWorld.h"
#include "Geometry.h"
#include "BaseMovingObject.h"
#include "BackGround.h"
#include "VertexBuffer.h"

//------------------------------------------
// 敵弾
#include "bulOneWay.h"
#include "bulHoming.h"
#include "bulAiming.h"

//------------------------------------------
// 敵配置用の構造体を作成
struct EnemySet{
	const int type;				// 敵タイプ
	const int pattern;			// 行動パターン
	const Vector2D pos;			// 出現場所
	const Vector2D velocity;	// 移動方向
	const int time;				// 出現タイミング
};

//------------------------------------------
// 配列を作り、初期的配置を設定
EnemySet EnemyArray[] = 
{
	1 , 3 , Vector2D(0,-40),	Vector2D(0,1) ,	300	,
	1 , 2 , Vector2D(20,-40),	Vector2D(0,0) ,	400	,
	1 , 1 , Vector2D(-20,-40),	Vector2D(0,0) ,	500	,
	1 , 4 , Vector2D(0,-50),	Vector2D(0,1) ,	600	,
	1 , 4 , Vector2D(-10,-50),	Vector2D(0,1) ,	600	,
	1 , 4 , Vector2D(10,-50),	Vector2D(0,1) ,	600	,
	1 , 4 , Vector2D(-20,-50),	Vector2D(0,1) ,	600	,
	1 , 4 , Vector2D(0,-50),	Vector2D(0,1) ,	700	,
	1 , 4 , Vector2D(-20,-50),	Vector2D(0,1) ,	800	,
	1 , 4 , Vector2D(40,-50),	Vector2D(0,1) ,	900	,
	1 , 4 , Vector2D(-40,-50),	Vector2D(0,1) ,	900	,

};

//------------------------------------------
// コンストラクタ
TGameWorld::TGameWorld( void )
	: FhWnd(NULL),
	  FiClientX(0),
	  FiClientY(0),
	  FpPlayer(NULL),
	  FiCollapsedTime(0)
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
	// ビーム
	{
		std::list< TobjBeam * >::iterator it;
		for( it=FpBeams.begin(); it!=FpBeams.end(); it++ ) {
			delete *it;
		}
		FpShots.clear();
	}
	// ホーミング弾
	{
		std::list< TobjHomingShot * >::iterator it;
		for( it=FpHomingShots.begin(); it!=FpHomingShots.end(); it++ ) {
			delete *it;
		}
		FpHomingShots.clear();
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

	// 自機作成
	FpPlayer = new TobjPlayer( Vector2D(-50,0), 1.6 ); 

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

	{	// ビーム
		std::list< TobjBeam * >::iterator it;
		for( it=FpBeams.begin(); it!=FpBeams.end();  ) {
			if( !((*it)->Update(elapsed)) ) {
				delete *it;
				// リスト削除
				it = FpBeams.erase(it);

			} else
				it++;
		}
	}
	
	{	// ホーミング弾
		std::list< TobjHomingShot * >::iterator it;
		for( it=FpHomingShots.begin(); it!=FpHomingShots.end();  ) {
			if( !((*it)->Update(elapsed)) ) {
				delete *it;
				// リスト削除
				it = FpHomingShots.erase(it);

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

	{	// ビーム
		std::list< TobjBeam * >::iterator it;
		for( it=FpBeams.begin(); it!=FpBeams.end();  ) {
			if( !((*it)->Move(elapsed)) ) {
				delete *it;
				// リスト削除
				it = FpBeams.erase(it);

			} else
				it++;
		}
	}

	{	// ホーミング弾
		std::list< TobjHomingShot * >::iterator it;
		for( it=FpHomingShots.begin(); it!=FpHomingShots.end();  ) {
			if( !((*it)->Move(elapsed)) ) {
				delete *it;
				// リスト削除
				it = FpHomingShots.erase(it);

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

	// enemyをEnemyArrayのデータを読み取り生成
	for(int i=0; i< sizeof EnemyArray / sizeof EnemyArray[0]; ++i){
		if(FiCollapsedTime == EnemyArray[i].time){
			CreateEnemy (EnemyArray[i].type, EnemyArray[i].pattern, EnemyArray[i].pos,EnemyArray[i].velocity);
		}
	}
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

	{	// ビーム
		std::list< TobjBeam * >::iterator it;
		for( it=FpBeams.begin(); it!=FpBeams.end(); it++ ) {
			(*it)->Render();
		}
	}

	{	// ホーミング弾
		std::list< TobjHomingShot * >::iterator it;
		for( it=FpHomingShots.begin(); it!=FpHomingShots.end(); it++ ) {
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

	{	// ビーム
		std::list< TobjBeam * >::iterator it;
		for( it=FpBeams.begin(); it!=FpBeams.end(); it++ ) {
			(*it)->RenderCgdi();
		}
	}

	{	// ビーム
		std::list< TobjHomingShot * >::iterator it;
		for( it=FpHomingShots.begin(); it!=FpHomingShots.end(); it++ ) {
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
void TGameWorld::CreateShot( const Vector2D &pos, const Vector2D &velocity )
{
	TobjShot *pshot = new TobjShot( pos, velocity );
	FpShots.push_back( pshot );

}

//------------------------------------------
// ビームを作成する
void TGameWorld::CreateBeam( const Vector2D &pos, const Vector2D &velocity )
{
	TobjBeam *pbeam = new TobjBeam( pos, velocity );
	FpBeams.push_back( pbeam );

}

//------------------------------------------
// ホーミング弾を作成する
void TGameWorld::CreateHomingShot( const Vector2D &pos, const Vector2D &velocity )
{
	TobjHomingShot *phomingshot = new TobjHomingShot( pos, velocity );
	FpHomingShots.push_back( phomingshot );

}

//------------------------------------------
// enemyを作成する
void TGameWorld::CreateEnemy( const int &type , const int &pattern ,const Vector2D &pos, const Vector2D &velocity )
{
	TobjEnemy *penemy;
	switch(type){
		case 0:
			break;
		case 1:
			penemy = new TenemBox( pattern, pos, velocity );
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
		// 追い撃ち弾
		case 3:
			pbullet = new TbulAiming(pos, velocity);
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

	{	// プレイヤーの通常弾と敵
		std::list< TobjShot * >::iterator sit;
		std::list< TobjEnemy * >::iterator eit;
		for( sit=FpShots.begin(); sit!=FpShots.end(); sit++ ) {
			for( eit=FpEnemies.begin(); eit!=FpEnemies.end(); eit++ ){
				if(CollisionCircle(*sit, *eit,elapsedtime) <= 1.0 ){
					(*sit)->ReactHit(elapsedtime);
					(*eit)->ReactHit(elapsedtime);
				}
			}
		}
	}

	{	// プレイヤーのビームと敵
		std::list< TobjBeam * >::iterator bit;
		std::list< TobjEnemy * >::iterator eit;
		for( bit=FpBeams.begin(); bit!=FpBeams.end(); bit++ ) {
			for( eit=FpEnemies.begin(); eit!=FpEnemies.end(); eit++ ){
				if(CollisionCircle(*bit, *eit,elapsedtime) <= 1.0 ){
					(*bit)->ReactHit(elapsedtime);
					(*eit)->ReactHit(elapsedtime);
				}
			}
		}
	}
}

// shotsとEnemyの距離を測り、一番距離が近いEnemyを返す
const TobjEnemy* TGameWorld::GetNearestEnemy(void)
{
	std::list< TobjEnemy * >::iterator it;
	TobjEnemy *ReturnEnemy = NULL;
	int length = (FiClientX*FiClientX)+(FiClientY*FiClientY);	// 画面の斜めの長さの2乗を入れておく
	for(it = FpEnemies.begin(); it != FpEnemies.end(); it++){
		if(length > ((*it)->vPosition - FpPlayer->vPosition).length() ){
			length = ((*it)->vPosition - FpPlayer->vPosition).length();
			ReturnEnemy = (*it);
		}
	}
	return ReturnEnemy;
}