//========================================================
//
//	リザルトの処理[result.cpp]
//	Author:越本愛彪
//
//========================================================
#include "main.h"
#include "result.h"
#include "player.h"
#include "input.h"
#include "fade.h"
#include "time.h"
#include "sound.h"
#include "game.h"
#include "high_score.h"

//マクロ定義
#define NUM_BACKGROUND (2)											//リザルト画面に使うテクスチャの数

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureResult[NUM_BACKGROUND] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;
int g_nResultTime;

//========================================================
//			リザルトの初期化処理
//========================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	GAMESTATE state = *GetGameState();

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/game_clear.png", &g_pTextureResult[0]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/game_over.png", &g_pTextureResult[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BACKGROUND, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffResult, NULL);

	VERTEX_2D *pVtx;												//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	if (state == GAMESTATE_CLEAR)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		PlaySound(SOUND_LABEL_RESULT);
	}
	else if (state == GAMESTATE_END)
	{
		pVtx += 4;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		PlaySound(SOUND_LABEL_GAMEOVER);
	}

	//頂点座標をアンロック
	g_pVtxBuffResult->Unlock();

	InitTimer();
	InitHighScore();
}

//========================================================
//			リザルトの終了処理
//========================================================
void UninitResult(void)
{
	UninitTimer();
	//UninitHighScore();

	//テクスチャの破棄
	for (int nCntTexture = 0; nCntTexture < NUM_BACKGROUND; nCntTexture++)
	{
		if (g_pTextureResult[nCntTexture] != NULL)
		{
			g_pTextureResult[nCntTexture]->Release();
			g_pTextureResult[nCntTexture] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	//サウンドの停止
	StopSound();
}

//========================================================
//			リザルトの更新処理
//========================================================
void UpdateResult(void)
{
	FADE fade = GetFade();

	if (fade == FADE_NONE)
	{//右クリックされた
		if (GetMouseTrigger(0))
		{
			PlaySound(SOUND_LABEL_SE_DECISION);

			SetFade(MODE_TITLE);
		}
	}
}

//========================================================
//			リザルトの描画処理
//========================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	GAMESTATE &pState = *GetGameState();
	
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTexture = 0; nCntTexture < NUM_BACKGROUND; nCntTexture++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureResult[nCntTexture]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,									//プリミティブの種類
			4 * nCntTexture,
			2);														//プリミティブの数
	}

	//テクスチャを元に戻す
	pDevice->SetTexture(0, NULL);

	if (pState == GAMESTATE_CLEAR)
	{
		DrawResultTime(g_nResultTime);
		DrawHighScore();
	}
}

//========================================================
//			最終的なタイムの取得
//========================================================
void SetResultTime(int nTime)
{
	g_nResultTime = nTime;
}