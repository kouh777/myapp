
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
// スクリーンサイズ定義
#define GAME_SCREEN_W 600
#define GAME_SCREEN_H 600

//--------------------------------------------------------
// セーフデリート
#define SAFE_RELEASE(x)	{ if(x!=NULL) x->Release(); x=NULL; };
#define SAFE_DELETE(x)	{ if(x!=NULL) x->delete; x=NULL; };

/*
//------------------------------------------
// ステージID定義
#define STAGE_1							1	//	ステージ1
#define STAGE_2							2	//	ステージ2
#define STAGE_3							3	//	ステージ3
#define STAGE_4							4	//	ステージ4
#define STAGE_5							5	//	ステージ5
*/

//------------------------------------------
// ステージID定義
enum STG_ID{
	STAGE_1,		//	ステージ1
	STAGE_2,		//	ステージ2
	STAGE_3,		//	ステージ3
	STAGE_4,		//	ステージ4
	STAGE_5,		//	ステージ5
	STAGE_DEBUG		//	デバッグ用ステージ
};

//------------------------------------------
// 選択プレイヤー定義
#define PL_GRANDVISOR					1	//	グランバイザー
#define PL_GRANDSAVER					2	//	グランセイバー
#define PL_COMBAT						3	//	初期戦闘機

//------------------------------------------
// プレイヤーショット定義
#define SH_NORMAL					1	// 通常弾
#define SH_BEAM						2	// ビーム
#define SH_AIMING					3	// 狙い撃ち弾
#define SH_HOMING					4	// ホーミング弾
#define SH_MULTIPLE					5	// 分裂弾(分裂前)
#define SH_MINI_MULTIPLE			6	// 分裂弾(分裂後)
#define SH_BLAST_SHOT				7	// 爆発弾
#define SH_BLAT						8	// 爆発弾(爆風)

//------------------------------------------
// 敵弾定義
#define BUL_ONE_WAY					1	//　通常弾
#define BUL_HOMING					2	//　ホーミング弾
#define BUL_AIMING					3	//　狙い撃ち弾
#define BUL_WAVE					4	//　波打ち弾
#define BUL_WAY_ALONG				5	//　経路追従弾

//------------------------------------------
// 敵ID定義
#define ENEM_NO						0	//	ダミーエネミー
#define ENEM_BOX					1	//	雑魚敵(その1)
#define ENEM_FISH					2	//	雑魚敵(その2)
#define ENEM_BOSS_FORTRESS			3	//	ステージ2ボス砲台
#define ENEM_BOSS_SPACESHITP		4	//	ステージ2ボス
#define ENEM_BOSS_RIGHT_WING		12	//	ステージ2ボス右翼
#define ENEM_BOSS_LEFT_WING			13	//	ステージ2ボス左翼
#define ENEM_BOSS_BODY				14	//	ステージ2ボス本体
#define ENEM_BOSS_DEGIN				20	//	ジークザデギン(ステージ1,ステージ3ボス)
#define ENEM_BOSS_UNDERSON			30	//	エルダアンダーソン(ステージ4ボス)
#define ENEM_BOSS_SHADOW_VISOR		40	//	闇男主人公機(ステージ5ボス)
#define ENEM_BOSS_SHADOW_SABER		41	//	闇女主人公機(ステージ5ボス)
#define ENEM_BOSS_ALBERT			50	//	アルバートロイアデウス(ステージ6ラスボス)

#define ENEM_MINI_COMMET			98	//	隕石障害物
#define ENEM_COMMET					99	//	隕石障害物(破片)

//---------------------------------------------------------------------
// エフェクト定義
#define EFF_EXPLOSION				1	// 爆発エフェクト
#define EFF_BARRIER					2	// バリアエフェクト
#define EFF_HIT						3	// ヒットエフェクト
#define EFF_SCOPE					4	// ボス弱点表示用スコープ
#define EFF_BIG_EXPLOSION			5	// 大爆発エフェクト
#define EFF_FINAL_BIG_EXPLOSION		6	// 超大爆発エフェクト

//---------------------------------------------------------------------
// ステージギミック定義
#define GIM_BEAM					1	// ビーム障害物
#define GIM_NETWORK					2	// 通信ギミック

//---------------------------------------------------------------------
// アイテム定義
#define ITM_POWER					1	// パワーアップアイテム
#define ITM_SOUL					2	// ソウルチャージパワーアップアイテム
#define ITM_SCORE					3	// スコアアップアイテム
#define ITM_NETWORK					4	// 通信アイテム

//---------------------------------------------------------------------
// UI関連定義
#define UI_PL_VITAL					1	// プレイヤー体力UI
#define UI_PL_BOM					2	// プレイヤー残りボム数UI
#define UI_BTN_STG_1				3	// ステージ1ボタン
#define UI_BTN_STG_2				4	// ステージ2ボタン
#define UI_BTN_STG_3				5	// ステージ3ボタン
#define UI_BTN_STG_4				6	// ステージ4ボタン
#define UI_BTN_STG_5				7	// ステージ5ボタン
#define UI_BTN_REW					8	// 戦果報酬ボタン
#define UI_CUR						9	// ボタンカーソル
#define UI_STG_DIS					10	// ステージ説明枠
#define UI_PL_DIS					11	// プレイヤー説明枠
#define UI_CHARACTER_SEIYA			12	// 男性主人公機立ち絵
#define UI_CHARACTER_KANATA			13	// 女性主人公機立ち絵
#define UI_PLAYER_VITALITY			14  // プレイヤー体力
#define UI_PLAYER_LIFE				15	// プレイヤー残機
#define UI_BTN_SHION				16	// 男主人公ボタン
#define UI_BTN_SHION_S				17	// 男主人公ボタン選択中
#define UI_BTN_KANATA				18	// 女主人公ボタン
#define UI_BTN_KANATA_S				19	// 女主人公ボタン選択中

//---------------------------------------------------------------------
// プレイヤーデータ関係定義
#define PLAYER_MAX_LIFE				3	// 最大プレイヤー残機			

//---------------------------------------------------------------------
// vector利用 
using std::vector;

//---------------------------------------------------------------------
#endif	// __GAMEDEF_H__