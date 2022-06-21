//=============================================================================
//
// プレイヤーの処理 [player.cpp]
// Author : 越本　愛彪
//
//=============================================================================
#include "player.h"
#include "input.h"
#include "pause.h"
#include "game.h"
#include "fade.h"
#include "block.h"
#include "goal.h"
#include "timer.h"
#include "stageinterval.h"
#include "sound.h"

//マクロ定義
#define MOVE_DOWN     (0.185f)							//慣性の減速率
#define PLYER_JUMP    (20.0f)							//ジャンプの移動量

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;				//プレイヤーのテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;		//プレイヤーの頂点情報のポインタ
Player g_player;										//プレイヤーの情報を格納

//=============================================================================
//		プレイヤーの初期化処理
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	g_player.pos = D3DXVECTOR3(100.0f, 640.0f, 0.0f);	//位置の初期化
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量の初期化
	g_player.bDisp = true;								//プレイヤーを表示状態に
	g_player.nCounterAnim = 0;							//アニメーションカウンターの初期化
	g_player.nPatternAnim = 0;							//アニメーションパターンの初期化
	g_player.nDirectionMove = 0;						//プレイヤーの向きの初期化
	g_player.state = PLAYERSTATE_NORMAL;				//プレイヤー状態の初期化
	g_player.nLife = 2;									//プレイヤーの体力の初期化
	
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D *pVtx;									//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH / 2, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH / 2, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH / 2, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH / 2, g_player.pos.y, 0.0f);
	
	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//頂点座標をアンロック
	g_pVtxBuffPlayer->Unlock();
}

//=============================================================================
//		プレイヤーの終了処理
//=============================================================================
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//=============================================================================
//		プレイヤーの更新処理
//=============================================================================
void UpdataPlayer(void)
{
	VERTEX_2D *pVtx;								//頂点情報へのポインタ
	FADE Fade = GetFade();

	//移動
	if (g_player.state != PLAYERSTATE_DEATH)
	{
		if (g_player.state == PLAYERSTATE_NORMAL)
		{//通常時
			if (GetKeyboardPress(DIK_A) || GetJoypadPress(JOYKEY_LEFT) == true)
			{//左
				g_player.move.x -= PLAYER_MOVE;

				g_player.nDirectionMove = 1;
			}
			else if (GetKeyboardPress(DIK_D) || GetJoypadPress(JOYKEY_RIGHT) == true)
			{//右
				g_player.move.x += PLAYER_MOVE;

				g_player.nDirectionMove = 0;
			}

			//ジャンプ
			if (GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_A) == true)
			{
				PlaySound(SOUND_LABEL_SE000);
				g_player.move.y -= PLYER_JUMP - 1.0f;
				g_player.state = PLAYERSTATE_JUMP;
			}
		}
		else if (g_player.state == PLAYERSTATE_JUMP)
		{//ジャンプ中
			if (GetKeyboardPress(DIK_A) || GetJoypadPress(JOYKEY_LEFT) == true)
			{//左
				g_player.move.x -= PLAYER_MOVE - 0.6f;

				g_player.nDirectionMove = 1;
			}
			else if (GetKeyboardPress(DIK_D) || GetJoypadPress(JOYKEY_RIGHT) == true)
			{//右
				g_player.move.x += PLAYER_MOVE - 0.6f;

				g_player.nDirectionMove = 0;
			}
		}

		//前回の位置を保存
		g_player.posOld = g_player.pos;

		//位置を更新
		g_player.pos += g_player.move;

		//重力
		g_player.move.y += 1.5f;

		//ジャンプの可否判定
		g_player.state = (ColisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, PLAYER_WIDTH, PLAYER_HEIGHT) == true) ?
			PLAYERSTATE_NORMAL : PLAYERSTATE_JUMP;

		//ゴールとの当たり判定
		ColisionGoal(&g_player.pos, &g_player.posOld, &g_player.move, PLAYER_WIDTH, PLAYER_HEIGHT);
	}

	//ブロックのスクロール処理
	if (g_player.pos.x >= SCREEN_WIDTH / 2)
	{
		g_player.pos.x = SCREEN_WIDTH / 2;
	}

	//画面外への移動の防止処理
	if (g_player.pos.x - PLAYER_WIDTH / 2 <= 0.0f)
	{//画面左端
		g_player.pos.x = 0.0f + PLAYER_WIDTH / 2;
	}
	else if (g_player.pos.x - PLAYER_WIDTH / 2 >= SCREEN_WIDTH)
	{//画面右端
		g_player.pos.x = 0.0f - PLAYER_WIDTH / 2;
	}

	//アニメーションの更新
	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL:									//通常時のアニメーション
		if (g_player.move.x >= 0.2f || g_player.move.x <= -0.2f)
		{//移動中
			g_player.nCounterAnim++;
			if (g_player.nCounterAnim % 10 == 0)
			{
				g_player.nCounterAnim = 0;
				g_player.nPatternAnim++;
				if (g_player.nPatternAnim >= 4)
				{
					g_player.nPatternAnim = 0;
				}
			}
		}
		else
		{//プレイヤー停止時のアニメーション固定
			if ((g_player.nPatternAnim + 1) % 2 == 0)
			{
				g_player.nPatternAnim++;
			}
		}
		break;
	case PLAYERSTATE_JUMP:										//ジャンプ中のアニメーション
		if (g_player.nPatternAnim % 2 == 0)
		{//ジャンプ中のアニメーション固定
			g_player.nPatternAnim++;
		}
		break;
	}

	//移動量の減衰（慣性）
	if (g_player.state == PLAYERSTATE_JUMP)
	{//ジャンプ中
		g_player.move.x += (0.0f - g_player.move.x) * 0.05f;
	}
	else
	{//通常時
		g_player.move.x += (0.0f - g_player.move.x) * MOVE_DOWN;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + (0.25f * g_player.nPatternAnim), 0.0f + (0.5f * g_player.nDirectionMove));
	pVtx[1].tex = D3DXVECTOR2(0.25f + (0.25f * g_player.nPatternAnim), 0.0f + (0.5f * g_player.nDirectionMove));
	pVtx[2].tex = D3DXVECTOR2(0.0f + (0.25f * g_player.nPatternAnim), 0.5f + (0.5f * g_player.nDirectionMove));
	pVtx[3].tex = D3DXVECTOR2(0.25f + (0.25f * g_player.nPatternAnim), 0.5f + (0.5f * g_player.nDirectionMove));

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH / 2, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH / 2, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH / 2, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH / 2, g_player.pos.y, 0.0f);

	//頂点座標をアンロック
	g_pVtxBuffPlayer->Unlock();

	//プレイヤー落下時の処理
	if (g_player.pos.y - PLAYER_HEIGHT >= 1280.0f || g_player.pos.y <= 0.0f)
	{
		GAMESTATE &state = *GetGameState();
		g_player.nLife--;										//プレイヤー残機の減少
		
		if (g_player.nLife <= 0)
		{//プレイヤーの死亡
			if (Fade == FADE_NONE)
			{
				state = GAMESTATE_END;
				g_player.state = PLAYERSTATE_DEATH;

				SetFade(MODE_RESULT);
			}
		}
		else
		{//ステージの初期位置に戻す
			SetStageInterval(state);
		}
	}
}

