//========================================================
//
//	プレイヤーモデルの処理[player.cpp]
//	AUTHOR:越本愛彪
//
//========================================================
#include <stdio.h>
#include "player.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "bullet.h"
#include "meshfield.h"
#include "model.h"
#include "loadfileh.h"
#include "fade.h"
#include "game.h"
#include "sound.h"

//マクロ定義
#define PLAYER_MOVE (1.0f)								//プレイヤーの移動量
#define PLAYER_ROTSPEED (0.1f)							//プレイヤーの回転の減衰量
#define ROT_PLAYERVIEW (0.075f)							//プレイヤーの回転に伴うカメラの回転量
#define NUM_PLAYERPARTS (4)								//プレイヤーを構成するパーツの数

//グローバル変数
int g_nIdxShadow;										//影のインデックス
Player g_player;										//プレイヤーの情報を格納
ModelParts g_ModelParts[NUM_PLAYERPARTS];				//モデルパーツの構造体
int g_nBulletInterval;									//次の弾を撃つまでのインターバル

//========================================================
//					プレイヤー初期化処理
//========================================================
void InitPlayer(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ファイル読み込み
	LoadMotionFile("data/motion.txt",&g_ModelParts[0]);

	//各情報の初期化
	g_player.pos = D3DXVECTOR3(-120.0f, 20.0f, 0.0f);	//位置の初期化
	g_player.rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);		//向きの初期化
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量の初期化
	g_player.State = PLAYERSTATE_NORMAL;				//プレイヤーの状態を”通常”に設定
	g_player.nLife = 10;								//体力を初期化
	g_nBulletInterval = 5;								//弾発射のインターバルの初期化				

	//パーツの親番号の設定
	g_ModelParts[0].ParentIdx = -1;						//胴体
	g_ModelParts[1].ParentIdx = 0;						//頭
	g_ModelParts[2].ParentIdx = 0;						//腕（左）
	g_ModelParts[3].ParentIdx = 0;						//腕（右）

	g_ModelParts[1].pos.y = 4.0f;

	g_player.rotDest.y = 0;								//目的の角度の初期化

	//影の設定
	g_nIdxShadow = SetShadow(D3DXVECTOR3(g_player.pos.x, 0.1f, g_player.pos.z), g_player.rot);
}

//========================================================
//					プレイヤー終了処理
//========================================================
void UninitPlayer(void)
{
	//メッシュの破棄
	if (g_ModelParts[0].pMesh != NULL)
	{
		g_ModelParts[0].pMesh->Release();
		g_ModelParts[0].pMesh = NULL;
	}

	//マテリアルの破棄
	if (g_ModelParts[0].pBuffMat != NULL)
	{
		g_ModelParts[0].pBuffMat->Release();
		g_ModelParts[0].pBuffMat = NULL;
	}
}

