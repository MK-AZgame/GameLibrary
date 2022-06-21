//========================================================
//
//	影の処理[shadow.h]
//	AUTHOR:越本愛彪
//
//========================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//影の構造体
typedef struct
{
	D3DXVECTOR3 pos;										//位置
	D3DXVECTOR3 rot;										//向き
	D3DXMATRIX mtxWorld;									//ワールドマトリックス
	bool bUse;												//使っているかどうか
} Shadow;

//プロトタイプ宣言
void InitShadow(void);										//影初期化処理
void UninitShadow(void);									//影終了処理
void UpdataShadow(void);									//影更新処理
void DrawShadow(void);										//影描画処理
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			//影の設定処理
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);	//影の座標更新の処理
void DeleteShadow(int nIdxShadow);							//影を消す処理

#endif 