//=============================================================================
//		プレイヤーの描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePlayer);

	if (g_player.bDisp == true)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,									//プリミティブの種類
			0,
			2);														//プリミティブの数			
	}
}

//=============================================================================
//		ブロックの当たり判定
//=============================================================================
bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
{
	bool bIsLanding = false;									//着地しているかどうか

	//ブロックとプレイヤーの当たり判定
	//上から下
	if (pPosOld->y - fHeight / 2 >= g_player.pos.y &&
		pPos->y - fHeight / 2 < g_player.pos.y &&
		pPos->x + fWidth / 2 > g_player.pos.x - PLAYER_WIDTH / 2 &&
		pPos->x - fWidth / 2 < g_player.pos.x + PLAYER_WIDTH / 2)
	{
		g_player.pos.y = pPos->y - fHeight / 2;
	}

	//下から上
	if (pPosOld->y + fHeight / 2 >= g_player.pos.y - PLAYER_HEIGHT &&
		pPos->y + fHeight / 2 < g_player.pos.y - PLAYER_HEIGHT &&
		pPos->x + fWidth / 2 > g_player.pos.x - PLAYER_WIDTH / 2 &&
		pPos->x - fWidth / 2 < g_player.pos.x + PLAYER_WIDTH / 2)
	{
	}

	if (pPosOld->y + fHeight / 2 > g_player.pos.y - PLAYER_HEIGHT &&
		pPosOld->y - fHeight / 2 < g_player.pos.y)
	{
		//左から右
		if (pPosOld->x - fWidth / 2 >= g_player.pos.x + PLAYER_WIDTH / 2 &&
			pPos->x - fWidth / 2 < g_player.pos.x + PLAYER_WIDTH / 2)
		{
			g_player.pos.x = pPos->x - fWidth / 2 - PLAYER_WIDTH / 2;
		}

		//右から左
		if (pPosOld->x + fWidth / 2 <= g_player.pos.x - PLAYER_WIDTH / 2 &&
			pPos->x + fWidth / 2 > g_player.pos.x - PLAYER_WIDTH / 2)
		{
			g_player.pos.x = pPos->x + fWidth / 2 + PLAYER_WIDTH / 2;
		}
	}
	return bIsLanding;
}

//=============================================================================
//		プレイヤー座標の設定
//=============================================================================
void SetPlayerPos(D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx;

	//座標更新
	g_player.pos = pos;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH / 2, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH / 2, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH / 2, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH / 2, g_player.pos.y, 0.0f);

	//頂点座標をアンロック
	g_pVtxBuffPlayer->Unlock();
}

//=============================================================================
//		プレイヤー情報の取得
//=============================================================================
Player *GetPlayer(void)
{
	return &g_player;
}