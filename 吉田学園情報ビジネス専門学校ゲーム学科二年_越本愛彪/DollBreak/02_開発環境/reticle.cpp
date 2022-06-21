//========================================================
//
//	レティクルの処理[reticle.cpp]
//	AUTHOR:越本愛彪
//
//========================================================
#include "main.h"
#include "game.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureReticle = NULL;						//レティクルのテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffReticle = NULL;					//レティクルの頂点情報へのポインタ
D3DXVECTOR3 g_posReticle;											//レティクルの位置

//========================================================
//			レティクルの初期化処理
//========================================================
void InitReticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/reticle.png", &g_pTextureReticle);

	//グローバル変数の初期化
	g_posReticle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//位置の初期化

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffReticle,
		NULL);

	VERTEX_2D *pVtx;												//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffReticle->Lock(0, 0, (void**)&pVtx, 0);

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

	//頂点座標をアンロック
	g_pVtxBuffReticle->Unlock();
}

//========================================================
//			レティクルの終了処理
//========================================================
void UninitReticle(void)
{
	//テクスチャの破棄
	if (g_pTextureReticle != NULL)
	{
		g_pTextureReticle->Release();
		g_pTextureReticle = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffReticle != NULL)
	{
		g_pVtxBuffReticle->Release();
		g_pVtxBuffReticle = NULL;
	}
}

//========================================================
//			レティクルの更新処理
//========================================================
void UpdateReticle(void)
{
}

//========================================================
//			レティクルの描画処理
//========================================================
void DrawReticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffReticle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureReticle);

	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,										//プリミティブの種類
		0,
		2);															//プリミティブの数	

	//テクスチャの放棄
	pDevice->SetTexture(0, NULL);
}