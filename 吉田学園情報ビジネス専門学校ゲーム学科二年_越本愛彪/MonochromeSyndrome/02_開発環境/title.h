//=============================================================================
//
// �^�C�g���̏��� [title.h]
// Author : �z�{�@���V
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//[push enter]
typedef enum
{
	BUTTON_NONE = 0,	//�������Ă��Ȃ����
	BUTTON_IN,			//�t�F�[�h�C�����
	BUTTON_OUT,			//�t�F�[�h�A�E�g���
	BUTTON_MAX
}BUTTON;

typedef enum
{
	SWITCH_NONE = 0,	//�������Ă��Ȃ����
	SWITCH_ON,			//�t�F�[�h�C�����
	SWITCH_OFF,			//�t�F�[�h�A�E�g���
	SWITCH_MAX
}SWITCH;

//�v���g�^�C�v�錾
void InitTitle(void);	//�^�C�g���̏�����
void UninitTitle(void);	//�^�C�g���̏I��
void UpdataTitle(void);	//�^�C�g���̍X�V
void DrawTitle(void);	//�^�C�g���̕`��

#endif 