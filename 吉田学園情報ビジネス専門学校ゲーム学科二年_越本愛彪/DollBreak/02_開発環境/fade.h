//========================================================
//
//	フェードの処理[fade.h]
//	AUTHOR:越本愛彪
//
//========================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"

//フェードの状態
typedef enum
{
	FADE_NONE = 0,							//何もしていない状態
	FADE_IN,								//フェードイン状態
	FADE_OUT,								//フェードアウト状態
	FADE_MAX
}FADE;

//プロトタイプ宣言
void InitFade(MODE modeNext);	//フェード初期化
void UninitFade(void);			//フェード終了
void UpdateFade(void);			//フェード更新
void DrawFade(void);			//フェード描画
void SetFade(MODE modeNext);	//フェード設定
FADE GetFade(void);				//フェード情報の取得

#endif
