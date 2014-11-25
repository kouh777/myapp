
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

//---------------------------------------------------------------------
// �X�N���[���T�C�Y��`
#define GAME_SCREEN_W 600
#define GAME_SCREEN_H 600

//---------------------------------------------------------------------
// vector���p 
using std::vector;

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
#define ENEM_NO						0
#define ENEM_BOX					1
#define ENEM_FISH					2
#define ENEM_BOSS_FORTRESS			3	//	�X�e�[�W2�{�X�C��
#define ENEM_BOSS_SPACESHITP		4	//	�X�e�[�W2�{�X
#define ENEM_BOSS_RIGHT_WING		12	//	�X�e�[�W2�{�X�E��
#define ENEM_BOSS_LEFT_WING			13	//	�X�e�[�W2�{�X����
#define ENEM_BOSS_BODY				14	//	�X�e�[�W2�{�X�{��

//---------------------------------------------------------------------
// �G�t�F�N�g��`
#define EFF_EXPLOSION				1	// �����G�t�F�N�g
#define EFF_BARRIER					2	// �o���A�G�t�F�N�g
#define EFF_HIT						3	// �q�b�g�G�t�F�N�g
#define EFF_SCOPE					4	// �{�X��_�\���p�X�R�[�v

//---------------------------------------------------------------------
// ��Q���E�X�e�[�W�M�~�b�N��`
#define GIM_COMMET					1	// 覐Ώ�Q��
#define GIM_MINI_COMMET				2	// 覐Ώ�Q��(�j��)
#define GIM_BEAM					3	// �r�[����Q��
#define GIM_NETWORK					4	// �ʐM�M�~�b�N

//---------------------------------------------------------------------
// �A�C�e����`
#define ITM_POWER					1	// �p���[�A�b�v�A�C�e��
#define ITM_SOUL					2	// �\�E���`���[�W�p���[�A�b�v�A�C�e��
#define ITM_SCORE					3	// �X�R�A�A�b�v�A�C�e��
#define ITM_NETWORK					4	// �ʐM�A�C�e��


//---------------------------------------------------------------------
#endif	// __GAMEDEF_H__