//=============================================================================
//
// ゲームの内部処理 [game.cpp]
// Author : 越本　愛彪
//
//=============================================================================
#include "main.h"
#include "game.h"
#include "block.h"
#include "goal.h"
#include "player.h"
#include "Bg.h"
#include "fade.h"
#include "pause.h"
#include "sound.h"
#include "timer.h"
#include "input.h"
#include "playerlife.h"
#include "stageinterval.h"

//グローバル変数
GAMESTATE g_gameState;		//ゲームの状態
PAUSE g_pause;

//=============================================================================
//		ゲームの初期化処理
//=============================================================================
void InitGame(void)
{
	g_pause.bDisp = false;

	//ステージ間のフェードの初期化
	InitStageInterval(g_gameState);
	//背景の初期化処理
	InitBg();
	//プレイヤーの初期化処理
	InitPlayer();
	//ゴールの初期化
	InitGoal();
	//ポーズの初期化
	InitPause();
	//タイマーの初期化
	InitTimer();
	//プレイヤー体力表示の初期化
	InitPlayerLife();
	
	SetGameState(GAMESTATE_STAGE1);

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM001);
}

//=============================================================================
//		ゲームの終了処理
//=============================================================================
void UninitGame(void)
{
	//背景の終了処理
	UninitBg();
	//ブロックの終了処理
	UninitBlock();
	//ゴールの終了処理
	UninitGoal();
	//ポーズの終了
	UninitPause();
	//タイマーの終了
	UninitTimer();
	//プレイヤーの終了処理
	UninitPlayer();
	//ステージ間のフェードの終了
	UninitStageInterval();
	//プレイヤーの体力表示終了
	UninitPlayerLife();

	//サウンドの停止
	StopSound();
}

//=============================================================================
//		ゲームの更新処理
//=============================================================================
void UpdataGame(void)
{
	INTERVAL interval = GetStageInterval();
	PAUSE *pause = GetPause();

	//ポーズ
	if (GetKeyboardTrigger(DIK_P) || GetJoypadPress(JOYKEY_START) == true)
	{
		pause->bDisp = true;
	}

	if (interval == INTERVAL_NONE)
	{
		if (g_pause.bDisp == false)
		{
			//背景の更新処理
			UpdataBg();
			//プレイヤーの更新処理
			UpdataPlayer();
			//ブロックの更新処理
			UpdataBlock();
			//ゴールの更新処理
			UpdataGoal();
			//タイマーの更新処理
			UpdataTimer();
			//プレイヤーの体力表示の更新
			UpdataPlayerLife();
		}
		//ポーズの更新
		UpdataPause();
	}

	//ステージ間のフェードの更新
	UpdataStageInterval();

	//デバッグ機能
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		SetGameState(GAMESTATE_STAGE1);
	}
	else if (GetKeyboardTrigger(DIK_1) == true)
	{
		SetGameState(GAMESTATE_STAGE2);
	}
	else if (GetKeyboardTrigger(DIK_2) == true)
	{
		SetGameState(GAMESTATE_STAGE3);
	}
	else if (GetKeyboardTrigger(DIK_3) == true)
	{
		SetGameState(GAMESTATE_STAGE4);
	}
	else if (GetKeyboardTrigger(DIK_4) == true)
	{
		SetGameState(GAMESTATE_STAGE5);
	}
	else if (GetKeyboardTrigger(DIK_5) == true)
	{
		SetGameState(GAMESTATE_STAGE6);
	}
	else if (GetKeyboardTrigger(DIK_6) == true)
	{
		SetGameState(GAMESTATE_STAGE7);
	}
}

//=============================================================================
//		ゲームの描画処理
//=============================================================================
void DrawGame(void)
{
	//背景の描画処理
	DrawBg();
	//プレイヤーの描画処理
	DrawPlayer();
	//ゴールの終了処理
	DrawGoal();
	//ブロックの描画処理
	DrawBlock();
	//ポーズの描画
	DrawPause();
	//タイマーの描画
	DrawTimer();
	//プレイヤーの体力表示の描画
	DrawPlayerLife();
	//ステージ間のフェードの描画
	DrawStageInterval();
}

//=============================================================================
//		ゲームの状態の設定
//=============================================================================
void SetGameState(GAMESTATE state)
{
	//ブロックの終了
	UninitBlock();
	//ブロックの初期化
	InitBlock();
	//ゴールの終了
	UninitGoal();
	//ゴールの初期化
	InitGoal();

	//ステージの読み込み
	switch (state)
	{
	case GAMESTATE_STAGE1:
		ScanFile("./stage/TEXT/stage.txt");
		break;
	case GAMESTATE_STAGE2:
		ScanFile("./stage/TEXT/stage2.txt");
		break;
	case GAMESTATE_STAGE3:
		ScanFile("./stage/TEXT/stage3.txt");
		break;
	case GAMESTATE_STAGE4:
		ScanFile("./stage/TEXT/stage4.txt");
		break;
	case GAMESTATE_STAGE5:
		ScanFile("./stage/TEXT/stage5.txt");
		break;
	case GAMESTATE_STAGE6:
		ScanFile("./stage/TEXT/stage6.txt");
		break;
	case GAMESTATE_STAGE7:
		ScanFile("./stage/TEXT/stage7.txt");
		break;
	}
	g_gameState = state;
}
//=============================================================================
//		ゲームの状態の取得
//=============================================================================
GAMESTATE *GetGameState(void)
{
	return &g_gameState;
}

//=============================================================================
//		ポーズの状態の取得
//=============================================================================
PAUSE *GetPause(void)
{
	return &g_pause;
}