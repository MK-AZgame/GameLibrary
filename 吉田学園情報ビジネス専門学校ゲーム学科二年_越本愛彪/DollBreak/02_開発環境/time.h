//================================================================
//
//	タイムの処理[time.h]
//	Author:越本愛彪
//
//================================================================
#ifndef _TIME_H_
#define _TIME_H_

//タイマーの構造体
typedef struct
{
	int nSec;								//タイマー（秒）
	int nDec;								//タイマー（小数点以下）
}Timer;

//プロトタイプ宣言
void InitTimer(void);						//タイマーの初期化処理
void UninitTimer(void);						//タイマーの終了処理
void UpdataTimer(void);						//タイマーの更新処理
void DrawTimer(void);						//タイマーの描画処理
void DrawResultTime(int nResultTime);		//リザルトタイムの描画処理
void StopTimer(void);						//タイマーを止める

#endif 
