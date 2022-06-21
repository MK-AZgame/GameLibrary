//========================================================
//
//	壁の処理[wall.h]
//	AUTHOR:越本愛彪
//
//========================================================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//プロトタイプ宣言
void InitWall(void);								//ポリゴン初期化処理
void UninitWall(void);								//ポリゴン終了処理
void UpdataWall(void);								//ポリゴン更新処理
void DrawWall(void);								//ポリゴン描画処理
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//壁の設定処理

#endif 


