//========================================================
//
//	ゲーム内部処理[game.cpp]
//	Author:越本愛彪
//
//========================================================
#include "main.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "fade.h"
#include "pause.h"
#include "sound.h"
#include "round.h"
#include "input.h"
#include "light.h"
#include "camera.h"
#include "shadow.h"
#include "wall.h"
#include "meshfield.h"
#include "bullet.h"
#include "effect.h"
#include "Explosion.h"
#include "player.h"
#include "line.h"
#include "model.h"
#include "time.h"
#include "reticle.h"
#include "remainingbullet.h"
#include <Windows.h>

//グローバル変数
GAMESTATE g_gameState;
int g_nCounterGameState;
PAUSE g_pause;

//========================================================
//			ゲームの初期化処理
//========================================================
void InitGame(void)
{
	//ポーズの初期化
	g_pause.bDisp = false;

	//残弾数の初期化
	InitRemain();
	//弾の初期化
	Initbullet();
	//プレイヤーの初期化処理
	InitPlayer();
	//エネミーの初期化処理
	InitEnemy();
	//爆発の初期化
	InitExplosion();
	//ポーズの初期化
	InitPause();
	//メッシュフィールドの初期化
	InitMeshfield();
	//影の初期化
	InitShadow();
	//モデルの初期化
	InitModel();
	//プレイヤーの初期化
	InitPlayer();
	//ビルボードの初期化
	//InitBillboard();
	//カメラの初期化
	InitCamera();
	//ライトの初期化
	InitLight();
	//壁の初期化
	InitWall();
	//エフェクトの初期化
	InitEffect();
	//ラインの初期化
	InitLine();
	//ラウンドの初期化
	InitRound();
	//タイマーの初期化
	InitTimer();
	//レティクルの初期化
	InitReticle();
	
	SetGameState(GAMESTATE_NORMAL);

	//サウンドの再生
	PlaySound(SOUND_LABEL_GAME);
}

//========================================================
//			ゲームの終了処理
//========================================================
void UninitGame(void)
{
	//ポーズの終了
	UninitPause();
	//ラウンドの終了
	UninitRound();	
	//タイマーの終了
	UninitTimer();
	//エネミーの終了処理
	UninitEnemy();
	//プレイヤーの終了処理
	UninitPlayer();
	//メッシュフィールドの終了処理
	UninitMeshfield();
	//プレイヤーの終了処理
	UninitPlayer();
	//ライトの終了処理
	UninitLight();
	//カエラの終了処理
	UninitCamera();
	//影の終了処理
	UninitShadow();
	//壁の終了処理
	UninitWall();
	//ビルボードの終了処理
	//UninitBillboard();
	//弾の終了処理
	Uninitbullet();
	//エフェクトの終了処理
	UninitEffect();
	//モデルの終了処理
	UninitModel();
	//ラインの終了処理
	UninitLine();
	//レティクルの終了処理
	UninitReticle();
	//残弾数の終了処理
	UninitRemain();
	//爆発の終了処理
	UninitExplosion();

	//サウンドの停止
	StopSound();
}

//========================================================
//			ゲームの更新処理
//========================================================
void UpdateGame(void)
{
	PAUSE *pause = GetPause();
	Enemy *penemy = GetEnemy();
	POINT mousePos;
	//debug
	FADE fade = GetFade();
	GAMESTATE &state = *GetGameState();
	//
	//ポーズ
	if (GetKeyboardTrigger(DIK_P) || GetJoypadPress(JOYKEY_START) == true)
	{
		pause->bDisp = true;
	}

	//debug
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		if (fade == FADE_NONE)
		{
			StopTimer();
			state = GAMESTATE_CLEAR;
			SetFade(MODE_RESULT);
		}
	}
	//else if (GetKeyboardTrigger(DIK_1))
	//{
	//	if (fade == FADE_NONE)
	//	{
	//		state = GAMESTATE_END;
	//		SetFade(MODE_RESULT);
	//	}
	//}

	if (g_pause.bDisp == false)
	{
		//マウスを非表示にする
		ShowCursor(FALSE);

		//マウスの位置を取得
		GetCursorPos(&mousePos);

		mousePos.x = 640.0f;
		mousePos.y = 360.0f;

		//マウスの位置を設定
		SetCursorPos(mousePos.x, mousePos.y);

		//プレイヤーの更新処理
		UpdatePlayer();
		//エネミーの更新処理
		UpdateEnemy();
		//エネミーのモーション
		EnemyMotion();
		//メッシュフィールドの更新処理
		UpdateMeshfield();
		//カメラの更新処理
		UpdateCamera();
		//影の更新処理
		UpdataShadow();
		//ライトの更新処理
		UpdateLight();
		//壁の更新処理
		UpdataWall();
		//ビルボードの更新処理
		//UpdataBillboard();
		//弾の更新処理
		Updatebullet();
		//エフェクトの更新処理
		UpdateEffect();
		//モデルの更新処理
		UpdateModel();
		//ラインの更新処理
		UpdateLine();
		//ラウンドの更新処理
		UpdataRound();
		//タイマーの更新処理
		UpdataTimer();
		//爆発の更新処理
		UpdateExplosion();
	}
	else
	{
		//マウスを表示にする
		ShowCursor(TRUE);

		//ポーズの更新
		UpdatePause();
	}
}

//========================================================
//			ゲームの描画処理
//========================================================
void DrawGame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DVIEWPORT9 viewport;
	pDevice->GetViewport(&viewport);

	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		//カメラの終了処理
		SetCamera(nCntCamera);

		//画面クリア
		pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

		//描画開始
		if (SUCCEEDED(pDevice->BeginScene()))
		{//描画開始が成功した場合
		 //各種オブジェクトの描画処理

			//プレイヤーの描画処理
			DrawPlayer();
			//エネミーの描画処理
			DrawEnemy();
			//メッシュフィールドの描画処理
			DrawMeshfield();
			//壁の描画処理
			DrawWall();
			//ビルボードの描画処理
			//DrawBillboard();
			//モデルの描画処理
			DrawModel();
			//影の描画処理
			DrawShadow();
			//弾の描画処理
			Drawbullet();
			//エフェクト描画処理
			DrawEffect();
			//ラインの描画処理
			DrawLine();
			//ラウンドの描画
			DrawRound();
			//レティクルの描画
			DrawReticle();
			//残弾数の描画
			DrawRemain();
			//ポーズの描画
			DrawPause();

			//描画終了
			pDevice->EndScene();
		}
	}

	//ビューポートを元に戻す
	pDevice->SetViewport(&viewport);

}

//========================================================
//			ゲームの状態の設定
//========================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;

	g_nCounterGameState = 0;
}
//========================================================
//			ゲームの状態の取得
//========================================================
GAMESTATE *GetGameState(void)
{
	return &g_gameState;
}

//========================================================
//			ポーズの状態の取得
//========================================================
PAUSE *GetPause(void)
{
	return &g_pause;
}