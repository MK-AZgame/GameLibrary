//========================================================
//
//	�J�����̏���[camera.cpp]
//	AUTHOR:�z�{���V
//
//========================================================
#include "camera.h"
#include "input.h"
#include "player.h"

//�J�����̎��
typedef enum
{
	CAMERATYPE_PLAYER = 0,
	CAMERATYPE_MAP,
	CAMERATYPE_MAX
}CAMERATYPE;

//�O���[�o���ϐ�
int g_nCntTime;								//�v���C���[�������Ă��Ȃ����ԁi�ҋ@���ԁj�̉��Z�p
Camera g_camera[MAX_CAMERA];				//�J�������

//========================================================
//					�J��������������
//========================================================
void InitCamera(void)
{
	////�r���[�|�[�g�\���̕ۑ�
	//�v���C���[���_
	g_camera[CAMERATYPE_PLAYER].viewport.X = 0.0f;
	g_camera[CAMERATYPE_PLAYER].viewport.Y = 0.0f;
	g_camera[CAMERATYPE_PLAYER].viewport.Width = SCREEN_WIDTH;
	g_camera[CAMERATYPE_PLAYER].viewport.Height = SCREEN_HEIGHT;
	g_camera[CAMERATYPE_PLAYER].viewport.MinZ = 0.0f;
	g_camera[CAMERATYPE_PLAYER].viewport.MaxZ = 1.0f;

	//�}�b�v
	g_camera[1].viewport.X = 10.0f;
	g_camera[1].viewport.Y = 10.0f;
	g_camera[1].viewport.Width = 240.0f;
	g_camera[1].viewport.Height = 240.0f;
	g_camera[1].viewport.MinZ = 0.0f;
	g_camera[1].viewport.MaxZ = 1.0f;

	//���_�E�����_�E�������ݒ肷��
	g_camera[CAMERATYPE_PLAYER].posV = D3DXVECTOR3(0.0f,100.0f,-100.0f);
	g_camera[CAMERATYPE_PLAYER].posR = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_camera[CAMERATYPE_PLAYER].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera[CAMERATYPE_PLAYER].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera[CAMERATYPE_PLAYER].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera[CAMERATYPE_PLAYER].fDistance = sqrtf((g_camera[CAMERATYPE_PLAYER].posR.z - g_camera[CAMERATYPE_PLAYER].posV.z) * (g_camera[CAMERATYPE_PLAYER].posR.z - g_camera[CAMERATYPE_PLAYER].posV.z) +
		(g_camera[CAMERATYPE_PLAYER].posR.x - g_camera[CAMERATYPE_PLAYER].posV.x) * (g_camera[CAMERATYPE_PLAYER].posR.x - g_camera[CAMERATYPE_PLAYER].posV.x));

	g_camera[1].posV = D3DXVECTOR3(0.0f, 750.0f, 0.01f);
	g_camera[1].posR = D3DXVECTOR3(0.0f, 0.0f, -0.05f);
	g_camera[1].vecU = D3DXVECTOR3(0.0f, -0.1f, 0.0f);
	g_camera[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera[1].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera[1].fDistance = sqrtf((g_camera[1].posR.z - g_camera[1].posV.z) * (g_camera[1].posR.z - g_camera[1].posV.z) +
		(g_camera[1].posR.x - g_camera[1].posV.x) * (g_camera[1].posR.x - g_camera[1].posV.x));

}

//========================================================
//					�J�����I������
//========================================================
void UninitCamera(void)
{

}

//========================================================
//					�J�����X�V����
//========================================================
void UpdateCamera(void)
{
	Player *pPlayer = GetPlayer();

	//�J�����̒Ǐ]����
	g_camera[CAMERATYPE_PLAYER].posRDest.x = pPlayer->pos.x + sinf(g_camera[0].rot.y) * 100.0f;
	g_camera[CAMERATYPE_PLAYER].posRDest.y = pPlayer->pos.y;
	g_camera[CAMERATYPE_PLAYER].posRDest.z = pPlayer->pos.z + cosf(g_camera[0].rot.y) * 100.0f;

	g_camera[CAMERATYPE_PLAYER].posVDest.x = pPlayer->pos.x - sinf(pPlayer->rot.y) * 1.0f;
	g_camera[CAMERATYPE_PLAYER].posVDest.y = pPlayer->pos.y;
	g_camera[CAMERATYPE_PLAYER].posVDest.z = pPlayer->pos.z - cosf(pPlayer->rot.y) * 1.0f;

	g_camera[CAMERATYPE_PLAYER].posR += (g_camera[CAMERATYPE_PLAYER].posRDest - g_camera[CAMERATYPE_PLAYER].posR) * 0.2f;
	g_camera[CAMERATYPE_PLAYER].posV += (g_camera[CAMERATYPE_PLAYER].posVDest - g_camera[CAMERATYPE_PLAYER].posV) * 0.2f;
	g_camera[CAMERATYPE_PLAYER].rot.y += (g_camera[CAMERATYPE_PLAYER].rotDest.y - g_camera[CAMERATYPE_PLAYER].rot.y) * 0.2f;

	//�J������]�̐��K��
	if (g_camera[CAMERATYPE_PLAYER].rot.y < -D3DX_PI)
	{
		g_camera[CAMERATYPE_PLAYER].rot.y += D3DX_PI * 2.0f;
	}
	else if (g_camera[CAMERATYPE_PLAYER].rot.y > D3DX_PI)
	{
		g_camera[CAMERATYPE_PLAYER].rot.y -= D3DX_PI * 2.0f;
	}

	if (g_camera[CAMERATYPE_PLAYER].rotDest.y - g_camera[CAMERATYPE_PLAYER].rot.y > D3DX_PI)
	{
		g_camera[CAMERATYPE_PLAYER].rotDest.y -= D3DX_PI * 2.0f;
	}
	else if (g_camera[CAMERATYPE_PLAYER].rotDest.y - g_camera[CAMERATYPE_PLAYER].rot.y < -D3DX_PI)
	{
		g_camera[CAMERATYPE_PLAYER].rotDest.y += D3DX_PI * 2.0f;
	}
}

//========================================================
//					�J�����ݒ菈��
//========================================================
void SetCamera(int nIdxCamera)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�r���[�|�[�g�̐ݒ�
	pDevice->SetViewport(&g_camera[nIdxCamera].viewport);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera[nIdxCamera].mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera[nIdxCamera].mtxView,
		&g_camera[nIdxCamera].posV,
		&g_camera[nIdxCamera].posR,
		&g_camera[nIdxCamera].vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera[nIdxCamera].mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera[nIdxCamera].mtxProjection);
		
	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_camera[nIdxCamera].mtxProjection,
		D3DXToRadian(75.0f - (nIdxCamera * 30.0f)),
		(float)g_camera[nIdxCamera].viewport.Width / (float)g_camera[nIdxCamera].viewport.Height,
		10.0f,
		1000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera[nIdxCamera].mtxProjection);
}

//========================================================
//				�J���������擾
//========================================================
Camera *GetCamera(void)
{
	return &g_camera[0];
}
