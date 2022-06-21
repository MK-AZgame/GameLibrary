//=============================================================================
//
// 入力の処理 [input.h]
// Author : 越本　愛彪
//
//=============================================================================
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
HRESULT InitJoypad(void);								//ジョイパッドの初期化
void UninitJoypad(void);								//ジョイパッドの終了
void UpdataJoypad(void);								//ジョイパッドの更新
bool GetJoypadPress(JOYKEY key);						//ジョイパッドが押されたときの情報を取得
bool GetJoypadTrigger(JOYKEY key);						//ジョイパッドが長押しされたときの情報を取得
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);	//キーボードの初期化
void UninitKeyboard(void);								//キーボードの終了
void UpdataKeyboard(void);								//キーボードの更新
bool GetKeyboardPress(int nKey);						//キーボードが押されたときの情報を取得
bool GetKeyboardTrigger(int nKey);						//キーボードが長押しされたときの情報を取得

#endif