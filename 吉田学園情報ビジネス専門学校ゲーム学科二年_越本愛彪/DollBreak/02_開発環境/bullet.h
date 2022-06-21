//========================================================
//
//	弾の処理[bullet.h]
//	AUTHOR:越本愛彪
//
//========================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;								//位置
	D3DXVECTOR3 move;								//移動量
	D3DXMATRIX  mtxWorld;							//ワールドマトリックス
	int nLife;										//寿命
	bool bUse;										//使用しているかどうか
}Bullet;

//プロトタイプ宣言
void Initbullet(void);								
void Uninitbullet(void);							
void Updatebullet(void);							
void Drawbullet(void);								
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//弾の設定
int GetBullet(void);								//弾の情報を取得

#endif
