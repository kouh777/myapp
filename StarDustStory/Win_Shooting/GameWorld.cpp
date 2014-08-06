
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
// �G�e
#include "bulOneWay.h"
#include "bulHoming.h"
#include "bulAiming.h"

//------------------------------------------
// �G�z�u�p�̍\���̂��쐬
struct EnemySet{
	const int type;				// �G�^�C�v
	const int pattern;			// �s���p�^�[��
	const Vector2D pos;			// �o���ꏊ
	const Vector2D velocity;	// �ړ�����
	const int time;				// �o���^�C�~���O
};

//------------------------------------------
// �z������A�����I�z�u��ݒ�
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
// �R���X�g���N�^
TGameWorld::TGameWorld( void )
	: FhWnd(NULL),
	  FiClientX(0),
	  FiClientY(0),
	  FpPlayer(NULL),
	  FiCollapsedTime(0)
{
}

//------------------------------------------
// �f�X�g���N�^
TGameWorld::~TGameWorld( void )
{
	// ���@
	if( FpPlayer ) delete FpPlayer;

	{
		// �V���b�g
		std::list< TobjShot * >::iterator it;
		for( it=FpShots.begin(); it!=FpShots.end(); it++ ) {
			delete *it;
		}
		FpShots.clear();
	}
	// �r�[��
	{
		std::list< TobjBeam * >::iterator it;
		for( it=FpBeams.begin(); it!=FpBeams.end(); it++ ) {
			delete *it;
		}
		FpShots.clear();
	}
	// �z�[�~���O�e
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
	// �G�e
	{
		std::list< TobjBullet * >::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end(); it++) {
			delete *it;
		}
		FpBullets.clear();
	}
}

