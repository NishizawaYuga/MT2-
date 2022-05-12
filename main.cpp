#include "DxLib.h"
#include "Vector3.h"


//���̕`��
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);

//�����̕`��
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	const int WindowWidth = 1024;
	const int WindowHeight = 576;

	ChangeWindowMode(true);							//�E�B���h�E���[�h�ɂ���
	SetGraphMode(WindowWidth, WindowHeight, 32);	//��ʃ��[�h�̃Z�b�g
	SetBackgroundColor(0, 0, 64);					//�w�i�F RGB
	if (DxLib_Init() == -1) return -1;				//DxLib�������ݒ�
	SetDrawScreen(DX_SCREEN_BACK);					//�`����ʂ𗠉�ʂɃZ�b�g

	//�N���b�v��	  ��	 ��
	SetCameraNearFar(1.0f, 1000.0f);		//�J�����̗L���͈͂�ݒ�
	SetCameraScreenCenter(WindowWidth / 2.0f, WindowHeight / 2.0f);	//��ʂ̒��S���J�����̒��S�ɍ��킹��
	SetCameraPositionAndTargetAndUpVec(
		VGet(0.0f, 0.0f, -100.0f),	//�J�����̈ʒu
		VGet(0.0f, 0.0f, 0.0f),		//�J�����̒����_
		VGet(0.0f, 1.0f, 0.0f));	//�J�����̏�̌���

	Vector3 position(0, 0, 0);			//�ʒu
	Vector3 velocity(0.0f, 0.0f, 0.5f); //���x

	//�Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//�X�V
		position += velocity;

		//�`��
		ClearDrawScreen();	//��ʂ�����
		DrawSphere3D(position, 80.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

		//�t���b�v����
		ScreenFlip();
	}
	DxLib_End();	//DxLib �I�����
	return 0;		//�\�t�g�̏I��
}

//Vector3�^�𗘗p���₷�����邽�߂̃I�[�o�[���[�h�֐��Q

//���̕`��
//DxLib -> int DrawSphere3D(VECTOR, float r,int DivNum, unsigned int DifColor, unsigned int SpcColor, int FillFlag);
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag)
{
	VECTOR centerPos = { CenterPos.x,CenterPos.y,CenterPos.z };	//�\���� �������q���X�g

	return DrawSphere3D(centerPos, r, DivNum, DifColor, SpcColor, FillFlag);	//DxLib�֐��̌Ăяo��
}

//�����̕`��
//DxLib -> int DrawLine3D(VECTOR Pos1, VECTOR Pos2, unsigned int Color);
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color)
{
	VECTOR p1 = { Pos1.x,Pos1.y,Pos1.z }; //�\���� �������q���X�g
	VECTOR p2 = { Pos2.x,Pos2.y,Pos2.z }; //�\���� �������q���X�g

	return DrawLine3D(p1, p2, Color);	  //DxLib�֐��̌Ăяo��
}