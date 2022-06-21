//========================================================
//
//	モデルの処理[model.h]
//	AUTHOR:越本愛彪
//
//========================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//マクロ定義
#define MAX_MODEL (128)				//モデルの最大数
#define MAX_MODELTYPE (1)			//モデルの種類の最大数

//モデル構造体
typedef struct
{
	D3DXVECTOR3 pos;				//モデルの位置
	D3DXVECTOR3 rot;				//モデルの角度
	D3DXMATRIX mtxWorld;			//ワールドマトリックス
	int nType;						//モデルの種類
	bool bUse;						//使用されているかどうか
}MODEL;

//モデル情報の構造体
typedef struct
{
	LPD3DXMESH pMeshModel;
	LPD3DXBUFFER pBuffMatModel;
	DWORD nNumMatModel;
	D3DXVECTOR3 vtxMin, vtxMax;		//モデルの頂点の最大値・最小値
}ModelInfo;

//プロトタイプ宣言
void InitModel(void);				//モデル初期化処理
void UninitModel(void);				//モデル終了処理
void UpdateModel(void);				//モデル更新処理
void DrawModel(void);				//モデル描画処理
void SetModel(D3DXVECTOR3 pos);		//モデルの設定処理
D3DXVECTOR3 GetVtxMax(int nType);	//モデルのサイズの最大値を取得する
D3DXVECTOR3 GetVtxMin(int nType);	//モデルのサイズの最小値を取得する
MODEL *GetModel(void);				//モデルの情報を取得する		

#endif