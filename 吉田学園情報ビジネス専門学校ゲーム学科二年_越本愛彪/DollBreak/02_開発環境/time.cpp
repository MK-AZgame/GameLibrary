//========================================================
//
//	タイマーの処理[time.cpp]
//	AUTHOR:越本愛彪
//
//========================================================
#include "main.h"
#include "time.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "high_score.h"

//マクロ定義
#define NUM_TIMER (3)											//タイマーの桁
#define ONE_SENT  (60)											//1フレームを1/60秒としたときの1秒

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTimer = NULL;						//タイマーのテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;					//タイマーの頂点情報へのポインタ
D3DXVECTOR3 g_posTimer;											//タイマーの位置
Timer g_timer;													//タイマーの情報を格納

//========================================================
//			タイマーの初期化処理
//========================================================
void InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/number000.png", &g_pTextureTimer);

	//グローバル変数の初期化
	g_posTimer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//位置の初期化
	g_timer.nSec = 0;											//タイマーカウント（秒）の初期化
	g_timer.nDec = 00;											//タイマーカウント（小数点以下）の初期化

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (NUM_TIMER * 2),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimer,
		NULL);

	VERTEX_2D *pVtx;											//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTimer = 0; nCntTimer < NUM_TIMER * 2; nCntTimer++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(1070.0f + (50.0f * nCntTimer), 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1120.0f + (50.0f * nCntTimer), 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1070.0f + (50.0f * nCntTimer), 60.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1120.0f + (50.0f * nCntTimer), 60.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点座標をアンロック
	g_pVtxBuffTimer->Unlock();
}

//========================================================
//			タイマーの終了処理
//========================================================
void UninitTimer(void)
{
	//テクスチャの破棄
	if (g_pTextureTimer != NULL)
	{
		g_pTextureTimer->Release();
		g_pTextureTimer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}
}

//========================================================
//			タイマーの更新処理
//========================================================
void UpdataTimer(void)
{
	GAMESTATE state = *GetGameState();

	//小数点以下の数値を減少
	g_timer.nDec++;

	//秒数の減少
	if (g_timer.nDec >= 60)
	{//小数点以下の数値が60以上になった時
		//少数手に科の数値を0に戻す
		g_timer.nDec = 0;

		//秒数を加算
		g_timer.nSec++;
	}
}

//========================================================
//			タイマーの描画処理
//========================================================
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTimer = 0; nCntTimer < NUM_TIMER; nCntTimer++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTimer);

		//ポリゴンの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,								//プリミティブの種類
			4 * nCntTimer,
			2);													//プリミティブの数	
	}
}

//========================================================
//			リザルトタイムの表示処理
//========================================================
void DrawResultTime(int nResultTime)
{
	VERTEX_2D *pVtx;
	float aPosTexU[NUM_TIMER];									//各桁の数値を収納

	//各桁の数値を計算
	aPosTexU[0] = ((nResultTime % 1000) / 100) * 0.1f;
	aPosTexU[1] = ((nResultTime % 100) / 10) * 0.1f;
	aPosTexU[2] = (nResultTime % 10) * 0.1f;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTimer = 0; nCntTimer < NUM_TIMER; nCntTimer++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(530.0f + (60.0f * nCntTimer), 240.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(590.0f + (60.0f * nCntTimer), 240.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(530.0f + (60.0f * nCntTimer), 320.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(590.0f + (60.0f * nCntTimer), 320.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + aPosTexU[nCntTimer], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aPosTexU[nCntTimer], 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aPosTexU[nCntTimer], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aPosTexU[nCntTimer], 1.0f);

		pVtx += 4;
	}

	//頂点座標をアンロック
	g_pVtxBuffTimer->Unlock();

	DrawTimer();
}

//========================================================
//			タイマーを止める
//========================================================
void StopTimer(void)
{
	//最終的なタイムを保存
	SetResultTime(g_timer.nSec);
	SaveHighScore(g_timer.nSec);
}