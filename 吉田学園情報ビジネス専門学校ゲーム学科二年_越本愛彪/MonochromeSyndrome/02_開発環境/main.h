//=============================================================================
//
// ���C���̏��� [main.h]
// Author : �z�{�@���V
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#include <windows.h>
#include "d3dx9.h"
#define  DIRECTINPUT_VERSION (0x0800)
#include "dinput.h" 
#include "xinput.h"
#include "xaudio2.h"

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")										//�V�X�e�������̎擾�ɕK�v
#pragma comment(lib,"dinput8.lib")										//���͏����ɕK�v
#pragma comment(lib,"xinput.lib")										//�W���C�p�b�h�����ɕK�v

//�}�N����`
#define SCREEN_WIDTH	 (1280)											//�E�B���h�E�̕�
#define SCREEN_HEIGHT	 (720)											//�E�B���h�E�̍���
#define FVF_VERTEX_2D    (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)		//���_�t�H�[�}�b�g

//���_���̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;													//���_���W	
	float rhw;															//���W�ϊ��p�W��
	D3DCOLOR col;														//���_�J���[
	D3DXVECTOR2 tex;													//�e�N�X�`���̍��W
} VERTEX_2D;

//��ʃ��[�h�̎��
typedef enum
{
	MODE_TITLE = 0,
	MODE_GAME,
	MODE_RESULT,
	MODE_TUTORIAL,
	MODE_RANKING,
	MODE_MAX
} MODE;

//�v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void);	//�f�o�C�X�̎擾
void SetMode(MODE mode);			//���[�h�̐ݒ�

#endif