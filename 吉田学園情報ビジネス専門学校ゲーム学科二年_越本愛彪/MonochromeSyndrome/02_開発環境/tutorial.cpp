//=============================================================================
//
// チュートリアルの処理 [tutorial.cpp]
// Author : 越本　愛彪
//
//=============================================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "sound.h"

#define NUM_TUTORIAL (2)											//チュートリアル画像の枚数

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTutorial[NUM_TUTORIAL] = {};			//チュートリアルのテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;					//チュートリアル頂点情報へのポインタ
int g_nTutorialChange;												//チュートリアル画像切り替え用の変数

//=============================================================================
//		チュートリアルの初期化処理
//=============================================================================
void InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/tutorial.png", &g_pTextureTutorial[0]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/tutorial2.png", &g_pTextureTutorial[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TUTORIAL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	g_nTutorialChange = 0;										//チュートリアル画像切り替えよう変数の初期化

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

	pVtx += 4;													//データを４つ分次に進める

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
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点座標をアンロック
	g_pVtxBuffTutorial->Unlock();

	//チュートリアル画面BGMの再生
	PlaySound(SOUND_LABEL_BGM003);
}

//=============================================================================
//		チュートリアルの終了処理
//=============================================================================
void UninitTutorial(void)
{
	//テクスチャの破棄
	for (int nCntTutorial = 0; nCntTutorial < NUM_TUTORIAL; nCntTutorial++)
	{
		if (g_pTextureTutorial[nCntTutorial] != NULL)
		{
			g_pTextureTutorial[nCntTutorial]->Release();
			g_pTextureTutorial[nCntTutorial] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

	//BGMの停止
	StopSound();
}

//=============================================================================
//		チュートリアルの更新処理
//=============================================================================
void UpdataTutorial(void)
{
	FADE fade = GetFade();										//フェードの情報を取得
	VERTEX_2D *pVtx;

	//キー入力
	if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) == true || GetJoypadTrigger(JOYKEY_B) == true ||
		GetJoypadTrigger(JOYKEY_X) == true || GetJoypadTrigger(JOYKEY_Y) == true)
	{//ENTERキーが押された
		if (g_nTutorialChange == 0)
		{
			//SEの再生
			PlaySound(SOUND_LABEL_SE001);

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

			pVtx += 4;											//データを４つ分進める

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//頂点座標をアンロック
			g_pVtxBuffTutorial->Unlock();

			//チュートリアル画像を次に進める
			g_nTutorialChange = 1;
		}
		else if(g_nTutorialChange == 1)
		{
			if (fade == FADE_NONE)
			{//fadeが行われていない場合のみ
				//SEの再生
				PlaySound(SOUND_LABEL_SE001);

				//モードの設定処理
				SetFade(MODE_GAME);
			}
		}
	}
}

//=============================================================================
//		チュートリアルの描画処理
//=============================================================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTutorial = 0; nCntTutorial < NUM_TUTORIAL; nCntTutorial++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTutorial[nCntTutorial]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,									//プリミティブの種類
			4 * nCntTutorial,
			2);														//プリミティブの数
	}
}