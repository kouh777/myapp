
#include <windows.h>
#include "__sound.h"

//------------------------------------------------------------------------------------------------------------------
_SoundInfo snd_tbl[] = {
	{ SND_SYS_MCROS,	TEXT("mcros.wav")},
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