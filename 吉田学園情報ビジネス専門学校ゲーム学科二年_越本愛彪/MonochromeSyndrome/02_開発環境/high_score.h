//=============================================================================
//
// �n�C�X�R�A�̏��� [high_score.h]
// Author : �z�{�@���V
//
//=============================================================================
#ifndef _HIGHSCORE_H_
#define _HIGHSCORE_H_

//�v���g�^�C�v�錾
void InitHighScore(void);	//�n�C�X�R�A�̏�����
void UninitHighScore(void);	//�n�C�X�R�A�̏I��
void UpdataHighScore(void);	//�n�C�X�R�A�̍X�V
void DrawHighScore(void);	//�n�C�X�R�A�̕`��
void SetHighScore(void);	//�n�C�X�R�A�̐ݒ�
void LoadHighScore(void);	//�n�C�X�R�A�̓ǂݍ���
void SaveHighScore(int nScore);	//�n�C�X�R�A�̏����o��

#endif 