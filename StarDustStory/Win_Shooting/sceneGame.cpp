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
// �e�X�g�Ńv���C���[�̗̑͂�0�ɂȂ�΃^�C�g���Ɉړ�
#include "sceneTitle.h"

//------------------------------------------
// �v���C���[���@
#include "plGranVisor.h"

//------------------------------------------
// �G
#include "enemBox.h"
#include "enemFish.h"
#include "enemBossFortress.h"

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
// �Q�[���X�N���v�g
#include "GameScript.h"

//------------------------------------------
// �GID��`
#define ENEM_BOX					1
#define ENEM_FISH					2
#define ENEM_BOSS_SPACESHITP		10	//	�X�e�[�W2�{�X
#define ENEM_BOSS_FORTRESS			11	//	�X�e�[�W2�{�X�C��
#define ENEM_BOSS_RIGHT_WING		12	//	�X�e�[�W2�{�X�E��
#define ENEM_BOSS_LEFT_WING			13	//	�X�e�[�W2�{�X����

//------------------------------------------
// �R���X�g���N�^
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
// �f�X�g���N�^
TsceneGame::~TsceneGame( void )
{
	int test = 0;

	// ���@
	if( FpPlayer )
		delete FpPlayer;

	{
		// �V���b�g
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
	// �G�e
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
// �������֐�
bool TsceneGame::Initialize( void )
{

	FhWnd = TaskManager().GethWnd();
	FiClientX = TaskManager().GetiClientX()-270;
	FiClientY = TaskManager().GetiClientY();

	// �摜���������ɓǂݍ���
	FpSprites = DxGraphics9().CreateSpriteFormFile(TEXT("sprites2.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 0));
	FpBackGroundSprite = DxGraphics9().CreateSpriteFormFile(TEXT("space3.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 0)); 
	FpUiBackGround = DxGraphics9().CreateSpriteFormFile(TEXT("uiback.png"),D3DFMT_A8R8G8B8 , 0);
	FpPlayerSprite = DxGraphics9().CreateSpriteFormFile(TEXT("player01.png"),D3DFMT_A8R8G8B8 , 0);
	FpShotSprite = DxGraphics9().CreateSpriteFormFile(TEXT("ef001.png"),D3DFMT_A8R8G8B8 , 0);
	FpEnemySprite = DxGraphics9().CreateSpriteFormFile(TEXT("chantougoke.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 0));
	FpBossSpaceshipSprite = DxGraphics9().CreateSpriteFormFile(TEXT("chantougoke.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 255));

	FpPlayerSaberSprite = DxGraphics9().CreateSpriteFormFile(TEXT("player001a.png"),D3DFMT_A8R8G8B8 , 0);
	FpPlayerVisorSprite = DxGraphics9().CreateSpriteFormFile(TEXT("player002a.png"),D3DFMT_A8R8G8B8 , 0);

	// �w�i�C���X�^���X�쐬
	FpBackGround = new TBackGround( *this );

	// ���@�쐬
	FpPlayer = new TplGranVisor( this, Vector2D(-50,0), 1.6 ); 

	// �Q�[���X�N���v�g�쐬
	FpGameScript = new TGameScript(this);
	FpGameScript->ReadScriptFile(TEXT("test_script.txt"));

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
		std::list< TobjShot * >::iterator it;
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
		std::list< TobjEnemy * >::iterator it;
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
		std::list< TobjBullet *>::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end(); ){
			if( !(*it)->Update(ElapsedTime)){
				delete *it;
				// ���X�g�폜
				it = FpBullets.erase(it);
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
		std::list< TobjShot * >::iterator it;
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
		std::list< TobjEnemy * >::iterator it;
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
		std::list< TobjBullet * >::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end();  ) {
			if( !((*it)->Move(ElapsedTime)) ) {
				delete *it;
				// ���X�g�폜
				it = FpBullets.erase(it);

			} else
				it++;
		}
	}

	FiCollapsedTime++;

	// GameScript����G�o������ǂݎ��
	FpGameScript->Excute(ElapsedTime);

	// FpPlayer��null�łȂ����
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

			// -2.0��fade���n�߂Ă��玟��new����܂ł̒x������
			if(FiTimer <= -2.0){
				new TsceneTitle();
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

	{	// �G�e
		std::list< TobjBullet *>::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end(); it++){
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

	{	// �G�e
		std::list< TobjBullet *>::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end(); it++){
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
// �V���b�g���쐬����
void TsceneGame::CreateShot( const int &type, const Vector2D &pos, const Vector2D &velocity )
{
	TobjShot *pshot;
	switch(type){
		// �����e
		case 1:
			pshot = new TshNormalShot( this, pos, velocity );
			break;
		// �r�[��
		case 2:
			pshot = new TshBeamShot( this, pos, velocity );
			break;
		// �_�������e
		case 3:
			pshot = new TshAimingShot( this, pos, velocity );
			break;
		// �z�[�~���O�e
		case 4:
			pshot = new TshHomingShot( this, pos, velocity);
			break;
		// �����e(�����O)
		case 5:
			pshot = new TshMultipleShot( this, pos, velocity);
			break;
		// �����e(�����)
		case 6:
			pshot = new TshMiniMultipleShot( this, pos, velocity);
			break;
		// �����e
		case 7:
			pshot = new TshBlastShot( this, pos, velocity);
			break;
		// �����e(����)
		case 8:
			pshot = new TshBlast( this, pos, velocity);
			break;
	}
	FpShots.push_back( pshot );
}

//------------------------------------------
// enemy���쐬����
void TsceneGame::CreateEnemy( const int &type , const int &pattern ,const Vector2D &pos, const Vector2D &velocity )
{
	TobjEnemy *penemy;
	switch(type){
		case 0:
			break;

		// �G���G�@�{�b�N�X
		case ENEM_BOX:
			penemy = new TenemBox( this, pattern, pos, velocity );
			break;

		// �G���I�@�t�B�b�V��
		case ENEM_FISH:
			penemy = new TenemFish( this, pattern, pos, velocity );
			break;

		// �X�e�[�W2�{�X
		case ENEM_BOSS_SPACESHITP:
			break;

		// �X�e�[�W2�{�X�C��
		case ENEM_BOSS_FORTRESS:
			penemy = new TenemBossFortress( this, pattern, pos, velocity );
			break;

		// �X�e�[�W2�{�X�E��
		case ENEM_BOSS_RIGHT_WING:
			break;

		// �X�e�[�W2�{�X����
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
		// �����e
		case 1:
			pbullet = new TbulOneWay( this, pos, velocity);
			break;
		// �z�[�~���O�e
		case 2:
			pbullet = new TbulHoming( this, pos, velocity);
			break;
		// �_�������e
		case 3:
			pbullet = new TbulAiming( this, pos, velocity);
			break;
		// �g�ł��e
		case 4:
			pbullet = new TbulWave( this, pos, velocity);
			break;
		// �o�H�Ǐ]�e ������
		case 5:
			pbullet = new TbulWayAlong( this, pos,velocity);
			break;
	}
	FpBullets.push_back( pbullet );
}

void TsceneGame::Collision (double elapsedtime)
{
	{	// �v���C���[�ƓG�̒e
		std::list< TobjBullet * >::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end(); it++ ) {
			if(CollisionCircleS(FpPlayer, *it))
			// �����蔻��̌v�Z�����������悤�Ȃ̂ŃR�����g�A�E�g
			//if(CollisionCircle(FpPlayer, *it,elapsedtime) <= 1.0 )
			{
				(*it)->ReactHit(elapsedtime);
				FpPlayer->ReactHit(elapsedtime);	// Player��hp��0�ɂȂ����Ƃ��̏���������ĂȂ��̂ň�U�R�����g�A�E�g
			}
		}
	}

	{	// �v���C���[�̒e�ƓG
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

// �v���C���[��Enemy�̋����𑪂�A��ԋ������߂�Enemy��Ԃ�
const TobjEnemy* TsceneGame::GetNearestEnemy(void)
{
	std::list< TobjEnemy * >::iterator it;
	TobjEnemy *ReturnEnemy = NULL;
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