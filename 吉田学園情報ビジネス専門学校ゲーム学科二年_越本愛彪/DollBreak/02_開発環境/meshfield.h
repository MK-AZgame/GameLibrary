//========================================================
//
//	メッシュフィールドの処理[mashfield.h]
//	AUTHOR:越本愛彪
//
//========================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//マクロ定義
#define MESHFIELD_SIZE (150.0f)			//メッシュのサイズ

//プロトタイプ宣言
void InitMeshfield(void);				//ポリゴン初期化処理
void UninitMeshfield(void);				//ポリゴン終了処理
void UpdateMeshfield(void);				//ポリゴン更新処理
void DrawMeshfield(void);				//ポリゴン描画処理

#endif 


