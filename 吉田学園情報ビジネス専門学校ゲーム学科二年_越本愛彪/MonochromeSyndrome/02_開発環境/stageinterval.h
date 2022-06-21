//=============================================================================
//
// ステージ間のフェードの処理 [stageinterval.h]
// Author : 越本　愛彪
//
//=============================================================================
#ifndef _STAGEINTERVAL_H_
#define _STAGEINTERVAL_H_

#include "game.h"

//フェードの状態
typedef enum
{
	INTERVAL_NONE = 0,							//何もしていない状態
	INTERVAL_IN,								//フェードイン状態
	INTERVAL_OUT,								//フェードアウト状態
	INTERVAL_MAX
}INTERVAL;

//プロトタイプ宣言
void InitStageInterval(GAMESTATE nextstage);	//ステージ間フェードの初期化
void UninitStageInterval(void);					//ステージ間フェードの終了
void UpdataStageInterval(void);					//ステージ間フェードの更新
void DrawStageInterval(void);					//ステージ間フェードの描画
void SetStageInterval(GAMESTATE nextstage);		//ステージ間フェードの設定
INTERVAL GetStageInterval(void);				//ステージ間フェード情報の取得

#endif