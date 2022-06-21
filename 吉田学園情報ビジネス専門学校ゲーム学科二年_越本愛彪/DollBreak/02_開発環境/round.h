//========================================================
//
//	ラウンドの処理[round.h]
//	AUTHOR:越本愛彪
//
//========================================================
#ifndef _ROUND_H_
#define _ROUND_H_

//ラウンドの構造体
typedef struct
{
	int nNumRound;							//ラウンド数
	int nIntervalTime;						//ラウンド間のインターバル
	int nState;								//ラウンドの状態
}Round;

//ラウンドの状態
typedef enum
{
	ROUND_NONE = 0,
	ROUND_FIRST,
	ROUND_SECOND,
	ROUND_THIRD,
	ROUND_FOURTH,
	ROUND_FIFTH,
	ROUND_INTERVAL,
	ROUND_MAX
}ROUNDNUM;

//プロトタイプ宣言
void InitRound(void);						//ラウンドの初期化処理
void UninitRound(void);						//ラウンドの終了処理
void UpdataRound(void);						//ラウンドの更新処理
void DrawRound(void);						//ラウンドの描画処理
void SetRound();							//ラウンドの設定処理
void ChangeRound(ROUNDNUM nextRound);		//ラウンドの状態を切り替える
Round *GetRound();							//ラウンドの情報を取得

#endif 