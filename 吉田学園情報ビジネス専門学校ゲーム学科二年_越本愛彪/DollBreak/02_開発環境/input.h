//========================================================
//
//	���͂̏���[input.h]
//	AUTHOR:�z�{���V
//
//========================================================
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
HRESULT InitJoypad(void);								//�W���C�p�b�h�̏���������
void UninitJoypad(void);								//�W���C�p�b�h�̏I������
void UpdateJoypad(void);								//�W���C�p�b�h�̍X�V����
bool GetJoypadPress(JOYKEY key);						//�W���C�p�b�h�̃v���X�����擾
bool GetJoypadTrigger(JOYKEY key);						//�W���C�p�b�h�̃g���K�[�����擾
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);	//�L�[�{�[�h�̏���������
void UninitKeyboard(void);								//�L�[�{�[�h�̏I������
void UpdateKeyboard(void);								//�L�[�{�[�h�̍X�V����
bool GetKeyboardPress(int nKey);						//�L�[�{�[�h�̃v���X�����擾
bool GetKeyboardTrigger(int nKey);						//�L�[�{�[�h�̃g���K�[�����擾
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);		//�}�E�X�̏���������
void UninitMouse(void);									//�}�E�X�̏I������
void UpdateMouse(void);									//�}�E�X�̍X�V����
bool GetMousePress(int nMouse);							//�}�E�X�̃v���X�����擾
bool GetMouseTrigger(int nMouse);						//�}�E�X�̃g���K�[�����擾
D3DXVECTOR3 GetMouseMove(void);							//�}�E�X�̈ړ��ʂ̎擾

#endif


