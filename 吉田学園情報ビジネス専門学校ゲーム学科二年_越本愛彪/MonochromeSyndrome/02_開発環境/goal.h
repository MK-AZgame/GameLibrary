//=============================================================================
//
// ゴールの処理 [goal.cpp]
// Author : 越本　愛彪
//
//=============================================================================
#ifndef _GOAL_H_
#define _GOAL_H_

#include "main.h"
#include "player.h"

//プロトタイプ宣言
void InitGoal(void);				//ゴールの初期化
void UninitGoal(void);				//ゴールの終了
void UpdataGoal(void);				//ゴールの更新
void DrawGoal(void);				//ゴールの描画
void SetGoal(D3DXVECTOR3 pos);		//ゴールの設定
void ColisionGoal(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight);	//ゴールの当たり判定
void ScrollGoal(D3DXVECTOR3 move);	//ゴールのスクロール

#endif