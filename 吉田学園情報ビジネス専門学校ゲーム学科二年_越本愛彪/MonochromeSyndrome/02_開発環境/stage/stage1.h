#ifndef _STAGE1_H_
#define _STAGE1_H_

#include "main.h"
#include "player.h"

//�u���b�N�̎��
typedef enum
{
	STAGE2_BLOCK_NONE = 0,
	STAGE2_BLOCK_NORMAL,						//�ʏ�̃u���b�N
	STAGE2_BLOCK_MOVE,							//�����u���b�N
	STAGE2_BLOCK_FAKE,
	STAGE2_BLOCK_MAX
}STAGE2_BLOCK_TYPE;

//�v���g�^�C�v�錾
void InitStage2(void);
void UninitStage2(void);
void UpdataStage2(void);
void DrawStage2(void);
void SetStage2(D3DXVECTOR3 pos, float fWidth, D3DXVECTOR3 move, STAGE2_BLOCK_TYPE block);
void ScrollStage2(D3DXVECTOR3 move, int nCntBlock);

#endif


