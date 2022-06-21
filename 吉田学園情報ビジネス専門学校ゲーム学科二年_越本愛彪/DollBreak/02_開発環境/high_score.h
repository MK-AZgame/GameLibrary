//========================================================
//
//	ハイスコアの処理[high_score.h]
//	AUTHOR:越本愛彪
//
//========================================================
#ifndef _HIGHSCORE_H_
#define _HIGHSCORE_H_

//プロトタイプ宣言
void InitHighScore(void);		//ハイスコア初期化
void UninitHighScore(void);		//ハイスコア終了
void UpdateHighScore(void);		//ハイスコア更新
void DrawHighScore(void);		//ハイスコア描画
void SetHighScore();			//ハイスコア設定
void LoadHighScore(void);		//ハイスコア読み込み
void SaveHighScore(int nScore);	//ハイスコア保存

#endif 