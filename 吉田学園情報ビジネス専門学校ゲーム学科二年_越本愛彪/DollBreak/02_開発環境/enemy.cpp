//========================================================
//
//	エネミーモデルの処理[enemy.cpp]
//	AUTHOR:越本愛彪
//
//========================================================
#include <stdio.h>
#include "enemy.h"
#include "player.h"
#include "round.h"
#include "input.h"
#include "shadow.h"
#include "bullet.h"
#include "meshfield.h"
#include "model.h"
#include "loadfileh.h"

//マクロ定義
#define ENEMY_MOVE (1.0f)												//エネミーの移動量
#define ENEMY_ROTSPEED (0.1f)											//エネミーの回転の減衰量

//グローバル変数
Enemy g_aEnemy[MAX_ENEMY];												//エネミーの情報を格納

//========================================================
//					エネミー初期化処理
//========================================================
void InitEnemy(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//エネミー情報の初期化
	for (int nCntEnem = 0; nCntEnem < MAX_ENEMY; nCntEnem++)
	{
		g_aEnemy[nCntEnem].pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);		//位置の初期化
		g_aEnemy[nCntEnem].rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);		//向きの初期化
		g_aEnemy[nCntEnem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量の初期化
		g_aEnemy[nCntEnem].state = ENEMYSTATE_NORMAL;					//状態の初期化
		g_aEnemy[nCntEnem].rotDest.y = 0;								//目的の角度の初期化
		g_aEnemy[nCntEnem].nEnemyLife = 0;								//えねみーの体力の初期化
		g_aEnemy[nCntEnem].nKey = 0;									//モーションのキーの初期化
		g_aEnemy[nCntEnem].nAttackTime = 0;								//攻撃の間隔の初期化
		g_aEnemy[nCntEnem].bUse = false;								//使われていない状態にする

		//パーツの初期化
		for (int nCntEnemyParts = 0; nCntEnemyParts < NUM_ENEMYPARTS; nCntEnemyParts++)
		{
			g_aEnemy[nCntEnem].aModel[nCntEnemyParts].rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
		}
	}
}

//========================================================
//					エネミー終了処理
//========================================================
void UninitEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].aModel[0].pMesh != NULL)
		{
			g_aEnemy[nCntEnemy].aModel[0].pMesh->Release();
			g_aEnemy[nCntEnemy].aModel[0].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_aEnemy[nCntEnemy].aModel[0].pBuffMat != NULL)
		{
			g_aEnemy[nCntEnemy].aModel[0].pBuffMat->Release();
			g_aEnemy[nCntEnemy].aModel[0].pBuffMat = NULL;
		}
	}

}

