//========================================================
//
//	メインの処理[main.h]
//	AUTHOR:越本愛彪
//
//========================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#include <windows.h>
#include "d3dx9.h"
#define  DIRECTINPUT_VERSION (0x0800)
#include "dinput.h" 
#include "xinput.h"
#include "xaudio2.h"

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")													//システム時刻の取得に必要
#pragma comment(lib,"dinput8.lib")													//入力処理に必要
#pragma comment(lib,"xinput.lib")													//ジョイパッド処理に必要

//マクロ定義
#define SCREEN_WIDTH	 (1280)														//ウィンドウの幅
#define SCREEN_HEIGHT	 (720)														//ウィンドウの高さ
#define FVF_VERTEX_2D    (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)					//頂点フォーマット
#define FVF_VERTEX_3D	 (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)		//座標・法線・カラー

//頂点情報の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;				//頂点座標	
	float rhw;						//座標変換用係数
	D3DCOLOR col;					//頂点カラー
	D3DXVECTOR2 tex;				//テクスチャの座標
} VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;				//頂点座標
	D3DXVECTOR3 nor;				//法線ベクトル
	D3DCOLOR col;					//頂点カラー
	D3DXVECTOR2 tex;				//テクスチャの座標
} VERTEX_3D;

//画面モードの種類
typedef enum
{
	MODE_TITLE = 0,
	MODE_GAME,
	MODE_RESULT,
	MODE_TUTORIAL,
	MODE_RANKING,
	MODE_MAX
} MODE;

//プロトタイプ宣言
LPDIRECT3DDEVICE9 GetDevice(void);	//デバイスの取得
void SetMode(MODE mode);			//モードの設定

#endif
