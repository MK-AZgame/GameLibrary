//=============================================================================
//
// ���͂̏��� [input.h]
// Author : �z�{�@���V
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include"main.h"

//�L�[�̎��
typedef enum
{
	JOYKEY_UP = 0,				//��
	JOYKEY_DOWN,				//��
	JOYKEY_LEFT,				//��
	JOYKEY_RIGHT,				//�E
	JOYKEY_START,
	JOYKEY_BACK,
	JOYKEY_L3,
	JOYKEY_R3,
	JOYKEY_L1,
	JOYKEY_R1,					//�e�̔���
	JOYKEY_L2,
	JOYKEY_R2,
	JOYKEY_A,
	JOYKEY_B,
	JOYKEY_X,
	JOYKEY_Y,
	JOYKEY_MAX
} JOYKEY;

//�v���g�^�C�v�錾
HRESULT InitJoypad(void);								//�W���C�p�b�h�̏�����
void UninitJoypad(void);								//�W���C�p�b�h�̏I��
void UpdataJoypad(void);								//�W���C�p�b�h�̍X�V
bool GetJoypadPress(JOYKEY key);						//�W���C�p�b�h�������ꂽ�Ƃ��̏����擾
bool GetJoypadTrigger(JOYKEY key);						//�W���C�p�b�h�����������ꂽ�Ƃ��̏����擾
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);	//�L�[�{�[�h�̏�����
void UninitKeyboard(void);								//�L�[�{�[�h�̏I��
void UpdataKeyboard(void);								//�L�[�{�[�h�̍X�V
bool GetKeyboardPress(int nKey);						//�L�[�{�[�h�������ꂽ�Ƃ��̏����擾
bool GetKeyboardTrigger(int nKey);						//�L�[�{�[�h�����������ꂽ�Ƃ��̏����擾

#endif