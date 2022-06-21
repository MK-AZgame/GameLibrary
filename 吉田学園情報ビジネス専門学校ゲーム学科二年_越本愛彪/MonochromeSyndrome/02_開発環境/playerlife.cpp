//=============================================================================
//
// プレイヤー体力の処理 [playerlife.cpp]
// Author : 越本　愛彪
//
//=============================================================================
#include "main.h"
#include "timer.h"
#include "game.h"
#include "result.h"
#include "player.h"

//マクロ定義
#define NUM_PLAYERLIFE (2)												//プレイヤーライフの桁

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePlayerLife = NULL;							//プレイヤーライフのテクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayerLife = NULL;					//プレイヤーライフの頂点情報のポインタ
D3DXVECTOR3 g_posPlayerLife;											//プレイヤーライフの位置
int g_nPlayerLife;														//プレイヤーライフの値

//=============================================================================
//		プレイヤーライフの初期化処理
//=============================================================================
void InitPlayerLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/playerlife.png", &g_pTexturePlayerLife);

	g_posPlayerLife = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//位置の初期化
	g_nPlayerLife = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLAYERLIFE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPlayerLife, NULL);

	VERTEX_2D *pVtx;													//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayerLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPlayerLife = 0; nCntPlayerLife < NUM_PLAYERLIFE; nCntPlayerLife++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f + (50.0f * nCntPlayerLife), 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f + (50.0f * nCntPlayerLife), 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(.0f + (50.0f * nCntPlayerLife), 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f + (50.0f * nCntPlayerLife), 50.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);

		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点座標をアンロック
	g_pVtxBuffPlayerLife->Unlock();
}

//=============================================================================
//		プレイヤーライフの終了処理
//=============================================================================
void UninitPlayerLife(void)
{
	//テクスチャの破棄
	if (g_pTexturePlayerLife != NULL)
	{
		g_pTexturePlayerLife->Release();
		g_pTexturePlayerLife = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPlayerLife != NULL)
	{
		g_pVtxBuffPlayerLife->Release();
		g_pVtxBuffPlayerLife = NULL;
	}
}

//=============================================================================
//		プレイヤーライフの更新処理
//=============================================================================
void UpdataPlayerLife(void)
{
	
}

//=============================================================================
//		プレイヤーライフの描画処理
//=============================================================================
void DrawPlayerLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	Player *pPlayer = GetPlayer();

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayerLife, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntPlayerLife = 0; nCntPlayerLife < pPlayer->nLife; nCntPlayerLife++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayerLife);

		//ポリゴンの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,									//プリミティブの種類
			4 * nCntPlayerLife,
			2);														//プリミティブの数	
	}
}