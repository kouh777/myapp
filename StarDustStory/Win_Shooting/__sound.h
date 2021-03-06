
#ifndef ____SOUND_H__
#define ____SOUND_H__

//--------------------------------------------------------------------------------
#include "DxSound.h"

//--------------------------------------------------------------------------------
enum {
	SND_SYS_MCROS = 0,		// サンプルBGM
	SND_SYS_STG01 = 1,		// ステージ1BGM
	SND_SE_PL_DEATH = 2,	// プレイヤー死亡効果音
	SND_SE_ENEM_DEATH = 3,	// 敵死亡効果音
	SND_SE_BOSS_DEATH = 4,	// ボス死亡効果音
	SND_SE_SHOT = 5,		// プレイヤーショット効果音
	SND_SE_HIT = 6,			// 攻撃ヒット時効果音
};

enum {
	USE_CH_BGM = 0,
	USe_CH_SE = 1,
};



//------------------------------------------------------------------------------------------------------------------
struct _SoundInfo
{
	DWORD Index;
	TCHAR AFileName[256];
};

//------------------------------------------------------------------------------------------------------------------
extern void LoadDxSound( void );
extern void UnLoadDxSound( void );

//--------------------------------------------------------------------------------
#endif	// ____SOUND_H__