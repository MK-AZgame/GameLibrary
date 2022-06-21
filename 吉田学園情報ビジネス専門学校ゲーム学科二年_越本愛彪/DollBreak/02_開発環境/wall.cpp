//========================================================
//
//	壁の処理[wall.cpp]
//	AUTHOR:越本愛彪
//
//========================================================
#include "main.h"
#include "wall.h"
#include "meshfield.h"

//マクロ定義
#define MAX_WALL (4)									//壁の最大数
#define WALL_HEIGHT (100.0f)							//壁の高さ

//構造体
typedef struct
{
	D3DXVECTOR3 pos;									//位置
	D3DXVECTOR3 rot;									//向き
	D3DXMATRIX  mtxWorld;								//ワールドマトリックス
	bool bUse;
} Wall;

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;			//壁の頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;				//テクスチャのポインタ
Wall g_Wall[MAX_WALL];									//壁の情報を格納

//========================================================
//					壁初期化処理
//========================================================
void InitWall(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/block000.jpg", &g_pTextureWall);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_Wall[nCntWall].bUse = false;
		g_Wall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY, 
		FVF_VERTEX_3D, D3DPOOL_MANAGED,
		&g_pVtxBuffWall, NULL);

	VERTEX_3D *pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	//頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(-MESHFIELD_SIZE * 2, WALL_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(MESHFIELD_SIZE * 2, WALL_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-MESHFIELD_SIZE * 2, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(MESHFIELD_SIZE * 2, 0.0f, 0.0f);

	//各頂点の法線の設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	g_pVtxBuffWall->Unlock();

	//壁の設定
	SetWall(D3DXVECTOR3(-MESHFIELD_SIZE * 2, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -MESHFIELD_SIZE * 2), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetWall(D3DXVECTOR3(MESHFIELD_SIZE * 2, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetWall(D3DXVECTOR3(0.0f, 0.0f, MESHFIELD_SIZE * 2), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//========================================================
//					壁終了処理
//========================================================
void UninitWall(void)
{
	//テクスチャの破棄
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//========================================================
//					壁更新処理
//========================================================
void UpdataWall(void)
{

}

//========================================================
//					壁描画処理
//========================================================
void DrawWall(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureWall);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Wall[nCntWall].mtxWorld);

			//向きを反転
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[nCntWall].rot.y, g_Wall[nCntWall].rot.x, g_Wall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorld, &g_Wall[nCntWall].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Wall[nCntWall].pos.x, g_Wall[nCntWall].pos.y, g_Wall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorld, &g_Wall[nCntWall].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Wall[nCntWall].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//壁の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}

	pDevice->SetTexture(0, NULL);
}

//========================================================
//					壁設定処理
//========================================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == false)
		{
			g_Wall[nCntWall].pos = pos;
			g_Wall[nCntWall].rot = rot;

			g_Wall[nCntWall].bUse = true;
			break;
		}
	}
}