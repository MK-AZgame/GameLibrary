//========================================================
//
//	ラウンドの処理[round.cpp]
//	AUTHOR:越本愛彪
//
//========================================================
#include "main.h"
#include "round.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "enemy.h"
#include "player.h"
#include "time.h"
#include "meshfield.h"
#include <stdlib.h>
#include <time.h>

//マクロ定義
#define NUM_ROUND (1)											//ラウンドの桁
#define ROUND_INTERVALTIME (300)								//ラウンド間のインターバルの時間
#define MAX_ROUND (5)											//ラウンドの最大数

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureRound = NULL;						//ラウンドのテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRound = NULL;					//ラウンドの頂点情報へのポインタ
D3DXVECTOR3 g_posRound;											//ラウンドの位置
Round g_Round;													//ラウンドの情報を格納
int g_roundOld;													//ひとつ前のラウンドを保存
float g_fPosZOld, g_fPosXOld;

//========================================================
//				ラウンドの初期化処理
//========================================================
void InitRound(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/number000.png", &g_pTextureRound);

	//グローバル変数の初期化
	g_posRound = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//位置の初期化
	g_Round.nIntervalTime = ROUND_INTERVALTIME;					//インターバルの時間の設定
	g_Round.nNumRound = 1;										//最初のラウンドの設定
	g_Round.nState = ROUND_FIRST;	
	g_roundOld = ROUND_FIRST;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (NUM_ROUND),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRound,
		NULL);

	VERTEX_2D *pVtx;											//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRound->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRound = 0; nCntRound < NUM_ROUND; nCntRound++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(1220.0f + (50.0f * nCntRound), 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1270.0f + (50.0f * nCntRound), 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1220.0f + (50.0f * nCntRound), 60.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1270.0f + (50.0f * nCntRound), 60.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点座標をアンロック
	g_pVtxBuffRound->Unlock();

	//ラウンドを１に設定
	ChangeRound(ROUND_FIRST);
}

//========================================================
//				ラウンドの終了処理
//========================================================
void UninitRound(void)
{
	//テクスチャの破棄
	if (g_pTextureRound != NULL)
	{
		g_pTextureRound->Release();
		g_pTextureRound = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRound != NULL)
	{
		g_pVtxBuffRound->Release();
		g_pVtxBuffRound = NULL;
	}
}

//========================================================
//				ラウンドの更新処理
//========================================================
void UpdataRound(void)
{
	FADE fade = GetFade();
	GAMESTATE &pState = *GetGameState();

	//現在のインターバル以外のラウンド数を保存
	if (g_Round.nState != ROUND_INTERVAL)
	{
		g_roundOld = g_Round.nState;
	}

	//ラウンド間のインターバル
	if (g_Round.nState == ROUND_INTERVAL)						
	{
		g_Round.nIntervalTime--;

		if (g_Round.nIntervalTime <= 0)
		{
			if (g_roundOld == ROUND_FIRST)
			{
				g_Round.nState = ROUND_SECOND;
				ChangeRound(ROUND_SECOND);
				//インターバルの秒数を再設定
				g_Round.nIntervalTime = ROUND_INTERVALTIME;
			}
			else if (g_roundOld == ROUND_SECOND)
			{
				g_Round.nState = ROUND_THIRD;
				ChangeRound(ROUND_THIRD);
				//インターバルの秒数を再設定
				g_Round.nIntervalTime = ROUND_INTERVALTIME;
			}
			else if (g_roundOld == ROUND_THIRD)
			{
				g_Round.nState = ROUND_FOURTH;
				ChangeRound(ROUND_FOURTH);
				//インターバルの秒数を再設定
				g_Round.nIntervalTime = ROUND_INTERVALTIME;
			}
			else if (g_roundOld == ROUND_FOURTH)
			{
				g_Round.nState = ROUND_FIFTH;
				ChangeRound(ROUND_FIFTH);
				//インターバルの秒数を再設定
				g_Round.nIntervalTime = ROUND_INTERVALTIME;
			}
		}
		else if (g_roundOld == ROUND_FIFTH)
		{
			if (fade == FADE_NONE)
			{
				pState = GAMESTATE_CLEAR;
				//SaveHighScore();

				//最終的なタイムを保存
				StopTimer();

				//リザルト画面に遷移
				SetFade(MODE_RESULT);
			}
		}
	}

}

//========================================================
//				ラウンドの描画処理
//========================================================
void DrawRound(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRound, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntRound = 0; nCntRound < NUM_ROUND; nCntRound++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRound);

		//ポリゴンの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,								//プリミティブの種類
			4 * nCntRound,
			2);													//プリミティブの数	
	}

	//テクスチャを元に戻す
	pDevice->SetTexture(0,NULL);
}

