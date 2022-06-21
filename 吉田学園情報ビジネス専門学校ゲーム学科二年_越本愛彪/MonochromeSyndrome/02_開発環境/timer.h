//=============================================================================
//
// タイマーの処理 [timer.h]
// Author : 越本　愛彪
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

//プロトタイプ宣言
void InitTimer(void);					//タイマーの初期化
void UninitTimer(void);					//タイマーの終了
void UpdataTimer(void);					//タイマーの更新
void DrawTimer(void);					//タイマーの描画
void DrawResultTime(int nResultTime);	//リザルトタイムの描画
void SetResultTime(int nResultTime);	//リザルトタイムの設定
void SetTimer();						//タイマーの設定
int GetTime();							//タイマー情報の設定

#endif 