//========================================================
//
//	�J�����̏���[camera.h]
//	AUTHOR:�z�{���V
//
//========================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//�}�N����`
#define MAX_CAMERA (2)						//�J�����̍ő吔

//�J�����\����
typedef struct
{
	D3DXVECTOR3 posV;				//���_�̈ʒu
	D3DXVECTOR3 posR;				//�����_�̈ʒu
	D3DXVECTOR3 posVDest;			//���_�̖ړI�̈ʒu
	D3DXVECTOR3 posRDest;			//�����_�̖ړI�̈ʒu
	D3DXVECTOR3 vecU;
	D3DXVECTOR3 rot;				//�p�x
	D3DXVECTOR3 rotDest;			//�ړI�̊p�x
	D3DXMATRIX  mtxProjection;
	D3DXMATRIX  mtxView;
	D3DVIEWPORT9 viewport;			//�r���[�|�[�g
	float fDistance;				//����
} Camera;

//�v���g�^�C�v�錾
void InitCamera(void);				//�J����������
void UninitCamera(void);			//�J�����I��
void UpdateCamera(void);			//�J�����X�V
void SetCamera(int nIdxCamera);		//�J�����ݒ�
Camera *GetCamera(void);			//�J�������̎擾

#endif