//========================================================
//					エネミー更新処理
//========================================================
void UpdateEnemy(void)
{
	Player *pPlayer = GetPlayer();

	for (int nCntEnem = 0; nCntEnem < MAX_ENEMY; nCntEnem++)
	{
		if (g_aEnemy[nCntEnem].bUse == true)
		{
			if (g_aEnemy[nCntEnem].state == ENEMYSTATE_APPEAR)
			{
				//for (int nCnt = 0; nCnt < 80; nCnt++)
				{
					g_aEnemy[nCntEnem].pos.y++;
				}

				if (g_aEnemy[nCntEnem].pos.y >= 30.0f)
				{
					//状態を”通常”にする
					g_aEnemy[nCntEnem].state = ENEMYSTATE_NORMAL;
				}
			}
			else if (g_aEnemy[nCntEnem].state != ENEMYSTATE_APPEAR&&g_aEnemy[nCntEnem].state != ENEMYSTATE_DEATH)
			{
				//posOldに現在の位置を保存
				g_aEnemy[nCntEnem].posOld = g_aEnemy[nCntEnem].pos;

				//エネミーの移動量を計算
				D3DXVECTOR3 vec = pPlayer->pos - g_aEnemy[nCntEnem].pos;

				//移動量をノーマライズ
				D3DXVec3Normalize(&vec, &vec);

				//moveにvecを代入
				g_aEnemy[nCntEnem].move = D3DXVECTOR3(vec.x, 0.0f, vec.z);

				//位置に移動量を加算してエネミーを移動させる
				g_aEnemy[nCntEnem].pos += g_aEnemy[nCntEnem].move * 0.5f;

				//敵の回転（プレイヤーの方向を向く）
				g_aEnemy[nCntEnem].rot.y = atan2f((-pPlayer->pos.x + g_aEnemy[nCntEnem].pos.x), (-pPlayer->pos.z + g_aEnemy[nCntEnem].pos.z));

				////回転の正規化
				//目的の角度が大きすぎたり小さすぎたりした時の計算
				if (g_aEnemy[nCntEnem].rotDest.y - g_aEnemy[nCntEnem].rot.y > D3DX_PI)
				{
					g_aEnemy[nCntEnem].rotDest.y -= D3DX_PI * 2.0f;
				}
				else if (g_aEnemy[nCntEnem].rotDest.y - g_aEnemy[nCntEnem].rot.y < -D3DX_PI)
				{
					g_aEnemy[nCntEnem].rotDest.y += D3DX_PI * 2.0f;
				}

				//回転の慣性の計算
				g_aEnemy[nCntEnem].rot.y += (g_aEnemy[nCntEnem].rotDest.y - g_aEnemy[nCntEnem].rot.y) * ENEMY_ROTSPEED;

				//計算結果が大きすぎたり小さすぎたりした時の調整
				if (g_aEnemy[nCntEnem].rot.y < -D3DX_PI)
				{
					g_aEnemy[nCntEnem].rot.y += D3DX_PI * 2.0f;
				}
				else if (g_aEnemy[nCntEnem].rot.y > D3DX_PI)
				{
					g_aEnemy[nCntEnem].rot.y -= D3DX_PI * 2.0f;
				}

				//影の更新
				SetPositionShadow(g_aEnemy[nCntEnem].nIdxShadow, D3DXVECTOR3(g_aEnemy[nCntEnem].pos.x, 0.1f, g_aEnemy[nCntEnem].pos.z));

				//行動範囲制限(壁との当たり判定)
				if (g_aEnemy[nCntEnem].pos.x + ENEMY_SIZE >= MESHFIELD_SIZE * 2)
				{//右
					if (g_aEnemy[nCntEnem].pos.z + ENEMY_SIZE >= MESHFIELD_SIZE * 2)
					{//右奥
						g_aEnemy[nCntEnem].pos.x = (MESHFIELD_SIZE * 2) - ENEMY_SIZE;
						g_aEnemy[nCntEnem].pos.z = (MESHFIELD_SIZE * 2) - ENEMY_SIZE;
					}
					else if (g_aEnemy[nCntEnem].pos.z - ENEMY_SIZE <= -MESHFIELD_SIZE * 2)
					{//右手前
						g_aEnemy[nCntEnem].pos.x = (MESHFIELD_SIZE * 2) - ENEMY_SIZE;
						g_aEnemy[nCntEnem].pos.z = (-MESHFIELD_SIZE * 2) + ENEMY_SIZE;
					}
					else
					{
						g_aEnemy[nCntEnem].pos.x = (MESHFIELD_SIZE * 2) - ENEMY_SIZE;
					}
				}
				else if (g_aEnemy[nCntEnem].pos.x - ENEMY_SIZE <= -MESHFIELD_SIZE * 2)
				{//左
					if (g_aEnemy[nCntEnem].pos.z + ENEMY_SIZE >= MESHFIELD_SIZE * 2)
					{//左奥
						g_aEnemy[nCntEnem].pos.x = (-MESHFIELD_SIZE * 2) + ENEMY_SIZE;
						g_aEnemy[nCntEnem].pos.z = (MESHFIELD_SIZE * 2) - ENEMY_SIZE;
					}
					else if (g_aEnemy[nCntEnem].pos.z - ENEMY_SIZE <= -MESHFIELD_SIZE * 2)
					{//右手前
						g_aEnemy[nCntEnem].pos.x = (-MESHFIELD_SIZE * 2) + ENEMY_SIZE;
						g_aEnemy[nCntEnem].pos.z = (-MESHFIELD_SIZE * 2) + ENEMY_SIZE;
					}
					else
					{
						g_aEnemy[nCntEnem].pos.x = (-MESHFIELD_SIZE * 2) + ENEMY_SIZE;
					}
				}
				else if (g_aEnemy[nCntEnem].pos.z + ENEMY_SIZE >= MESHFIELD_SIZE * 2)
				{//奥
					g_aEnemy[nCntEnem].pos.z = (MESHFIELD_SIZE * 2) - ENEMY_SIZE;
				}
				else if (g_aEnemy[nCntEnem].pos.z - ENEMY_SIZE <= (-MESHFIELD_SIZE * 2))
				{//手前
					g_aEnemy[nCntEnem].pos.z = (-MESHFIELD_SIZE * 2) + ENEMY_SIZE;
				}

				//プレイヤーとの距離が一定未満の場合攻撃を行う
				if (sqrtf((g_aEnemy[nCntEnem].pos.z - pPlayer->pos.z) * (g_aEnemy[nCntEnem].pos.z - pPlayer->pos.z) +
					(g_aEnemy[nCntEnem].pos.x - pPlayer->pos.x) * (g_aEnemy[nCntEnem].pos.x - pPlayer->pos.x)) < 50.0f)
				{
					AttackEnemy(nCntEnem, g_aEnemy[nCntEnem].nAttack);
				}

				//各種オブジェクトとの当たり判定
				CollisionObjectEnemy(nCntEnem);

				//エネミー同士の当たり判定
				CollisionEnemies(nCntEnem);
			}
			else if (g_aEnemy[nCntEnem].state == ENEMYSTATE_DEATH)
			{
				//回転の慣性の計算
				for (int nCntParts = 0; nCntParts < NUM_ENEMYPARTS; nCntParts++)
				{
					////回転の正規化
					//目的の角度が大きすぎたり小さすぎたりした時の計算
					//X
					if (g_aEnemy[nCntEnem].aModel[nCntParts].rotDest.x - g_aEnemy[nCntEnem].aModel[nCntParts].rot.x > D3DX_PI)
					{
						g_aEnemy[nCntEnem].aModel[nCntParts].rotDest.x -= D3DX_PI * 2.0f;
					}
					else if (g_aEnemy[nCntEnem].aModel[nCntParts].rotDest.x - g_aEnemy[nCntEnem].aModel[nCntParts].rot.x < -D3DX_PI)
					{
						g_aEnemy[nCntEnem].aModel[nCntParts].rotDest.x += D3DX_PI * 2.0f;
					}

					//Y
					if (g_aEnemy[nCntEnem].aModel[nCntParts].rotDest.y - g_aEnemy[nCntEnem].aModel[nCntParts].rot.y > D3DX_PI)
					{
						g_aEnemy[nCntEnem].aModel[nCntParts].rotDest.y -= D3DX_PI * 2.0f;
					}
					else if (g_aEnemy[nCntEnem].aModel[nCntParts].rotDest.y - g_aEnemy[nCntEnem].aModel[nCntParts].rot.y < -D3DX_PI)
					{
						g_aEnemy[nCntEnem].aModel[nCntParts].rotDest.y += D3DX_PI * 2.0f;
					}

					//回転の慣性の計算
					g_aEnemy[nCntEnem].aModel[nCntParts].rot.x += (g_aEnemy[nCntEnem].aModel[nCntParts].rotDest.x - g_aEnemy[nCntEnem].aModel[nCntParts].rot.x) * 0.05f;
					g_aEnemy[nCntEnem].aModel[nCntParts].rot.y += (g_aEnemy[nCntEnem].aModel[nCntParts].rotDest.y - g_aEnemy[nCntEnem].aModel[nCntParts].rot.y) * 0.05f;

					//計算結果が大きすぎたり小さすぎたりした時の調整
					if (g_aEnemy[nCntEnem].aModel[nCntParts].rot.x < -D3DX_PI)
					{
						g_aEnemy[nCntEnem].aModel[nCntParts].rot.x += D3DX_PI * 2.0f;
					}
					else if (g_aEnemy[nCntEnem].aModel[nCntParts].rot.x > D3DX_PI)
					{
						g_aEnemy[nCntEnem].aModel[nCntParts].rot.x -= D3DX_PI * 2.0f;
					}			

					if (g_aEnemy[nCntEnem].aModel[nCntParts].rot.y < -D3DX_PI)
					{
						g_aEnemy[nCntEnem].aModel[nCntParts].rot.y += D3DX_PI * 2.0f;
					}
					else if (g_aEnemy[nCntEnem].aModel[nCntParts].rot.y > D3DX_PI)
					{
						g_aEnemy[nCntEnem].aModel[nCntParts].rot.y -= D3DX_PI * 2.0f;
					}

					g_aEnemy[nCntEnem].aModel[nCntParts].pos += (g_aEnemy[nCntEnem].aModel[nCntParts].posDest - g_aEnemy[nCntEnem].aModel[nCntParts].pos) * 0.05f;
				}

				//死亡した敵が消えるまでの時間の設定
				static int nCnt = 120;

				nCnt--;

				if (nCnt <= 0)
				{
					g_aEnemy[nCntEnem].bUse = false;

					//敵が残っているかを判定
					RestEnemy();

					nCnt = 120;
				}
			}
		}
	}
}

