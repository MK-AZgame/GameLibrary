//========================================================
//
//	ゲーム内部処理[game.h]
//	Author:越本愛彪
//
//========================================================
#ifndef _GAME_H_
#define _GAME_H_

typedef enum
{
	GAMESTATE_NONE = 0,
	GAMESTATE_NORMAL,
	GAMESTATE_CLEAR,
	GAMESTATE_END,
	GAMESTATE_MAX
} GAMESTATE;

typedef struct
{
	bool bDisp;
} PAUSE;

//プロトタイプ宣言
void InitGame(void);				//ゲーム初期化
void UninitGame(void);				//ゲーム終了
void UpdateGame(void);				//ゲーム更新
void DrawGame(void);				//ゲーム描画
void SetGameState(GAMESTATE state);	//ゲーム状態の設定
GAMESTATE *GetGameState(void);		//ゲーム状態の取得
PAUSE *GetPause(void);				//ポーズの情報の取得

#endif 
