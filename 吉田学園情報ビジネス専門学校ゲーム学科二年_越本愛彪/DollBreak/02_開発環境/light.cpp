//========================================================
//
//	ライトの処理[light.cpp]
//	AUTHOR:越本愛彪
//
//========================================================
#include "main.h"
#include "light.h"

//マクロ定義
#define MAX_LIGHT (3)							//ライトの最大数

//グローバル変数
D3DLIGHT9 g_aLight[MAX_LIGHT];					//ライト情報を格納

//========================================================
//					ライト初期化処理
//========================================================
void InitLight(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXVECTOR3 vecDir[MAX_LIGHT];				//ライト方向ベクトル

	//ライトをクリアする
	ZeroMemory(&g_aLight[0], sizeof(g_aLight));

	////ライト1
	//ライトの種類設定
	g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	//ライトの拡散光を設定
	g_aLight[0].Diffuse = D3DXCOLOR(1.0f, 0.8f, 0.7f, 1.0f);

	//ライトの方向を指定
	vecDir[0] = D3DXVECTOR3(1.57f, -0.6f, -0.9f);

	//正規化する
	D3DXVec3Normalize(&vecDir[0], &vecDir[0]);
	g_aLight[0].Direction = vecDir[0];

	//ライトを設定する
	pDevice->SetLight(0,&g_aLight[0]);

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);

	////ライト2
	//ライトの種類設定
	g_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	//ライトの拡散光を設定
	g_aLight[1].Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

	//ライトの方向を指定
	vecDir[1] = D3DXVECTOR3(0.6f, 1.0f, -1.57f);

	//正規化する
	D3DXVec3Normalize(&vecDir[1], &vecDir[1]);
	g_aLight[1].Direction = vecDir[1];

	//ライトを設定する
	pDevice->SetLight(1, &g_aLight[1]);

	//ライトを有効にする
	pDevice->LightEnable(1, TRUE);

	////ライト3
	//ライトの種類設定
	g_aLight[2].Type = D3DLIGHT_DIRECTIONAL;

	//ライトの拡散光を設定
	g_aLight[2].Diffuse = D3DXCOLOR(0.6f, 0.4f, 0.3f, 1.0f);

	//ライトの方向を指定
	vecDir[2] = D3DXVECTOR3(-1.57f, -0.2f, 0.9f);

	//正規化する
	D3DXVec3Normalize(&vecDir[2], &vecDir[2]);
	g_aLight[2].Direction = vecDir[2];

	//ライトを設定する
	pDevice->SetLight(2, &g_aLight[2]);

	//ライトを有効にする
	pDevice->LightEnable(2, TRUE);
}

//========================================================
//					ライト終了処理
//========================================================
void UninitLight()
{

}

//========================================================
//					ライト更新処理
//========================================================
void UpdateLight()
{

}