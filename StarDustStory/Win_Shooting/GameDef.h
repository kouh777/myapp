
#ifndef __GAMEDEF_H__
#define __GAMEDEF_H__

//---------------------------------------------------------------------
#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <list>
#include <math.h>
#include <time.h>
#include "Vector2D.h"
#include "cgdi.h"
#include "Input.h"
#include "Matrix2D.h"
#include "DirectGraphics9.h"
#include "isprite.h"
#include "__sound.h"

//---------------------------------------------------------------------
// �X�N���[���T�C�Y��`
#define GAME_SCREEN_W 600
#define GAME_SCREEN_H 600

//--------------------------------------------------------
// �Z�[�t�f���[�g
#define SAFE_RELEASE(x)	{ if(x!=NULL) x->Release(); x=NULL; };
#define SAFE_DELETE(x)	{ if(x!=NULL) x->delete; x=NULL; };

/*
//------------------------------------------
// �X�e�[�WID��`
#define STAGE_1							1	//	�X�e�[�W1
#define STAGE_2							2	//	�X�e�[�W2
#define STAGE_3							3	//	�X�e�[�W3
#define STAGE_4							4	//	�X�e�[�W4
#define STAGE_5							5	//	�X�e�[�W5
*/

//------------------------------------------
// �X�e�[�WID��`
enum STG_ID{
	STAGE_1,		//	�X�e�[�W1
	STAGE_2,		//	�X�e�[�W2
	STAGE_3,		//	�X�e�[�W3
	STAGE_4,		//	�X�e�[�W4
	STAGE_5,		//	�X�e�[�W5
	STAGE_DEBUG		//	�f�o�b�O�p�X�e�[�W
};

//------------------------------------------
// �I���v���C���[��`
#define PL_GRANDVISOR					1	//	�O�����o�C�U�[
#define PL_GRANDSAVER					2	//	�O�����Z�C�o�[
#define PL_COMBAT						3	//	�����퓬�@

//------------------------------------------
// �v���C���[�V���b�g��`
#define SH_NORMAL					1	// �ʏ�e
#define SH_BEAM						2	// �r�[��
#define SH_AIMING					3	// �_�������e
#define SH_HOMING					4	// �z�[�~���O�e
#define SH_MULTIPLE					5	// �����e(�����O)
#define SH_MINI_MULTIPLE			6	// �����e(�����)
#define SH_BLAST_SHOT				7	// �����e
#define SH_BLAT						8	// �����e(����)

//------------------------------------------
// �G�e��`
#define BUL_ONE_WAY					1	//�@�ʏ�e
#define BUL_HOMING					2	//�@�z�[�~���O�e
#define BUL_AIMING					3	//�@�_�������e
#define BUL_WAVE					4	//�@�g�ł��e
#define BUL_WAY_ALONG				5	//�@�o�H�Ǐ]�e

//------------------------------------------
// �GID��`
#define ENEM_NO						0	//	�_�~�[�G�l�~�[
#define ENEM_BOX					1	//	�G���G(����1)
#define ENEM_FISH					2	//	�G���G(����2)
#define ENEM_BOSS_FORTRESS			3	//	�X�e�[�W2�{�X�C��
#define ENEM_BOSS_SPACESHITP		4	//	�X�e�[�W2�{�X
#define ENEM_BOSS_RIGHT_WING		12	//	�X�e�[�W2�{�X�E��
#define ENEM_BOSS_LEFT_WING			13	//	�X�e�[�W2�{�X����
#define ENEM_BOSS_BODY				14	//	�X�e�[�W2�{�X�{��
#define ENEM_BOSS_DEGIN				20	//	�W�[�N�U�f�M��(�X�e�[�W1,�X�e�[�W3�{�X)
#define ENEM_BOSS_UNDERSON			30	//	�G���_�A���_�[�\��(�X�e�[�W4�{�X)
#define ENEM_BOSS_SHADOW_VISOR		40	//	�Œj��l���@(�X�e�[�W5�{�X)
#define ENEM_BOSS_SHADOW_SABER		41	//	�ŏ���l���@(�X�e�[�W5�{�X)
#define ENEM_BOSS_ALBERT			50	//	�A���o�[�g���C�A�f�E�X(�X�e�[�W6���X�{�X)

#define ENEM_MINI_COMMET			98	//	覐Ώ�Q��
#define ENEM_COMMET					99	//	覐Ώ�Q��(�j��)

//---------------------------------------------------------------------
// �G�t�F�N�g��`
#define EFF_EXPLOSION				1	// �����G�t�F�N�g
#define EFF_BARRIER					2	// �o���A�G�t�F�N�g
#define EFF_HIT						3	// �q�b�g�G�t�F�N�g
#define EFF_SCOPE					4	// �{�X��_�\���p�X�R�[�v
#define EFF_BIG_EXPLOSION			5	// �唚���G�t�F�N�g
#define EFF_FINAL_BIG_EXPLOSION		6	// ���唚���G�t�F�N�g

//---------------------------------------------------------------------
// �X�e�[�W�M�~�b�N��`
#define GIM_BEAM					1	// �r�[����Q��
#define GIM_NETWORK					2	// �ʐM�M�~�b�N

//---------------------------------------------------------------------
// �A�C�e����`
#define ITM_POWER					1	// �p���[�A�b�v�A�C�e��
#define ITM_SOUL					2	// �\�E���`���[�W�p���[�A�b�v�A�C�e��
#define ITM_SCORE					3	// �X�R�A�A�b�v�A�C�e��
#define ITM_NETWORK					4	// �ʐM�A�C�e��

//---------------------------------------------------------------------
// UI�֘A��`
#define UI_PL_VITAL					1	// �v���C���[�̗�UI
#define UI_PL_BOM					2	// �v���C���[�c��{����UI
#define UI_BTN_STG_1				3	// �X�e�[�W1�{�^��
#define UI_BTN_STG_2				4	// �X�e�[�W2�{�^��
#define UI_BTN_STG_3				5	// �X�e�[�W3�{�^��
#define UI_BTN_STG_4				6	// �X�e�[�W4�{�^��
#define UI_BTN_STG_5				7	// �X�e�[�W5�{�^��
#define UI_BTN_REW					8	// ��ʕ�V�{�^��
#define UI_CUR						9	// �{�^���J�[�\��
#define UI_STG_DIS					10	// �X�e�[�W�����g
#define UI_PL_DIS					11	// �v���C���[�����g
#define UI_CHARACTER_SEIYA			12	// �j����l���@�����G
#define UI_CHARACTER_KANATA			13	// ������l���@�����G
#define UI_PLAYER_VITALITY			14  // �v���C���[�̗�
#define UI_PLAYER_LIFE				15	// �v���C���[�c�@
#define UI_BTN_SHION				16	// �j��l���{�^��
#define UI_BTN_SHION_S				17	// �j��l���{�^���I��
#define UI_BTN_KANATA				18	// ����l���{�^��
#define UI_BTN_KANATA_S				19	// ����l���{�^���I��

//---------------------------------------------------------------------
// �v���C���[�f�[�^�֌W��`
#define PLAYER_MAX_LIFE				3	// �ő�v���C���[�c�@			

//---------------------------------------------------------------------
// vector���p 
using std::vector;

//---------------------------------------------------------------------
#endif	// __GAMEDEF_H__