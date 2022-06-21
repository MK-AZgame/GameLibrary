//========================================================
//
//	デバッグラインの処理[line.cpp]
//	AUTHOR:越本愛彪
//
//========================================================
#include "line.h"
#include "model.h"

//マクロ定義
#define MAX_LINE (12 * MAX_MODEL)				//ラインの最大数

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLine = NULL;	//ラインの頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureLine = NULL;		//ラインのテクスチャへのポインタ
Line g_aLine[MAX_LINE];							//ラインの情報の格納

//========================================================
//					ライン初期化処理
//========================================================
void InitLine(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2 * MAX_LINE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLine,
		NULL);

	VERTEX_3D *pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		//頂点情報の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//各頂点の法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//テクスチャ
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 2;
	}

	//頂点バッファのアンロック
	g_pVtxBuffLine->Unlock();
}

//========================================================
//					ライン終了処理
//========================================================
void UninitLine(void)
{
	//テクスチャの解放
	if (g_pTextureLine != NULL)
	{
		g_pTextureLine->Release();
		g_pTextureLine = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffLine != NULL)
	{
		g_pVtxBuffLine->Release();
		g_pVtxBuffLine = NULL;
	}
}

//========================================================
//					ライン更新処理
//========================================================
void UpdateLine(void)
{

}

//========================================================
//					ライン描画処理
//========================================================
void DrawLine(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureLine);

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		if (g_aLine[nCntLine].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aLine[nCntLine].mtxWorld);

			//向きを反転
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aLine[nCntLine].rot.y, g_aLine[nCntLine].rot.x, g_aLine[nCntLine].rot.z);
			D3DXMatrixMultiply(&g_aLine[nCntLine].mtxWorld, &g_aLine[nCntLine].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aLine[nCntLine].pos.x, g_aLine[nCntLine].pos.y, g_aLine[nCntLine].pos.z);
			D3DXMatrixMultiply(&g_aLine[nCntLine].mtxWorld, &g_aLine[nCntLine].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aLine[nCntLine].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffLine, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//ラインの描画
			pDevice->DrawPrimitive(D3DPT_LINELIST, 2 * nCntLine, 1);
		}
	}

	//カメラを有効に戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetTexture(0, NULL);
}

//========================================================
//					ラインの設定処理
//========================================================
void SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 startPos, D3DXVECTOR3 endPos)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		if (g_aLine[nCntLine].bUse == false)
		{
			g_aLine[nCntLine].pos = pos;		//構造体のpos情報に引数を代入
			g_aLine[nCntLine].rot = rot;		//構造体のrot情報に引数を代入

			//頂点座標の設定
			pVtx[0].pos = startPos;				//ラインの始点
			pVtx[1].pos = endPos;				//ラインの終点

			g_aLine[nCntLine].bUse = true;		//ラインのbUseをtrueに
			break;
		}
		pVtx += 2;
	}

	//頂点バッファのアンロック
	g_pVtxBuffLine->Unlock();
}