//------------------------------------------
// �������֐�
bool TGameWorld::Initialize( HWND hWnd, int cx, int cy )
{
	FhWnd = hWnd;
	FiClientX = cx-270;
	FiClientY = cy;

	// �摜���������ɓǂݍ���
	FpSprites = DxGraphics9().CreateSpriteFormFile(TEXT("sprites2.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 0));
	FpBackGround = DxGraphics9().CreateSpriteFormFile(TEXT("background2.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 0)); 
	FpUiBackGround = DxGraphics9().CreateSpriteFormFile(TEXT("uiback.png"),D3DFMT_A8R8G8B8 , 0);
	FpPlayerSprite = DxGraphics9().CreateSpriteFormFile(TEXT("player01.png"),D3DFMT_A8R8G8B8 , 0);
	FpShotSprite = DxGraphics9().CreateSpriteFormFile(TEXT("ef001.png"),D3DFMT_A8R8G8B8 , 0);

	// ���@�쐬
	FpPlayer = new TobjPlayer( Vector2D(-50,0), 1.6 ); 

	return true;
}
//------------------------------------------
// ���s�֐�
void TGameWorld::Execute( double elapsed )
{
	BackGround().Update(elapsed);
	if( FpPlayer )
		FpPlayer->Update( elapsed );

	{	// �V���b�g
		std::list< TobjShot * >::iterator it;
		for( it=FpShots.begin(); it!=FpShots.end();  ) {
			if( !((*it)->Update(elapsed)) ) {
				delete *it;
				// ���X�g�폜
				it = FpShots.erase(it);

			} else
				it++;
		}
	}

	{	// �r�[��
		std::list< TobjBeam * >::iterator it;
		for( it=FpBeams.begin(); it!=FpBeams.end();  ) {
			if( !((*it)->Update(elapsed)) ) {
				delete *it;
				// ���X�g�폜
				it = FpBeams.erase(it);

			} else
				it++;
		}
	}
	
	{	// �z�[�~���O�e
		std::list< TobjHomingShot * >::iterator it;
		for( it=FpHomingShots.begin(); it!=FpHomingShots.end();  ) {
			if( !((*it)->Update(elapsed)) ) {
				delete *it;
				// ���X�g�폜
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
				// ���X�g�폜
				it = FpEnemies.erase(it);

			} else
				it++;
		}
	}

	{	// �G�e
		std::list< TobjBullet *>::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end(); ){
			if( !(*it)->Update(elapsed)){
				delete *it;
				// ���X�g�폜
				it = FpBullets.erase(it);
			} else
				it++;
		}
	}
	// �Փ˔���
	Collision(elapsed);

	// �ړ�
	if(FpPlayer)FpPlayer->Move(elapsed);

	{	// �V���b�g
		std::list< TobjShot * >::iterator it;
		for( it=FpShots.begin(); it!=FpShots.end();  ) {
			if( !((*it)->Move(elapsed)) ) {
				delete *it;
				// ���X�g�폜
				it = FpShots.erase(it);

			} else
				it++;
		}
	}

	{	// �r�[��
		std::list< TobjBeam * >::iterator it;
		for( it=FpBeams.begin(); it!=FpBeams.end();  ) {
			if( !((*it)->Move(elapsed)) ) {
				delete *it;
				// ���X�g�폜
				it = FpBeams.erase(it);

			} else
				it++;
		}
	}

	{	// �z�[�~���O�e
		std::list< TobjHomingShot * >::iterator it;
		for( it=FpHomingShots.begin(); it!=FpHomingShots.end();  ) {
			if( !((*it)->Move(elapsed)) ) {
				delete *it;
				// ���X�g�폜
				it = FpHomingShots.erase(it);

			} else
				it++;
		}
	}

	{	// �G
		std::list< TobjEnemy * >::iterator it;
		for( it=FpEnemies.begin(); it!=FpEnemies.end();  ) {
			if( !((*it)->Move(elapsed)) ) {
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
			if( !((*it)->Move(elapsed)) ) {
				delete *it;
				// ���X�g�폜
				it = FpBullets.erase(it);

			} else
				it++;
		}
	}

	FiCollapsedTime++;

	// enemy��EnemyArray�̃f�[�^��ǂݎ�萶��
	for(int i=0; i< sizeof EnemyArray / sizeof EnemyArray[0]; ++i){
		if(FiCollapsedTime == EnemyArray[i].time){
			CreateEnemy (EnemyArray[i].type, EnemyArray[i].pattern, EnemyArray[i].pos,EnemyArray[i].velocity);
		}
	}
}

//------------------------------------------
// �`��֐�
void TGameWorld::Draw( void )
{
	BackGround().Render();

	// Ui�`��
	RECT srcRec2 = { 0, 0, 250, 600};	// �摜�̒�����؂�����W
	FpUiBackGround->Render(&srcRec2, D3DXVECTOR3( 550, 0, 0), 0.6f);

	if( FpPlayer ) FpPlayer->Render();

	{	// �V���b�g
		std::list< TobjShot * >::iterator it;
		for( it=FpShots.begin(); it!=FpShots.end(); it++ ) {
			(*it)->Render();
		}
	}

	{	// �r�[��
		std::list< TobjBeam * >::iterator it;
		for( it=FpBeams.begin(); it!=FpBeams.end(); it++ ) {
			(*it)->Render();
		}
	}

	{	// �z�[�~���O�e
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

	{	// �G�e
		std::list< TobjBullet *>::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end(); it++){
			(*it)->Render();
		}
	}
}

//------------------------------------------
// �`��֐�
void TGameWorld::DrawCgdi( void )
{

	if( FpPlayer ) FpPlayer->RenderCgdi();

	{	// �V���b�g
		std::list< TobjShot * >::iterator it;
		for( it=FpShots.begin(); it!=FpShots.end(); it++ ) {
			(*it)->RenderCgdi();
		}
	}

	{	// �r�[��
		std::list< TobjBeam * >::iterator it;
		for( it=FpBeams.begin(); it!=FpBeams.end(); it++ ) {
			(*it)->RenderCgdi();
		}
	}

	{	// �r�[��
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

	{	// �G�e
		std::list< TobjBullet *>::iterator it;
		for( it=FpBullets.begin(); it!=FpBullets.end(); it++){
			(*it)->RenderCgdi();
		}
	}
}


//------------------------------------------
// ���b�Z�[�W����
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
// �V���b�g���쐬����
void TGameWorld::CreateShot( const Vector2D &pos, const Vector2D &velocity )
{
	TobjShot *pshot = new TobjShot( pos, velocity );
	FpShots.push_back( pshot );

}

//------------------------------------------
// �r�[�����쐬����
void TGameWorld::CreateBeam( const Vector2D &pos, const Vector2D &velocity )
{
	TobjBeam *pbeam = new TobjBeam( pos, velocity );
	FpBeams.push_back( pbeam );

}

//------------------------------------------
// �z�[�~���O�e���쐬����
void TGameWorld::CreateHomingShot( const Vector2D &pos, const Vector2D &velocity )
{
	TobjHomingShot *phomingshot = new TobjHomingShot( pos, velocity );
	FpHomingShots.push_back( phomingshot );

}

//------------------------------------------
// enemy���쐬����
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
		// �����e
		case 1:
			pbullet = new TbulOneWay(pos, velocity);
			break;
		// �z�[�~���O�e
		case 2:
			pbullet = new TbulHoming(pos, velocity);
			break;
		// �ǂ������e
		case 3:
			pbullet = new TbulAiming(pos, velocity);
	}
	FpBullets.push_back( pbullet );
}

void TGameWorld::Collision (double elapsedtime)
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

	{	// �v���C���[�̒ʏ�e�ƓG
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

	{	// �v���C���[�̃r�[���ƓG
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

// shots��Enemy�̋����𑪂�A��ԋ������߂�Enemy��Ԃ�
const TobjEnemy* TGameWorld::GetNearestEnemy(void)
{
	std::list< TobjEnemy * >::iterator it;
	TobjEnemy *ReturnEnemy = NULL;
	int length = (FiClientX*FiClientX)+(FiClientY*FiClientY);	// ��ʂ̎΂߂̒�����2������Ă���
	for(it = FpEnemies.begin(); it != FpEnemies.end(); it++){
		if(length > ((*it)->vPosition - FpPlayer->vPosition).length() ){
			length = ((*it)->vPosition - FpPlayer->vPosition).length();
			ReturnEnemy = (*it);
		}
	}
	return ReturnEnemy;
}