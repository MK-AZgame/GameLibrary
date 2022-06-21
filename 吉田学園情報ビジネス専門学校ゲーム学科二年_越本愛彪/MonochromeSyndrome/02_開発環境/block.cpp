//=============================================================================
//
//	ブロック生成の処理[block.cpp]
//	Author：越本愛彪
//
//=============================================================================
#include <stdio.h>
#include "main.h"
#include "input.h"
#include "player.h"
#include "block.h"
#include "goal.h"
#include "sound.h"

//マクロ定義
#define MAX_BLOCK_WIDTH (30)								//ブロックのX方向の最大数
#define MAX_BLOCK_HEIGHT (20)								//ブロックのT方向の最大数
#define MAX_BLOCK  (MAX_BLOCK_WIDTH * MAX_BLOCK_HEIGHT)		//ブロックの最大数
#define BLOCK_SIZE (SCREEN_HEIGHT / MAX_BLOCK_HEIGHT)		//ブロックのサイズ

//ブロック構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;										//位置
	D3DXVECTOR3 posOld;										//前回の位置
	D3DXVECTOR3 move;										//移動量
	float fWidth;											//幅
	float fHeight;											//高さ
	BLOCK_TYPE Type;										//種類
	bool bUse;												//使用しているかどうか
}BLOCK;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureblock = NULL;					//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffblock = NULL;				//頂点バッファへのポインタ
BLOCK g_aBlock[MAX_BLOCK];									//ブロックの情報
int g_nBlock[MAX_BLOCK_HEIGHT][MAX_BLOCK_WIDTH];			//ブロックの配置情報

//=============================================================================
//		ブロックの初期化処理
//=============================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	
	//デバイスの取得
	pDevice = GetDevice();

	//ブロックの情報の初期化
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期化
		g_aBlock[nCntBlock].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//前回の位置の初期化
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量の初期化
		g_aBlock[nCntBlock].fWidth = 0.0f;								//ブロックの横幅の初期化						
		g_aBlock[nCntBlock].fHeight = 0.0f;								//ブロックの高さの初期化
		g_aBlock[nCntBlock].Type = BLOCK_NONE;							//ブロックの種類の初期化
		g_aBlock[nCntBlock].bUse = false;								//ブロックを使っていない状態にする
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffblock, NULL);

	VERTEX_2D *pVtx;													//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffblock->Lock(0, 0, (void**)&pVtx, 0);

	//MAX_BLOCK分ブロックの情報を初期化
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - BLOCK_SIZE / 2, g_aBlock[nCntBlock].pos.y - BLOCK_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + BLOCK_SIZE / 2, g_aBlock[nCntBlock].pos.y - BLOCK_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - BLOCK_SIZE / 2, g_aBlock[nCntBlock].pos.y + BLOCK_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + BLOCK_SIZE / 2, g_aBlock[nCntBlock].pos.y + BLOCK_SIZE, 0.0f);

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

		pVtx += 4;
	}

	//頂点座標をアンロッ
	g_pVtxBuffblock->Unlock();
}

//=============================================================================
//		ブロックの終了処理
//=============================================================================
void UninitBlock(void)
{
	//テクスチャの破棄
	if (g_pTextureblock != NULL)
	{
		g_pTextureblock->Release();
		g_pTextureblock = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffblock != NULL)
	{
		g_pVtxBuffblock->Release();
		g_pVtxBuffblock = NULL;
	}
}

