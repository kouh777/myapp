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
// �e�X�g�Ńv���C���[�̗̑͂�0�ɂȂ�΃^�C�g���Ɉړ�
#include "sceneTitle.h"

//------------------------------------------
// �v���C���[���@
#include "plGranVisor.h"
#include "plGranSaber.h"

//------------------------------------------
// �G
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
// �v���C���[�e
#include "shNormalShot.h"
#include "shBeamShot.h"
#include "shAimingShot.h"
#include "shHomingShot.h"
#include "shMultipleShot.h"
#include "shMiniMultipleShot.h"
#include "shBlastShot.h"
#include "shBlast.h"

//------------------------------------------
// �G�e
#include "bulOneWay.h"
#include "bulHoming.h"
#include "bulAiming.h"
#include "bulWave.h"
#include "bulWayAlong.h"

//------------------------------------------
// �G�t�F�N�g
#include "effExplosion.h"
#include "effHit.h"
#include "effBarrier.h"
#include "effScope.h"
#include "effBigExplosion.h"
#include "effFinalBigExplosion.h"

//------------------------------------------
// ��Q��

//------------------------------------------
// �A�C�e��

//------------------------------------------
// Ui
#include "uiCharacter.h"
#include "uiPlayerLife.h"
#include "uiPlayerVitality.h"

//------------------------------------------
// �Q�[���X�N���v�g
#include "GameScript.h"

//------------------------------------------
// 
#define UI_WIDTH 270