//========================================================
//					エネミー描画処理
//========================================================
void DrawEnemy(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	//現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	for (int nCntEnem = 0; nCntEnem < MAX_ENEMY; nCntEnem++)
	{
		if (g_aEnemy[nCntEnem].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEnemy[nCntEnem].mtxWorld);

			//向きを反転
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy[nCntEnem].rot.y, g_aEnemy[nCntEnem].rot.x, g_aEnemy[nCntEnem].rot.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnem].mtxWorld, &g_aEnemy[nCntEnem].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCntEnem].pos.x, g_aEnemy[nCntEnem].pos.y, g_aEnemy[nCntEnem].pos.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnem].mtxWorld, &g_aEnemy[nCntEnem].mtxWorld, &mtxTrans);

			//階層構造（親子付け）
			for (int nCntPlayerParts = 0; nCntPlayerParts < NUM_ENEMYPARTS; nCntPlayerParts++)
			{
				//ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_aEnemy[nCntEnem].aModel[nCntPlayerParts].mtxWorld);

				//向きを反転
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy[nCntEnem].aModel[nCntPlayerParts].rot.y, g_aEnemy[nCntEnem].aModel[nCntPlayerParts].rot.x, g_aEnemy[nCntEnem].aModel[nCntPlayerParts].rot.z);
				D3DXMatrixMultiply(&g_aEnemy[nCntEnem].aModel[nCntPlayerParts].mtxWorld, &g_aEnemy[nCntEnem].aModel[nCntPlayerParts].mtxWorld, &mtxRot);

				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCntEnem].aModel[nCntPlayerParts].pos.x, g_aEnemy[nCntEnem].aModel[nCntPlayerParts].pos.y, g_aEnemy[nCntEnem].aModel[nCntPlayerParts].pos.z);
				D3DXMatrixMultiply(&g_aEnemy[nCntEnem].aModel[nCntPlayerParts].mtxWorld, &g_aEnemy[nCntEnem].aModel[nCntPlayerParts].mtxWorld, &mtxTrans);

				//自分の親モデルのマトリックスとの掛け算
				if (g_aEnemy[nCntEnem].aModel[nCntPlayerParts].ParentIdx < 0)
				{
					D3DXMatrixMultiply(&g_aEnemy[nCntEnem].aModel[nCntPlayerParts].mtxWorld, &g_aEnemy[nCntEnem].aModel[nCntPlayerParts].mtxWorld, &g_aEnemy[nCntEnem].mtxWorld);
				}
				else
				{
					D3DXMatrixMultiply(&g_aEnemy[nCntEnem].aModel[nCntPlayerParts].mtxWorld, &g_aEnemy[nCntEnem].aModel[nCntPlayerParts].mtxWorld, &g_aEnemy[nCntEnem].aModel[g_aEnemy[nCntEnem].aModel[nCntPlayerParts].ParentIdx].mtxWorld);
				}

				//ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnem].aModel[nCntPlayerParts].mtxWorld);

				//マテリアルデータのポインタを取得
				pMat = (D3DXMATERIAL*)g_aEnemy[nCntEnem].aModel[nCntPlayerParts].pBuffMat->GetBufferPointer();
				for (int nCntMat = 0; nCntMat < (int)g_aEnemy[nCntEnem].aModel[nCntPlayerParts].nNumMat; nCntMat++)
				{
					//マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//エネミーパーツの描画
					g_aEnemy[nCntEnem].aModel[nCntPlayerParts].pMesh->DrawSubset(nCntMat);
				}
			}
		}
	}

	//保持していたマテリアルを返す
	pDevice->SetMaterial(&matDef);
}

