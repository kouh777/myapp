// 以下の ifdef ブロックは DLL からのエクスポートを容易にするマクロを作成するための 
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された DLL_DXSOUND_EXPORTS
// シンボルでコンパイルされます。このシンボルは、この DLL を使うプロジェクトで定義することはできません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、 
// DLL_DXSOUND_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。

#ifndef __DXSOUND_H__
#define __DXSOUND_H__

#ifdef DLL_DXSOUND_EXPORTS
#define DLL_DXSOUND_API __declspec(dllexport)
#else
#define DLL_DXSOUND_API __declspec(dllimport)
#endif

//----------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------------
#define SNDCHNL_BGM  0
#define SNDCHNL_MAX 16

// 1/100 dB (デシベル) 単位で指定する
#define VOLUME_MAX			 0		// 減衰なし
#define VOLUME_MIN		-10000		// 無音

#define PAN_LEFT		-10000		// 右チャンネルが無音
#define PAN_RIGHT		 10000		// 左チャンネルが無音
#define PAN_CENTER			 0

// 周波数(Hz)を指定する
#define FREQUENCY_MIN		100
#define FREQUENCY_MAX	100000
#define FREQUENCY_ORIGINAL	  0		// デフォルト値

//----------------------------------------------------------------------------------

//----------------
// 初期化・解放
//----------------

/** DirectSoundを初期化する
	* @param hwnd ウィンドウハンドル 
	* @retval TRUE-成功　FALSE-失敗
*/
extern DLL_DXSOUND_API BOOL InitDxSound( HWND hwnd ); 
/** DirectSoundを解放する 
	* @retval なし
*/
extern DLL_DXSOUND_API void ReleaseDxSound( void );

//-------------
// ファイル
//-------------

/** 番号をつけてwavファイルを読み込む
	* @param idx		インデックス値
	* @param AFileName	ファイル名 
	* @retval TRUE-成功　FALSE-失敗
*/
extern DLL_DXSOUND_API BOOL LoadWaveFile( DWORD idx, LPTSTR AFileName );

/** wavファイルを解放します
	* @param idx		インデックス値
	* @retval なし
*/
extern DLL_DXSOUND_API void UnloadWaveFile( DWORD idx );

//------------
// サウンド
//------------

/** サウンドを再生します
	* @param idx		再生する音声のインデックス値
	* @param isloop		ループ
	* @retval 成功-再生したチャンネル番号(1～15)　失敗--1
*/
extern DLL_DXSOUND_API int PlayDxSound( int idx, BOOL isloop = FALSE );
/** チャンネルを指定してサウンドを再生します
	* @param ch			再生するチャンネル
	* @param idx		再生する音声のインデックス値
	* @param isloop		ループ
	* @retval 成功-再生したチャンネル番号(1～15)　失敗--1
*/
extern DLL_DXSOUND_API int PlayDxSoundToCh( int ch, int idx, BOOL isloop = FALSE );
/** サウンドをストップします
	* @param ch			ストップするチャンネル
	* @retval なし
*/
extern DLL_DXSOUND_API void StopDxSound( int ch );
/** サウンドをポーズします
	* @param ch			ポーズするチャンネル
	* @param flag		再開するかどうかのフラグ
	* @retval なし
*/
extern DLL_DXSOUND_API void PauseDxSound( int ch, BOOL flag );

//-------
// BGM
//-------

/** BGMを再生します
	* @param idx			再生するチャンネル
	* @retval 成功-0　失敗--1
*/
extern DLL_DXSOUND_API int PlayDxBGM( int idx );
/** BGMをストップします
	* @retval なし
*/
extern DLL_DXSOUND_API void StopDxBGM( void );
/** BGMをポーズします
	* @param flag		再開するかどうかのフラグ
	* @retval なし
*/
//extern DLL_DXSOUND_API void PauseDxBGM( BOOL flag );
/** ストリーミングしながらBGMを再生します
	* @param AFileName		ファイル名
	* @retval 成功-0　失敗--1
*/
extern DLL_DXSOUND_API int PlayStreamBGM( const LPTSTR AFileName );

