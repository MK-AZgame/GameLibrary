//========================================================
//
//	爆発の処理[explosion.h]
//	AUTHOR:越本愛彪
//
//========================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//プロトタイプ宣言
void InitExplosion(void);			//爆発初期化
void UninitExplosion(void);			//爆発終了
void UpdateExplosion(void);			//爆発更新
void SetExplosion(D3DXVECTOR3 pos); //爆発設定

#endif