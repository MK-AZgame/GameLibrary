//=============================================================================
//
//	�u���b�N�����̏���[block.h]
//	Author�F�z�{���V
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//�u���b�N�̎��
typedef enum
{
	BLOCK_NONE = 0,
	BLOCK_NORMAL,																	//�ʏ�̃u���b�N
	BLOCK_MOVE,																		//�����u���b�N
	BLOCK_MAX
}BLOCK_TYPE;

//�v���g�^�C�v�錾
void InitBlock(void);																//�u���b�N�̏�����
void UninitBlock(void);																//�u���b�N�̏I��
void UpdataBlock(void);																//�u���b�N�̍X�V
void DrawBlock(void);																//�u���b�N�̕`��
void SetBlock(D3DXVECTOR3 pos,float fWidth,D3DXVECTOR3 move,BLOCK_TYPE block);		//�u���b�N�̐ݒ�
bool ColisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld,
	D3DXVECTOR3 *pMove,float fWidth, float fHeight);								//�����蔻��
void ScrollBlock(D3DXVECTOR3 move,int nCntBlock);									//�u���b�N�̃X�N���[��
void ScanFile(char *pfilename);														//Excel��ǂݍ���Ń}�b�v����ǂݍ���

#endif