//=============================================================================
//		ブロックの更新処理
//=============================================================================
void UpdataBlock(void)
{
	VERTEX_2D *pVtx;
	Player *pPlayer = GetPlayer();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffblock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//使用されている場合
			if (pPlayer->pos.x >= SCREEN_WIDTH / 2)
			{
				ScrollBlock(D3DXVECTOR3(pPlayer->move.x, 0.0f, 0.0f),nCntBlock);
			}

			if (g_aBlock[nCntBlock].Type == BLOCK_MOVE)
			{//BLOCK_TYPE が BLOCK_MOVEの時
				//posOld に pos を保存
				g_aBlock[nCntBlock].posOld = g_aBlock[nCntBlock].pos;

				//移動量を更新
				g_aBlock[nCntBlock].pos += g_aBlock[nCntBlock].move;

				//当たり判定
				CollisionPlayer(&g_aBlock[nCntBlock].pos, &g_aBlock[nCntBlock].posOld, &g_aBlock[nCntBlock].move, 
					g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].fHeight);

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2, g_aBlock[nCntBlock].pos.y - BLOCK_SIZE / 2, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2, g_aBlock[nCntBlock].pos.y - BLOCK_SIZE / 2, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2, g_aBlock[nCntBlock].pos.y + BLOCK_SIZE / 2, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2, g_aBlock[nCntBlock].pos.y + BLOCK_SIZE / 2, 0.0f);

				//ブロックのループ
				if (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight / 2 <= 0.0f)
				{//画面上部に到達時
					g_aBlock[nCntBlock].pos.y = SCREEN_HEIGHT + g_aBlock[nCntBlock].fHeight / 2;
				}
				else if (g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight / 2 >= SCREEN_HEIGHT)
				{//画面下部に到達時
					g_aBlock[nCntBlock].pos.y = 0.0f - g_aBlock[nCntBlock].fHeight / 2;
				}
			}
		}
		pVtx += 4;
	}
	//頂点座標をアンロック
	g_pVtxBuffblock->Unlock();
}

//=============================================================================
//		ブロックの描画処理
//=============================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffblock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureblock);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//bUseがtrueの時
			//ポリゴンの描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,				//プリミティブの種類
				4 * nCntBlock,
				2);									//プリミティブの数	
		}
	}
}

//=============================================================================
//		ブロックの設定処理
//=============================================================================
void SetBlock(D3DXVECTOR3 pos,float fWidth, D3DXVECTOR3 move,BLOCK_TYPE block)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffblock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{
			//ブロックの各情報の設定
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].move = move;
			g_aBlock[nCntBlock].fHeight = BLOCK_SIZE;
			g_aBlock[nCntBlock].fWidth = fWidth;
			g_aBlock[nCntBlock].Type = block;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - fWidth / 2, g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth / 2, g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - fWidth / 2, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth / 2, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight / 2, 0.0f);

			if (g_aBlock[nCntBlock].Type == BLOCK_NORMAL)
			{//通常のブロックの色設定
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			}

			//テクスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(fWidth / (BLOCK_SIZE / 2), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(fWidth / (BLOCK_SIZE / 2), 1.0f);

			//使用している状態に変更
			g_aBlock[nCntBlock].bUse = true;
			break;
		}
		pVtx += 4;
	}

	//頂点座標をアンロック
	g_pVtxBuffblock->Unlock();
}

//=============================================================================
//		ブロックの当たり判定
//=============================================================================
bool ColisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
{
	bool bIsLanding = false;											//着地しているかどうか

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//使用されているとき
				//ブロックとプレイヤーの当たり判定
				//上から下
			if (pPosOld->y <= g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight / 2 &&
				pPos->y >= g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight / 2 &&
				pPos->x + fWidth / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2 &&
				pPos->x - fWidth / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2)
			{
				bIsLanding = true;									//着地している状態にする
				pPos->y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight / 2;
				pMove->y = 0;
				if (g_aBlock[nCntBlock].Type == BLOCK_MOVE)
				{//動くブロックの移動量の更新
					pPos->x += g_aBlock[nCntBlock].move.x;
					pPos->y += g_aBlock[nCntBlock].move.y;
				}
			}
			if (pPosOld->y - fHeight >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight / 2 &&
				pPos->y - fHeight < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight / 2 &&
				pPos->x + fWidth / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2 &&
				pPos->x - fWidth / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2)
			{//下から上
				pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight / 2 + fHeight;
				pMove->y = 1;
			}

			if (pPosOld->y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight / 2 &&
				pPosOld->y - fHeight < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight / 2)
			{
				//左から右
				if (pPosOld->x + fWidth / 2 <= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2 &&
					pPos->x + fWidth / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2)
				{
					pPos->x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2 - fWidth / 2;
					pMove->x = 0;
				}

				//右から左
				if (pPosOld->x - fWidth / 2 >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2 &&
					pPos->x - fWidth / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2)
				{
					pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2 + fWidth / 2;
					pMove->x = 0;
				}
			}
		}
	}
	return bIsLanding;
}