//========================================================
//					エネミーの設定処理
//========================================================
void SetEnemy(D3DXVECTOR3 pos,int nLife,int nAttack)
{
	for (int nCntEnem = 0; nCntEnem < MAX_ENEMY; nCntEnem++)
	{
		if (g_aEnemy[nCntEnem].bUse == false)
		{
			//ファイル読み込み
			LoadEnemyFile("data/enemy.txt", &g_aEnemy[nCntEnem].aModel[0]);

			//パーツの親番号の設定
			g_aEnemy[nCntEnem].aModel[0].ParentIdx = -1;				//胴体
			g_aEnemy[nCntEnem].aModel[1].ParentIdx = 0;					//頭
			g_aEnemy[nCntEnem].aModel[2].ParentIdx = 0;					//腕（右）
			g_aEnemy[nCntEnem].aModel[3].ParentIdx = 0;					//腕（左）
			g_aEnemy[nCntEnem].aModel[4].ParentIdx = 0;					//もも（右）
			g_aEnemy[nCntEnem].aModel[5].ParentIdx = 0;					//もも（左）
			g_aEnemy[nCntEnem].aModel[6].ParentIdx = 4;					//ふくらはぎ（右）
			g_aEnemy[nCntEnem].aModel[7].ParentIdx = 5;					//ふくらはぎ（左）

			//体
			g_aEnemy[nCntEnem].aModel[0].pos.y = 12.0f;
			g_aEnemy[nCntEnem].aModel[0].rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
			//頭
			g_aEnemy[nCntEnem].aModel[1].pos.y = 15.0f;
			g_aEnemy[nCntEnem].aModel[1].pos.z = 0.0f;
			g_aEnemy[nCntEnem].aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//右腕
			g_aEnemy[nCntEnem].aModel[2].pos.x = -10.0f;
			g_aEnemy[nCntEnem].aModel[2].pos.y = 12.0f;
			g_aEnemy[nCntEnem].aModel[2].rot.x = 0.0f;
			g_aEnemy[nCntEnem].aModel[2].rot.z = -30.0f;
			//左腕
			g_aEnemy[nCntEnem].aModel[3].pos.x = 10.0f;
			g_aEnemy[nCntEnem].aModel[3].pos.y = 12.0f;
			g_aEnemy[nCntEnem].aModel[3].rot.x = 0.0f;
			g_aEnemy[nCntEnem].aModel[3].rot.z = 30.0f;
			//右もも
			g_aEnemy[nCntEnem].aModel[4].pos.x = -5.0f;
			g_aEnemy[nCntEnem].aModel[4].pos.y = -12.0f;
			g_aEnemy[nCntEnem].aModel[4].pos.z = 0.0f;
			g_aEnemy[nCntEnem].aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//左もも
			g_aEnemy[nCntEnem].aModel[5].pos.x = 5.0f;
			g_aEnemy[nCntEnem].aModel[5].pos.y = -12.0f;
			g_aEnemy[nCntEnem].aModel[5].pos.z = 0.0f;
			g_aEnemy[nCntEnem].aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//右ふくらはぎ
			g_aEnemy[nCntEnem].aModel[6].pos.x = 0.1f;
			g_aEnemy[nCntEnem].aModel[6].pos.y = -18.0f;
			g_aEnemy[nCntEnem].aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//左ふくらはぎ
			g_aEnemy[nCntEnem].aModel[7].pos.x = -0.5f;
			g_aEnemy[nCntEnem].aModel[7].pos.y = -18.0f;
			g_aEnemy[nCntEnem].aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_aEnemy[nCntEnem].pos = pos;								//位置の設定
			g_aEnemy[nCntEnem].nEnemyLife = nLife;						//ライフの設定
			g_aEnemy[nCntEnem].nAttack = nAttack;						//攻撃力の設定
			g_aEnemy[nCntEnem].state = ENEMYSTATE_APPEAR;				//敵の状態を”出現”にする
			g_aEnemy[nCntEnem].nKey = rand() % 2;

			//影の設定
			g_aEnemy[nCntEnem].nIdxShadow = SetShadow(D3DXVECTOR3(g_aEnemy[nCntEnem].pos.x, 0.1f, g_aEnemy[nCntEnem].pos.z), g_aEnemy[nCntEnem].rot);

			g_aEnemy[nCntEnem].bUse = true;								//使用している状態にする

			break;
		}
	}
}

