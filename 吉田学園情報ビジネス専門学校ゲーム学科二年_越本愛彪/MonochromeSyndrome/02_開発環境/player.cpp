//=============================================================================
//
// �v���C���[�̏��� [player.cpp]
// Author : �z�{�@���V
//
//=============================================================================
#include "player.h"
#include "input.h"
#include "pause.h"
#include "game.h"
#include "fade.h"
#include "block.h"
#include "goal.h"
#include "timer.h"
#include "stageinterval.h"
#include "sound.h"

//�}�N����`
#define MOVE_DOWN     (0.185f)							//�����̌�����
#define PLYER_JUMP    (20.0f)							//�W�����v�̈ړ���

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;				//�v���C���[�̃e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;		//�v���C���[�̒��_���̃|�C���^
Player g_player;										//�v���C���[�̏����i�[

//=============================================================================
//		�v���C���[�̏���������
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_player.pos = D3DXVECTOR3(100.0f, 640.0f, 0.0f);	//�ʒu�̏�����
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʂ̏�����
	g_player.bDisp = true;								//�v���C���[��\����Ԃ�
	g_player.nCounterAnim = 0;							//�A�j���[�V�����J�E���^�[�̏�����
	g_player.nPatternAnim = 0;							//�A�j���[�V�����p�^�[���̏�����
	g_player.nDirectionMove = 0;						//�v���C���[�̌����̏�����
	g_player.state = PLAYERSTATE_NORMAL;				//�v���C���[��Ԃ̏�����
	g_player.nLife = 2;									//�v���C���[�̗̑͂̏�����
	
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D *pVtx;									//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH / 2, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH / 2, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH / 2, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH / 2, g_player.pos.y, 0.0f);
	
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//���_���W���A�����b�N
	g_pVtxBuffPlayer->Unlock();
}

//=============================================================================
//		�v���C���[�̏I������
//=============================================================================
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//=============================================================================
//		�v���C���[�̍X�V����
//=============================================================================
void UpdataPlayer(void)
{
	VERTEX_2D *pVtx;								//���_���ւ̃|�C���^
	FADE Fade = GetFade();

	//�ړ�
	if (g_player.state != PLAYERSTATE_DEATH)
	{
		if (g_player.state == PLAYERSTATE_NORMAL)
		{//�ʏ펞
			if (GetKeyboardPress(DIK_A) || GetJoypadPress(JOYKEY_LEFT) == true)
			{//��
				g_player.move.x -= PLAYER_MOVE;

				g_player.nDirectionMove = 1;
			}
			else if (GetKeyboardPress(DIK_D) || GetJoypadPress(JOYKEY_RIGHT) == true)
			{//�E
				g_player.move.x += PLAYER_MOVE;

				g_player.nDirectionMove = 0;
			}

			//�W�����v
			if (GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_A) == true)
			{
				PlaySound(SOUND_LABEL_SE000);
				g_player.move.y -= PLYER_JUMP - 1.0f;
				g_player.state = PLAYERSTATE_JUMP;
			}
		}
		else if (g_player.state == PLAYERSTATE_JUMP)
		{//�W�����v��
			if (GetKeyboardPress(DIK_A) || GetJoypadPress(JOYKEY_LEFT) == true)
			{//��
				g_player.move.x -= PLAYER_MOVE - 0.6f;

				g_player.nDirectionMove = 1;
			}
			else if (GetKeyboardPress(DIK_D) || GetJoypadPress(JOYKEY_RIGHT) == true)
			{//�E
				g_player.move.x += PLAYER_MOVE - 0.6f;

				g_player.nDirectionMove = 0;
			}
		}

		//�O��̈ʒu��ۑ�
		g_player.posOld = g_player.pos;

		//�ʒu���X�V
		g_player.pos += g_player.move;

		//�d��
		g_player.move.y += 1.5f;

		//�W�����v�̉۔���
		g_player.state = (ColisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, PLAYER_WIDTH, PLAYER_HEIGHT) == true) ?
			PLAYERSTATE_NORMAL : PLAYERSTATE_JUMP;

		//�S�[���Ƃ̓����蔻��
		ColisionGoal(&g_player.pos, &g_player.posOld, &g_player.move, PLAYER_WIDTH, PLAYER_HEIGHT);
	}

	//�u���b�N�̃X�N���[������
	if (g_player.pos.x >= SCREEN_WIDTH / 2)
	{
		g_player.pos.x = SCREEN_WIDTH / 2;
	}

	//��ʊO�ւ̈ړ��̖h�~����
	if (g_player.pos.x - PLAYER_WIDTH / 2 <= 0.0f)
	{//��ʍ��[
		g_player.pos.x = 0.0f + PLAYER_WIDTH / 2;
	}
	else if (g_player.pos.x - PLAYER_WIDTH / 2 >= SCREEN_WIDTH)
	{//��ʉE�[
		g_player.pos.x = 0.0f - PLAYER_WIDTH / 2;
	}

	//�A�j���[�V�����̍X�V
	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL:									//�ʏ펞�̃A�j���[�V����
		if (g_player.move.x >= 0.2f || g_player.move.x <= -0.2f)
		{//�ړ���
			g_player.nCounterAnim++;
			if (g_player.nCounterAnim % 10 == 0)
			{
				g_player.nCounterAnim = 0;
				g_player.nPatternAnim++;
				if (g_player.nPatternAnim >= 4)
				{
					g_player.nPatternAnim = 0;
				}
			}
		}
		else
		{//�v���C���[��~���̃A�j���[�V�����Œ�
			if ((g_player.nPatternAnim + 1) % 2 == 0)
			{
				g_player.nPatternAnim++;
			}
		}
		break;
	case PLAYERSTATE_JUMP:										//�W�����v���̃A�j���[�V����
		if (g_player.nPatternAnim % 2 == 0)
		{//�W�����v���̃A�j���[�V�����Œ�
			g_player.nPatternAnim++;
		}
		break;
	}

	//�ړ��ʂ̌����i�����j
	if (g_player.state == PLAYERSTATE_JUMP)
	{//�W�����v��
		g_player.move.x += (0.0f - g_player.move.x) * 0.05f;
	}
	else
	{//�ʏ펞
		g_player.move.x += (0.0f - g_player.move.x) * MOVE_DOWN;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + (0.25f * g_player.nPatternAnim), 0.0f + (0.5f * g_player.nDirectionMove));
	pVtx[1].tex = D3DXVECTOR2(0.25f + (0.25f * g_player.nPatternAnim), 0.0f + (0.5f * g_player.nDirectionMove));
	pVtx[2].tex = D3DXVECTOR2(0.0f + (0.25f * g_player.nPatternAnim), 0.5f + (0.5f * g_player.nDirectionMove));
	pVtx[3].tex = D3DXVECTOR2(0.25f + (0.25f * g_player.nPatternAnim), 0.5f + (0.5f * g_player.nDirectionMove));

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH / 2, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH / 2, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH / 2, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH / 2, g_player.pos.y, 0.0f);

	//���_���W���A�����b�N
	g_pVtxBuffPlayer->Unlock();

	//�v���C���[�������̏���
	if (g_player.pos.y - PLAYER_HEIGHT >= 1280.0f || g_player.pos.y <= 0.0f)
	{
		GAMESTATE &state = *GetGameState();
		g_player.nLife--;										//�v���C���[�c�@�̌���
		
		if (g_player.nLife <= 0)
		{//�v���C���[�̎��S
			if (Fade == FADE_NONE)
			{
				state = GAMESTATE_END;
				g_player.state = PLAYERSTATE_DEATH;

				SetFade(MODE_RESULT);
			}
		}
		else
		{//�X�e�[�W�̏����ʒu�ɖ߂�
			SetStageInterval(state);
		}
	}
}

