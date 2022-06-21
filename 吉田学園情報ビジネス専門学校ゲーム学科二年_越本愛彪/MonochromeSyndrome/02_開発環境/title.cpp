//=============================================================================
//
// タイトルの処理 [title.cpp]
// Author : 越本　愛彪
//
//=============================================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//マクロ定義
#define NUM_BACKGROUND (2)

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTitle[NUM_BACKGROUND] = {};	//タイトルのテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//タイトルの頂点情報へのポインタ
D3DXCOLOR g_colorTitle;										//タイトルのカラー用
D3DXCOLOR g_colorButton;									//ボタンのカラー用
BUTTON g_button;											//ボタンの情報を格納
SWITCH g_switch;											//タイトルの状態を切り替えるための構造体情報を格納
int g_nCoolCount;											//クールタイムをカウントする用
int g_nCountStop;											
int g_nflag;

//=============================================================================
//		タイトルの初期化処理
//=============================================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//グローバル変数の初期化
	g_button = BUTTON_IN;
	g_switch = SWITCH_ON;
	g_colorTitle = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	g_colorButton = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	g_nCoolCount = 0;
	g_nCountStop = 0;
	g_nflag = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/title.png", &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/pressenter.png", &g_pTextureTitle[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BACKGROUND,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D *pVtx;												//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

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

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(500.0f, 400.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(780.0f, 400.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(500.0f, 550.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(780.0f, 550.0f, 0.0f);

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
	g_pVtxBuffTitle->Unlock();

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM000);
}

//=============================================================================
//		タイトルの終了処理
//=============================================================================
void UninitTitle(void)
{
	for (int nCount = 0; nCount < NUM_BACKGROUND; nCount++)
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

//=============================================================================
//		タイトルの更新処理
//=============================================================================
void UpdataTitle(void)
{
	VERTEX_2D *pVtx;												//頂点情報へのポインタ
	FADE fade = GetFade();

	//フェード状態のタイトルを即座に表示させる
	if (g_switch == SWITCH_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) == true)
		{
			g_switch = SWITCH_ON;
		}
	}

	//タイトルからチュートリアル画面に遷移させる
	if (g_switch == SWITCH_ON)
	{
		g_nCountStop++;

		if (g_nCountStop > 5)
		{
			if (fade == FADE_NONE)
			{
				//キー入力
				if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) == true || GetJoypadTrigger(JOYKEY_B) == true || 
					GetJoypadTrigger(JOYKEY_X) == true|| GetJoypadTrigger(JOYKEY_Y) == true)
				{//ENTERキーが押された
					g_nflag = 1;
					PlaySound(SOUND_LABEL_SE001);
					//モードの設定処理
					SetFade(MODE_TUTORIAL);
				}
			}
		}

		//[PUSH ENTER]の点滅
		if (g_nflag == 1)
		{//エンターキーが押された状態
			if (g_button == BUTTON_OUT)
			{//徐々に薄くしていく
				g_colorButton.a -= 1.0f;
				if (g_colorButton.a <= 0)
				{
					g_colorButton.a = 0.0f;
					g_button = BUTTON_IN;
				}
			}
			else if (g_button == BUTTON_IN)
			{//徐々に濃くしていく
				g_colorButton.a += 1.0f;
				if (g_colorButton.a >= 1.0f)
				{
					g_colorButton.a = 1.0f;
					g_button = BUTTON_OUT;
				}
			}
		}
		else
		{
			if (g_button == BUTTON_OUT)
			{
				g_colorButton.a -= 0.05f;
				if (g_colorButton.a <= 0)
				{
					g_colorButton.a = 0.0f;
					g_button = BUTTON_IN;
				}
			}
			else if (g_button == BUTTON_IN)
			{
				g_colorButton.a += 0.05f;
				if (g_colorButton.a >= 1.0f)
				{
					g_colorButton.a = 1.0f;
					g_button = BUTTON_OUT;
				}
			}
		}

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorButton.a);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorButton.a);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorButton.a);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorButton.a);

		//頂点座標をアンロック
		g_pVtxBuffTitle->Unlock();
	}
	else if (g_switch != SWITCH_ON)
	{
		if (g_nCoolCount >= 180)
		{
			if (g_nflag == 1)
			{
				if (g_button == BUTTON_OUT)
				{
					g_colorButton.a -= 1.0f;
					if (g_colorButton.a <= 0)
					{
						g_colorButton.a = 0.0f;
						g_button = BUTTON_IN;
					}
				}
				else if (g_button == BUTTON_IN)
				{
					g_colorButton.a += 1.0f;
					if (g_colorButton.a >= 1.0f)
					{
						g_colorButton.a = 1.0f;
						g_button = BUTTON_OUT;
					}
				}
			}
			else
			{
				//[PUSH ENTER]の点滅
				if (g_button == BUTTON_OUT)
				{
					g_colorButton.a -= 0.05f;
					if (g_colorButton.a <= 0)
					{
						g_colorButton.a = 0.0f;
						g_button = BUTTON_IN;
					}
				}
				else if (g_button == BUTTON_IN)
				{
					g_colorButton.a += 0.05f;
					if (g_colorButton.a >= 1.0f)
					{
						g_colorButton.a = 1.0f;
						g_button = BUTTON_OUT;
					}
				}
			}
		}

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorButton.a);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorButton.a);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorButton.a);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorButton.a);

		//頂点座標をアンロック
		g_pVtxBuffTitle->Unlock();
	}
}

//=============================================================================
//		タイトルの描画処理
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < NUM_BACKGROUND; nCount++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[nCount]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,									//プリミティブの種類
			4 * nCount,
			2);														//プリミティブの数
	}
}