//========================================================
//			オブジェクト（モデル）との当たり判定
//========================================================
void CollisionObjectEnemy(int nIdxEnemy)
{
	MODEL *pModel = GetModel();

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (pModel->bUse == true)
		{
			D3DXVECTOR3 vtxMax = GetVtxMax(pModel->nType);
			D3DXVECTOR3 vtxMin = GetVtxMin(pModel->nType);

			//オブジェクト（モデル）との当たり判定
			if (pModel->pos.x + vtxMin.x >= g_aEnemy[nIdxEnemy].posOld.x + ENEMY_SIZE&&
				pModel->pos.x + vtxMin.x < g_aEnemy[nIdxEnemy].pos.x + ENEMY_SIZE&&
				pModel->pos.z + vtxMin.z < g_aEnemy[nIdxEnemy].pos.z + ENEMY_SIZE&&
				pModel->pos.z + vtxMax.z > g_aEnemy[nIdxEnemy].pos.z - ENEMY_SIZE)
			{
				g_aEnemy[nIdxEnemy].pos.x = pModel->pos.x + vtxMin.x - ENEMY_SIZE;
			}
			if ((pModel->pos.x + vtxMax.x + ENEMY_SIZE) <= g_aEnemy[nIdxEnemy].posOld.x &&
				(pModel->pos.x + vtxMax.x + ENEMY_SIZE) > g_aEnemy[nIdxEnemy].pos.x &&
				pModel->pos.z + vtxMin.z < g_aEnemy[nIdxEnemy].pos.z + ENEMY_SIZE&&
				pModel->pos.z + vtxMax.z > g_aEnemy[nIdxEnemy].pos.z - ENEMY_SIZE)
			{
				g_aEnemy[nIdxEnemy].pos.x = (pModel->pos.x + vtxMax.x + ENEMY_SIZE);
			}
			if (pModel->pos.z + vtxMin.z >= g_aEnemy[nIdxEnemy].posOld.z + ENEMY_SIZE&&
				pModel->pos.z + vtxMin.z < g_aEnemy[nIdxEnemy].pos.z + ENEMY_SIZE&&
				pModel->pos.x + vtxMin.x < g_aEnemy[nIdxEnemy].pos.x + ENEMY_SIZE&&
				pModel->pos.x + vtxMax.x > g_aEnemy[nIdxEnemy].pos.x - ENEMY_SIZE)
			{
				g_aEnemy[nIdxEnemy].pos.z = pModel->pos.z + vtxMin.z - ENEMY_SIZE;
			}
			if (pModel->pos.z + vtxMax.z <= g_aEnemy[nIdxEnemy].posOld.z - ENEMY_SIZE&&
				pModel->pos.z + vtxMax.z > g_aEnemy[nIdxEnemy].pos.z - ENEMY_SIZE&&
				pModel->pos.x + vtxMin.x < g_aEnemy[nIdxEnemy].pos.x + ENEMY_SIZE&&
				pModel->pos.x + vtxMax.x > g_aEnemy[nIdxEnemy].pos.x - ENEMY_SIZE)
			{
				g_aEnemy[nIdxEnemy].pos.z = pModel->pos.z + vtxMax.z + ENEMY_SIZE;
			}
		}
		pModel++;
	}
}