//----------
// その他
//----------

/** 指定チャンネルが再生中かどうか調べます
	* @param ch		チャンネル
	* @retval TRUE-再生中　FALSE-停止中
*/
extern DLL_DXSOUND_API BOOL IsPlay( BYTE ch );
/** ボリューム値を変更します
	* @param ch		チャンネル
	* @param value	減衰。1/100 dB (デシベル) 単位で指定します
	* @retval なし
	* @attention　設定可能な値の範囲は、VOLUME_MAX (減衰なし) から VOLUME_MIN (無音) までである。
	これらの値は、それぞれ 0 および ?10,000 と定義されている。
	値 VOLUME_MAX は、ストリーム本来の未調整のボリュームを表す。
	値 VOLUME_MIN は、オーディオのボリュームが 100 dB 減衰していることを表し、これは実際的には無音を意味する。
	DirectSound は増幅をサポートしていない。
*/
extern DLL_DXSOUND_API void SetVolume( BYTE ch, int value );
/** ボリューム値を取得します
	* @param ch		チャンネル
	* @retval ボリューム値 (単位は 1/100 デシベル)。
	* @attention　戻り値の範囲は、VOLUME_MAX から VOLUME_MIN である。
	これらの値は、それぞれ 0 および ?10,000 と定義されている。
	値 VOLUME_MAX は、サウンド本来の未調整のボリュームを表す。
	値 VOLUME_MIN は、オーディオのボリュームが 100 dB 減衰していることを表すが、これは実際的には無音を意味する。
*/
extern DLL_DXSOUND_API int GetVolume( BYTE ch );
/** パン値を変更します
	* @param ch		チャンネル
	* @param value	左右のチャンネルの相対ボリューム
	* @retval なし
	* @attention　設定可能な値の範囲は PAN_LEFT から PAN_RIGHT の範囲で、1/100 デシベル (dB) の単位で測定される。
	これらの値は、それぞれ -10,000 および 10,000 と定義されている。
	値 PAN_LEFT は、右チャンネルが 100 dB 減衰し、実質的に無音であることを意味する。
	値 PAN_RIGHT は、左チャンネルが無音であることを意味する。
	PAN_CENTER は中立値で 0 と定義されており、両方のチャンネルが最大ボリュームであることを意味する。
	一方のチャンネルが減衰するとき、もう一方は最大音量のままである。
*/
extern DLL_DXSOUND_API void SetPan( BYTE ch, int value );
/** パン値を取得します
	* @param ch		チャンネル
	* @retval 相対ボリューム (1/100 デシベル単位) 
	* @attention　戻り値は 1/100 デシベル (dB) 単位で測定され、範囲は PAN_LEFT から PAN_RIGHT までです。
	これらの値は、それぞれ -10,000 および 10,000 と定義されています。
	値 PAN_LEFT は、右チャンネルが実質的に無音であることを意味します。
	値 PAN_RIGHT は、左チャンネルが実質的に無音であることを意味します。
	PAN_CENTER は中立値で、0 と定義されており、両方のチャンネルが最大ボリュームであることを意味します。
	一方のチャンネルが減衰するとき、もう一方のチャンネルは最大ボリュームのままです。
*/
extern DLL_DXSOUND_API int GetPan( BYTE ch );
/** サンプリング オーディオの再生周波数を設定する
	* @param ch		チャンネル
	* @param value	再生周波数
	* @retval なし
	* @attention　周波数を上下させると、オーディオ データの認識ピッチが変化する。
	このメソッドは、バッファのフォーマットには影響を与えない。
*/
extern DLL_DXSOUND_API void SetFrequency( BYTE ch, int value );
/** バッファが再生されている周波数 (1 秒あたりのサンプリング数) を取得する
	* @param ch		チャンネル
	* @retval バッファの周波数の値
	* @attention　ソフトウェア バッファの周波数の値の範囲は FREQUENCY_MIN から FREQUENCY_MAX までである。
*/
extern DLL_DXSOUND_API int GetFrequency( BYTE ch );


//----------------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif

#endif	// __DXSOUND_H__
