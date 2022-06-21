//========================================================
//
//	チュートリアルの処理[tutorial.cpp]
//	AUTHOR:越本愛彪
//
//========================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "sound.h"

#define NUM_TUTORIAL (1)											//チュートリアル画像の枚数

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTutorial = NULL;						//チュートリアルのテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;					//チュートリアル頂点情報へのポインタ

//========================================================
//			チュートリアルの初期化処理
//========================================================
void InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/tutorial.png", &g_pTextureTutorial);
	//D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/tutorial2.png", &g_pTextureTutorial[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TUTORIAL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	VERTEX_2D *pVtx;											//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTutorial->Unlock();

	//チュートリアル画面BGMの再生
	//PlaySound(SOUND_LABEL_BGM000);
}

//========================================================
//			チュートリアルの終了処理
//========================================================
void UninitTutorial(void)
{
	//テクスチャの破棄
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();
		g_pTextureTutorial = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

	//BGMの停止
	//StopSound();
}

//========================================================
//			チュートリアルの更新処理
//========================================================
void UpdateTutorial(void)
{
	FADE fade = GetFade();										//フェードの情報を取得

	//キー入力
	if (GetMouseTrigger(0))
	{//クリックされた
		if (fade == FADE_NONE)
		{//fadeが行われていない場合のみ
			//SEの再生
			PlaySound(SOUND_LABEL_SE_DECISION);

			//モードの設定処理
			SetFade(MODE_TITLE);
		}
	}
}

//========================================================
//			チュートリアルの描画処理
//========================================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTutorial);

		//ポリゴンの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,									//プリミティブの種類
			0,
			2);														//プリミティブの数
}

