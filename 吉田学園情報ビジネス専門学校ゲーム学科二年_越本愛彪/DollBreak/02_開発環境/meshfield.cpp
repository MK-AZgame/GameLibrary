//========================================================
//
//	メッシュフィールドの処理[meshfield.cpp]
//	AUTHOR:越本愛彪
//
//========================================================
#include "main.h"
#include "meshfield.h"
#include "input.h"

//マクロ定義
#define MESHFIELD_X_BLOCK		(4)														//X方向のブロック数
#define MESHFIELD_Z_BLOCK	    (4)														//Y方向のブロック数
#define MESHFIELD_VEREX_NUM		((MESHFIELD_X_BLOCK + 1) * (MESHFIELD_Z_BLOCK + 1))		//頂点数
#define MESHFIELD_INDEX_NUM		((MESHFIELD_X_BLOCK + 1) * 2 * MESHFIELD_Z_BLOCK + (MESHFIELD_Z_BLOCK - 1) * ((MESHFIELD_X_BLOCK * MESHFIELD_X_BLOCK) - 2))
																						//インデックス数
#define MESHFIELD_PRIMITIVE_NUM (MESHFIELD_X_BLOCK * MESHFIELD_Z_BLOCK * 2 + (MESHFIELD_Z_BLOCK - 1) * ((MESHFIELD_X_BLOCK * MESHFIELD_X_BLOCK) - 2))
																						//プリミティブ数

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;										//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL;											//メッシュフィールドのテクスチャ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshfield = NULL;										//インデックスバッファへのポインタ
D3DXVECTOR3 g_posMeshfield;																//位置
D3DXVECTOR3 g_rotMeshfield;																//向き
D3DXMATRIX  g_mtxWorldMeshfield;														//ワールドマトリックス
int g_nDebugFlug;																		//画面の表示設定の変更用（F1/F2で切り替え）
int g_nCntVtxNum;																		//pVtxのカウント用

//========================================================
//				メッシュフィールド初期化処理
//========================================================
void InitMeshfield(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/field003.jpg", &g_pTextureMeshfield);

	//グローバル変数の初期化
	g_nDebugFlug = 0;
	g_nCntVtxNum = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHFIELD_VEREX_NUM, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffMeshfield, NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIELD_INDEX_NUM, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIdxBuffMeshfield, NULL);

	VERTEX_3D *pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の各情報の設定
	for (int nCntVtx = 0; nCntVtx < MESHFIELD_Z_BLOCK + 1; nCntVtx++)
	{
		for (int nCntVtxX = 0; nCntVtxX < MESHFIELD_X_BLOCK + 1; nCntVtxX++)
		{
			//頂点位置の設定
			pVtx[g_nCntVtxNum].pos = D3DXVECTOR3(-((MESHFIELD_SIZE * MESHFIELD_X_BLOCK) / 2) + (MESHFIELD_SIZE * nCntVtxX), 0.0f, ((MESHFIELD_SIZE * MESHFIELD_Z_BLOCK) / 2) + (-MESHFIELD_SIZE * nCntVtx));

			//頂点カラーの設定
			pVtx[g_nCntVtxNum].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//各頂点の法線の設定
			pVtx[g_nCntVtxNum].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//テクスチャ座標の設定
			pVtx[g_nCntVtxNum].tex = D3DXVECTOR2(0.0f + (1.0f * nCntVtxX), 0.0f + (1.0f * nCntVtx));

			g_nCntVtxNum++;																//pVtxを一つ分次に進める
		}
	}
	
	//インデックスバッファをロック
	WORD *pIdx;
	g_pIdxBuffMeshfield->Lock(0, 0, (void**)&pIdx, 0);

	//頂点インデックスの設定
	for (int nCntIdxZ = 0; nCntIdxZ < MESHFIELD_Z_BLOCK; nCntIdxZ++)
	{
		for (int nCntIdxX =0; nCntIdxX < MESHFIELD_X_BLOCK + 1; nCntIdxX++)
		{
			pIdx[0] = nCntIdxX + (nCntIdxZ * (MESHFIELD_X_BLOCK + 1)) + (MESHFIELD_X_BLOCK + 1);
			pIdx[1] = nCntIdxX + (nCntIdxZ * (MESHFIELD_X_BLOCK + 1));

			pIdx += 2;																	//pIdxを二個分ずらす
		}

		//縮退ポリゴンの設定
		if (nCntIdxZ < (MESHFIELD_Z_BLOCK - 1))
		{
			pIdx[0] = pIdx[-1];															//ひとつ前のデータの中身を入れる
			pIdx[1] = ((MESHFIELD_X_BLOCK + 1) * (nCntIdxZ + MESHFIELD_X_BLOCK));

			pIdx += 2;																	//pIdxを二個分ずらす
		}
	}

	//インデックスバッファのアンロック
	g_pIdxBuffMeshfield->Unlock();
	
	//頂点バッファのアンロック
	g_pVtxBuffMeshfield->Unlock();
}

//========================================================
//				メッシュフィールド終了処理
//========================================================
void UninitMeshfield(void)
{
	//テクスチャの破棄
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

	//インデックスバッファ解放
	if (g_pIdxBuffMeshfield != NULL)
	{
		g_pIdxBuffMeshfield->Release();
		g_pIdxBuffMeshfield = NULL;
	}
}

//========================================================
//				メッシュフィールド更新処理
//========================================================
void UpdateMeshfield(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//画面表示の設定の変更
	if (GetKeyboardTrigger(DIK_F1))
	{//F1キー押下で切り替え
		if (g_nDebugFlug == 0)
		{
			g_nDebugFlug = 1;
		}
		else if (g_nDebugFlug == 1)
		{
			g_nDebugFlug = 0;
		}
	}

	if (g_nDebugFlug == 1)
	{//ワイヤーフレーム表示
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else if (g_nDebugFlug == 0)
	{//通常の表示
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}

//========================================================
//				メッシュフィールド描画処理
//========================================================
void DrawMeshfield(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshfield);

	//向きを反転
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshfield.y, g_rotMeshfield.x, g_rotMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshfield.x, g_posMeshfield.y, g_posMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshfield);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshfield);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshfield);

	//メッシュフィールドの描画
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,															//プリミティブの種類
		0,																				//描画する最初のインデックス
		0,																				//インデックス最小値
		MESHFIELD_VEREX_NUM,															//頂点の数
		0,																				//インデックスの最初の数
		MESHFIELD_INDEX_NUM);															//プリミティブ(ポリゴン)数

	pDevice->SetTexture(0, NULL);
}