//========================================================
//
//	デバッグラインの処理[line.h]
//	AUTHOR:越本愛彪
//
//========================================================
#ifndef _LINE_H_
#define _LINE_H_

#include "main.h"

//ライン構造体
typedef struct
{
	D3DXVECTOR3 pos;										//位置
	D3DXVECTOR3 rot;										//向き
	bool bUse;												//使用しているかどうか
	D3DXMATRIX mtxWorld;									//ワールドマトリックス
} Line;

void InitLine(void);										//ラインの初期化処理
void UninitLine(void);										//ラインの終了処理
void UpdateLine(void);										//ラインの更新処理
void DrawLine(void);										//ラインの描画処理
void SetLine(D3DXVECTOR3 pos,D3DXVECTOR3 rot,
				D3DXVECTOR3 startPos,D3DXVECTOR3 endPos);	//ラインの設定処理

#endif
