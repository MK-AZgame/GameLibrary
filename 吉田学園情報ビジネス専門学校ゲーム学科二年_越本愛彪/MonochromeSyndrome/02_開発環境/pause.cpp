//=============================================================================
//
// ポーズの処理 [pause.cpp]
// Author : 越本　愛彪
//
//=============================================================================
#include "main.h"
#include "pause.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "sound.h"

//マクロ定義	
#define MAX_TEX (4)

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePause[MAX_TEX] = {};				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;					//頂点バッファへのポインタ
int g_nFlug;

//=============================================================================
//		ポーズの初期化処理
//=============================================================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/pause100.png", &g_pTexturePause[0]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/pause000.png", &g_pTexturePause[1]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/pause001.png", &g_pTexturePause[2]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/pause002.png", &g_pTexturePause[3]);

	g_nFlug = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPause, NULL);

	VERTEX_2D *pVtx;											//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(200.0f, 100.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1080.0f, 100.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(200.0f, 620.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1080.0f, 620.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//[CONTINUE]
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(300.0f, 150.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(980.0f, 150.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(300.0f, 270.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(980.0f, 270.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//[RETRY]
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(980.0f, 300.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(300.0f, 420.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(980.0f, 420.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;
	//[QUIT]
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(300.0f, 450.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(980.0f, 450.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(300.0f, 570.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(980.0f, 570.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点座標をアンロック
	g_pVtxBuffPause->Unlock();
}

//=============================================================================
//		ポーズの終了処理
//=============================================================================
void UninitPause(void)
{
	//テクスチャの破棄
	for (int nCount = 0; nCount < MAX_TEX; nCount++)
	{
		if (g_pTexturePause[nCount] != NULL)
		{
			g_pTexturePause[nCount]->Release();
			g_pTexturePause[nCount] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//=============================================================================
//		ポーズの更新処理
//=============================================================================
void UpdataPause(void)
{
	VERTEX_2D *pVtx;
	GAMESTATE gamestate = *GetGameState();
	PAUSE *pause = GetPause();
	FADE fade = GetFade();

	//選択肢の移動
	if (pause->bDisp == true)
	{
		if (GetKeyboardTrigger(DIK_S) || GetJoypadTrigger(JOYKEY_DOWN) == true)
		{
			g_nFlug++;
			if (g_nFlug >= 2)
			{
				g_nFlug = 2;
			}
		}
		else if (GetKeyboardTrigger(DIK_W) || GetJoypadTrigger(JOYKEY_UP) == true)
		{
			g_nFlug--;
			if (g_nFlug <= 0)
			{
				g_nFlug = 0;
			}
		}

		//選択
		if (fade == FADE_NONE)
		{
			if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) == true)
			{
				PlaySound(SOUND_LABEL_SE001);

				if (g_nFlug == 0)
				{
					pause->bDisp = false;
				}
				else if (g_nFlug == 1)
				{
					SetFade(MODE_GAME);
				}
				else if (g_nFlug == 2)
				{
					SetFade(MODE_TITLE);
				}
			}
		}
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//選択されている場所の色変更
	for (int nCount = 0; nCount < 3; nCount++)
	{
		pVtx += 4;
		if (nCount == g_nFlug)
		{
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		}
	}

	//頂点座標をアンロック
	g_pVtxBuffPause->Unlock();
}

//=============================================================================
//		ポーズの描画処理
//=============================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	PAUSE *pause = GetPause();

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_TEX; nCount++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePause[nCount]);

		if (pause->bDisp == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,									//プリミティブの種類
				4 * nCount,
				2);														//プリミティブの数	
		}
	}
}