//=============================================================================
//		ブロックのスクロール処理
//=============================================================================
void ScrollBlock(D3DXVECTOR3 move,int nCntBlock)
{
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffblock->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aBlock[nCntBlock].bUse == true)
	{
		g_aBlock[nCntBlock].pos -= move;
	}

	pVtx += 4 * nCntBlock;

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2, g_aBlock[nCntBlock].pos.y - BLOCK_SIZE / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2, g_aBlock[nCntBlock].pos.y - BLOCK_SIZE / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2, g_aBlock[nCntBlock].pos.y + BLOCK_SIZE / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2, g_aBlock[nCntBlock].pos.y + BLOCK_SIZE / 2, 0.0f);

	//アンロック
	g_pVtxBuffblock->Unlock();
}

//=============================================================================
//		ファイルの読み込み
//=============================================================================
void ScanFile(char *pfilename)
{
	FILE *fp;															//ファイルポインタ

	//ファイルを開く
	fp = fopen(pfilename, "r");

	if (fp != NULL)
	{//成功
		for (int nCntBlockHeight = 0; nCntBlockHeight < MAX_BLOCK_HEIGHT; nCntBlockHeight++)
		{
			for (int nCntBlockWidth = 0; nCntBlockWidth < MAX_BLOCK_WIDTH; nCntBlockWidth++)
			{//ファイル読み込み
				fscanf(fp, "%d", &g_nBlock[nCntBlockHeight][nCntBlockWidth]);
			}
		}
		//ファイルを閉じる
		fclose(fp);
	}
	else
	{//失敗
	}

	//各種ブロックごとにマップを生成
	for (int nCntBlockHeight = 0; nCntBlockHeight < MAX_BLOCK_HEIGHT; nCntBlockHeight++)
	{
		for (int nCntBlockWidth = 0; nCntBlockWidth < MAX_BLOCK_WIDTH; nCntBlockWidth++)
		{
			if (g_nBlock[nCntBlockHeight][nCntBlockWidth] == 1)
			{//通常ブロックの生成
				SetBlock(D3DXVECTOR3(nCntBlockWidth * BLOCK_SIZE + (BLOCK_SIZE / 2.0f), nCntBlockHeight * BLOCK_SIZE + (BLOCK_SIZE / 2.0f), 0.0f), BLOCK_SIZE, D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_NORMAL);
			}
			else if (g_nBlock[nCntBlockHeight][nCntBlockWidth] == 2)
			{//動くブロック(上移動)の生成
				SetBlock(D3DXVECTOR3(nCntBlockWidth * BLOCK_SIZE + (BLOCK_SIZE / 2.0f), nCntBlockHeight * BLOCK_SIZE + (BLOCK_SIZE / 2.0f), 0.0f), BLOCK_SIZE, D3DXVECTOR3(0.0f, -1.0f, 0.0f), BLOCK_MOVE);
			}
			else if (g_nBlock[nCntBlockHeight][nCntBlockWidth] == 3)
			{//動くブロック(下移動)の生成
				SetBlock(D3DXVECTOR3(nCntBlockWidth * BLOCK_SIZE + (BLOCK_SIZE / 2.0f), nCntBlockHeight * BLOCK_SIZE + (BLOCK_SIZE / 2.0f), 0.0f), BLOCK_SIZE, D3DXVECTOR3(0.0f, 1.0f, 0.0f), BLOCK_MOVE);
			}
			else if (g_nBlock[nCntBlockHeight][nCntBlockWidth] == 99)
			{//ゴールの生成

			}
		}
	}
}