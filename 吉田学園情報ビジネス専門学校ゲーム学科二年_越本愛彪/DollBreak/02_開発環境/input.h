//========================================================
//
//	入力の処理[input.h]
//	AUTHOR:越本愛彪
//
//========================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include"main.h"

//キーの種類
typedef enum
{
	JOYKEY_UP = 0,				//上
	JOYKEY_DOWN,				//下
	JOYKEY_LEFT,				//左
	JOYKEY_RIGHT,				//右
	JOYKEY_START,
	JOYKEY_BACK,
	JOYKEY_L3,
	JOYKEY_R3,
	JOYKEY_L1,
	JOYKEY_R1,					//弾の発射
	JOYKEY_L2,
	JOYKEY_R2,
	JOYKEY_A,
	JOYKEY_B,
	JOYKEY_X,
	JOYKEY_Y,
	JOYKEY_MAX
} JOYKEY;

//プロトタイプ宣言
HRESULT InitJoypad(void);								//ジョイパッドの初期化処理
void UninitJoypad(void);								//ジョイパッドの終了処理
void UpdateJoypad(void);								//ジョイパッドの更新処理
bool GetJoypadPress(JOYKEY key);						//ジョイパッドのプレス情報を取得
bool GetJoypadTrigger(JOYKEY key);						//ジョイパッドのトリガー情報を取得
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);	//キーボードの初期化処理
void UninitKeyboard(void);								//キーボードの終了処理
void UpdateKeyboard(void);								//キーボードの更新処理
bool GetKeyboardPress(int nKey);						//キーボードのプレス情報を取得
bool GetKeyboardTrigger(int nKey);						//キーボードのトリガー情報を取得
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);		//マウスの初期化処理
void UninitMouse(void);									//マウスの終了処理
void UpdateMouse(void);									//マウスの更新処理
bool GetMousePress(int nMouse);							//マウスのプレス情報を取得
bool GetMouseTrigger(int nMouse);						//マウスのトリガー情報を取得
D3DXVECTOR3 GetMouseMove(void);							//マウスの移動量の取得

#endif


