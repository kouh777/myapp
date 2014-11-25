
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
// スクリーンサイズ定義
#define GAME_SCREEN_W 600
#define GAME_SCREEN_H 600

//---------------------------------------------------------------------
// vector利用 
using std::vector;

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
#define ENEM_NO						0
#define ENEM_BOX					1
#define ENEM_FISH					2
#define ENEM_BOSS_FORTRESS			3	//	ステージ2ボス砲台
#define ENEM_BOSS_SPACESHITP		4	//	ステージ2ボス
#define ENEM_BOSS_RIGHT_WING		12	//	ステージ2ボス右翼
#define ENEM_BOSS_LEFT_WING			13	//	ステージ2ボス左翼
#define ENEM_BOSS_BODY				14	//	ステージ2ボス本体

//---------------------------------------------------------------------
// エフェクト定義
#define EFF_EXPLOSION				1	// 爆発エフェクト
#define EFF_BARRIER					2	// バリアエフェクト
#define EFF_HIT						3	// ヒットエフェクト
#define EFF_SCOPE					4	// ボス弱点表示用スコープ

//---------------------------------------------------------------------
// 障害物・ステージギミック定義
#define GIM_COMMET					1	// 隕石障害物
#define GIM_MINI_COMMET				2	// 隕石障害物(破片)
#define GIM_BEAM					3	// ビーム障害物
#define GIM_NETWORK					4	// 通信ギミック

//---------------------------------------------------------------------
// アイテム定義
#define ITM_POWER					1	// パワーアップアイテム
#define ITM_SOUL					2	// ソウルチャージパワーアップアイテム
#define ITM_SCORE					3	// スコアアップアイテム
#define ITM_NETWORK					4	// 通信アイテム


//---------------------------------------------------------------------
#endif	// __GAMEDEF_H__