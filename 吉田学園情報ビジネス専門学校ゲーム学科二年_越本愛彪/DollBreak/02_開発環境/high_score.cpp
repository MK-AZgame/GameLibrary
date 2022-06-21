//========================================================
//
//	ハイスコア処理[high_score.cpp]
//	AUTHOR:越本愛彪
//
//========================================================
#include <stdio.h>
#include "main.h"
#include "time.h"
#include "game.h"
#include "result.h"
#include "high_score.h"

//マクロ定義
#define NUM_TIMER (3)									//ハイスコアの桁
#define ONE_SENT  (60)

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureHighScore = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHighScore = NULL;
D3DXVECTOR3 g_posHighScore;								//ハイスコアの位置
int g_nHighScore;										//ハイスコアの値

//========================================================
//			ハイスコアの初期化処理
//========================================================
void InitHighScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTimer;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/number000.png", &g_pTextureHighScore);

	g_posHighScore = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期化
	g_nHighScore = 0;									//ハイスコアの初期化

	//ハイスコアを読み込む
	LoadHighScore();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TIMER, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffHighScore, NULL);

	VERTEX_2D *pVtx;									//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffHighScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTimer = 0; nCntTimer < NUM_TIMER; nCntTimer++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(530.0f + (60.0f * nCntTimer), 450.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(590.0f + (60.0f * nCntTimer), 450.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(530.0f + (60.0f * nCntTimer), 530.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(590.0f + (60.0f * nCntTimer), 530.0f, 0.0f);

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
	g_pVtxBuffHighScore->Unlock();

	//ハイスコアの設定処理
	SetHighScore();
}

//========================================================
//			ハイスコアの終了処理
//========================================================
void UninitHighScore(void)
{
	//テクスチャの破棄
	if (g_pTextureHighScore != NULL)
	{
		g_pTextureHighScore->Release();
		g_pTextureHighScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffHighScore != NULL)
	{
		g_pVtxBuffHighScore->Release();
		g_pVtxBuffHighScore = NULL;
	}
}

//========================================================
//			ハイスコアの更新処理
//========================================================
void UpdateHighScore(void)
{
}

//========================================================
//			ハイスコアの描画処理
//========================================================
void DrawHighScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTimer;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffHighScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntTimer = 0; nCntTimer < NUM_TIMER; nCntTimer++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureHighScore);

		//ポリゴンの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,									//プリミティブの種類
			4 * nCntTimer,
			2);														//プリミティブの数	
	}
}

//========================================================
//			ハイスコアの設定処理
//========================================================
void SetHighScore()
{
	VERTEX_2D *pVtx;
	float aPosTexU[NUM_TIMER];										//各桁の数値を格納
	int nCntTimer;

	aPosTexU[0] = ((g_nHighScore % 1000) / 100) * 0.1f;
	aPosTexU[1] = ((g_nHighScore % 100) / 10) * 0.1f;
	aPosTexU[2] = (g_nHighScore % 10) * 0.1f;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffHighScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTimer = 0; nCntTimer < NUM_TIMER; nCntTimer++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f + aPosTexU[nCntTimer], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aPosTexU[nCntTimer], 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aPosTexU[nCntTimer], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aPosTexU[nCntTimer], 1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		pVtx += 4;
	}

	//頂点座標をアンロック
	g_pVtxBuffHighScore->Unlock();
}

//========================================================
//			ハイスコアの読み込み
//========================================================
void LoadHighScore(void)
{
	FILE *fp;

	//ファイルを開く
	fp = fopen("highscore.txt", "r");

	if (fp != NULL)
	{//成功
		//ファイル読み込み
		fscanf(fp, "%d", &g_nHighScore);
	
		//ファイルを閉じる
		fclose(fp);
	}
	else
	{//失敗
	}
}

//========================================================
//			ハイスコアのセーブ
//========================================================
void SaveHighScore(int nScore)
{
	FILE *fp;

	//ハイスコア読み込み
	LoadHighScore();

	if (nScore <= g_nHighScore || g_nHighScore == 0)
	{
		g_nHighScore = nScore;

		//ファイルを開く
		fp = fopen("highscore.txt", "w");

		if (fp != NULL)
		{//成功
		 //ファイル書き出しみ
			fprintf(fp, "%d", g_nHighScore);

			//ファイルを閉じる
			fclose(fp);
		}
		else
		{//失敗
		}
	}
}