//------------------------------------------
// �R���X�g���N�^
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
// �f�X�g���N�^
TsceneGame::~TsceneGame( void )
{

	// ���@
	if( FpPlayer )
		delete FpPlayer;

	{
		// �V���b�g
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
	// �G�e
	{
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end(); it++) {
			delete *it;
		}
		FpBullets.clear();
	}
	// �G�t�F�N�g
	{
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpEffects.begin(); it!=FpEffects.end(); it++) {
			delete *it;
		}
		FpEffects.clear();
	}
	// ��Q��
	{
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpGimmicks.begin(); it!=FpGimmicks.end(); it++) {
			delete *it;
		}
		FpGimmicks.clear();
	}

	// �A�C�e��
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
// �������֐�
bool TsceneGame::Initialize( void )
{

	FhWnd = TaskManager().GethWnd();
	FiClientX = TaskManager().GetiClientX();
	FiClientY = TaskManager().GetiClientY();

	// �摜���������ɓǂݍ���
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

	// �w�i�C���X�^���X�쐬
	FpBackGround = new TBackGround( *this );

	// Ui�쐬
	CreateUi( UI_CHARACTER_SEIYA , Vector2D( 50, 17)  , Vector2D( 0, 0 ) );
	CreateUi( UI_PLAYER_LIFE , Vector2D( 10, -35)  , Vector2D( 0, 0 ) );
	CreateUi( UI_PLAYER_VITALITY , Vector2D( 50, -45)  , Vector2D( 0, 0 ) );

	// �I�������L�����N�^�[��ǂݎ���Ă̎��@�쐬
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

	// �Q�[���X�N���v�g�쐬
	FpGameScript = new TGameScript(this);
	// �I�������X�e�[�W��ǂݎ���ăX�N���v�g��ǂݍ���
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
	
	// �o�b�N�~���[�W�b�N�Đ�
	int ch = PlayStreamBGM( TEXT("stage01_bgm.wav") );
	int bgm_vol = GetVolume(ch);
	SetVolume(ch, -300);
	
	return true;
}
//------------------------------------------
// ���s�֐�
bool TsceneGame::Execute( double ElapsedTime )
{

	FpBackGround->Update(ElapsedTime);
	if( FpPlayer )
		FpPlayer->Update( ElapsedTime );
	if( !FpPlayer)
		int test = 0;

	{	// �V���b�g
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpShots.begin(); it!=FpShots.end();  ) {
			if( !((*it)->Update(ElapsedTime)) ) {
				delete *it;
				// ���X�g�폜
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
				// ���X�g�폜
				it = FpEnemies.erase(it);

			} else
				it++;
		}
	}

	{	// �G�e
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end(); ){
			if( !(*it)->Update(ElapsedTime)){
				delete *it;
				// ���X�g�폜
				it = FpBullets.erase(it);
			} else
				it++;
		}
	}

	{	// �G�t�F�N�g
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpEffects.begin(); it!=FpEffects.end(); ){
			if( !(*it)->Update(ElapsedTime)){
				delete *it;
				// ���X�g�폜
				it = FpEffects.erase(it);
			} else
				it++;
		}
	}

	{	// ��Q��
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpGimmicks.begin(); it!=FpGimmicks.end(); ){
			if( !(*it)->Update(ElapsedTime)){
				delete *it;
				// ���X�g�폜
				it = FpGimmicks.erase(it);
			} else
				it++;
		}
	}

	{	// �A�C�e��
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpItems.begin(); it!=FpItems.end(); ){
			if( !(*it)->Update(ElapsedTime)){
				delete *it;
				// ���X�g�폜
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
				// ���X�g�폜
				it = FpUis.erase(it);
			} else
				it++;
		}
	}


	// �Փ˔���
	Collision(ElapsedTime);

	// �ړ�
	if(FpPlayer)
		FpPlayer->Move(ElapsedTime);

	{	// �V���b�g
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpShots.begin(); it!=FpShots.end();  ) {
			if( !((*it)->Move(ElapsedTime)) ) {
				delete *it;
				// ���X�g�폜
				it = FpShots.erase(it);

			} else
				it++;
		}
	}

	{	// �G
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpEnemies.begin(); it!=FpEnemies.end();  ) {
			if( !((*it)->Move(ElapsedTime)) ) {
				delete *it;
				// ���X�g�폜
				it = FpEnemies.erase(it);

			} else
				it++;
		}
	}

	{	// �G�̒e
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end();  ) {
			if( !((*it)->Move(ElapsedTime)) ) {
				delete *it;
				// ���X�g�폜
				it = FpBullets.erase(it);

			} else
				it++;
		}
	}

	{	// �G�t�F�N�g
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpEffects.begin(); it!=FpEffects.end();  ) {
			if( !((*it)->Move(ElapsedTime)) ) {
				delete *it;
				// ���X�g�폜
				it = FpEffects.erase(it);

			} else
				it++;
		}
	}

	{	// ��Q��
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpGimmicks.begin(); it!=FpGimmicks.end();  ) {
			if( !((*it)->Move(ElapsedTime)) ) {
				delete *it;
				// ���X�g�폜
				it = FpGimmicks.erase(it);

			} else
				it++;
		}
	}

	{	// �A�C�e��
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpItems.begin(); it!=FpItems.end();  ) {
			if( !((*it)->Move(ElapsedTime)) ) {
				delete *it;
				// ���X�g�폜
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
				// ���X�g�폜
				it = FpUis.erase(it);

			} else
				it++;
		}
	}


	FiCollapsedTime++;

	// GameScript����G�o������ǂݎ��AScript�̍Ō�ɒB���Ă���΃V�[���I��
	if ( !FpGameScript->Excute(ElapsedTime) ){
//		FbOverFlg = TRUE;
	}

	
	// �v���C���[��null�łȂ����
	if(FpPlayer){
		// �v���C���[�����S������c�@�����炵�A�v���C���[�𕜋A������
		if(FpPlayer->Update(ElapsedTime) == FALSE){
			delete FpPlayer;
			FpPlayer = NULL;
			FiLife--;
			if( FiLife > 0 )
				FpPlayer = new TplGranVisor( this, Vector2D(0,40), 0.8 ); 
		}
	}
	// �v���C���[�̎c�@��0�ȉ��ɂȂ�΃Q�[���I�[�o�[
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

			// -2.0��fade���n�߂Ă��玟��new����܂ł̒x������
			if(FiTimer <= -2.0){
				new TsceneGameOver();
				return false;
			}
		}
	}
	return true;
}

