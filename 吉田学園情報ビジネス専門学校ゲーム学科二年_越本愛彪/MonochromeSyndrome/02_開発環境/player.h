//=============================================================================
//
// �v���C���[�̏��� [player.h]
// Author : �z�{�@���V
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

#define PLAYER_WIDTH  (20.0f)									//�v���C���[�̉���
#define PLAYER_HEIGHT (20.0f)									//�v���C���[�̍���
#define PLAYER_MOVE   (1.0f)									//�v���C���[�̈ړ���

//�v���C���[�̏�Ԃ��Ǘ�
typedef enum
{
	PLAYERSTATE_NORMAL = 0,
	PLAYERSTATE_JUMP,
	PLAYERSTATE_DEATH,
	PLAYERSTATE_MAX
} PLAYERSTATE;

//�v���C���[�\����
typedef struct
{
	D3DXVECTOR3 pos;											//�v���C���[�̍��W
	D3DXVECTOR3 posOld;											//�v���C���[�̑O��̈ʒu
	D3DXVECTOR3 move;											//�v���C���[�̈ړ���
	PLAYERSTATE state;											//�v���C���[�̏��
	int nCounterAnim;											//�A�j���[�V�����J�E���^�[
	int nPatternAnim;											//�A�j���[�V�����p�^�[��
	int nDirectionMove;											//����(0�F�E�ړ����@1�F���ړ���)
	int nLife;													//�v���C���[�̃��C�t
	bool bDisp;													//�\�����邩�ǂ���
} Player;

//�v���g�^�C�v�錾
void InitPlayer(void);											//�v���C���[�̏�����
void UninitPlayer(void);										//�v���C���[�̏I��
void UpdataPlayer(void);										//�v���C���[�̍X�V
void DrawPlayer(void);											//�v���C���[�̕`��
bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight);	//�v���C���[�̓����蔻��
void SetPlayerPos(D3DXVECTOR3 pos);								//�v���C���[�ʒu�̐ݒ�
Player *GetPlayer(void);										//�v���C���[���̎擾

#endif