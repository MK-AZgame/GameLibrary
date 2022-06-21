//========================================================
//
//	���f���̏���[model.h]
//	AUTHOR:�z�{���V
//
//========================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//�}�N����`
#define MAX_MODEL (128)				//���f���̍ő吔
#define MAX_MODELTYPE (1)			//���f���̎�ނ̍ő吔

//���f���\����
typedef struct
{
	D3DXVECTOR3 pos;				//���f���̈ʒu
	D3DXVECTOR3 rot;				//���f���̊p�x
	D3DXMATRIX mtxWorld;			//���[���h�}�g���b�N�X
	int nType;						//���f���̎��
	bool bUse;						//�g�p����Ă��邩�ǂ���
}MODEL;

//���f�����̍\����
typedef struct
{
	LPD3DXMESH pMeshModel;
	LPD3DXBUFFER pBuffMatModel;
	DWORD nNumMatModel;
	D3DXVECTOR3 vtxMin, vtxMax;		//���f���̒��_�̍ő�l�E�ŏ��l
}ModelInfo;

//�v���g�^�C�v�錾
void InitModel(void);				//���f������������
void UninitModel(void);				//���f���I������
void UpdateModel(void);				//���f���X�V����
void DrawModel(void);				//���f���`�揈��
void SetModel(D3DXVECTOR3 pos);		//���f���̐ݒ菈��
D3DXVECTOR3 GetVtxMax(int nType);	//���f���̃T�C�Y�̍ő�l���擾����
D3DXVECTOR3 GetVtxMin(int nType);	//���f���̃T�C�Y�̍ŏ��l���擾����
MODEL *GetModel(void);				//���f���̏����擾����		

#endif