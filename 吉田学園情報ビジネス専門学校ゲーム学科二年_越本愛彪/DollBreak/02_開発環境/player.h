//========================================================
//
//	�v���C���[�̏���[player.h]
//	AUTHOR:�z�{���V
//
//========================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//�}�N����`
#define PLAYER_SIZE (20.0f)								//�v���C���[�̃T�C�Y

//�v���C���[�̏�ԁ@��
typedef enum
{
	PLAYERSTATE_NORMAL = 0,
	PLAERSTATE_DEATH,
	PLAYERSTATE_RELOAD,
	PLAYERSTATE_MAX
}PLAYERSTATE;

//�v���C���[�\����
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 posOld;			//�O��̈ʒu
	D3DXVECTOR3 rot;			//����
	D3DXVECTOR3 move;			//�ړ���
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	D3DXVECTOR3 rotDest;		//�ړI�̌���
	PLAYERSTATE State;			//�v���C���[�̏��
	int nLife;					//�̗�
} Player;

//���f���\����
typedef struct
{
	LPD3DXMESH pMesh;			//���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;		//���_�o�b�t�@�ւ̃|�C���^
	DWORD nNumMat;				
	char modelfilename;			//���f���̃t�@�C����
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;			//�p�[�c�̈ʒu
	D3DXVECTOR3 rot;			//�p�[�c�̌���
	int ParentIdx;				//�e�̔ԍ�
	int nMaxModelNum;			//���f���̐�
}ModelParts;

//�v���g�^�C�v�錾
void InitPlayer(void);				//�v���C���[�̏���������
void UninitPlayer(void);			//�v���C���[�̏I������
void UpdatePlayer(void);			//�v���C���[�̍X�V����
void DrawPlayer(void);				//�v���C���[�̕`�揈��
void CollisionObject(void);			//�I�u�W�F�N�g�i���f���j�Ƃ̓����蔻��
void HitEnemyAttack(int nAttack);	//�G�l�~�[�̍U���������������̏���
Player *GetPlayer(void);			//�v���C���[�̏��̎擾

#endif
