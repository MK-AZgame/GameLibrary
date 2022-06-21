//========================================================
//
//	�e�̏���[bullet.h]
//	AUTHOR:�z�{���V
//
//========================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;								//�ʒu
	D3DXVECTOR3 move;								//�ړ���
	D3DXMATRIX  mtxWorld;							//���[���h�}�g���b�N�X
	int nLife;										//����
	bool bUse;										//�g�p���Ă��邩�ǂ���
}Bullet;

//�v���g�^�C�v�錾
void Initbullet(void);								
void Uninitbullet(void);							
void Updatebullet(void);							
void Drawbullet(void);								
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//�e�̐ݒ�
int GetBullet(void);								//�e�̏����擾

#endif
