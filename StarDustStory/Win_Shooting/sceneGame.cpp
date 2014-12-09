#include "GameDef.h"
#include "TaskManager.h"

#include "sceneGame.h"
#include "sceneGameOver.h"
#include "sceneFade.h"

#include "ObjPlayer.h"
#include "objShot.h"
#include "observerEnemy.h"
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
#include "plGranSaber.h"

//------------------------------------------
// 敵
#include "enemBox.h"
#include "enemFish.h"
#include "enemBossFortress.h"
#include "enemBossSpaceShip.h"
#include "enemBossRightWing.h"
#include "enemBossLeftWing.h"
#include "enemBossBody.h"
#include "enemBossDegin.h"
#include "enemBossUnderson.h"
#include "enemBossShadowSaber.h"
#include "enemBossShadowVisor.h"
#include "enemBossAlbert.h"
#include "enemCommet.h"

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
// エフェクト
#include "effExplosion.h"
#include "effHit.h"
#include "effBarrier.h"
#include "effScope.h"
#include "effBigExplosion.h"
#include "effFinalBigExplosion.h"

//------------------------------------------
// 障害物

//------------------------------------------
// アイテム

//------------------------------------------
// Ui
#include "uiCharacter.h"
#include "uiPlayerLife.h"
#include "uiPlayerVitality.h"

//------------------------------------------
// ゲームスクリプト
#include "GameScript.h"

//------------------------------------------
// 
#define UI_WIDTH 270

//------------------------------------------
// コンストラクタ
TsceneGame::TsceneGame( int player_id, STG_ID stage_id )
	: _Task(12),
	  FiTimer(1),
	  FbFadeFlg(false),
	  FbOverFlg(false),
	  FhWnd(NULL),
	  FiClientX(0),
	  FiClientY(0),
	  FpPlayer(NULL),
	  FpBackGround(NULL),
	  FiCollapsedTime(0),
	  FiPlayerId(player_id),
	  FStageId(stage_id),
	  FiLife(PLAYER_MAX_LIFE)
{
	Initialize();
}

//------------------------------------------
// デストラクタ
TsceneGame::~TsceneGame( void )
{

	// 自機
	if( FpPlayer )
		delete FpPlayer;

	{
		// ショット
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpShots.begin(); it!=FpShots.end(); it++ ) {
			delete *it;
		}
		FpShots.clear();
	}

	// enemy
	{
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpEnemies.begin(); it!=FpEnemies.end(); it++ ) {
			delete *it;
		}
		FpEnemies.clear();
	}
	// 敵弾
	{
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end(); it++) {
			delete *it;
		}
		FpBullets.clear();
	}
	// エフェクト
	{
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpEffects.begin(); it!=FpEffects.end(); it++) {
			delete *it;
		}
		FpEffects.clear();
	}
	// 障害物
	{
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpGimmicks.begin(); it!=FpGimmicks.end(); it++) {
			delete *it;
		}
		FpGimmicks.clear();
	}

	// アイテム
	{
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpItems.begin(); it!=FpItems.end(); it++) {
			delete *it;
		}
		FpItems.clear();
	}

	// Ui
	{
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpUis.begin(); it!=FpUis.end(); it++) {
			delete *it;
		}
		FpUis.clear();
	}

	if( FpBackGround ) delete FpBackGround;
//	if( FpGameScript ) delete FpGameScript;
}