//========================================================
//					プレイヤー更新処理
//========================================================
void UpdatePlayer(void)
{
	Camera *pCamera = GetCamera();

	//弾の発射
	if (g_player.State == PLAYERSTATE_NORMAL)
	{
		if (GetMousePress(0))
		{
			g_nBulletInterval--;

			if (g_nBulletInterval <= 0)
			{
				SetBullet(D3DXVECTOR3(g_player.pos.x,g_player.pos.y - 5.0f,g_player.pos.z), D3DXVECTOR3(-sinf(g_player.rot.y), tanf(g_player.rot.x), -cosf(g_player.rot.y)));

				g_nBulletInterval = 10;
			}
		}

		//弾をリロードする
		if (GetKeyboardTrigger(DIK_R))
		{
			g_player.State = PLAYERSTATE_RELOAD;
			PlaySound(SOUND_LABEL_RELOAD);
		}
	}

	//プレイヤーにかかる重力
	g_player.move.y--;

	//posOldに現在の位置を保存
	g_player.posOld = g_player.pos;

	//マウスの移動量を取得
	D3DXVECTOR3 mouseMove = GetMouseMove();

	//移動量をノーマライズ
	D3DXVec3Normalize(&mouseMove, &mouseMove);

	g_player.rotDest.y += mouseMove.x / 25.0f;
	pCamera->rotDest.y += mouseMove.x / 25.0f;

	//プレイヤーの移動
	if (GetKeyboardPress(DIK_W))
	{//方向キーの上が押された
		if (GetKeyboardPress(DIK_D))
		{//右斜め
			g_player.move.x += sinf(pCamera->rot.y + (D3DX_PI * 0.25f)) * PLAYER_MOVE;
			g_player.move.z += cosf(pCamera->rot.y + (D3DX_PI * 0.25f)) * PLAYER_MOVE;
		}
		else if (GetKeyboardPress(DIK_A))
		{//左斜め
			g_player.move.x += sinf(pCamera->rot.y + (D3DX_PI * -0.25f)) * PLAYER_MOVE;
			g_player.move.z += cosf(pCamera->rot.y + (D3DX_PI * -0.25f)) * PLAYER_MOVE;
		}
		else if (GetKeyboardPress(DIK_LSHIFT))
		{
			g_player.move.x += sinf(pCamera->rot.y) * (PLAYER_MOVE + 1.0f);
			g_player.move.z += cosf(pCamera->rot.y) * (PLAYER_MOVE + 1.0f);
			g_player.rotDest.y = (pCamera->rot.y + (D3DX_PI));
		}
		else
		{//前
			g_player.move.x += sinf(pCamera->rot.y) * PLAYER_MOVE;
			g_player.move.z += cosf(pCamera->rot.y) * PLAYER_MOVE;
			g_player.rotDest.y = (pCamera->rot.y + (D3DX_PI));
		}
	}
	else if (GetKeyboardPress(DIK_S))
	{//方向キーの下が押された
		if (GetKeyboardPress(DIK_D))
		{//右斜め
			g_player.move.x += sinf(pCamera->rot.y + (D3DX_PI * 0.75f)) * PLAYER_MOVE;
			g_player.move.z += cosf(pCamera->rot.y + (D3DX_PI * 0.75f)) * PLAYER_MOVE;
		}
		else if (GetKeyboardPress(DIK_A))
		{//左斜め
			g_player.move.x += sinf(pCamera->rot.y + (D3DX_PI * -0.75f)) * PLAYER_MOVE;
			g_player.move.z += cosf(pCamera->rot.y + (D3DX_PI * -0.75f)) * PLAYER_MOVE;
		}
		else
		{//後ろ
			g_player.move.x -= sinf(pCamera->rot.y) * PLAYER_MOVE;
			g_player.move.z -= cosf(pCamera->rot.y) * PLAYER_MOVE;
			g_player.rotDest.y = (pCamera->rot.y + (D3DX_PI));
		}
	}
	else if (GetKeyboardPress(DIK_A))
	{//左
		g_player.move.x += sinf(pCamera->rot.y + (D3DX_PI * -0.5f)) * PLAYER_MOVE;
		g_player.move.z += cosf(pCamera->rot.y + (D3DX_PI * -0.5f)) * PLAYER_MOVE;
	}
	else if (GetKeyboardPress(DIK_D))
	{//右
		g_player.move.x += sinf(pCamera->rot.y + (D3DX_PI * 0.5f)) * PLAYER_MOVE;
		g_player.move.z += cosf(pCamera->rot.y + (D3DX_PI * 0.5f)) * PLAYER_MOVE;
	}
	//ジャンプ
	else if (GetKeyboardTrigger(DIK_SPACE))
	{
		g_player.move.y += 100.0f;
	}

	//プレイヤーの向きを前向きに固定
	g_player.rotDest.y = (pCamera->rot.y + (D3DX_PI));

	//慣性の追加
	g_player.move.x += (0.0f - g_player.move.x) * 0.5f;
	g_player.move.z += (0.0f - g_player.move.z) * 0.5f;

	//位置に移動量を加算
	g_player.pos += g_player.move;

	////回転の正規化
	//目的の角度が大きすぎたり小さすぎたりした時の計算
	if (g_player.rotDest.y - g_player.rot.y > D3DX_PI)
	{
		g_player.rotDest.y -= D3DX_PI * 2.0f;
	}
	else if (g_player.rotDest.y - g_player.rot.y < -D3DX_PI)
	{
		g_player.rotDest.y += D3DX_PI * 2.0f;
	}

	//慣性の計算
	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * PLAYER_ROTSPEED;

	//計算結果が大きすぎたり小さすぎたりした時の調整
	if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y += D3DX_PI * 2.0f;
	}
	else if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2.0f;
	}

	//影の更新
	SetPositionShadow(g_nIdxShadow, D3DXVECTOR3(g_player.pos.x, 0.1f, g_player.pos.z));

	//行動範囲制限(壁との当たり判定)
	if (g_player.pos.x + PLAYER_SIZE >= MESHFIELD_SIZE * 2)
	{//右
		if (g_player.pos.z + PLAYER_SIZE >= MESHFIELD_SIZE * 2)
		{//右奥
			g_player.pos.x = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
			g_player.pos.z = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
		}
		else if (g_player.pos.z - PLAYER_SIZE <= -MESHFIELD_SIZE * 2)
		{//右手前
			g_player.pos.x = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
			g_player.pos.z = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
		}
		else
		{
			g_player.pos.x = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
		}
	}
	else if (g_player.pos.x - PLAYER_SIZE <= -MESHFIELD_SIZE * 2)
	{//左
		if (g_player.pos.z + PLAYER_SIZE >= MESHFIELD_SIZE * 2)
		{//左奥
			g_player.pos.x = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
			g_player.pos.z = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
		}
		else if (g_player.pos.z - PLAYER_SIZE <= -MESHFIELD_SIZE * 2)
		{//右手前
			g_player.pos.x = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
			g_player.pos.z = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
		}
		else
		{
			g_player.pos.x = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
		}
	}
	else if (g_player.pos.z + PLAYER_SIZE >= MESHFIELD_SIZE * 2)
	{//奥
		g_player.pos.z = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
	}
	else if (g_player.pos.z - PLAYER_SIZE <= (-MESHFIELD_SIZE * 2))
	{//手前
		g_player.pos.z = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
	}

	//床との当たり判定
	if (g_player.pos.y - PLAYER_SIZE * 2 <= 0.1f||g_player.pos.y - PLAYER_SIZE * 2 >= -0.1f)
	{
		g_player.pos.y = 0.0f + PLAYER_SIZE * 2;
	}

	CollisionObject();
}