//========================================================
//				エネミー同士のあたり判定
//========================================================
void CollisionEnemies(int nIdxEnemy)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			if (g_aEnemy[nIdxEnemy].posOld.x >= g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE * 2&&
				g_aEnemy[nIdxEnemy].pos.x< g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE * 2 &&
				g_aEnemy[nIdxEnemy].pos.z> g_aEnemy[nCntEnemy].pos.z - ENEMY_SIZE * 2 &&
				g_aEnemy[nIdxEnemy].pos.z< g_aEnemy[nCntEnemy].pos.z + ENEMY_SIZE * 2)
			{
				g_aEnemy[nIdxEnemy].pos.x = g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE * 2;
			}
			if (g_aEnemy[nIdxEnemy].posOld.x <= g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE * 2 &&
				g_aEnemy[nIdxEnemy].pos.x> g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE * 2 &&
				g_aEnemy[nIdxEnemy].pos.z> g_aEnemy[nCntEnemy].pos.z - ENEMY_SIZE * 2 &&
				g_aEnemy[nIdxEnemy].pos.z< g_aEnemy[nCntEnemy].pos.z + ENEMY_SIZE * 2)
			{
				g_aEnemy[nIdxEnemy].pos.x = g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE * 2;
			}
			if (g_aEnemy[nIdxEnemy].posOld.z >= g_aEnemy[nCntEnemy].pos.z + ENEMY_SIZE * 2 &&
				g_aEnemy[nIdxEnemy].pos.z < g_aEnemy[nCntEnemy].pos.z + ENEMY_SIZE * 2 &&
				g_aEnemy[nIdxEnemy].pos.x > g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE * 2 &&
				g_aEnemy[nIdxEnemy].pos.x < g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE * 2)
			{
				g_aEnemy[nIdxEnemy].pos.z = g_aEnemy[nCntEnemy].pos.z + ENEMY_SIZE * 2;
			}
			if (g_aEnemy[nIdxEnemy].posOld.z <= g_aEnemy[nCntEnemy].pos.z - ENEMY_SIZE * 2 &&
				g_aEnemy[nIdxEnemy].pos.z > g_aEnemy[nCntEnemy].pos.z - ENEMY_SIZE * 2 &&
				g_aEnemy[nIdxEnemy].pos.x > g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE * 2 &&
				g_aEnemy[nIdxEnemy].pos.x < g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE * 2)
			{
				g_aEnemy[nIdxEnemy].pos.z = g_aEnemy[nCntEnemy].pos.z - ENEMY_SIZE * 2;
			}
		}
	}
}

