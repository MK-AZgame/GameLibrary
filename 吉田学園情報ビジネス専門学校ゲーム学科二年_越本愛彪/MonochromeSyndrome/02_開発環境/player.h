//=============================================================================
//
// プレイヤーの処理 [player.h]
// Author : 越本　愛彪
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

#define PLAYER_WIDTH  (20.0f)									//プレイヤーの横幅
#define PLAYER_HEIGHT (20.0f)									//プレイヤーの高さ
#define PLAYER_MOVE   (1.0f)									//プレイヤーの移動量

//プレイヤーの状態を管理
typedef enum
{
	PLAYERSTATE_NORMAL = 0,
	PLAYERSTATE_JUMP,
	PLAYERSTATE_DEATH,
	PLAYERSTATE_MAX
} PLAYERSTATE;

//プレイヤー構造体
typedef struct
{
	D3DXVECTOR3 pos;											//プレイヤーの座標
	D3DXVECTOR3 posOld;											//プレイヤーの前回の位置
	D3DXVECTOR3 move;											//プレイヤーの移動量
	PLAYERSTATE state;											//プレイヤーの状態
	int nCounterAnim;											//アニメーションカウンター
	int nPatternAnim;											//アニメーションパターン
	int nDirectionMove;											//向き(0：右移動中　1：左移動中)
	int nLife;													//プレイヤーのライフ
	bool bDisp;													//表示するかどうか
} Player;

//プロトタイプ宣言
void InitPlayer(void);											//プレイヤーの初期化
void UninitPlayer(void);										//プレイヤーの終了
void UpdataPlayer(void);										//プレイヤーの更新
void DrawPlayer(void);											//プレイヤーの描画
bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight);	//プレイヤーの当たり判定
void SetPlayerPos(D3DXVECTOR3 pos);								//プレイヤー位置の設定
Player *GetPlayer(void);										//プレイヤー情報の取得

#endif