//========================================================
//					プレイヤー描画処理
//========================================================
void DrawPlayer(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_player.mtxWorld);

	//向きを反転
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	//現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	//階層構造（親子付け）
	for (int nCntPlayerParts = 0; nCntPlayerParts < NUM_PLAYERPARTS; nCntPlayerParts++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_ModelParts[nCntPlayerParts].mtxWorld);

		//向きを反転
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ModelParts[nCntPlayerParts].rot.y, g_ModelParts[nCntPlayerParts].rot.x, g_ModelParts[nCntPlayerParts].rot.z);
		D3DXMatrixMultiply(&g_ModelParts[nCntPlayerParts].mtxWorld, &g_ModelParts[nCntPlayerParts].mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_ModelParts[nCntPlayerParts].pos.x, g_ModelParts[nCntPlayerParts].pos.y, g_ModelParts[nCntPlayerParts].pos.z);
		D3DXMatrixMultiply(&g_ModelParts[nCntPlayerParts].mtxWorld, &g_ModelParts[nCntPlayerParts].mtxWorld, &mtxTrans);

		//自分の親モデルのマトリックスとの掛け算
		if (g_ModelParts[nCntPlayerParts].ParentIdx < 0)
		{
			D3DXMatrixMultiply(&g_ModelParts[nCntPlayerParts].mtxWorld, &g_ModelParts[nCntPlayerParts].mtxWorld, &g_player.mtxWorld);
		}
		else
		{
			D3DXMatrixMultiply(&g_ModelParts[nCntPlayerParts].mtxWorld, &g_ModelParts[nCntPlayerParts].mtxWorld, &g_ModelParts[g_ModelParts[nCntPlayerParts].ParentIdx].mtxWorld);
		}

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_ModelParts[nCntPlayerParts].mtxWorld);

		//マテリアルデータのポインタを取得
		pMat = (D3DXMATERIAL*)g_ModelParts[nCntPlayerParts].pBuffMat->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (int)g_ModelParts[nCntPlayerParts].nNumMat; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//プレイヤーパーツの描画
			g_ModelParts[nCntPlayerParts].pMesh->DrawSubset(nCntMat);
		}
	}

	//保持していたマテリアルを返す
	pDevice->SetMaterial(&matDef);
}

