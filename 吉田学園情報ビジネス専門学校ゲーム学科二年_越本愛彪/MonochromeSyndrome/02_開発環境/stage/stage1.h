#ifndef _STAGE1_H_
#define _STAGE1_H_

#include "main.h"
#include "player.h"

//ブロックの種類
typedef enum
{
	STAGE2_BLOCK_NONE = 0,
	STAGE2_BLOCK_NORMAL,						//通常のブロック
	STAGE2_BLOCK_MOVE,							//動くブロック
	STAGE2_BLOCK_FAKE,
	STAGE2_BLOCK_MAX
}STAGE2_BLOCK_TYPE;

//プロトタイプ宣言
void InitStage2(void);
void UninitStage2(void);
void UpdataStage2(void);
void DrawStage2(void);
void SetStage2(D3DXVECTOR3 pos, float fWidth, D3DXVECTOR3 move, STAGE2_BLOCK_TYPE block);
void ScrollStage2(D3DXVECTOR3 move, int nCntBlock);

#endif


