//=============================================================================
//
// フェードの処理 [fade.h]
// Author : 越本　愛彪
//
//=============================================================================
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
void InitFade(MODE modeNext);	//フェードの初期化
void UninitFade(void);			//フェードの終了
void UpdataFade(void);			//フェードの更新
void DrawFade(void);			//フェードの描画
void SetFade(MODE modeNext);	//フェードの設定
FADE GetFade(void);				//フェード情報の取得

#endif