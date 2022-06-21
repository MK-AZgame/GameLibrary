//=============================================================================
//
//	ブロック生成の処理[block.h]
//	Author：越本愛彪
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//ブロックの種類
typedef enum
{
	BLOCK_NONE = 0,
	BLOCK_NORMAL,																	//通常のブロック
	BLOCK_MOVE,																		//動くブロック
	BLOCK_MAX
}BLOCK_TYPE;

//プロトタイプ宣言
void InitBlock(void);																//ブロックの初期化
void UninitBlock(void);																//ブロックの終了
void UpdataBlock(void);																//ブロックの更新
void DrawBlock(void);																//ブロックの描画
void SetBlock(D3DXVECTOR3 pos,float fWidth,D3DXVECTOR3 move,BLOCK_TYPE block);		//ブロックの設定
bool ColisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld,
	D3DXVECTOR3 *pMove,float fWidth, float fHeight);								//当たり判定
void ScrollBlock(D3DXVECTOR3 move,int nCntBlock);									//ブロックのスクロール
void ScanFile(char *pfilename);														//Excelを読み込んでマップ情報を読み込む

#endif