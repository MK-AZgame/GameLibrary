//=============================================================================
//
// �^�C�}�[�̏��� [timer.h]
// Author : �z�{�@���V
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

//�v���g�^�C�v�錾
void InitTimer(void);					//�^�C�}�[�̏�����
void UninitTimer(void);					//�^�C�}�[�̏I��
void UpdataTimer(void);					//�^�C�}�[�̍X�V
void DrawTimer(void);					//�^�C�}�[�̕`��
void DrawResultTime(int nResultTime);	//���U���g�^�C���̕`��
void SetResultTime(int nResultTime);	//���U���g�^�C���̐ݒ�
void SetTimer();						//�^�C�}�[�̐ݒ�
int GetTime();							//�^�C�}�[���̐ݒ�

#endif 