//=============================================================================
//		�v���C���[�̕`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);

	if (g_player.bDisp == true)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,									//�v���~�e�B�u�̎��
			0,
			2);														//�v���~�e�B�u�̐�			
	}
}

//=============================================================================
//		�u���b�N�̓����蔻��
//=============================================================================
bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
{
	bool bIsLanding = false;									//���n���Ă��邩�ǂ���

	//�u���b�N�ƃv���C���[�̓����蔻��
	//�ォ�牺
	if (pPosOld->y - fHeight / 2 >= g_player.pos.y &&
		pPos->y - fHeight / 2 < g_player.pos.y &&
		pPos->x + fWidth / 2 > g_player.pos.x - PLAYER_WIDTH / 2 &&
		pPos->x - fWidth / 2 < g_player.pos.x + PLAYER_WIDTH / 2)
	{
		g_player.pos.y = pPos->y - fHeight / 2;
	}

	//�������
	if (pPosOld->y + fHeight / 2 >= g_player.pos.y - PLAYER_HEIGHT &&
		pPos->y + fHeight / 2 < g_player.pos.y - PLAYER_HEIGHT &&
		pPos->x + fWidth / 2 > g_player.pos.x - PLAYER_WIDTH / 2 &&
		pPos->x - fWidth / 2 < g_player.pos.x + PLAYER_WIDTH / 2)
	{
	}

	if (pPosOld->y + fHeight / 2 > g_player.pos.y - PLAYER_HEIGHT &&
		pPosOld->y - fHeight / 2 < g_player.pos.y)
	{
		//������E
		if (pPosOld->x - fWidth / 2 >= g_player.pos.x + PLAYER_WIDTH / 2 &&
			pPos->x - fWidth / 2 < g_player.pos.x + PLAYER_WIDTH / 2)
		{
			g_player.pos.x = pPos->x - fWidth / 2 - PLAYER_WIDTH / 2;
		}

		//�E���獶
		if (pPosOld->x + fWidth / 2 <= g_player.pos.x - PLAYER_WIDTH / 2 &&
			pPos->x + fWidth / 2 > g_player.pos.x - PLAYER_WIDTH / 2)
		{
			g_player.pos.x = pPos->x + fWidth / 2 + PLAYER_WIDTH / 2;
		}
	}
	return bIsLanding;
}

//=============================================================================
//		�v���C���[���W�̐ݒ�
//=============================================================================
void SetPlayerPos(D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx;

	//���W�X�V
	g_player.pos = pos;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH / 2, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH / 2, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH / 2, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH / 2, g_player.pos.y, 0.0f);

	//���_���W���A�����b�N
	g_pVtxBuffPlayer->Unlock();
}

//=============================================================================
//		�v���C���[���̎擾
//=============================================================================
Player *GetPlayer(void)
{
	return &g_player;
}