//========================================================
//					弾と当たった時の処理
//========================================================
void HitBullet(int nIdxEnemy)
{
	//エネミーのライフを減少
	g_aEnemy[nIdxEnemy].nEnemyLife--;

	//エネミーのライフが0以下になった時
	if (g_aEnemy[nIdxEnemy].nEnemyLife <= 0)
	{
		//状態を”死亡”にする
		g_aEnemy[nIdxEnemy].state = ENEMYSTATE_DEATH;

		//パーツの親番号の設定
		g_aEnemy[nIdxEnemy].aModel[0].ParentIdx = -1;				//胴体
		g_aEnemy[nIdxEnemy].aModel[1].ParentIdx = -1;				//頭
		g_aEnemy[nIdxEnemy].aModel[2].ParentIdx = -1;				//腕（右）
		g_aEnemy[nIdxEnemy].aModel[3].ParentIdx = -1;				//腕（左）
		g_aEnemy[nIdxEnemy].aModel[4].ParentIdx = -1;				//もも（右）
		g_aEnemy[nIdxEnemy].aModel[5].ParentIdx = -1;				//もも（左）
		g_aEnemy[nIdxEnemy].aModel[6].ParentIdx = -1;				//ふくらはぎ（右）
		g_aEnemy[nIdxEnemy].aModel[7].ParentIdx = -1;				//ふくらはぎ（左）

		//体
		g_aEnemy[nIdxEnemy].aModel[0].posDest.y = -30.0f;
		g_aEnemy[nIdxEnemy].aModel[0].rotDest.x = 1.57f;
		//頭
		g_aEnemy[nIdxEnemy].aModel[1].posDest.y = -30.0f;
		g_aEnemy[nIdxEnemy].aModel[1].posDest.z = 30.0f;
		g_aEnemy[nIdxEnemy].aModel[1].rotDest.x = 1.57f;
		//右腕
		g_aEnemy[nIdxEnemy].aModel[2].posDest.x = -10.0f;
		g_aEnemy[nIdxEnemy].aModel[2].posDest.y = -30.0f;
		g_aEnemy[nIdxEnemy].aModel[2].rotDest.x = 1.57f;
		//左腕
		g_aEnemy[nIdxEnemy].aModel[3].posDest.x = 10.0f;
		g_aEnemy[nIdxEnemy].aModel[3].posDest.y = -30.0f;
		g_aEnemy[nIdxEnemy].aModel[3].rotDest.x = 1.57f;
		//右もも
		g_aEnemy[nIdxEnemy].aModel[4].posDest.x = -10.0f;
		g_aEnemy[nIdxEnemy].aModel[4].posDest.y = -30.0f;
		g_aEnemy[nIdxEnemy].aModel[4].posDest.z = -20.0f;
		g_aEnemy[nIdxEnemy].aModel[4].rotDest.x = 1.57f;
		g_aEnemy[nIdxEnemy].aModel[4].rotDest.y = 2.67f;
		//左もも
		g_aEnemy[nIdxEnemy].aModel[5].posDest.x = 10.0f;
		g_aEnemy[nIdxEnemy].aModel[5].posDest.y = -30.0f;
		g_aEnemy[nIdxEnemy].aModel[5].posDest.z = -20.0f;
		g_aEnemy[nIdxEnemy].aModel[5].rotDest.x = 1.57f;
		g_aEnemy[nIdxEnemy].aModel[5].rotDest.y = -1.26f;
		//右ふくらはぎ
		g_aEnemy[nIdxEnemy].aModel[6].posDest.x = -10.0f;
		g_aEnemy[nIdxEnemy].aModel[6].posDest.y = -30.0f;
		g_aEnemy[nIdxEnemy].aModel[6].rotDest.x = 1.57f;
		g_aEnemy[nIdxEnemy].aModel[6].rotDest.y = -1.57f;
		//左ふくらはぎ
		g_aEnemy[nIdxEnemy].aModel[7].posDest.x = -10.0f;
		g_aEnemy[nIdxEnemy].aModel[7].posDest.y = -30.0f;
		g_aEnemy[nIdxEnemy].aModel[7].rotDest.x = 1.57f;
		g_aEnemy[nIdxEnemy].aModel[7].rotDest.y = 1.57f;

		//影の消去
		DeleteShadow(g_aEnemy[nIdxEnemy].nIdxShadow);
	}
}

