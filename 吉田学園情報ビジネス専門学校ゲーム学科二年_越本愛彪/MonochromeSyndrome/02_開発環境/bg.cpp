//=============================================================================
//
// 背景の処理 [bg.cpp]
// Author : 越本　愛彪
//
//=============================================================================
#include "main.h"
#include "Bg.h"
#include "player.h"

//マクロ定義
#define NUM_BG (2)								//背景のテクスチャ数

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBg[NUM_BG] = {};	//背景テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg = NULL;	//頂点バッファのポインタ
float g_PosTexX;								//背景座標の中開始位置(X)
float g_PosTexY;								//背景座標の中開始位置(Y)

//=============================================================================
//			背景の初期化処理
//=============================================================================
void InitBg(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	g_PosTexX = 0;
	g_PosTexY = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBg, NULL);

	VERTEX_2D *pVtx;							//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].tex = D3DXVECTOR2(g_PosTexX, g_PosTexY);
	pVtx[1].tex = D3DXVECTOR2(g_PosTexX + 0.01f, g_PosTexY);
	pVtx[2].tex = D3DXVECTOR2(g_PosTexX, g_PosTexY + 0.01f);
	pVtx[3].tex = D3DXVECTOR2(g_PosTexX + 0.01f, g_PosTexY + 0.01f);

	pVtx += 4;

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1340.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1340.0f, 720.0f, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

	//頂点座標をアンロック
	g_pVtxBuffBg->Unlock();
}

//=============================================================================
//			背景の終了処理
//=============================================================================
void UninitBg(void)
{
	for (int nCntBg = 0; nCntBg < NUM_BG; nCntBg++)
	{
		//テクスチャの破棄
		if (g_pTextureBg[nCntBg] != NULL)
		{
			g_pTextureBg[nCntBg]->Release();
			g_pTextureBg[nCntBg] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBg != NULL)
	{
		g_pVtxBuffBg->Release();
		g_pVtxBuffBg = NULL;
	}
}

//=============================================================================
//			背景の更新処理
//=============================================================================
void UpdataBg(void)
{
	VERTEX_2D *pVtx;

	g_PosTexX += 0.00001f;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(g_PosTexX, g_PosTexY);
	pVtx[1].tex = D3DXVECTOR2(g_PosTexX + 0.3f, g_PosTexY);
	pVtx[2].tex = D3DXVECTOR2(g_PosTexX, g_PosTexY + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_PosTexX + 0.3f, g_PosTexY + 1.0f);

	//頂点座標をアンロック
	g_pVtxBuffBg->Unlock();
}

//=============================================================================
//			背景の描画処理
//=============================================================================
void DrawBg(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBg, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBg = 0; nCntBg < NUM_BG; nCntBg++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBg[nCntBg]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			//プリミティブの種類
			4 * nCntBg,
			2);								//プリミティブの数		
	}
}