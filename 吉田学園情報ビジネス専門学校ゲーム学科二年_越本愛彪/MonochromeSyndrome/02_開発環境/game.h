//=============================================================================
//
// ゲームの内部処理 [game.h]
// Author : 越本　愛彪
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

typedef enum
{
	GAMESTATE_NONE = 0,
	GAMESTATE_STAGE1,
	GAMESTATE_STAGE2,
	GAMESTATE_STAGE3,
	GAMESTATE_STAGE4,
	GAMESTATE_STAGE5,
	GAMESTATE_STAGE6,
	GAMESTATE_STAGE7,
	GAMESTATE_CLEAR,
	GAMESTATE_END,
	GAMESTATE_MAX
} GAMESTATE;

typedef struct
{
	bool bDisp;
} PAUSE;

//プロトタイプ宣言
void InitGame(void);				//ゲームの初期化
void UninitGame(void);				//ゲームの終了
void UpdataGame(void);				//ゲームの更新
void DrawGame(void);				//ゲームの描画
void SetGameState(GAMESTATE state);	//ゲーム状態の設定
GAMESTATE *GetGameState(void);		//ゲーム情報の取得
PAUSE *GetPause(void);				//ポーズ状態を取得

#endif 