//========================================================
//				ラウンドの設定処理
//========================================================
void SetRound()
{
	VERTEX_2D *pVtx;
	float aPosTexU[NUM_ROUND];									//各桁の数値を格納

	//aPosTexU[0] = ((g_Round.nNumRound % 100) / 10) * 0.1f;
	aPosTexU[0] = g_Round.nNumRound * 0.1f;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRound->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f + aPosTexU[0], 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + aPosTexU[0], 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + aPosTexU[0], 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + aPosTexU[0], 1.0f);

	//頂点座標をアンロック
	g_pVtxBuffRound->Unlock();
}

//========================================================
//				ラウンドの状態を切り替える
//========================================================
void ChangeRound(ROUNDNUM nextRound)
{
	Player *pPlayer = GetPlayer();
	float fPosX, fPosZ;											//敵の湧き位置設定用

	//ラウンド状態の切り替え（各ラウンドでの敵の設定）
	switch (nextRound)
	{
	case ROUND_FIRST:											//ラウンド１
		for (int nCntEnemyAppear = 0; nCntEnemyAppear < 5; nCntEnemyAppear++)
		{
			//ランダムな値を設定
			fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
			fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;

			//沸き位置がかぶっていた場合ずらす
			while (1)
			{
				if (g_fPosZOld - ENEMY_SIZE < fPosZ + ENEMY_SIZE &&
					g_fPosZOld + ENEMY_SIZE > fPosZ - ENEMY_SIZE &&
					g_fPosXOld - ENEMY_SIZE < fPosX + ENEMY_SIZE &&
					g_fPosXOld + ENEMY_SIZE > fPosX - ENEMY_SIZE)
				{
					//ランダムな値を設定
					fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
					fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;

					//沸き位置がプレイヤーと近すぎた場合にずらす
					if (pPlayer->pos.z - PLAYER_SIZE < fPosZ + ENEMY_SIZE &&
						pPlayer->pos.z + PLAYER_SIZE > fPosZ - ENEMY_SIZE &&
						pPlayer->pos.x - PLAYER_SIZE < fPosX + ENEMY_SIZE &&
						pPlayer->pos.x + PLAYER_SIZE > fPosX - ENEMY_SIZE)
					{
						fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
						fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
					}
				}
				else
				{
					break;
				}
			}

			//今回の沸き位置を保存
			g_fPosZOld = fPosZ; 
			g_fPosXOld = fPosX;

			//エネミーをセット（位置・体力）
			SetEnemy(D3DXVECTOR3(fPosX, -50.0f, fPosZ), 2, 1);
		}

		//表示されるラウンド数をセット
		SetRound();
		break;
	case ROUND_SECOND:											//ラウンド２
		for (int nCntEnemyAppear = 0; nCntEnemyAppear < 8; nCntEnemyAppear++)
		{
			//ランダムな値を設定
			fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
			fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;

			//沸き位置がかぶっていた場合ずらす
			while (1)
			{
				if (g_fPosZOld - ENEMY_SIZE < fPosZ + ENEMY_SIZE &&
					g_fPosZOld + ENEMY_SIZE > fPosZ - ENEMY_SIZE &&
					g_fPosXOld - ENEMY_SIZE < fPosX + ENEMY_SIZE &&
					g_fPosXOld + ENEMY_SIZE > fPosX - ENEMY_SIZE)
				{
					//ランダムな値を設定
					fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
					fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;

					//沸き位置がプレイヤーと近すぎた場合にずらす
					if (pPlayer->pos.z - PLAYER_SIZE < fPosZ + ENEMY_SIZE &&
						pPlayer->pos.z + PLAYER_SIZE > fPosZ - ENEMY_SIZE &&
						pPlayer->pos.x - PLAYER_SIZE < fPosX + ENEMY_SIZE &&
						pPlayer->pos.x + PLAYER_SIZE > fPosX - ENEMY_SIZE)
					{
						fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
						fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
					}
				}
				else
				{
					break;
				}
			}

			//エネミーをセット（位置・体力）
			SetEnemy(D3DXVECTOR3(fPosX, -50.0f, fPosZ),4,1);
		}

		//ラウンド数を加算
		g_Round.nNumRound++;

		//表示されるラウンド数をセット
		SetRound();
		break;
	case ROUND_THIRD:											//ラウンド３
		for (int nCntEnemyAppear = 0; nCntEnemyAppear < 10; nCntEnemyAppear++)
		{
			//ランダムな値を設定
			fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
			fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;

			//沸き位置がかぶっていた場合ずらす
			while (1)
			{
				if (g_fPosZOld - ENEMY_SIZE < fPosZ + ENEMY_SIZE &&
					g_fPosZOld + ENEMY_SIZE > fPosZ - ENEMY_SIZE &&
					g_fPosXOld - ENEMY_SIZE < fPosX + ENEMY_SIZE &&
					g_fPosXOld + ENEMY_SIZE > fPosX - ENEMY_SIZE)
				{
					//ランダムな値を設定
					fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
					fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;

					//沸き位置がプレイヤーと近すぎた場合にずらす
					if (pPlayer->pos.z - PLAYER_SIZE < fPosZ + ENEMY_SIZE &&
						pPlayer->pos.z + PLAYER_SIZE > fPosZ - ENEMY_SIZE &&
						pPlayer->pos.x - PLAYER_SIZE < fPosX + ENEMY_SIZE &&
						pPlayer->pos.x + PLAYER_SIZE > fPosX - ENEMY_SIZE)
					{
						fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
						fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
					}
				}
				else
				{
					break;
				}
			}

			//エネミーをセット（位置・体力）
			SetEnemy(D3DXVECTOR3(fPosX, -50.0f, fPosZ),6,2);
		}

		//ラウンド数を加算
		g_Round.nNumRound++;

		//表示されるラウンド数をセット
		SetRound();
		break;
	case ROUND_FOURTH:											//ラウンド４
		for (int nCntEnemyAppear = 0; nCntEnemyAppear < 13; nCntEnemyAppear++)
		{
			//ランダムな値を設定
			fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
			fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;

			//沸き位置がかぶっていた場合ずらす
			while (1)
			{
				if (g_fPosZOld - ENEMY_SIZE < fPosZ + ENEMY_SIZE &&
					g_fPosZOld + ENEMY_SIZE > fPosZ - ENEMY_SIZE &&
					g_fPosXOld - ENEMY_SIZE < fPosX + ENEMY_SIZE &&
					g_fPosXOld + ENEMY_SIZE > fPosX - ENEMY_SIZE)
				{
					//ランダムな値を設定
					fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
					fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;

					//沸き位置がプレイヤーと近すぎた場合にずらす
					if (pPlayer->pos.z - PLAYER_SIZE < fPosZ + ENEMY_SIZE &&
						pPlayer->pos.z + PLAYER_SIZE > fPosZ - ENEMY_SIZE &&
						pPlayer->pos.x - PLAYER_SIZE < fPosX + ENEMY_SIZE &&
						pPlayer->pos.x + PLAYER_SIZE > fPosX - ENEMY_SIZE)
					{
						fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
						fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
					}
				}
				else
				{
					break;
				}
			}

			//エネミーをセット（位置・体力）
			SetEnemy(D3DXVECTOR3(fPosX, -50.0f, fPosZ),6,3);
		}

		//ラウンド数を加算
		g_Round.nNumRound++;

		//表示されるラウンド数をセット
		SetRound();
		break;
	case ROUND_FIFTH:											//ラウンド５
		for (int nCntEnemyAppear = 0; nCntEnemyAppear < 15; nCntEnemyAppear++)
		{
			//ランダムな値を設定
			fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
			fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;

			//沸き位置がかぶっていた場合ずらす
			while (1)
			{
				if (g_fPosZOld - ENEMY_SIZE < fPosZ + ENEMY_SIZE &&
					g_fPosZOld + ENEMY_SIZE > fPosZ - ENEMY_SIZE &&
					g_fPosXOld - ENEMY_SIZE < fPosX + ENEMY_SIZE &&
					g_fPosXOld + ENEMY_SIZE > fPosX - ENEMY_SIZE)
				{
					//ランダムな値を設定
					fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
					fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;

					//沸き位置がプレイヤーと近すぎた場合にずらす
					if (pPlayer->pos.z - PLAYER_SIZE < fPosZ + ENEMY_SIZE &&
						pPlayer->pos.z + PLAYER_SIZE > fPosZ - ENEMY_SIZE &&
						pPlayer->pos.x - PLAYER_SIZE < fPosX + ENEMY_SIZE &&
						pPlayer->pos.x + PLAYER_SIZE > fPosX - ENEMY_SIZE)
					{
						fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
						fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
					}
				}
				else
				{
					break;
				}
			}

			//エネミーをセット（位置・体力）
			SetEnemy(D3DXVECTOR3(fPosX, -50.0f, fPosZ),6,5);
		}

		//ラウンド数を加算
		g_Round.nNumRound++;

		//表示されるラウンド数をセット
		SetRound();
		break;
	}
}

//===============================================================================================
//									ラウンドの情報を取得
//===============================================================================================
Round *GetRound()
{
	return &g_Round;
}