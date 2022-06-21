//========================================================
//
//	���f���̏���[model.cpp]
//	AUTHOR:�z�{���V
//
//========================================================
#include "main.h"
#include "model.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "line.h"
#include "loadfileh.h"

//�O���[�o���ϐ�
MODEL g_model[MAX_MODEL];										//���f���̍\���̏����i�[
ModelInfo g_modelInfo[MAX_MODELTYPE];							//���f�����̍\���̂��i�[

//========================================================
//					���f������������
//========================================================
void InitModel(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�t�@�C���̓ǂݍ���
	LoadModelFile("data/model.txt",&g_modelInfo[0]);

	//�ʒu�E�����̏�����
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		g_model[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu�̏�����
		g_model[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�����̏�����
		g_model[nCntModel].bUse = false;						//�g�p����Ă��Ȃ���Ԃɂ���
	}

	int nNumVtx;												//���f���̒��_���̕ۑ��p
	DWORD sizeFVF;												//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;												//���_�o�b�t�@�ւ̃|�C���^

	//���_���̎擾
	for (int nCntType = 0; nCntType < MAX_MODELTYPE; nCntType++)
	{
		nNumVtx = g_modelInfo[nCntType].pMeshModel->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_modelInfo[nCntType].pMeshModel->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_modelInfo[nCntType].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			////���_���W���r���ă��f���̍ő�E�ŏ��l���擾
			//�ŏ��l
			if (vtx.x <= g_modelInfo[nCntType].vtxMin.x)
			{
				g_modelInfo[nCntType].vtxMin.x = vtx.x;
			}

			if (vtx.y <= g_modelInfo[nCntType].vtxMin.y)
			{
				g_modelInfo[nCntType].vtxMin.y = vtx.y;
			}

			if (vtx.z <= g_modelInfo[nCntType].vtxMin.z)
			{
				g_modelInfo[nCntType].vtxMin.z = vtx.z;
			}

			//�ő�l
			if (vtx.x >= g_modelInfo[nCntType].vtxMax.x)
			{
				g_modelInfo[nCntType].vtxMax.x = vtx.x;
			}

			if (vtx.y >= g_modelInfo[nCntType].vtxMax.y)
			{
				g_modelInfo[nCntType].vtxMax.y = vtx.y;
			}

			if (vtx.z >= g_modelInfo[nCntType].vtxMax.z)
			{
				g_modelInfo[nCntType].vtxMax.z = vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		//���_�o�b�t�@���A�����b�N
		g_modelInfo[nCntType].pMeshModel->UnlockVertexBuffer();
	}

	//���f�����Z�b�g
	SetModel(D3DXVECTOR3(75.0f, 0.0f, -75.0f));
	SetModel(D3DXVECTOR3(-75.0f, 0.0f, -75.0f));
	SetModel(D3DXVECTOR3(75.0f, 0.0f, 75.0f));
	SetModel(D3DXVECTOR3(-75.0f, 0.0f, 75.0f));
}

//========================================================
//					���f���I������
//========================================================
void UninitModel(void)
{
	//���b�V���̔j��
	for (int nCntMeshType = 0; nCntMeshType < MAX_MODELTYPE; nCntMeshType++)
	{
		if (g_modelInfo[nCntMeshType].pMeshModel != NULL)
		{
			g_modelInfo[nCntMeshType].pMeshModel->Release();
			g_modelInfo[nCntMeshType].pMeshModel = NULL;
		}
	}

	//�}�e���A���̔j��
	for (int nCntMatType = 0; nCntMatType < MAX_MODELTYPE; nCntMatType++)
	{
		if (g_modelInfo[nCntMatType].pBuffMatModel != NULL)
		{
			g_modelInfo[nCntMatType].pBuffMatModel->Release();
			g_modelInfo[nCntMatType].pBuffMatModel = NULL;
		}
	}
}

//========================================================
//					���f���X�V����
//========================================================
void UpdateModel(void)
{
	//if (GetKeyboardTrigger(DIK_F7))
	//{
	//	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	//	{
	//		if (g_model[nCntModel].bUse == true)
	//		{
	//			SetLine(g_model[nCntModel].pos, g_model.rot, D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMin.y, g_model.vtxMin.z), D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMin.y, g_model.vtxMax.z));
	//			SetLine(g_model[nCntModel].pos, g_model.rot, D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMin.y, g_model.vtxMin.z), D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMin.y, g_model.vtxMin.z));
	//			SetLine(g_model[nCntModel].pos, g_model.rot, D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMin.y, g_model.vtxMin.z), D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMin.y, g_model.vtxMax.z));
	//			SetLine(g_model[nCntModel].pos, g_model.rot, D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMin.y, g_model.vtxMax.z), D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMin.y, g_model.vtxMax.z));
	//			SetLine(g_model.pos, g_model.rot, D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMin.y, g_model.vtxMin.z), D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMax.y, g_model.vtxMin.z));
	//			SetLine(g_model.pos, g_model.rot, D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMin.y, g_model.vtxMin.z), D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMax.y, g_model.vtxMin.z));
	//			SetLine(g_model.pos, g_model.rot, D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMin.y, g_model.vtxMax.z), D3DXVECTOR3(g_model.vtxMin.x, g_model.vtxMax.y, g_model.vtxMax.z));
	//			SetLine(g_model.pos, g_model.rot, D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMin.y, g_model.vtxMax.z), D3DXVECTOR3(g_model.vtxMax.x, g_model.vtxMax.y, g_model.vtxMax.z));
	//		}
	//	}
	//}
}

//========================================================
//					���f���`�揈��
//========================================================
void DrawModel(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_model[nCntModel].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_model[nCntModel].mtxWorld);

			//�����𔽓]
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_model[nCntModel].rot.y, g_model[nCntModel].rot.x, g_model[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_model[nCntModel].mtxWorld, &g_model[nCntModel].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_model[nCntModel].pos.x, g_model[nCntModel].pos.y, g_model[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_model[nCntModel].mtxWorld, &g_model[nCntModel].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_model[nCntModel].mtxWorld);

			//�}�e���A���f�[�^�̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_modelInfo[g_model[nCntModel].nType].pBuffMatModel->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)g_modelInfo[g_model[nCntModel].nType].nNumMatModel; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//���f���p�[�c�̕`��
				g_modelInfo[g_model[nCntModel].nType].pMeshModel->DrawSubset(nCntMat);
			}
		}
	}

	//�ێ����Ă����}�e���A����Ԃ�
	pDevice->SetMaterial(&matDef);
}

//========================================================
//				���f���̐ݒ菈��
//========================================================
void SetModel(D3DXVECTOR3 pos)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_model[nCntModel].bUse == false)
		{//bUse��false�̎�����
			g_model[nCntModel].pos = pos;						//�ʒu��ݒ�

			g_model[nCntModel].bUse = true;						//�g�p����Ă����Ԃɂ���

			break;
		}
	}
}

//========================================================
//				���f���̃T�C�Y�̍ő�l���擾����
//========================================================
D3DXVECTOR3 GetVtxMax(int nType)
{
	return g_modelInfo[nType].vtxMax;
}

//========================================================
//				���f���̃T�C�Y�̍ŏ��l���擾����
//========================================================
D3DXVECTOR3 GetVtxMin(int nType)
{
	return g_modelInfo[nType].vtxMin;
}

//========================================================
//				���f���̏����擾����
//========================================================
MODEL *GetModel(void)
{
	return &g_model[0];
}
