//========================================================
//
//	カメラの処理[camera.h]
//	AUTHOR:越本愛彪
//
//========================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//マクロ定義
#define MAX_CAMERA (2)						//カメラの最大数

//カメラ構造体
typedef struct
{
	D3DXVECTOR3 posV;				//視点の位置
	D3DXVECTOR3 posR;				//注視点の位置
	D3DXVECTOR3 posVDest;			//視点の目的の位置
	D3DXVECTOR3 posRDest;			//注視点の目的の位置
	D3DXVECTOR3 vecU;
	D3DXVECTOR3 rot;				//角度
	D3DXVECTOR3 rotDest;			//目的の角度
	D3DXMATRIX  mtxProjection;
	D3DXMATRIX  mtxView;
	D3DVIEWPORT9 viewport;			//ビューポート
	float fDistance;				//距離
} Camera;

//プロトタイプ宣言
void InitCamera(void);				//カメラ初期化
void UninitCamera(void);			//カメラ終了
void UpdateCamera(void);			//カメラ更新
void SetCamera(int nIdxCamera);		//カメラ設定
Camera *GetCamera(void);			//カメラ情報の取得

#endif