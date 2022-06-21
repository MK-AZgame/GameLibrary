//========================================================
//
//	タイトルの処理[title.cpp]
//	AUTHOR:越本愛彪
//
//========================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include <Windows.h>

//マクロ定義
#define NUM_TITLETEXTURE (2)								//タイトルのテクスチャ数
#define NUM_TITLEMENU (2)									//タイトルのメニューの数
#define NUM_TITLEALL (NUM_TITLETEXTURE + NUM_TITLEMENU)		//タイトルで使用するテクスチャの総数

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTitle[NUM_TITLEALL] = {};		//タイトルのテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//タイトルの頂点情報へのポインタ

//========================================================
//					タイトルの初期化処理
//========================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/title.jpeg", &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/title.png", &g_pTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/title_start.png", &g_pTextureTitle[2]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/title_tutorial.png", &g_pTextureTitle[3]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TITLEALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D *pVtx;												//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//タイトル・タイトル背景のテクスチャ
	for (int nCntTitle = 0; nCntTitle < NUM_TITLETEXTURE; nCntTitle++)
	{
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

		pVtx += 4;
	}

	//タイトル内メニューのテクスチャ
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(540.0f, 400.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(740.0f, 400.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(540.0f, 500.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(740.0f, 500.0f, 0.0f);

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

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(540.0f, 520.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(740.0f, 520.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(540.0f, 620.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(740.0f, 620.0f, 0.0f);

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
	g_pVtxBuffTitle->Unlock();

	//サウンドの再生
	PlaySound(SOUND_LABEL_TITLE);
}

//========================================================
//				タイトルの終了処理
//========================================================
void UninitTitle(void)
{
	for (int nCount = 0; nCount < NUM_TITLEALL; nCount++)
	{
		//テクスチャの破棄
		if (g_pTextureTitle[nCount] != NULL)
		{
			g_pTextureTitle[nCount]->Release();
			g_pTextureTitle[nCount] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	//サウンドの停止
	StopSound();
}

//========================================================
//				タイトルの更新処理
//========================================================
void UpdateTitle(void)
{
	VERTEX_2D *pVtx;												//頂点情報へのポインタ
	FADE fade = GetFade();
	POINT mousePos;

	//マウスの位置を取得
	GetCursorPos(&mousePos);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 8;

	if (mousePos.x > 540.0f&&mousePos.x < 740.0f
		&&mousePos.y > 400.0f&&mousePos.y < 500.0f)
	{//マウスカーソルが”スタート”の位置にあるとき
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		if (GetMouseTrigger(0))
		{
			PlaySound(SOUND_LABEL_SE_DECISION);

			SetFade(MODE_GAME);
		}
	}
	else
	{
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	}

	pVtx += 4;

	if (mousePos.x > 540.0f&&mousePos.x < 740.0f
		&&mousePos.y > 520.0f&&mousePos.y < 620.0f)
	{//マウスカーソルが”遊び方”の位置にあるとき
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		if (GetMouseTrigger(0))
		{
			PlaySound(SOUND_LABEL_SE_DECISION);

			SetFade(MODE_TUTORIAL);
		}
	}
	else
	{
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	}

	//頂点座標をアンロック
	g_pVtxBuffTitle->Unlock();
}

//========================================================
//				タイトルの描画処理
//========================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < NUM_TITLEALL; nCount++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[nCount]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,									//プリミティブの種類
			4 * nCount,
			2);														//プリミティブの数
	}

	//テクスチャを元に戻す
	pDevice->SetTexture(0, NULL);
}