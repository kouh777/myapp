
#include <windows.h>
#include "__sound.h"

//------------------------------------------------------------------------------------------------------------------
_SoundInfo snd_tbl[] = {
	{ SND_SYS_MCROS,	TEXT("mcros.wav")},
	{ SND_SYS_STG01,	TEXT("stage01_bgm.wav") },
	{ SND_SE_PL_DEATH,	 TEXT("se_pl_death01.wav") },
	{ SND_SE_ENEM_DEATH, TEXT("se_enem_death01.wav") },
	{ SND_SE_BOSS_DEATH, TEXT("se_boss_death01.wav") },
	{ SND_SE_SHOT,		 TEXT("se_shot01.wav") },
	{ SND_SE_HIT,		 TEXT("se_shot01.wav") },
	
};
const int snd_cnt = sizeof(snd_tbl) / sizeof(_SoundInfo);

//------------------------------------------------------------------------------------------------------------------
void LoadDxSound( void )
{
	for( int i=0; i<snd_cnt; i++ ) {
		_SoundInfo *pInfo = &snd_tbl[i];
		LoadWaveFile( pInfo->Index, pInfo->AFileName );
	}
}

//------------------------------------------------------------------------------------------------------------------
void UnLoadDxSound( void )
{
	for( int i=0; i<snd_cnt; i++ ) {
		_SoundInfo *pInfo = &snd_tbl[i];
		UnloadWaveFile( pInfo->Index ); 
	}
}