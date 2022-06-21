//========================================================
//
//	プレイヤーの処理[player.h]
//	AUTHOR:越本愛彪
//
//========================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//マクロ定義
#define PLAYER_SIZE (20.0f)								//プレイヤーのサイズ

//プレイヤーの状態　列挙
typedef enum
{
	PLAYERSTATE_NORMAL = 0,
	PLAERSTATE_DEATH,
	PLAYERSTATE_RELOAD,
	PLAYERSTATE_MAX
}PLAYERSTATE;

//プレイヤー構造体
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 posOld;			//前回の位置
	D3DXVECTOR3 rot;			//向き
	D3DXVECTOR3 move;			//移動量
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	D3DXVECTOR3 rotDest;		//目的の向き
	PLAYERSTATE State;			//プレイヤーの状態
	int nLife;					//体力
} Player;

//モデル構造体
typedef struct
{
	LPD3DXMESH pMesh;			//メッシュへのポインタ
	LPD3DXBUFFER pBuffMat;		//頂点バッファへのポインタ
	DWORD nNumMat;				
	char modelfilename;			//モデルのファイル名
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	D3DXVECTOR3 pos;			//パーツの位置
	D3DXVECTOR3 rot;			//パーツの向き
	int ParentIdx;				//親の番号
	int nMaxModelNum;			//モデルの数
}ModelParts;

//プロトタイプ宣言
void InitPlayer(void);				//プレイヤーの初期化処理
void UninitPlayer(void);			//プレイヤーの終了処理
void UpdatePlayer(void);			//プレイヤーの更新処理
void DrawPlayer(void);				//プレイヤーの描画処理
void CollisionObject(void);			//オブジェクト（モデル）との当たり判定
void HitEnemyAttack(int nAttack);	//エネミーの攻撃が当たった時の処理
Player *GetPlayer(void);			//プレイヤーの情報の取得

#endif
