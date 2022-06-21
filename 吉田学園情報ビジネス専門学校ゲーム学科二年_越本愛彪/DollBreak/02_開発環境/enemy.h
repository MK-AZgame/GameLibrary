//========================================================
//
//	エネミーの処理[enemy.h]
//	AUTHOR:越本愛彪
//
//========================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

#define NUM_ENEMYPARTS (8)					//エネミーを構成するパーツの数

//エネミー状態の列挙型
typedef enum
{
	ENEMYSTATE_NORMAL = 0,					//通常			
	ENEMYSTATE_APPEAR,						//出現する
	ENEMYSTATE_HIT,							//弾が当たった
	ENEMYSTATE_ATTACK,						//攻撃中
	ENEMYSTATE_DEATH,						//死亡
	ENEMYSTATE_MAX
}ENEMYSTATE;

//モデル構造体
typedef struct
{
	LPD3DXMESH pMesh;						//メッシュへのポインタ
	LPD3DXBUFFER pBuffMat;					//頂点バッファへのポインタ
	DWORD nNumMat;
	char modelfilename;						//モデルのファイル名
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	D3DXVECTOR3 pos;						//パーツの位置
	D3DXVECTOR3 posDest;					//パーツの目的の位置
	D3DXVECTOR3 rot;						//パーツの向き
	D3DXVECTOR3 rotDest;					//目的の向き
	int ParentIdx;							//親の番号
	int nMaxModelNum;						//モデルの数
}EnemyModel;

//エネミー構造体
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 posOld;						//前回の位置
	D3DXVECTOR3 move;						//移動量
	D3DXVECTOR3 rot;						//向き
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	D3DXVECTOR3 rotDest;					//目的の向き
	ENEMYSTATE state;						//エネミーの状態
	int nEnemyLife;							//エネミーの体力
	int nIdxShadow;							//影のインデックス
	int nAttack;							//敵の攻撃力
	int nAttackTime;						//攻撃の間隔
	int nKey;								//モーションの切り替え
	bool bUse;								//使用されているかどうか
	EnemyModel aModel[NUM_ENEMYPARTS];		//エネミーのモデル
} Enemy;

//マクロ定義
#define ENEMY_SIZE (20.0f)					//エネミーのサイズ
#define MAX_ENEMY (128)						//敵の最大数

//プロトタイプ宣言
void InitEnemy(void);						
void UninitEnemy(void);						
void UpdateEnemy(void);						
void DrawEnemy(void);						
void CollisionObjectEnemy(int nIdxEnemy);	//オブジェクト（モデル）との当たり判定
void CollisionEnemies(int nIdxEnemy);		//エネミー同士の当たり判定
void HitBullet(int nIdxEnemy);				//弾との当たり判定
void SetEnemy(D3DXVECTOR3 pos,int nLife,
	int nAttack);							//エネミーの設定処理
void EnemyMotion(void);						//エネミーのモーション
void AttackEnemy(int nIdxEnemy,
	int nAttack);							//エネミーの攻撃の処理
void RestEnemy(void);						//エネミーの残りを判定
Enemy *GetEnemy(void);						//エネミーの情報の取得

#endif