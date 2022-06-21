//=============================================================================
//
// �^�C�g���̏��� [title.cpp]
// Author : �z�{�@���V
//
//=============================================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//�}�N����`
#define NUM_BACKGROUND (2)

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTitle[NUM_BACKGROUND] = {};	//�^�C�g���̃e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//�^�C�g���̒��_���ւ̃|�C���^
D3DXCOLOR g_colorTitle;										//�^�C�g���̃J���[�p
D3DXCOLOR g_colorButton;									//�{�^���̃J���[�p
BUTTON g_button;											//�{�^���̏����i�[
SWITCH g_switch;											//�^�C�g���̏�Ԃ�؂�ւ��邽�߂̍\���̏����i�[
int g_nCoolCount;											//�N�[���^�C�����J�E���g����p
int g_nCountStop;											
int g_nflag;

//=============================================================================
//		�^�C�g���̏���������
//=============================================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�O���[�o���ϐ��̏�����
	g_button = BUTTON_IN;
	g_switch = SWITCH_ON;
	g_colorTitle = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	g_colorButton = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	g_nCoolCount = 0;
	g_nCountStop = 0;
	g_nflag = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/title.png", &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/pressenter.png", &g_pTextureTitle[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BACKGROUND,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D *pVtx;												//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(500.0f, 400.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(780.0f, 400.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(500.0f, 550.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(780.0f, 550.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//���_���W���A�����b�N
	g_pVtxBuffTitle->Unlock();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM000);
}

//=============================================================================
//		�^�C�g���̏I������
//=============================================================================
void UninitTitle(void)
{
	for (int nCount = 0; nCount < NUM_BACKGROUND; nCount++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureTitle[nCount] != NULL)
		{
			g_pTextureTitle[nCount]->Release();
			g_pTextureTitle[nCount] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	//�T�E���h�̒�~
	StopSound();
}

//=============================================================================
//		�^�C�g���̍X�V����
//=============================================================================
void UpdataTitle(void)
{
	VERTEX_2D *pVtx;												//���_���ւ̃|�C���^
	FADE fade = GetFade();

	//�t�F�[�h��Ԃ̃^�C�g���𑦍��ɕ\��������
	if (g_switch == SWITCH_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) == true)
		{
			g_switch = SWITCH_ON;
		}
	}

	//�^�C�g������`���[�g���A����ʂɑJ�ڂ�����
	if (g_switch == SWITCH_ON)
	{
		g_nCountStop++;

		if (g_nCountStop > 5)
		{
			if (fade == FADE_NONE)
			{
				//�L�[����
				if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) == true || GetJoypadTrigger(JOYKEY_B) == true || 
					GetJoypadTrigger(JOYKEY_X) == true|| GetJoypadTrigger(JOYKEY_Y) == true)
				{//ENTER�L�[�������ꂽ
					g_nflag = 1;
					PlaySound(SOUND_LABEL_SE001);
					//���[�h�̐ݒ菈��
					SetFade(MODE_TUTORIAL);
				}
			}
		}

		//[PUSH ENTER]�̓_��
		if (g_nflag == 1)
		{//�G���^�[�L�[�������ꂽ���
			if (g_button == BUTTON_OUT)
			{//���X�ɔ������Ă���
				g_colorButton.a -= 1.0f;
				if (g_colorButton.a <= 0)
				{
					g_colorButton.a = 0.0f;
					g_button = BUTTON_IN;
				}
			}
			else if (g_button == BUTTON_IN)
			{//���X�ɔZ�����Ă���
				g_colorButton.a += 1.0f;
				if (g_colorButton.a >= 1.0f)
				{
					g_colorButton.a = 1.0f;
					g_button = BUTTON_OUT;
				}
			}
		}
		else
		{
			if (g_button == BUTTON_OUT)
			{
				g_colorButton.a -= 0.05f;
				if (g_colorButton.a <= 0)
				{
					g_colorButton.a = 0.0f;
					g_button = BUTTON_IN;
				}
			}
			else if (g_button == BUTTON_IN)
			{
				g_colorButton.a += 0.05f;
				if (g_colorButton.a >= 1.0f)
				{
					g_colorButton.a = 1.0f;
					g_button = BUTTON_OUT;
				}
			}
		}

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorButton.a);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorButton.a);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorButton.a);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorButton.a);

		//���_���W���A�����b�N
		g_pVtxBuffTitle->Unlock();
	}
	else if (g_switch != SWITCH_ON)
	{
		if (g_nCoolCount >= 180)
		{
			if (g_nflag == 1)
			{
				if (g_button == BUTTON_OUT)
				{
					g_colorButton.a -= 1.0f;
					if (g_colorButton.a <= 0)
					{
						g_colorButton.a = 0.0f;
						g_button = BUTTON_IN;
					}
				}
				else if (g_button == BUTTON_IN)
				{
					g_colorButton.a += 1.0f;
					if (g_colorButton.a >= 1.0f)
					{
						g_colorButton.a = 1.0f;
						g_button = BUTTON_OUT;
					}
				}
			}
			else
			{
				//[PUSH ENTER]�̓_��
				if (g_button == BUTTON_OUT)
				{
					g_colorButton.a -= 0.05f;
					if (g_colorButton.a <= 0)
					{
						g_colorButton.a = 0.0f;
						g_button = BUTTON_IN;
					}
				}
				else if (g_button == BUTTON_IN)
				{
					g_colorButton.a += 0.05f;
					if (g_colorButton.a >= 1.0f)
					{
						g_colorButton.a = 1.0f;
						g_button = BUTTON_OUT;
					}
				}
			}
		}

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorButton.a);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorButton.a);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorButton.a);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_colorButton.a);

		//���_���W���A�����b�N
		g_pVtxBuffTitle->Unlock();
	}
}

//=============================================================================
//		�^�C�g���̕`�揈��
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < NUM_BACKGROUND; nCount++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[nCount]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,									//�v���~�e�B�u�̎��
			4 * nCount,
			2);														//�v���~�e�B�u�̐�
	}
}