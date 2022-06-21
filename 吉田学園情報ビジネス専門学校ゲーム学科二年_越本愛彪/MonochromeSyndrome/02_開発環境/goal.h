//=============================================================================
//
// �S�[���̏��� [goal.cpp]
// Author : �z�{�@���V
//
//=============================================================================
#ifndef _GOAL_H_
#define _GOAL_H_

#include "main.h"
#include "player.h"

//�v���g�^�C�v�錾
void InitGoal(void);				//�S�[���̏�����
void UninitGoal(void);				//�S�[���̏I��
void UpdataGoal(void);				//�S�[���̍X�V
void DrawGoal(void);				//�S�[���̕`��
void SetGoal(D3DXVECTOR3 pos);		//�S�[���̐ݒ�
void ColisionGoal(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight);	//�S�[���̓����蔻��
void ScrollGoal(D3DXVECTOR3 move);	//�S�[���̃X�N���[��

#endif