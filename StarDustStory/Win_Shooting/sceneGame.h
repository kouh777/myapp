#ifndef __TSCENEGAME_H__
#define __TSCENEGAME_H__

//--------------------------------------------------------
#include "GameDef.h"
#include "TaskManager.h"
#include <vector>

//--------------------------------------------------------
class TobjPlayer;
class TobjShot;
class TobjBullet;
class TobserverEnemy;
class TBaseMovingObject;

class ISprite;

//--------------------------------------------------------
// �v���C���[
class TplGranVisor;
class TplGransaber;

//--------------------------------------------------------
// �G
class TenemBox;
class TenemFish;
class TenemBossFortress;
class TenemBossSpaceShip;
class TenemBossRightWing;
class TenemBossLeftWing;
class TenemBossBody;
class TenemBossDegin;
class TenemBossUnderson;
class TenemBossShadowSaber;
class TenemBossShadowVisor;
class TenemBossAlbert;
class TenemCommet;

//--------------------------------------------------------
// �v���C���[�e
class TshNormalShot;
class TshBeamShot;
class TshAimingShot;
class TshHomingShot;
class TshMultipleShot;
class TshMiniMultipleShot;
class TshBlastShot;
class TshBlast;

//--------------------------------------------------------
// �G�e
class TbulOneWay;
class TbulHoming;
class TbulAiming;
class TbulWave;
class TbulWayAlong;

//------------------------------------------
// �G�t�F�N�g
class TeffExplosion;
class TeffBarrier;
class TeffScope;
class TeffBigExplosion;
class TeffHit;
class TeffFInalBigExplosion;

//------------------------------------------
// ��Q��

//------------------------------------------
// �A�C�e��

//------------------------------------------
// Ui
class TuiCharacter;
class TuiPlayerVitality;
class TuiPlayerLife;

//--------------------------------------------------------
// �w�i
class TBackGround;

//--------------------------------------------------------
// �Q�[���X�N���v�g
class TGameScript;

//--------------------------------------------------------
// ViewPort���
enum VIEWPORT_KIND{
	GAME_VIEWPORT,
	STAGE_VIEWPORT,
	UI_VIEWPORT,
};

//--------------------------------------------------------
class TsceneGame: public _Task
{
private:
	HWND FhWnd;
	int FiClientX;
	int FiClientY;
	double FiTimer;
	STG_ID FStageId;
	int FiPlayerId;
	bool FbFadeFlg;
	bool FbOverFlg;
	DWORD FiLife;	// �v���C���[�c�@

	TobjPlayer *FpPlayer;
	std::list< TBaseMovingObject * > FpShots;
	std::list< TBaseMovingObject * > FpBullets;
	std::list< TBaseMovingObject * > FpEnemies;
	std::list< TBaseMovingObject * > FpEffects;
	std::list< TBaseMovingObject * > FpGimmicks;
	std::list< TBaseMovingObject * > FpItems;
	std::list< TBaseMovingObject * > FpUis;

	int FiCollapsedTime;
	TGameScript *FpGameScript;

	TBackGround *FpBackGround;

public:
	TsceneGame( int player_id, STG_ID stage_id );
	~TsceneGame( void );
	bool Execute( double ElapsedTime);
	void Draw( void );
	void DrawCgdi(void);

	bool Initialize( void );
	HRESULT MessageHandle( UINT message, WPARAM wParam, LPARAM lParam );
	void ViewPortTransform( std::vector<Vector2D> &vPoints );
	void ViewPortTransform( VIEWPORT_KIND kind, std::vector<Vector2D> &vPoints );
	//-----------------------
	// Create BaseMovingObject
	//-----------------------
	void CreateShot( const int &type, const Vector2D &pos, const Vector2D &velocity );
	void CreateEnemy( const int &type , const int &pattern , const Vector2D &pos, const Vector2D &velocity );
	void CreateBullet(const int &type, const Vector2D &pos, const Vector2D &velocity );
	void CreateEffect(const int &type, const Vector2D &pos, const Vector2D &velocity );
	void CreateGimmick(const int &type, const Vector2D &pos, const Vector2D &velocity );
	void CreateItem(const int &type, const Vector2D &pos, const Vector2D &velocity );
	void CreateUi(const int &type, const Vector2D &pos, const Vector2D &velocity );
	//-----------------------
	// Control GameScript
	//-----------------------
	void ScriptPause(void);			// �X�N���v�g���|�[�Y����
	void ScriptResume(void);		// �X�N���v�g���ĊJ����

	void Collision (double elapsedtime);
	const TBaseMovingObject *GetNearestEnemy(void);
	const TBaseMovingObject *GetNewestEnemy(void);	// return the newest Enemy
	// 3d test
	void Draw3D(void);

	// �摜���\�[�X
	ISprite	*FpSprites;					// �e�X�g�p�X�v���C�g
	ISprite *FpBackGroundSprite;		// �Q�[���w�i
	ISprite *FpUiBackGround;			// UI�w�i
	ISprite *FpPlayerSprite;			// �v���C���[(�e�X�g��)
	ISprite *FpShotSprite;				// �e
	ISprite *FpEnemySprite;				// �G
	ISprite *FpPlayerVisorSprite;		// �j����l���@
	ISprite *FpPlayerSaberSprite;		// ������l���@
	ISprite *FpBossSpaceshipSprite;		// �X�e�[�W2�{�X
	ISprite *FpBossDegin;				// �W�[�N�U�f�M��(�X�e�[�W1,�X�e�[�W3�{�X)
	ISprite *FpBossUnderson;			// �G���_�A���_�[�\��(�X�e�[�W4�{�X)
	ISprite *FpBossShadowVisor;			// �Œj��l���@(�X�e�[�W5�{�X)
	ISprite *FpBossShadowSaber;			// �ŏ���l���@(�X�e�[�W5�{�X)
	ISprite *FpBossAlbert;				// �A���o�[�g���C�A�f�E�X(�X�e�[�W6���X�{�X)
	ISprite *FpCharacterSeiya;			// �j�������G
	ISprite *FpCharacterKanata;			// ���������G
	ISprite *FpHpGauge;					// HP�Q�[�W

	ISprite *FpBarrier;					// �o���A�G�t�F�N�g
	ISprite *FpScope;					// �{�X��_�\���p�X�R�[�v
	ISprite *FpHit;						// �q�b�g�G�t�F�N�g
	ISprite *FpExplosionSprite;			// ���唚���G�t�F�N�g
	ISprite *FpAsteroid;				// ��Q��(覐�)

	

	// �A�N�Z�T
	__declspec( property(get=GetiClientX) ) int iClientX;
	int GetiClientX( void ) const { return FiClientX; }

	__declspec( property(get=GetiClientY) ) int iClientY;
	int GetiClientY( void ) const { return FiClientY; }

	__declspec( property(get=GetPlayer) ) TobjPlayer *pPlayer;
	const TobjPlayer *GetPlayer(void) const {return FpPlayer;}

	__declspec( property(get=GetPlayerLife) ) DWORD iLife;
	const DWORD GetPlayerLife(void) const {return FiLife;}

};

#endif //__TSCENEGAME_H__