//------------------------------------------
// 初期化関数
bool TsceneGame::Initialize( void )
{

	FhWnd = TaskManager().GethWnd();
	FiClientX = TaskManager().GetiClientX();
	FiClientY = TaskManager().GetiClientY();

	// 画像をメモリに読み込む
	FpSprites = DxGraphics9().CreateSpriteFormFile(TEXT("sprites2.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 0));
	FpBackGroundSprite = DxGraphics9().CreateSpriteFormFile(TEXT("space4.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 255, 255)); 
	FpUiBackGround = DxGraphics9().CreateSpriteFormFile(TEXT("uiback.png"),D3DFMT_A8R8G8B8 , 0);
	FpPlayerSprite = DxGraphics9().CreateSpriteFormFile(TEXT("player01.png"),D3DFMT_A8R8G8B8 , 0);
	FpShotSprite = DxGraphics9().CreateSpriteFormFile(TEXT("ef001.png"),D3DFMT_A8R8G8B8 , 0);
	FpEnemySprite = DxGraphics9().CreateSpriteFormFile(TEXT("chantougoke.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 0));
	FpBossSpaceshipSprite = DxGraphics9().CreateSpriteFormFile(TEXT("boss002c.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 255));
	FpBossDegin= DxGraphics9().CreateSpriteFormFile(TEXT("boss_degin01.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 255));			
	FpBossUnderson= DxGraphics9().CreateSpriteFormFile(TEXT("boss_underson01.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 255));	
	FpBossShadowVisor= DxGraphics9().CreateSpriteFormFile(TEXT("boss_shawdow_visor01.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 255));
	FpBossShadowSaber= DxGraphics9().CreateSpriteFormFile(TEXT("boss_shawdow_visor01.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 255));
	FpBossAlbert= DxGraphics9().CreateSpriteFormFile(TEXT("boss_albert01.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 255));
	
	FpCharacterSeiya= DxGraphics9().CreateSpriteFormFile(TEXT("character_seiya.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 255));
	FpCharacterKanata= DxGraphics9().CreateSpriteFormFile(TEXT("character_kanata.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 255));

	FpBarrier = DxGraphics9().CreateSpriteFormFile(TEXT("barrier.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 255));
	FpScope = DxGraphics9().CreateSpriteFormFile(TEXT("scope.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 255));
	FpHit = DxGraphics9().CreateSpriteFormFile(TEXT("hit_effects.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 255));
	FpAsteroid = DxGraphics9().CreateSpriteFormFile(TEXT("asteroid_fit.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 255));
	FpHpGauge = DxGraphics9().CreateSpriteFormFile(TEXT("hp_gage_sprite.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 80, 80, 80));
	FpExplosionSprite = DxGraphics9().CreateSpriteFormFile(TEXT("final_big_explosion.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 80, 80, 80));

	FpPlayerSaberSprite = DxGraphics9().CreateSpriteFormFile(TEXT("player001a.png"),D3DFMT_A8R8G8B8 , 0);
	FpPlayerVisorSprite = DxGraphics9().CreateSpriteFormFile(TEXT("player002a.png"),D3DFMT_A8R8G8B8 , 0);

	// 背景インスタンス作成
	FpBackGround = new TBackGround( *this );

	// Ui作成
	CreateUi( UI_CHARACTER_SEIYA , Vector2D( 50, 17)  , Vector2D( 0, 0 ) );
	CreateUi( UI_PLAYER_LIFE , Vector2D( 10, -35)  , Vector2D( 0, 0 ) );
	CreateUi( UI_PLAYER_VITALITY , Vector2D( 50, -45)  , Vector2D( 0, 0 ) );

	// 選択したキャラクターを読み取っての自機作成
	switch( FiPlayerId ){
		case PL_GRANDVISOR:
			FpPlayer = new TplGranVisor( this, Vector2D(-50,0), 0.8 ); 
			break;

		case PL_GRANDSAVER:
			FpPlayer = new TplGranSaber( this, Vector2D(-50,0), 0.8 ); 
			break;

		case PL_COMBAT:
			// FpPlayer = new TplGranVisor( this, Vector2D(-50,0), 1.6 ); 
			break;

		default:
			FpPlayer = new TplGranVisor( this, Vector2D(-50,0), 1.6 ); 
			break;
	}

	// ゲームスクリプト作成
	FpGameScript = new TGameScript(this);
	// 選択したステージを読み取ってスクリプトを読み込む
	switch( FStageId ){
		case STAGE_1:
//			FpGameScript->ReadScriptFile(TEXT("stage_debug_script.txt"));
			FpGameScript->ReadScriptFile(TEXT("stage1_script.txt"));
			break;

		case STAGE_2:
			FpGameScript->ReadScriptFile(TEXT("stage2_script.txt"));
			break;

		case STAGE_3:
			FpGameScript->ReadScriptFile(TEXT("stage3_script.txt"));
			break;

		case STAGE_4:
			FpGameScript->ReadScriptFile(TEXT("stage4_script.txt"));
			break;

		case STAGE_5:
			FpGameScript->ReadScriptFile(TEXT("stage5_script.txt"));
			break;

		default:
			FpGameScript->ReadScriptFile(TEXT("stage_debug_script.txt"));
			break;
	}
	
	// バックミュージック再生
	int ch = PlayStreamBGM( TEXT("stage01_bgm.wav") );
	int bgm_vol = GetVolume(ch);
	SetVolume(ch, -300);
	
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
		std::list< TBaseMovingObject * >::iterator it;
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
		std::list< TBaseMovingObject * >::iterator it;
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
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end(); ){
			if( !(*it)->Update(ElapsedTime)){
				delete *it;
				// リスト削除
				it = FpBullets.erase(it);
			} else
				it++;
		}
	}

	{	// エフェクト
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpEffects.begin(); it!=FpEffects.end(); ){
			if( !(*it)->Update(ElapsedTime)){
				delete *it;
				// リスト削除
				it = FpEffects.erase(it);
			} else
				it++;
		}
	}

	{	// 障害物
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpGimmicks.begin(); it!=FpGimmicks.end(); ){
			if( !(*it)->Update(ElapsedTime)){
				delete *it;
				// リスト削除
				it = FpGimmicks.erase(it);
			} else
				it++;
		}
	}

	{	// アイテム
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpItems.begin(); it!=FpItems.end(); ){
			if( !(*it)->Update(ElapsedTime)){
				delete *it;
				// リスト削除
				it = FpItems.erase(it);
			} else
				it++;
		}
	}

	{	// Ui
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpUis.begin(); it!=FpUis.end(); ){
			if( !(*it)->Update(ElapsedTime)){
				delete *it;
				// リスト削除
				it = FpUis.erase(it);
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
		std::list< TBaseMovingObject * >::iterator it;
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
		std::list< TBaseMovingObject * >::iterator it;
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
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end();  ) {
			if( !((*it)->Move(ElapsedTime)) ) {
				delete *it;
				// リスト削除
				it = FpBullets.erase(it);

			} else
				it++;
		}
	}

	{	// エフェクト
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpEffects.begin(); it!=FpEffects.end();  ) {
			if( !((*it)->Move(ElapsedTime)) ) {
				delete *it;
				// リスト削除
				it = FpEffects.erase(it);

			} else
				it++;
		}
	}

	{	// 障害物
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpGimmicks.begin(); it!=FpGimmicks.end();  ) {
			if( !((*it)->Move(ElapsedTime)) ) {
				delete *it;
				// リスト削除
				it = FpGimmicks.erase(it);

			} else
				it++;
		}
	}

	{	// アイテム
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpItems.begin(); it!=FpItems.end();  ) {
			if( !((*it)->Move(ElapsedTime)) ) {
				delete *it;
				// リスト削除
				it = FpItems.erase(it);

			} else
				it++;
		}
	}

	
	{	// Ui
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpUis.begin(); it!=FpUis.end();  ) {
			if( !((*it)->Move(ElapsedTime)) ) {
				delete *it;
				// リスト削除
				it = FpUis.erase(it);

			} else
				it++;
		}
	}


	FiCollapsedTime++;

	// GameScriptから敵出現情報を読み取る、Scriptの最後に達していればシーン終了
	if ( !FpGameScript->Excute(ElapsedTime) ){
//		FbOverFlg = TRUE;
	}

	
	// プレイヤーがnullでなければ
	if(FpPlayer){
		// プレイヤーが死亡したら残機を減らし、プレイヤーを復帰させる
		if(FpPlayer->Update(ElapsedTime) == FALSE){
			delete FpPlayer;
			FpPlayer = NULL;
			FiLife--;
			if( FiLife > 0 )
				FpPlayer = new TplGranVisor( this, Vector2D(0,40), 0.8 ); 
		}
	}
	// プレイヤーの残機が0以下になればゲームオーバー
	if( FiLife <= 0 ){
		FbOverFlg = TRUE;
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
				new TsceneGameOver();
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
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpShots.begin(); it!=FpShots.end(); it++ ) {
			(*it)->Render();
		}
	}

	{	// enemy
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpEnemies.begin(); it!=FpEnemies.end(); it++ ) {
			(*it)->Render();
		}
	}

	{	// 敵弾
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end(); it++){
			(*it)->Render();
		}
	}

	{	// エフェクト
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpEffects.begin(); it!=FpEffects.end(); it++){
			(*it)->Render();
		}
	}

	{	// 障害物
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpGimmicks.begin(); it!=FpGimmicks.end(); it++){
			(*it)->Render();
		}
	}

	{	// アイテム
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpItems.begin(); it!=FpItems.end(); it++){
			(*it)->Render();
		}
	}

	{	// アイテム
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpUis.begin(); it!=FpUis.end(); it++){
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
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpShots.begin(); it!=FpShots.end(); it++ ) {
			(*it)->RenderCgdi();
		}
	}

	{	// enemy
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpEnemies.begin(); it!=FpEnemies.end(); it++ ) {
			(*it)->RenderCgdi();
		}
	}

	{	// 敵弾
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end(); it++){
			(*it)->RenderCgdi();
		}
	}

	{	// エフェクト
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpEffects.begin(); it!=FpEffects.end(); it++){
			(*it)->RenderCgdi();
		}
	}

	{	// 障害物
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpGimmicks.begin(); it!=FpGimmicks.end(); it++){
			(*it)->RenderCgdi();
		}
	}

	{	// アイテム
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpItems.begin(); it!=FpItems.end(); it++){
			(*it)->RenderCgdi();
		}
	}

	{	// Ui
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpUis.begin(); it!=FpUis.end(); it++){
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
	double xs = ( FiClientX - UI_WIDTH ) / 100.;
	double ys = FiClientY / 100.;

	// (   w/100      0  0 )
	// (   0      h/100  0 )
	// (   w/2      h/2  1 )
	for( DWORD i=0; i<vPoints.size(); i++ ) {
		vPoints[i].x = vPoints[i].x * xs + ( FiClientX - UI_WIDTH )/2.;  
		vPoints[i].y = vPoints[i].y * ys + FiClientY/2.;  
	}
}

//------------------------------------------
void TsceneGame::ViewPortTransform( VIEWPORT_KIND kind, std::vector<Vector2D> &vPoints )
{
	double xs = 0;
	double ys = FiClientY / 100.;;
	switch(kind){
		case GAME_VIEWPORT:
			xs = FiClientX / 100.;
			break;

		case UI_VIEWPORT:
			xs = UI_WIDTH / 100.;
			// (   w/100      0  0 )
			// (   0      h/100  0 )
			// (   w/2      h/2  1 )
			for( DWORD i=0; i<vPoints.size(); i++ ) {
				vPoints[i].x = vPoints[i].x * xs + ( FiClientX + UI_WIDTH ) / 2;  
				vPoints[i].y = vPoints[i].y * ys + FiClientY/2.;  
			}
			break;

		case STAGE_VIEWPORT:
			xs = ( FiClientX - UI_WIDTH ) / 100.;
			// (   w/100      0  0 )
			// (   0      h/100  0 )
			// (   w/2      h/2  1 )
			for( DWORD i=0; i<vPoints.size(); i++ ) {
				vPoints[i].x = vPoints[i].x * xs + ( FiClientX - UI_WIDTH )/2.;  
				vPoints[i].y = vPoints[i].y * ys + FiClientY/2.;  
			}
			break;
	}
}

//------------------------------------------
// ショットを作成する
void TsceneGame::CreateShot( const int &type, const Vector2D &pos, const Vector2D &velocity )
{
	TBaseMovingObject *pshot;
	switch(type){
		// 方向弾
		case SH_NORMAL:
			pshot = new TshNormalShot( this, pos, velocity );
			break;
		// ビーム
		case SH_BEAM:
			pshot = new TshBeamShot( this, pos, velocity );
			break;
		// 狙い撃ち弾
		case SH_AIMING:
			pshot = new TshAimingShot( this, pos, velocity );
			break;
		// ホーミング弾
		case SH_HOMING:
			pshot = new TshHomingShot( this, pos, velocity);
			break;
		// 分裂弾(分裂前)
		case SH_MULTIPLE:
			pshot = new TshMultipleShot( this, pos, velocity);
			break;
		// 分裂弾(分裂後)
		case SH_MINI_MULTIPLE:
			pshot = new TshMiniMultipleShot( this, pos, velocity);
			break;
		// 爆発弾
		case SH_BLAST_SHOT:
			pshot = new TshBlastShot( this, pos, velocity);
			break;
		// 爆発弾(爆風)
		case SH_BLAT:
			pshot = new TshBlast( this, pos, velocity);
			break;
	}
	FpShots.push_back( pshot );
}

//------------------------------------------
// enemyを作成する
void TsceneGame::CreateEnemy( const int &type , const int &pattern ,const Vector2D &pos, const Vector2D &velocity )
{
	TBaseMovingObject *penemy;
	switch(type){
		case ENEM_NO:
			break;

		// 雑魚敵　ボックス
		case ENEM_BOX:
			penemy = new TenemBox( this, pattern, pos, velocity );
			break;

		// 雑魚的　フィッシュ
		case ENEM_FISH:
			penemy = new TenemFish( this, pattern, pos, velocity );
			break;

		// ステージ2ボス砲台
		case ENEM_BOSS_FORTRESS:
			penemy = new TenemBossFortress( this, pattern, pos, velocity );
			break;

		// ステージ2ボス
		case ENEM_BOSS_SPACESHITP:
			penemy = new TenemBossSpaceship( this, pattern, pos, velocity );
			break;

		// ステージ2ボス右翼
		case ENEM_BOSS_RIGHT_WING:
			penemy = new TenemBossRightWing( this , pattern , pos, velocity );
			break;

		// ステージ2ボス左翼
		case ENEM_BOSS_LEFT_WING:
			penemy = new TenemBossLeftWing( this , pattern , pos, velocity );
			break;

		// ステージ2ボス左翼
		case ENEM_BOSS_BODY:
			penemy = new TenemBossBody( this , pattern , pos, velocity );
			break;

		//	ジークザデギン(ステージ1,ステージ3ボス)
		case ENEM_BOSS_DEGIN:
			penemy = new TenemBossDegin( this , pattern , pos, velocity );
			break;

		//	エルダアンダーソン(ステージ4ボス)
		case ENEM_BOSS_UNDERSON:
			penemy = new TenemBossUnderson( this , pattern , pos, velocity );
			break;

		//	闇男主人公機(ステージ5ボス)
		case ENEM_BOSS_SHADOW_VISOR:
			penemy = new TenemBossShadowVisor( this , pattern , pos, velocity );
			break;

		//	闇女主人公機(ステージ5ボス)
		case ENEM_BOSS_SHADOW_SABER:
			penemy = new TenemBossShadowSaber( this , pattern , pos, velocity );
			break;

		//	アルバートロイアデウス(ステージ6ラスボス)
		case ENEM_BOSS_ALBERT:
			penemy = new TenemBossAlbert( this , pattern , pos, velocity );
			break;

		// 隕石障害物
		case ENEM_COMMET:
			penemy = new TenemCommet( this, pattern, pos, velocity);
			break;
		// 隕石障害物破片
		case ENEM_MINI_COMMET:
//			penemy = new TbulOneWay( this, pos, velocity);
			break;
	}
	FpEnemies.push_back( penemy );
}

//------------------------------------------
void TsceneGame::CreateBullet( const int &type , const Vector2D &pos, const Vector2D &velocity)
{
	TBaseMovingObject *pbullet;
	switch(type){
		// 方向弾
		case BUL_ONE_WAY:
			pbullet = new TbulOneWay( this, pos, velocity);
			break;
		// ホーミング弾
		case BUL_HOMING:
			pbullet = new TbulHoming( this, pos, velocity);
			break;
		// 狙い撃ち弾
		case BUL_AIMING:
			pbullet = new TbulAiming( this, pos, velocity);
			break;
		// 波打ち弾
		case BUL_WAVE:
			pbullet = new TbulWave( this, pos, velocity);
			break;
		// 経路追従弾 未実装
		case BUL_WAY_ALONG:
			pbullet = new TbulWayAlong( this, pos,velocity);
			break;
	}
	FpBullets.push_back( pbullet );
}

//------------------------------------------
void TsceneGame::CreateEffect( const int &type , const Vector2D &pos, const Vector2D &velocity)
{
	TBaseMovingObject *peffect;
	switch(type){
		// 爆発
		case EFF_EXPLOSION:
			peffect = new TeffExplosion( this, pos, velocity);
			break;
		// バリア
		case EFF_BARRIER:
			peffect = new TeffBarrier( this, pos, velocity);
			break;
		// ヒットエフェクト
		case EFF_HIT:
			peffect = new TeffHit( this, pos, velocity);
			break;
		// ボス弱点表示用スコープ
		case EFF_SCOPE:
			peffect = new TeffScope( this, pos, velocity);
			break;
		// 大爆発エフェクト
		case EFF_BIG_EXPLOSION:
			peffect = new TeffBigExplosion( this, pos, velocity);
			break;
		// 最大爆発エフェクト
		case EFF_FINAL_BIG_EXPLOSION:
			peffect = new TeffFinalBigExplosion( this, pos, velocity);
			break;
	}
	FpEffects.push_back( peffect );
}

//------------------------------------------
void TsceneGame::CreateGimmick( const int &type , const Vector2D &pos, const Vector2D &velocity)
{
	TBaseMovingObject *pgimmick;
	switch(type){
		// ビーム障害物
		case GIM_BEAM:
//			peffect = new TbulOneWay( this, pos, velocity);
			break;
		// 通信ギミック
		case GIM_NETWORK:
//			peffect = new TbulOneWay( this, pos, velocity);
			break;
	}
	FpGimmicks.push_back( pgimmick );
}

//------------------------------------------
void TsceneGame::CreateItem( const int &type , const Vector2D &pos, const Vector2D &velocity)
{
	TBaseMovingObject *pitem;
	switch(type){
		// パワーアップアイテム
		case ITM_POWER:
			pitem = new TbulOneWay( this, pos, velocity);
			break;
		// ソウルチャージパワーアップアイテム
		case ITM_SOUL:
//			peffect = new TbulOneWay( this, pos, velocity);
			break;
		// スコアアップアイテム
		case ITM_SCORE:
//			peffect = new TbulOneWay( this, pos, velocity);
			break;
		// 通信アイテム
		case ITM_NETWORK:
//			peffect = new TbulOneWay( this, pos, velocity);
			break;
	}
	FpBullets.push_back( pitem );
}

//------------------------------------------
void TsceneGame::CreateUi( const int &type , const Vector2D &pos, const Vector2D &velocity)
{
	TBaseMovingObject *ui;
	switch(type){
		// 男性主人公機立ち絵
		case UI_CHARACTER_SEIYA:
			ui = new TuiCharacter( this, pos, velocity);
			break;
		// 女性主人公機立ち絵
		case UI_CHARACTER_KANATA:
//			ui = new TbulOneWay( this, pos, velocity);
			break;
		// プレイヤー体力
		case UI_PLAYER_VITALITY:
			ui = new TuiPlayerVitality( this, pos, velocity);
			break;
		// プレイヤー残機
		case UI_PLAYER_LIFE:
			ui = new TuiPlayerLife( this, pos, velocity);
			break;
	}
	FpUis.push_back( ui );
}

//-----------------------
// Control GameScript
//-----------------------
// スクリプトをポーズする
void TsceneGame::ScriptPause(void)
{
	FpGameScript->Pause();
}

// スクリプトを再開する
void TsceneGame::ScriptResume(void)
{
	FpGameScript->Resume();
}

//------------------------------------------
void TsceneGame::Collision (double elapsedtime)
{
	{	// プレイヤーと敵の弾
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end(); it++ ) {
			if(CollisionCircleS(FpPlayer, *it))
			// 当たり判定の計算がおかしいようなのでコメントアウト
			//if(CollisionCircle(FpPlayer, *it,elapsedtime) <= 1.0 )
			{
				(*it)->ReactHit(elapsedtime);
				FpPlayer->ReactHit(elapsedtime);
			}
		}
	}

	{	// プレイヤーの弾と敵
		std::list< TBaseMovingObject * >::iterator sit;
		std::list< TBaseMovingObject * >::iterator eit;
		for( sit=FpShots.begin(); sit!=FpShots.end(); sit++ ) {
			for( eit=FpEnemies.begin(); eit!=FpEnemies.end(); eit++ ){
				if(CollisionCircleS(*sit, *eit)){
					(*sit)->ReactHit(elapsedtime);
					(*eit)->ReactHit(elapsedtime);
				}
			}
		}
	}

	{	// プレイヤーと敵
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpEnemies.begin(); it!=FpEnemies.end(); it++ ) {
			if(CollisionCircleS(FpPlayer, *it))
			{
				FpPlayer->ReactHit(elapsedtime);
			}
		}
	}

	{	// プレイヤーと障害物
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpGimmicks.begin(); it!=FpGimmicks.end(); it++ ) {
			if(CollisionCircleS(FpPlayer, *it))
			{
//				(*it)->ReactHit(elapsedtime);
//				FpPlayer->ReactHit(elapsedtime);
			}
		}
	}

	{	// プレイヤーとアイテム
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpItems.begin(); it!=FpItems.end(); it++ ) {
			if(CollisionCircleS(FpPlayer, *it))
			{
//				(*it)->ReactHit(elapsedtime);
//				FpPlayer->ReactHit(elapsedtime);
			}
		}
	}
}

// プレイヤーとEnemyの距離を測り、一番距離が近いEnemyを返す
const TBaseMovingObject* TsceneGame::GetNearestEnemy(void)
{
	std::list< TBaseMovingObject * >::iterator it;
	TBaseMovingObject *ReturnEnemy = NULL;
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

// 一番最新の追加されたEnemyを返す。ボスを生成時にSubjectEnemyのコンストラクタで呼び出す
const TBaseMovingObject* TsceneGame::GetNewestEnemy(void)
{
	std::list< TBaseMovingObject * >::reverse_iterator it;
	TBaseMovingObject *ReturnEnemy = NULL;
	if( FpEnemies.empty() == TRUE )
		return NULL;
	else{
		for( it=FpEnemies.rbegin(); it != FpEnemies.rend(); it++ ){
			if( (*it)->bObserver == true ){
				ReturnEnemy = (*it);
				break;
			}
		}
	}
	return ReturnEnemy;
}