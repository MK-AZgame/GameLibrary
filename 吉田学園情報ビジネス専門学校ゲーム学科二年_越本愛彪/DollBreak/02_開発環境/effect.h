//========================================================
//
//	エフェクトの処理[effect.h]
//	AUTHOR:越本愛彪
//
//========================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//エフェクトの構造体
typedef struct
{
	D3DXVECTOR3 pos;				//位置
	D3DXVECTOR3 move;				//移動量
	D3DXVECTOR3 rot;				//向き
	float fRadius;					//半径
	D3DXCOLOR	col;				//色
	D3DXMATRIX mtxWorld;			//ワールドマトリックス
	int nLife;						//エフェクトの寿命
	bool bUse;						//使っているかどうか
} Effect;

//プロトタイプ宣言
void InitEffect(void);																	//エフェクト初期化処理
void UninitEffect(void);																//エフェクト終了処理
void UpdateEffect(void);																//エフェクト更新処理
void DrawEffect(void);																	//エフェクト描画処理
void SetEffect(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXCOLOR col,float rad,int nLife);	//エフェクトの設定処理

#endif 