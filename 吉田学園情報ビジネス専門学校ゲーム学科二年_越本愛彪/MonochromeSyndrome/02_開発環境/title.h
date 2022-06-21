//=============================================================================
//
// タイトルの処理 [title.h]
// Author : 越本　愛彪
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//[push enter]
typedef enum
{
	BUTTON_NONE = 0,	//何もしていない状態
	BUTTON_IN,			//フェードイン状態
	BUTTON_OUT,			//フェードアウト状態
	BUTTON_MAX
}BUTTON;

typedef enum
{
	SWITCH_NONE = 0,	//何もしていない状態
	SWITCH_ON,			//フェードイン状態
	SWITCH_OFF,			//フェードアウト状態
	SWITCH_MAX
}SWITCH;

//プロトタイプ宣言
void InitTitle(void);	//タイトルの初期化
void UninitTitle(void);	//タイトルの終了
void UpdataTitle(void);	//タイトルの更新
void DrawTitle(void);	//タイトルの描画

#endif 