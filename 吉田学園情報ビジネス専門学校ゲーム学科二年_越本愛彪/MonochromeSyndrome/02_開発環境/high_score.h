//=============================================================================
//
// ハイスコアの処理 [high_score.h]
// Author : 越本　愛彪
//
//=============================================================================
#ifndef _HIGHSCORE_H_
#define _HIGHSCORE_H_

//プロトタイプ宣言
void InitHighScore(void);	//ハイスコアの初期化
void UninitHighScore(void);	//ハイスコアの終了
void UpdataHighScore(void);	//ハイスコアの更新
void DrawHighScore(void);	//ハイスコアの描画
void SetHighScore(void);	//ハイスコアの設定
void LoadHighScore(void);	//ハイスコアの読み込み
void SaveHighScore(int nScore);	//ハイスコアの書き出し

#endif 