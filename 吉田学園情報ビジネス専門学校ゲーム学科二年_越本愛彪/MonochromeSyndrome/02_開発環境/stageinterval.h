//=============================================================================
//
// �X�e�[�W�Ԃ̃t�F�[�h�̏��� [stageinterval.h]
// Author : �z�{�@���V
//
//=============================================================================
#ifndef _STAGEINTERVAL_H_
#define _STAGEINTERVAL_H_

#include "game.h"

//�t�F�[�h�̏��
typedef enum
{
	INTERVAL_NONE = 0,							//�������Ă��Ȃ����
	INTERVAL_IN,								//�t�F�[�h�C�����
	INTERVAL_OUT,								//�t�F�[�h�A�E�g���
	INTERVAL_MAX
}INTERVAL;

//�v���g�^�C�v�錾
void InitStageInterval(GAMESTATE nextstage);	//�X�e�[�W�ԃt�F�[�h�̏�����
void UninitStageInterval(void);					//�X�e�[�W�ԃt�F�[�h�̏I��
void UpdataStageInterval(void);					//�X�e�[�W�ԃt�F�[�h�̍X�V
void DrawStageInterval(void);					//�X�e�[�W�ԃt�F�[�h�̕`��
void SetStageInterval(GAMESTATE nextstage);		//�X�e�[�W�ԃt�F�[�h�̐ݒ�
INTERVAL GetStageInterval(void);				//�X�e�[�W�ԃt�F�[�h���̎擾

#endif