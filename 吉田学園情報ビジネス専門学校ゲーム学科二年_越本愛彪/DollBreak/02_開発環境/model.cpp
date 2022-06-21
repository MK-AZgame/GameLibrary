//========================================================
//
//	モデルの処理[model.cpp]
//	AUTHOR:越本愛彪
//
//========================================================
#include "main.h"
#include "model.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "line.h"
#include "loadfileh.h"

//グローバル変数
MODEL g_model[MAX_MODEL];										//モデルの構造体情報を格納
ModelInfo g_modelInfo[MAX_MODELTYPE];							//モデル情報の構造体を格納

//========================================================
//					モデル初期化処理
//========================================================
void InitModel(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ファイルの読み込み
	LoadModelFile("data/model.txt",&g_modelInfo[0]);

	//位置・向きの初期化
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		g_model[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置の初期化
		g_model[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向きの初期化
		g_model[nCntModel].bUse = false;						//使用されていない状態にする
	}

	int nNumVtx;												//モデルの頂点数の保存用
	DWORD sizeFVF;												//頂点フォーマットのサイズ
	BYTE *pVtxBuff;												//頂点バッファへのポインタ

	//頂点数の取得
	for (int nCntType = 0; nCntType < MAX_MODELTYPE; nCntType++)
	{
		nNumVtx = g_modelInfo[nCntType].pMeshModel->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_modelInfo[nCntType].pMeshModel->GetFVF());

		//頂点バッファのロック
		g_modelInfo[nCntType].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			////頂点座標を比較してモデルの最大・最小値を取得
			//最小値
			if (vtx.x <= g_modelInfo[nCntType].vtxMin.x)
			{
				g_modelInfo[nCntType].vtxMin.x = vtx.x;
			}

			if (vtx.y <= g_modelInfo[nCntType].vtxMin.y)
			{
				g_modelInfo[nCntType].vtxMin.y = vtx.y;
			}

			if (vtx.z <= g_modelInfo[nCntType].vtxMin.z)
			{
				g_modelInfo[nCntType].vtxMin.z = vtx.z;
			}

			//最大値
			if (vtx.x >= g_modelInfo[nCntType].vtxMax.x)
			{
				g_modelInfo[nCntType].vtxMax.x = vtx.x;
			}

			if (vtx.y >= g_modelInfo[nCntType].vtxMax.y)
			{
				g_modelInfo[nCntType].vtxMax.y = vtx.y;
			}

			if (vtx.z >= g_modelInfo[nCntType].vtxMax.z)
			{
				g_modelInfo[nCntType].vtxMax.z = vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}

		//頂点バッファをアンロック
		g_modelInfo[nCntType].pMeshModel->UnlockVertexBuffer();
	}

	//モデルをセット
	SetModel(D3DXVECTOR3(75.0f, 0.0f, -75.0f));
	SetModel(D3DXVECTOR3(-75.0f, 0.0f, -75.0f));
	SetModel(D3DXVECTOR3(75.0f, 0.0f, 75.0f));
	SetModel(D3DXVECTOR3(-75.0f, 0.0f, 75.0f));
}

//========================================================
//					モデル終了処理
//========================================================
void UninitModel(void)
{
	//メッシュの破棄
	for (int nCntMeshType = 0; nCntMeshType < MAX_MODELTYPE; nCntMeshType++)
	{
		if (g_modelInfo[nCntMeshType].pMeshModel != NULL)
		{
			g_modelInfo[nCntMeshType].pMeshModel->Release();
			g_modelInfo[nCntMeshType].pMeshModel = NULL;
		}
	}

	//マテリアルの破棄
	for (int nCntMatType = 0; nCntMatType < MAX_MODELTYPE; nCntMatType++)
	{
		if (g_modelInfo[nCntMatType].pBuffMatModel != NULL)
		{
			g_modelInfo[nCntMatType].pBuffMatModel->Release();
			g_modelInfo[nCntMatType].pBuffMatModel = NULL;
		}
	}
}

//========================================================
//					モデル更新処理
//========================================================
void UpdateModel(void)
{
	//if (GetKeyboardTrigger(DIK_F7))
	//{
	//	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	//	{
	//		if (g_model[nCntModel].bUse == true)
	//		{
	//			SetLine(g_model[nCntModel].pos, g_model.rot, D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMin.y, g_model.vtxMin.z), D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMin.y, g_model.vtxMax.z));
	//			SetLine(g_model[nCntModel].pos, g_model.rot, D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMin.y, g_model.vtxMin.z), D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMin.y, g_model.vtxMin.z));
	//			SetLine(g_model[nCntModel].pos, g_model.rot, D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMin.y, g_model.vtxMin.z), D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMin.y, g_model.vtxMax.z));
	//			SetLine(g_model[nCntModel].pos, g_model.rot, D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMin.y, g_model.vtxMax.z), D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMin.y, g_model.vtxMax.z));
	//			SetLine(g_model.pos, g_model.rot, D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMin.y, g_model.vtxMin.z), D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMax.y, g_model.vtxMin.z));
	//			SetLine(g_model.pos, g_model.rot, D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMin.y, g_model.vtxMin.z), D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMax.y, g_model.vtxMin.z));
	//			SetLine(g_model.pos, g_model.rot, D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMin.y, g_model.vtxMax.z), D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMax.y, g_model.vtxMax.z));
	//			SetLine(g_model.pos, g_model.rot, D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMin.y, g_model.vtxMax.z), D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMax.y, g_model.vtxMax.z));
	//		}
	//	}
	//}
}

//========================================================
//					モデル描画処理
//========================================================
void DrawModel(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	//現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_model[nCntModel].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_model[nCntModel].mtxWorld);

			//向きを反転
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_model[nCntModel].rot.y, g_model[nCntModel].rot.x, g_model[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_model[nCntModel].mtxWorld, &g_model[nCntModel].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_model[nCntModel].pos.x, g_model[nCntModel].pos.y, g_model[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_model[nCntModel].mtxWorld, &g_model[nCntModel].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_model[nCntModel].mtxWorld);

			//マテリアルデータのポインタを取得
			pMat = (D3DXMATERIAL*)g_modelInfo[g_model[nCntModel].nType].pBuffMatModel->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)g_modelInfo[g_model[nCntModel].nType].nNumMatModel; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//モデルパーツの描画
				g_modelInfo[g_model[nCntModel].nType].pMeshModel->DrawSubset(nCntMat);
			}
		}
	}

	//保持していたマテリアルを返す
	pDevice->SetMaterial(&matDef);
}

//========================================================
//				モデルの設定処理
//========================================================
void SetModel(D3DXVECTOR3 pos)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_model[nCntModel].bUse == false)
		{//bUseがfalseの時だけ
			g_model[nCntModel].pos = pos;						//位置を設定

			g_model[nCntModel].bUse = true;						//使用されている状態にする

			break;
		}
	}
}

//========================================================
//				モデルのサイズの最大値を取得する
//========================================================
D3DXVECTOR3 GetVtxMax(int nType)
{
	return g_modelInfo[nType].vtxMax;
}

//========================================================
//				モデルのサイズの最小値を取得する
//========================================================
D3DXVECTOR3 GetVtxMin(int nType)
{
	return g_modelInfo[nType].vtxMin;
}

//========================================================
//				モデルの情報を取得する
//========================================================
MODEL *GetModel(void)
{
	return &g_model[0];
}
