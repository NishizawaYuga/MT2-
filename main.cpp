#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	const int WindowWidth = 1024;
	const int WindowHeight = 576;

	ChangeWindowMode(true);							//�E�B���h�E���[�h�ɂ���
	SetGraphMode(WindowWidth, WindowHeight, 32);	//��ʃ��[�h�̃Z�b�g
	SetBackgroundColor(0, 0, 64);					//�w�i�F RGB
	if (DxLib_Init() == -1) return -1;				//DxLib�������ݒ�
	SetDrawScreen(DX_SCREEN_BACK);					//�`����ʂ𗠉�ʂɃZ�b�g

	//�Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();			//��ʂ�����

		//�X�V

		//�`��
		DrawCircle(WindowWidth / 2, WindowHeight / 2, 16, GetColor(128, 255, 128));	//�~��`��

		//�t���b�v����
		ScreenFlip();
	}
	DxLib_End();	//DxLib �I�����
	return 0;		//�\�t�g�̏I��
}