
#ifndef ____SOUND_H__
#define ____SOUND_H__

//--------------------------------------------------------------------------------
#include "DxSound.h"

//--------------------------------------------------------------------------------
enum {
	SND_SYS_LOG = 0,
	SND_SYS_SEL,
	SND_SHT_SHOT,
	SND_SHT_BEAM,
	SND_EMY_CRUSH_S,
	SND_EMY_CRUSH_M,
	SND_EMY_CRUSH_B,
	SND_ITM_POWER,
	SND_ITM_SCORE,
};

enum {
	USE_CH_BGM = 0,
	USE_CH_SYS,
	USE_CH_CHAR,
	USE_CH_CHAR2,
	USE_CH_SHOT,
	USE_CH_BEAM,
	USE_CH_ENYSML,
	USE_CH_ENYBIG,
	USE_CH_MESSAGE,
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