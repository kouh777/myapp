
#include <windows.h>
#include "__sound.h"

//------------------------------------------------------------------------------------------------------------------
_SoundInfo snd_tbl[] = {
	{ SND_SYS_LOG,		TEXT("wav/_sys_log.wav")},
	{ SND_SYS_SEL,		TEXT("wav/_sys_select.wav")},
	{ SND_SHT_SHOT,		TEXT("wav/sht_shot.wav")},
	{ SND_SHT_BEAM,		TEXT("wav/sht_beam.wav")},
	{ SND_EMY_CRUSH_S,	TEXT("wav/emy_crash_s.wav")},
	{ SND_EMY_CRUSH_M,	TEXT("wav/emy_crash_m.wav")},
	{ SND_EMY_CRUSH_B,	TEXT("wav/emy_crash_b.wav")},
	{ SND_ITM_POWER,	TEXT("wav/itm_power.wav")},
	{ SND_ITM_SCORE,	TEXT("wav/itm_score.wav")},
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