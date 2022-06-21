//=============================================================================
//
// ステージ間のフェードの処理 [stageinterval.cpp]
// Author : 越本　愛彪
//
//=============================================================================
#include "stageinterval.h"
#include "player.h"

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStageInterval = NULL;		//ステージ間のフェードの頂点情報のポインタ
INTERVAL g_StageInterval;									//ステージ間のフェードの情報を格納
GAMESTATE g_Nextstage;										//次のステージの情報を格納
D3DXCOLOR g_Interval;										//ステージ間のフェードの透明度

//=============================================================================
//		フェードの初期化処理
//=============================================================================
void InitStageInterval(GAMESTATE Nextstage)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	g_StageInterval = INTERVAL_IN;
	g_Nextstage = Nextstage;
	g_Interval = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffStageInterval, NULL);

	VERTEX_2D *pVtx;												//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffStageInterval->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点座標をアンロック
	g_pVtxBuffStageInterval->Unlock();

	//モード設定
	SetGameState(g_Nextstage);
}

//=============================================================================
//		フェードの終了処理
//=============================================================================
void UninitStageInterval(void)
{
	//頂点バッファの破棄
	if (g_pVtxBuffStageInterval != NULL)
	{
		g_pVtxBuffStageInterval->Release();
		g_pVtxBuffStageInterval = NULL;
	}
}

//=============================================================================
//		フェードの更新処理
//=============================================================================
void UpdataStageInterval(void)
{
	VERTEX_2D *pVtx;												//頂点情報へのポインタ

	if (g_StageInterval != INTERVAL_NONE)
	{
		if (g_StageInterval == INTERVAL_IN)
		{//フェードイン状態
			g_Interval.a -= 0.025f;
			if (g_Interval.a <= 0.0f)
			{
				g_Interval.a = 0.0f;
				g_StageInterval = INTERVAL_NONE;
			}
		}
		else if (g_StageInterval == INTERVAL_OUT)
		{//フェードアウト状態
			g_Interval.a += 0.025f;
			if (g_Interval.a >= 1.0f)
			{
				SetPlayerPos(D3DXVECTOR3(50.0f, 660.0f, 0.0f));
				g_Interval.a = 1.0f;
				g_StageInterval = INTERVAL_IN;

				//モード設定
				SetGameState(g_Nextstage);
			}
		}
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffStageInterval->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_Interval.a);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_Interval.a);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_Interval.a);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_Interval.a);

	//頂点座標をアンロック
	g_pVtxBuffStageInterval->Unlock();
}

//=============================================================================
//		フェードの描画処理
//=============================================================================
void DrawStageInterval(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffStageInterval, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,									//プリミティブの種類
		0,
		2);														//プリミティブの数
}

//=============================================================================
//		フェードの設定処理
//=============================================================================
void SetStageInterval(GAMESTATE Nextstage)
{
	g_StageInterval = INTERVAL_OUT;
	g_Nextstage = Nextstage;
	g_Interval = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//=============================================================================
//		フェードの取得処理
//=============================================================================
INTERVAL GetStageInterval(void)
{
	return g_StageInterval;
}