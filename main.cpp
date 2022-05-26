#include "DxLib.h"
#include "Vector3.h"


//���̕`��
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);

//�����̕`��
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color);

//�J�����̈ʒu�Ǝp���̐ݒ�
// DxLib => int SetCameraPositionAndTargetAndUpVec(VECTOR Position, VECTOR Target, VECTOR Up);
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,	//�J�����̈ʒu
	const Vector3& cameraTarget,	//�J�����̒��ӓ_
	const Vector3& cameraUp			//�J�����̏�̌���
);

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
	Vector3 cameraPosition(0.0f, 0.0f, -30.0f);
	//Vector3 cameraPosition(0.0f, 10.0f, 30.0f);
	Vector3 cameraTarget  (0.0f, 0.0f, 0.0f);
	Vector3 cameraUp	  (0.0f, 1.0f, 0.0f);

	SetCameraPositionAndTargetAndUpVec(
		cameraPosition,		//�J�����̈ʒu
		cameraTarget,		//�J�����̒����_
		cameraUp);			//�J�����̏�̌���

	Vector3 A(3, -1, 2);
	Vector3 B(1, 5, -4);
	Vector3 C(-1, 7, 6);

	Vector3 AB = B - A;	//AB�x�N�g���̐���
	Vector3 BC = C - B;	//BC�x�N�g���̐���

	Vector3 n = AB.cross(BC);	//�@���x�N�g�������߂�(AB�x�N�g����BC�x�N�g���̊O�ς����߂�)
	n.normalize();				//�@���x�N�g���̒P�ʃx�N�g����

	float th = 270.0f;	//�J���������

	//�Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//�X�V
		/*th += 0.2f;
		float radian = th * PI / 180.0f;
		cameraPosition = Vector3(std::cosf(radian) * 30, 0.0f, std::sinf(radian)*30);

		SetCameraPositionAndTargetAndUpVec(
			cameraPosition,
			cameraTarget,
			cameraUp
		);*/

		Vector3 v = cameraPosition - (A + B + C) / 3.0f;	//���_�ւ̕����x�N�g��
		v.normalize();

		unsigned color = GetColor(255, 255, 255);

		if (v.dot(n) < 0)
		{
			color = GetColor(255, 0, 0);
		}

		//�`��
		ClearDrawScreen();	//��ʂ�����

		DrawLine3D(A, B, color);
		DrawLine3D(B, C, color);
		DrawLine3D(C, A, color);

		//�@���̎��o��
		DrawLine3D(A, A + n, GetColor(0, 255, 0));
		DrawLine3D(B, B + n, GetColor(0, 255, 0));
		DrawLine3D(C, C + n, GetColor(0, 255, 0));

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

int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,	//�J�����̈ʒu
	const Vector3& cameraTarget,	//�J�����̒��ӓ_
	const Vector3& cameraUp			//�J�����̏�̌���
) {
	VECTOR position = { cameraPosition.x,cameraPosition.y,cameraPosition.z };
	VECTOR target = { cameraTarget.x,cameraTarget.y,cameraTarget.z };
	VECTOR up = { cameraUp.x,cameraUp.y,cameraUp.z };

	return SetCameraPositionAndTargetAndUpVec(position, target, up);
}