//------------------------------------------
// �`��֐�
void TsceneGame::Draw( void )
{
	FpBackGround->Render();

	// Ui�`��
	RECT srcRec2 = { 0, 0, 250, 600};	// �摜�̒�����؂�����W
//	FpUiBackGround->Render(&srcRec2, D3DXVECTOR3( 550, 0, 0), 0.6f);

	if( FpPlayer )
		FpPlayer->Render();

	{	// �V���b�g
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

	{	// �G�e
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end(); it++){
			(*it)->Render();
		}
	}

	{	// �G�t�F�N�g
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpEffects.begin(); it!=FpEffects.end(); it++){
			(*it)->Render();
		}
	}

	{	// ��Q��
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpGimmicks.begin(); it!=FpGimmicks.end(); it++){
			(*it)->Render();
		}
	}

	{	// �A�C�e��
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpItems.begin(); it!=FpItems.end(); it++){
			(*it)->Render();
		}
	}

	{	// �A�C�e��
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpUis.begin(); it!=FpUis.end(); it++){
			(*it)->Render();
		}
	}
}

//------------------------------------------
// 3d�`��֐�
void TsceneGame::Draw3D(void)
{
}

//------------------------------------------
// �`��֐�
void TsceneGame::DrawCgdi( void )
{
	if( FpPlayer ) FpPlayer->RenderCgdi();

	{	// �V���b�g
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

	{	// �G�e
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end(); it++){
			(*it)->RenderCgdi();
		}
	}

	{	// �G�t�F�N�g
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpEffects.begin(); it!=FpEffects.end(); it++){
			(*it)->RenderCgdi();
		}
	}

	{	// ��Q��
		std::list< TBaseMovingObject *>::iterator it;
		for( it=FpGimmicks.begin(); it!=FpGimmicks.end(); it++){
			(*it)->RenderCgdi();
		}
	}

	{	// �A�C�e��
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
// ���b�Z�[�W����
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
// �V���b�g���쐬����
void TsceneGame::CreateShot( const int &type, const Vector2D &pos, const Vector2D &velocity )
{
	TBaseMovingObject *pshot;
	switch(type){
		// �����e
		case SH_NORMAL:
			pshot = new TshNormalShot( this, pos, velocity );
			break;
		// �r�[��
		case SH_BEAM:
			pshot = new TshBeamShot( this, pos, velocity );
			break;
		// �_�������e
		case SH_AIMING:
			pshot = new TshAimingShot( this, pos, velocity );
			break;
		// �z�[�~���O�e
		case SH_HOMING:
			pshot = new TshHomingShot( this, pos, velocity);
			break;
		// �����e(�����O)
		case SH_MULTIPLE:
			pshot = new TshMultipleShot( this, pos, velocity);
			break;
		// �����e(�����)
		case SH_MINI_MULTIPLE:
			pshot = new TshMiniMultipleShot( this, pos, velocity);
			break;
		// �����e
		case SH_BLAST_SHOT:
			pshot = new TshBlastShot( this, pos, velocity);
			break;
		// �����e(����)
		case SH_BLAT:
			pshot = new TshBlast( this, pos, velocity);
			break;
	}
	FpShots.push_back( pshot );
}

//------------------------------------------
// enemy���쐬����
void TsceneGame::CreateEnemy( const int &type , const int &pattern ,const Vector2D &pos, const Vector2D &velocity )
{
	TBaseMovingObject *penemy;
	switch(type){
		case ENEM_NO:
			break;

		// �G���G�@�{�b�N�X
		case ENEM_BOX:
			penemy = new TenemBox( this, pattern, pos, velocity );
			break;

		// �G���I�@�t�B�b�V��
		case ENEM_FISH:
			penemy = new TenemFish( this, pattern, pos, velocity );
			break;

		// �X�e�[�W2�{�X�C��
		case ENEM_BOSS_FORTRESS:
			penemy = new TenemBossFortress( this, pattern, pos, velocity );
			break;

		// �X�e�[�W2�{�X
		case ENEM_BOSS_SPACESHITP:
			penemy = new TenemBossSpaceship( this, pattern, pos, velocity );
			break;

		// �X�e�[�W2�{�X�E��
		case ENEM_BOSS_RIGHT_WING:
			penemy = new TenemBossRightWing( this , pattern , pos, velocity );
			break;

		// �X�e�[�W2�{�X����
		case ENEM_BOSS_LEFT_WING:
			penemy = new TenemBossLeftWing( this , pattern , pos, velocity );
			break;

		// �X�e�[�W2�{�X����
		case ENEM_BOSS_BODY:
			penemy = new TenemBossBody( this , pattern , pos, velocity );
			break;

		//	�W�[�N�U�f�M��(�X�e�[�W1,�X�e�[�W3�{�X)
		case ENEM_BOSS_DEGIN:
			penemy = new TenemBossDegin( this , pattern , pos, velocity );
			break;

		//	�G���_�A���_�[�\��(�X�e�[�W4�{�X)
		case ENEM_BOSS_UNDERSON:
			penemy = new TenemBossUnderson( this , pattern , pos, velocity );
			break;

		//	�Œj��l���@(�X�e�[�W5�{�X)
		case ENEM_BOSS_SHADOW_VISOR:
			penemy = new TenemBossShadowVisor( this , pattern , pos, velocity );
			break;

		//	�ŏ���l���@(�X�e�[�W5�{�X)
		case ENEM_BOSS_SHADOW_SABER:
			penemy = new TenemBossShadowSaber( this , pattern , pos, velocity );
			break;

		//	�A���o�[�g���C�A�f�E�X(�X�e�[�W6���X�{�X)
		case ENEM_BOSS_ALBERT:
			penemy = new TenemBossAlbert( this , pattern , pos, velocity );
			break;

		// 覐Ώ�Q��
		case ENEM_COMMET:
			penemy = new TenemCommet( this, pattern, pos, velocity);
			break;
		// 覐Ώ�Q���j��
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
		// �����e
		case BUL_ONE_WAY:
			pbullet = new TbulOneWay( this, pos, velocity);
			break;
		// �z�[�~���O�e
		case BUL_HOMING:
			pbullet = new TbulHoming( this, pos, velocity);
			break;
		// �_�������e
		case BUL_AIMING:
			pbullet = new TbulAiming( this, pos, velocity);
			break;
		// �g�ł��e
		case BUL_WAVE:
			pbullet = new TbulWave( this, pos, velocity);
			break;
		// �o�H�Ǐ]�e ������
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
		// ����
		case EFF_EXPLOSION:
			peffect = new TeffExplosion( this, pos, velocity);
			break;
		// �o���A
		case EFF_BARRIER:
			peffect = new TeffBarrier( this, pos, velocity);
			break;
		// �q�b�g�G�t�F�N�g
		case EFF_HIT:
			peffect = new TeffHit( this, pos, velocity);
			break;
		// �{�X��_�\���p�X�R�[�v
		case EFF_SCOPE:
			peffect = new TeffScope( this, pos, velocity);
			break;
		// �唚���G�t�F�N�g
		case EFF_BIG_EXPLOSION:
			peffect = new TeffBigExplosion( this, pos, velocity);
			break;
		// �ő唚���G�t�F�N�g
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
		// �r�[����Q��
		case GIM_BEAM:
//			peffect = new TbulOneWay( this, pos, velocity);
			break;
		// �ʐM�M�~�b�N
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
		// �p���[�A�b�v�A�C�e��
		case ITM_POWER:
			pitem = new TbulOneWay( this, pos, velocity);
			break;
		// �\�E���`���[�W�p���[�A�b�v�A�C�e��
		case ITM_SOUL:
//			peffect = new TbulOneWay( this, pos, velocity);
			break;
		// �X�R�A�A�b�v�A�C�e��
		case ITM_SCORE:
//			peffect = new TbulOneWay( this, pos, velocity);
			break;
		// �ʐM�A�C�e��
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
		// �j����l���@�����G
		case UI_CHARACTER_SEIYA:
			ui = new TuiCharacter( this, pos, velocity);
			break;
		// ������l���@�����G
		case UI_CHARACTER_KANATA:
//			ui = new TbulOneWay( this, pos, velocity);
			break;
		// �v���C���[�̗�
		case UI_PLAYER_VITALITY:
			ui = new TuiPlayerVitality( this, pos, velocity);
			break;
		// �v���C���[�c�@
		case UI_PLAYER_LIFE:
			ui = new TuiPlayerLife( this, pos, velocity);
			break;
	}
	FpUis.push_back( ui );
}

//-----------------------
// Control GameScript
//-----------------------
// �X�N���v�g���|�[�Y����
void TsceneGame::ScriptPause(void)
{
	FpGameScript->Pause();
}

// �X�N���v�g���ĊJ����
void TsceneGame::ScriptResume(void)
{
	FpGameScript->Resume();
}

//------------------------------------------
void TsceneGame::Collision (double elapsedtime)
{
	{	// �v���C���[�ƓG�̒e
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end(); it++ ) {
			if(CollisionCircleS(FpPlayer, *it))
			// �����蔻��̌v�Z�����������悤�Ȃ̂ŃR�����g�A�E�g
			//if(CollisionCircle(FpPlayer, *it,elapsedtime) <= 1.0 )
			{
				(*it)->ReactHit(elapsedtime);
				FpPlayer->ReactHit(elapsedtime);
			}
		}
	}

	{	// �v���C���[�̒e�ƓG
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

	{	// �v���C���[�ƓG
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpEnemies.begin(); it!=FpEnemies.end(); it++ ) {
			if(CollisionCircleS(FpPlayer, *it))
			{
				FpPlayer->ReactHit(elapsedtime);
			}
		}
	}

	{	// �v���C���[�Ə�Q��
		std::list< TBaseMovingObject * >::iterator it;
		for( it=FpGimmicks.begin(); it!=FpGimmicks.end(); it++ ) {
			if(CollisionCircleS(FpPlayer, *it))
			{
//				(*it)->ReactHit(elapsedtime);
//				FpPlayer->ReactHit(elapsedtime);
			}
		}
	}

	{	// �v���C���[�ƃA�C�e��
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

// �v���C���[��Enemy�̋����𑪂�A��ԋ������߂�Enemy��Ԃ�
const TBaseMovingObject* TsceneGame::GetNearestEnemy(void)
{
	std::list< TBaseMovingObject * >::iterator it;
	TBaseMovingObject *ReturnEnemy = NULL;
	// �v���C���[��NULL�Ȃ��NULL��Ԃ�
	if(FpPlayer == NULL)
		return ReturnEnemy;
	// �v���C���[��NULL�łȂ���Έ�ԋ߂��̓G��Ԃ�
	else{
		int length = (FiClientX*FiClientX)+(FiClientY*FiClientY);	// ��ʂ̎΂߂̒�����2������Ă���
		for(it = FpEnemies.begin(); it != FpEnemies.end(); it++){
			if(length > ((*it)->vPosition - FpPlayer->vPosition).lengthSq() ){
				length = (int)( ((*it)->vPosition - FpPlayer->vPosition).lengthSq() );
				ReturnEnemy = (*it);
			}
		}
	}
	return ReturnEnemy;
}

// ��ԍŐV�̒ǉ����ꂽEnemy��Ԃ��B�{�X�𐶐�����SubjectEnemy�̃R���X�g���N�^�ŌĂяo��
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