//========================================================
//			オブジェクト（モデル）との当たり判定
//========================================================
void CollisionObject(void)
{
	MODEL *pModel = GetModel();

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (pModel->bUse == true)
		{
			D3DXVECTOR3 vtxMax = GetVtxMax(pModel->nType);
			D3DXVECTOR3 vtxMin = GetVtxMin(pModel->nType);

			//オブジェクト（モデル）との当たり判定
			if (pModel->pos.x + vtxMin.x >= g_player.posOld.x + PLAYER_SIZE&&
				pModel->pos.x + vtxMin.x < g_player.pos.x + PLAYER_SIZE&&
				pModel->pos.z + vtxMin.z < g_player.pos.z + PLAYER_SIZE&&
				pModel->pos.z + vtxMax.z > g_player.pos.z - PLAYER_SIZE)
			{
				g_player.pos.x = pModel->pos.x + vtxMin.x - PLAYER_SIZE;
			}
			if ((pModel->pos.x + vtxMax.x + PLAYER_SIZE) <= g_player.posOld.x &&
				(pModel->pos.x + vtxMax.x + PLAYER_SIZE) > g_player.pos.x &&
				pModel->pos.z + vtxMin.z < g_player.pos.z + PLAYER_SIZE&&
				pModel->pos.z + vtxMax.z > g_player.pos.z - PLAYER_SIZE)
			{
				g_player.pos.x = (pModel->pos.x + vtxMax.x + PLAYER_SIZE);
			}
			if (pModel->pos.z + vtxMin.z >= g_player.posOld.z + PLAYER_SIZE&&
				pModel->pos.z + vtxMin.z < g_player.pos.z + PLAYER_SIZE&&
				pModel->pos.x + vtxMin.x < g_player.pos.x + PLAYER_SIZE&&
				pModel->pos.x + vtxMax.x > g_player.pos.x - PLAYER_SIZE)
			{
				g_player.pos.z = pModel->pos.z + vtxMin.z - PLAYER_SIZE;
			}
			if (pModel->pos.z + vtxMax.z <= g_player.posOld.z - PLAYER_SIZE&&
				pModel->pos.z + vtxMax.z > g_player.pos.z - PLAYER_SIZE&&
				pModel->pos.x + vtxMin.x < g_player.pos.x + PLAYER_SIZE&&
				pModel->pos.x + vtxMax.x > g_player.pos.x - PLAYER_SIZE)
			{
				g_player.pos.z = pModel->pos.z + vtxMax.z + PLAYER_SIZE;
			}
		}
		pModel++;
	}

}

//========================================================
//				エネミーの攻撃が当たった時の処理
//========================================================
void HitEnemyAttack(int nAttack)
{
	GAMESTATE &pState = *GetGameState();
	FADE fade = GetFade();

	g_player.nLife -= nAttack;

	if (g_player.nLife <= 0)
	{
		if (fade == FADE_NONE)
		{
			pState = GAMESTATE_END;
			SetFade(MODE_RESULT);
		}
	}
}

//========================================================
//				プレイヤー情報の取得
//========================================================
Player *GetPlayer(void)
{
	return &g_player;
}