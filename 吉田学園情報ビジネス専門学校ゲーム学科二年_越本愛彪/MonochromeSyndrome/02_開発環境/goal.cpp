//=============================================================================
//
// ゴールの処理 [goal.cpp]
// Author : 越本　愛彪
//
//=============================================================================
#include <stdio.h>
#include "main.h"
#include "input.h"
#include "player.h"
#include "Goal.h"
#include "goal.h"
#include "game.h"
#include "fade.h"
#include "timer.h"
#include "high_score.h"
#include "stageinterval.h"

//マクロ定義
#define GOAL_SIZE (40)									//ゴールのサイズ

//ゴール構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;									//位置
	D3DXVECTOR3 posOld;
	float fWidth;										//幅
	float fHeight;										//高さ
	bool bUse;											//使用しているかどうか
}Goal;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureGoal = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGoal = NULL;			//頂点バッファへのポインタ
Goal g_Goal;											//ゴールの情報

//=============================================================================
//		ゴールの初期化処理
//=============================================================================
void InitGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//ゴールの情報の初期化
	g_Goal.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Goal.fWidth = 0.0f;
	g_Goal.fHeight = 0.0f;
	g_Goal.bUse = false;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffGoal, NULL);

	VERTEX_2D *pVtx;									//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_Goal.pos.x - GOAL_SIZE / 2, g_Goal.pos.y - GOAL_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Goal.pos.x + GOAL_SIZE / 2, g_Goal.pos.y - GOAL_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Goal.pos.x - GOAL_SIZE / 2, g_Goal.pos.y + GOAL_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Goal.pos.x + GOAL_SIZE / 2, g_Goal.pos.y + GOAL_SIZE, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点座標をアンロッ
	g_pVtxBuffGoal->Unlock();
}

//=============================================================================
//		ゴールの終了処理
//=============================================================================
void UninitGoal(void)
{
	//テクスチャの破棄
	if (g_pTextureGoal != NULL)
	{
		g_pTextureGoal->Release();
		g_pTextureGoal = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffGoal != NULL)
	{
		g_pVtxBuffGoal->Release();
		g_pVtxBuffGoal = NULL;
	}
}

//=============================================================================
//		ゴールの更新処理
//=============================================================================
void UpdataGoal(void)
{
	Player *pPlayer = GetPlayer();

	if (g_Goal.bUse == true)
	{
		if (pPlayer->pos.x >= SCREEN_WIDTH / 2)
		{
			ScrollGoal(D3DXVECTOR3(pPlayer->move.x, 0.0f, 0.0f));
		}
	}
}

//=============================================================================
//		ゴールの描画処理
//=============================================================================
void DrawGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGoal, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureGoal);

	if (g_Goal.bUse == true)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,									//プリミティブの種類
			0,
			2);														//プリミティブの数	
	}
}

//=============================================================================
//		ゴールの設定処理
//=============================================================================
void SetGoal(D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Goal.bUse == false)
	{
		//ゴールの各情報の設定
		g_Goal.pos = pos;
		g_Goal.fHeight = GOAL_SIZE;
		g_Goal.fWidth = GOAL_SIZE;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_Goal.pos.x - GOAL_SIZE / 2, g_Goal.pos.y - GOAL_SIZE / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Goal.pos.x + GOAL_SIZE / 2, g_Goal.pos.y - GOAL_SIZE / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Goal.pos.x - GOAL_SIZE / 2, g_Goal.pos.y + GOAL_SIZE / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Goal.pos.x + GOAL_SIZE / 2, g_Goal.pos.y + GOAL_SIZE / 2, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//使用している状態に変更
		g_Goal.bUse = true;
	}

	//頂点座標をアンロック
	g_pVtxBuffGoal->Unlock();
}

//=============================================================================
//		ゴールの当たり判定
//=============================================================================
void ColisionGoal(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
{
	Player *pPlayer = GetPlayer();
	GAMESTATE &pState = *GetGameState();
	FADE fade = GetFade();

	//ゴールに触れたときの処理
	if (g_Goal.bUse == true)
	{
		if (pPos->x + fWidth / 2 > g_Goal.pos.x - g_Goal.fWidth / 2 &&
			pPos->x - fWidth / 2 < g_Goal.pos.x + g_Goal.fWidth / 2 &&
			pPos->y > g_Goal.pos.y - g_Goal.fHeight / 2 &&
			pPos->y - fHeight < g_Goal.pos.y + g_Goal.fHeight / 2)
		{
			if (pState == GAMESTATE_STAGE1)
			{//ステージ１クリア時
				SetStageInterval(GAMESTATE_STAGE2);
			}
			else if (pState == GAMESTATE_STAGE2)
			{//ステージ２クリア時
				SetStageInterval(GAMESTATE_STAGE3);
			}
			else if (pState == GAMESTATE_STAGE3)
			{//ステージ３クリア時
				SetStageInterval(GAMESTATE_STAGE4);
			}
			else if (pState == GAMESTATE_STAGE4)
			{//ステージ４クリア時
				SetStageInterval(GAMESTATE_STAGE5);
			}
			else if (pState == GAMESTATE_STAGE5)
			{//ステージ５クリア時
				SetStageInterval(GAMESTATE_STAGE6);
			}
			else if (pState == GAMESTATE_STAGE6)
			{//ステージ6クリア時
				SetStageInterval(GAMESTATE_STAGE7);
			}
			else if (pState == GAMESTATE_STAGE7)
			{//ステージ7クリア時
				if (fade == FADE_NONE)
				{
					pPlayer->bDisp = false;
					pState = GAMESTATE_CLEAR;
					SaveHighScore(GetTime());
					SetFade(MODE_RESULT);
					SetResultTime(GetTime());
				}
			}
		}
	}
}

//=============================================================================
//		ブロックのスクロール処理
//=============================================================================
void ScrollGoal(D3DXVECTOR3 move)
{
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Goal.bUse == true)
	{
		g_Goal.pos.x -= move.x;
	}

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_Goal.pos.x - g_Goal.fWidth / 2, g_Goal.pos.y - GOAL_SIZE / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Goal.pos.x + g_Goal.fWidth / 2, g_Goal.pos.y - GOAL_SIZE / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Goal.pos.x - g_Goal.fWidth / 2, g_Goal.pos.y + GOAL_SIZE / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Goal.pos.x + g_Goal.fWidth / 2, g_Goal.pos.y + GOAL_SIZE / 2, 0.0f);

	//アンロック
	g_pVtxBuffGoal->Unlock();
}