//================================================================
//
//	�^�C���̏���[time.h]
//	Author:�z�{���V
//
//================================================================
#ifndef _TIME_H_
#define _TIME_H_

//�^�C�}�[�̍\����
typedef struct
{
	int nSec;								//�^�C�}�[�i�b�j
	int nDec;								//�^�C�}�[�i�����_�ȉ��j
}Timer;

//�v���g�^�C�v�錾
void InitTimer(void);						//�^�C�}�[�̏���������
void UninitTimer(void);						//�^�C�}�[�̏I������
void UpdataTimer(void);						//�^�C�}�[�̍X�V����
void DrawTimer(void);						//�^�C�}�[�̕`�揈��
void DrawResultTime(int nResultTime);		//���U���g�^�C���̕`�揈��
void StopTimer(void);						//�^�C�}�[���~�߂�

#endif 
