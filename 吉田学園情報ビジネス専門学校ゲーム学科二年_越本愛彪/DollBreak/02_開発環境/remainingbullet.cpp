//========================================================
//
//	残弾数の処理[remainingbullet.cpp]
//	AUTHOR:越本愛彪
//
//========================================================
#include "main.h"
#include "bullet.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "enemy.h"

//マクロ定義
#define NUM_REMAIN (2)												//残弾数の桁

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureRemain = NULL;							//残弾数のテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRemain = NULL;					//残弾数の頂点情報へのポインタ
D3DXVECTOR3 g_posRemain;											//残弾数の位置

//========================================================
//			残弾数の初期化処理
//========================================================
void InitRemain(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/number000.png", &g_pTextureRemain);

	//グローバル変数の初期化
	g_posRemain = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//位置の初期化

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_REMAIN,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRemain,
		NULL);

	VERTEX_2D *pVtx;											//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRemain->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRemain = 0; nCntRemain < NUM_REMAIN; nCntRemain++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f + (50.0f * nCntRemain), 660.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f + (50.0f * nCntRemain), 660.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f + (50.0f * nCntRemain), 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f + (50.0f * nCntRemain), 720.0f, 0.0f);

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
	g_pVtxBuffRemain->Unlock();
}

//========================================================
//			残弾数の終了処理
//========================================================
void UninitRemain(void)
{
	//テクスチャの破棄
	if (g_pTextureRemain != NULL)
	{
		g_pTextureRemain->Release();
		g_pTextureRemain = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRemain != NULL)
	{
		g_pVtxBuffRemain->Release();
		g_pVtxBuffRemain = NULL;
	}
}

//========================================================
//			残弾数の更新処理
//========================================================
void UpdateRemain(void)
{

}

//========================================================
//			残弾数の描画処理
//========================================================
void DrawRemain(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRemain, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntRemain = 0; nCntRemain < NUM_REMAIN; nCntRemain++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRemain);

		//ポリゴンの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,								//プリミティブの種類
			4 * nCntRemain,
			2);													//プリミティブの数	
	}
}

//========================================================
//			残弾数の設定処理
//========================================================
void SetRemain()
{
	VERTEX_2D *pVtx;
	float aPosTexU[NUM_REMAIN];									//各桁の数値を格納
	int remainingBullet = GetBullet();							//弾の情報を取得

	aPosTexU[0] = ((remainingBullet % 100) / 10) * 0.1f;
	aPosTexU[1] = (remainingBullet % 10) * 0.1f;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRemain->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRemain = 0; nCntRemain < NUM_REMAIN; nCntRemain++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f + aPosTexU[nCntRemain], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aPosTexU[nCntRemain], 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aPosTexU[nCntRemain], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aPosTexU[nCntRemain], 1.0f);

		pVtx += 4;
	}

	//頂点座標をアンロック
	g_pVtxBuffRemain->Unlock();
}