//========================================================
//					エネミーのモーション
//========================================================
void EnemyMotion(void)
{
	//モーション
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_NORMAL)
			{//移動モーション
				if (g_aEnemy[nCntEnemy].nKey == 0)
				{
					//右手・右足
					g_aEnemy[nCntEnemy].aModel[2].rot.x += 0.02f;

					//左手・左足
					g_aEnemy[nCntEnemy].aModel[3].rot.x -= 0.02f;

					if (g_aEnemy[nCntEnemy].aModel[2].rot.x >= 1.2f)
					{
						g_aEnemy[nCntEnemy].aModel[2].rot.x = 1.2f;
						g_aEnemy[nCntEnemy].aModel[3].rot.x = -1.2f;

						g_aEnemy[nCntEnemy].nKey = 1;
					}
				}
				else
				{
					//右手・右足
					g_aEnemy[nCntEnemy].aModel[2].rot.x -= 0.02f;

					//左手・左足
					g_aEnemy[nCntEnemy].aModel[3].rot.x += 0.02f;

					if (g_aEnemy[nCntEnemy].aModel[2].rot.x <= -1.2f)
					{
						g_aEnemy[nCntEnemy].aModel[2].rot.x = -1.2f;
						g_aEnemy[nCntEnemy].aModel[3].rot.x = 1.2f;

						g_aEnemy[nCntEnemy].nKey = 0;
					}
				}
			}
			else if(g_aEnemy[nCntEnemy].state == ENEMYSTATE_ATTACK)
			{//攻撃モーション
				if (g_aEnemy[nCntEnemy].nKey == 0)
				{
					//右手・右足
					g_aEnemy[nCntEnemy].aModel[2].rot.x += 0.04f;

					//左手・左足
					g_aEnemy[nCntEnemy].aModel[3].rot.x += 0.04f;

					if (g_aEnemy[nCntEnemy].aModel[2].rot.x >= 2.4f)
					{
						g_aEnemy[nCntEnemy].aModel[2].rot.x = 2.4f;
						g_aEnemy[nCntEnemy].aModel[3].rot.x = 2.4f;

						g_aEnemy[nCntEnemy].nKey = 1;
					}
				}
				else
				{
					//右手・右足
					g_aEnemy[nCntEnemy].aModel[2].rot.x -= 0.04f;

					//左手・左足
					g_aEnemy[nCntEnemy].aModel[3].rot.x -= 0.04f;

					if (g_aEnemy[nCntEnemy].aModel[2].rot.x <= 0.0f)
					{
						g_aEnemy[nCntEnemy].aModel[2].rot.x = 0.0f;
						g_aEnemy[nCntEnemy].aModel[3].rot.x = 0.0f;

						//g_aEnemy[nCntEnemy].nKey = 0;
						g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
					}
				}

			}
			
			if(g_aEnemy[nCntEnemy].state != ENEMYSTATE_DEATH)
			{
				if (g_aEnemy[nCntEnemy].nKey == 0)
				{
					//右手・右足
					g_aEnemy[nCntEnemy].aModel[4].rot.x -= 0.01f;

					//左手・左足
					g_aEnemy[nCntEnemy].aModel[5].rot.x += 0.01f;

					if (g_aEnemy[nCntEnemy].aModel[4].rot.x <= -0.6f)
					{
						g_aEnemy[nCntEnemy].aModel[4].rot.x = -0.6f;
						g_aEnemy[nCntEnemy].aModel[5].rot.x = 0.6f;
					}
				}
				else
				{
					//右手・右足
					g_aEnemy[nCntEnemy].aModel[4].rot.x += 0.01f;

					//左手・左足
					g_aEnemy[nCntEnemy].aModel[5].rot.x -= 0.01f;

					if (g_aEnemy[nCntEnemy].aModel[4].rot.x >= 0.6f)
					{
						g_aEnemy[nCntEnemy].aModel[4].rot.x = 0.6f;
						g_aEnemy[nCntEnemy].aModel[5].rot.x = -0.6f;
					}
				}

			}
		}
	}
}

//========================================================
//					エネミーの攻撃の処理
//========================================================
void AttackEnemy(int nIdxEnemy,int nAttack)
{
	g_aEnemy[nIdxEnemy].nAttackTime++;

	if (g_aEnemy[nIdxEnemy].nAttackTime >= 40)
	{
		//攻撃モーションに入る直前に腕の回転の初期位置を決めておく
		g_aEnemy[nIdxEnemy].aModel[2].rot.x = 0.0f;
		g_aEnemy[nIdxEnemy].aModel[3].rot.x = 0.0f;

		g_aEnemy[nIdxEnemy].state = ENEMYSTATE_ATTACK;
		g_aEnemy[nIdxEnemy].nAttackTime = 0;
		HitEnemyAttack(nAttack);
	}
	else
	{
		//g_aEnemy[nIdxEnemy].nAttackTime = 60;
	}
}

//========================================================
//					エネミー情報の取得
//========================================================
void RestEnemy(void)
{
	Round *pRound = GetRound();

	//エネミーが残って以下を判定する変数
	int nfalseEnemy = 0;

	//エネミーが残っているかを判定する処理
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			nfalseEnemy++;												//状態がfalseのエネミーの数を加算
		}
	}

	if (nfalseEnemy == MAX_ENEMY)
	{//状態がfalseのエネミーの数がMAX_ENEMYと同じだった場合
		pRound->nState = ROUND_INTERVAL;								//ラウンドの状態をROUND_INTERVALに変更
	}
}

//========================================================
//					エネミー情報の取得
//========================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}