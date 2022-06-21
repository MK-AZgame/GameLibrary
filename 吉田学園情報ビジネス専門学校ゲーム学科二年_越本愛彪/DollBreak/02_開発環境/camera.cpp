//========================================================
//
//	カメラの処理[camera.cpp]
//	AUTHOR:越本愛彪
//
//========================================================
#include "camera.h"
#include "input.h"
#include "player.h"

//カメラの種類
typedef enum
{
	CAMERATYPE_PLAYER = 0,
	CAMERATYPE_MAP,
	CAMERATYPE_MAX
}CAMERATYPE;

//グローバル変数
int g_nCntTime;								//プレイヤーが動いていない時間（待機時間）の加算用
Camera g_camera[MAX_CAMERA];				//カメラ情報

//========================================================
//					カメラ初期化処理
//========================================================
void InitCamera(void)
{
	////ビューポート構成の保存
	//プレイヤー視点
	g_camera[CAMERATYPE_PLAYER].viewport.X = 0.0f;
	g_camera[CAMERATYPE_PLAYER].viewport.Y = 0.0f;
	g_camera[CAMERATYPE_PLAYER].viewport.Width = SCREEN_WIDTH;
	g_camera[CAMERATYPE_PLAYER].viewport.Height = SCREEN_HEIGHT;
	g_camera[CAMERATYPE_PLAYER].viewport.MinZ = 0.0f;
	g_camera[CAMERATYPE_PLAYER].viewport.MaxZ = 1.0f;

	//マップ
	g_camera[1].viewport.X = 10.0f;
	g_camera[1].viewport.Y = 10.0f;
	g_camera[1].viewport.Width = 240.0f;
	g_camera[1].viewport.Height = 240.0f;
	g_camera[1].viewport.MinZ = 0.0f;
	g_camera[1].viewport.MaxZ = 1.0f;

	//視点・注視点・上方向を設定する
	g_camera[CAMERATYPE_PLAYER].posV = D3DXVECTOR3(0.0f,100.0f,-100.0f);
	g_camera[CAMERATYPE_PLAYER].posR = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_camera[CAMERATYPE_PLAYER].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera[CAMERATYPE_PLAYER].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera[CAMERATYPE_PLAYER].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera[CAMERATYPE_PLAYER].fDistance = sqrtf((g_camera[CAMERATYPE_PLAYER].posR.z - g_camera[CAMERATYPE_PLAYER].posV.z) * (g_camera[CAMERATYPE_PLAYER].posR.z - g_camera[CAMERATYPE_PLAYER].posV.z) +
		(g_camera[CAMERATYPE_PLAYER].posR.x - g_camera[CAMERATYPE_PLAYER].posV.x) * (g_camera[CAMERATYPE_PLAYER].posR.x - g_camera[CAMERATYPE_PLAYER].posV.x));

	g_camera[1].posV = D3DXVECTOR3(0.0f, 750.0f, 0.01f);
	g_camera[1].posR = D3DXVECTOR3(0.0f, 0.0f, -0.05f);
	g_camera[1].vecU = D3DXVECTOR3(0.0f, -0.1f, 0.0f);
	g_camera[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera[1].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera[1].fDistance = sqrtf((g_camera[1].posR.z - g_camera[1].posV.z) * (g_camera[1].posR.z - g_camera[1].posV.z) +
		(g_camera[1].posR.x - g_camera[1].posV.x) * (g_camera[1].posR.x - g_camera[1].posV.x));

}

//========================================================
//					カメラ終了処理
//========================================================
void UninitCamera(void)
{

}

//========================================================
//					カメラ更新処理
//========================================================
void UpdateCamera(void)
{
	Player *pPlayer = GetPlayer();

	//カメラの追従処理
	g_camera[CAMERATYPE_PLAYER].posRDest.x = pPlayer->pos.x + sinf(g_camera[0].rot.y) * 100.0f;
	g_camera[CAMERATYPE_PLAYER].posRDest.y = pPlayer->pos.y;
	g_camera[CAMERATYPE_PLAYER].posRDest.z = pPlayer->pos.z + cosf(g_camera[0].rot.y) * 100.0f;

	g_camera[CAMERATYPE_PLAYER].posVDest.x = pPlayer->pos.x - sinf(pPlayer->rot.y) * 1.0f;
	g_camera[CAMERATYPE_PLAYER].posVDest.y = pPlayer->pos.y;
	g_camera[CAMERATYPE_PLAYER].posVDest.z = pPlayer->pos.z - cosf(pPlayer->rot.y) * 1.0f;

	g_camera[CAMERATYPE_PLAYER].posR += (g_camera[CAMERATYPE_PLAYER].posRDest - g_camera[CAMERATYPE_PLAYER].posR) * 0.2f;
	g_camera[CAMERATYPE_PLAYER].posV += (g_camera[CAMERATYPE_PLAYER].posVDest - g_camera[CAMERATYPE_PLAYER].posV) * 0.2f;
	g_camera[CAMERATYPE_PLAYER].rot.y += (g_camera[CAMERATYPE_PLAYER].rotDest.y - g_camera[CAMERATYPE_PLAYER].rot.y) * 0.2f;

	//カメラ回転の正規化
	if (g_camera[CAMERATYPE_PLAYER].rot.y < -D3DX_PI)
	{
		g_camera[CAMERATYPE_PLAYER].rot.y += D3DX_PI * 2.0f;
	}
	else if (g_camera[CAMERATYPE_PLAYER].rot.y > D3DX_PI)
	{
		g_camera[CAMERATYPE_PLAYER].rot.y -= D3DX_PI * 2.0f;
	}

	if (g_camera[CAMERATYPE_PLAYER].rotDest.y - g_camera[CAMERATYPE_PLAYER].rot.y > D3DX_PI)
	{
		g_camera[CAMERATYPE_PLAYER].rotDest.y -= D3DX_PI * 2.0f;
	}
	else if (g_camera[CAMERATYPE_PLAYER].rotDest.y - g_camera[CAMERATYPE_PLAYER].rot.y < -D3DX_PI)
	{
		g_camera[CAMERATYPE_PLAYER].rotDest.y += D3DX_PI * 2.0f;
	}
}

//========================================================
//					カメラ設定処理
//========================================================
void SetCamera(int nIdxCamera)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ビューポートの設定
	pDevice->SetViewport(&g_camera[nIdxCamera].viewport);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera[nIdxCamera].mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera[nIdxCamera].mtxView,
		&g_camera[nIdxCamera].posV,
		&g_camera[nIdxCamera].posR,
		&g_camera[nIdxCamera].vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera[nIdxCamera].mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera[nIdxCamera].mtxProjection);
		
	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_camera[nIdxCamera].mtxProjection,
		D3DXToRadian(75.0f - (nIdxCamera * 30.0f)),
		(float)g_camera[nIdxCamera].viewport.Width / (float)g_camera[nIdxCamera].viewport.Height,
		10.0f,
		1000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera[nIdxCamera].mtxProjection);
}

//========================================================
//				カメラ情報を取得
//========================================================
Camera *GetCamera(void)
{
	return &g_camera[0];
}
