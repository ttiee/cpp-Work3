#define _CRT_SECURE_NO_WARNINGS
// Bug���ࡣ����������ˡ�����
#include "myfunc.h"

extern int iScoring, iFail;
extern int char_x, char_y;
extern char target_char;
extern int left, top, right, bottom;

void ShowScoring(HDC hdc, int x, int y, int iScoring, int iFail);	// ��ʾ�÷�

void GameOver(HDC hdc, int x, int y);	// ��ʾ��Ϸ����

void Fire(HDC hdc, int x, int y1, int y2);	// ��ʾ���Ч��

void PlayCorrectSound();	// ������ȷ��Ч

void PlayWrongSound();	// ���Ŵ�����Ч

void PlayStartSound();	// ���ſ�ʼ��Ч

void PlayGameOverSound();	// ������Ϸ������Ч

void PlayAboutSound();	// ���Ź�����Ч

void PlayQuitSound();	// �����˳���Ч

void DrawWhiteBack(HDC hdc, int left, int top, int right, int bottom);	// ���ư�ɫ����

void SpawnChar();	// ����Ŀ���ַ�

void Draw_Ingame_rect(HDC hdc, int left, int top, int right, int bottom);	// ������Ϸ����

void DrawStartScreen(HDC hdc, int left, int top, int right, int bottom);	// ���ƿ�ʼ����

void DrawImage(HDC hdc, int x, int y, int w, int h, const char* filename);	// ����ͼƬ����

void DrawWhiteBack(HDC hdc, int left, int top, int right, int bottom);		// ���ư�ɫ����

void GameOver(HDC hdc, int x, int y);	// ��ʾ��Ϸ����

void ShowScoring(HDC hdc, int x, int y, int iScoring, int iFail);	// ��ʾ�÷�

void Fire(HDC hdc, int x, int y1, int y2);	// ��ʾ���Ч��

void SpawnChar() {
	target_char = rand() % 26 + 'A';
	char_x = left + 5 + (target_char - 'A') * 9;
	char_y = top;
}

// ������ȷ��Ч
void PlayCorrectSound()
{
	PlaySound(TEXT("sound/correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

// ���Ŵ�����Ч
void PlayWrongSound()
{
	PlaySound(TEXT("sound/wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

// ���ſ�ʼ��Ч
void PlayStartSound()
{
	PlaySound(TEXT("sound/start.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

// ������Ϸ������Ч
void PlayGameOverSound()
{
	PlaySound(TEXT("sound/quack.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

// ���Ź�����Ч
void PlayAboutSound()
{
	PlaySound(TEXT("sound/tuturu.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

// �����˳���Ч
void PlayQuitSound()
{
	PlaySound(TEXT("sound/vk.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

// ���ư�ɫ����
void DrawWhiteBack(HDC hdc, int left, int top, int right, int bottom)
{
	HBRUSH hOldBrush, hNewBrush = CreateSolidBrush(RGB(255, 255, 255));
	hOldBrush = (HBRUSH)SelectObject(hdc, hNewBrush);
	Rectangle(hdc, left, top - 5, right, bottom);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hNewBrush);
}

// ����ͼƬ����
void DrawImage(HDC hdc, int x, int y, int w, int h, const char* filename)
{
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = (HBITMAP)LoadImageA(NULL, filename, IMAGE_BITMAP, w, h, LR_LOADFROMFILE);
	SelectObject(hMemDC, hBitmap);
	BitBlt(hdc, x, y, w, h, hMemDC, 0, 0, SRCCOPY);
	DeleteDC(hMemDC);
	DeleteObject(hBitmap);
}

// ������Ϸ�ڽ���
void Draw_Ingame_rect(HDC hdc, int left, int top, int right, int bottom)
{
	const char* filename = "image/Win_game_bk_e.bmp";
	DrawImage(hdc, left - 10, top - 10, right - left + 20, bottom - top, filename);
}

// ���ƿ�ʼ����
void DrawStartScreen(HDC hdc, int left, int top, int right, int bottom)
{
	const char* filename = "image/Start.bmp";
	int w = 216, h = 100;
	int x1 = 132, y1 = 130;
	DrawImage(hdc, x1, y1, w, h, filename);
	char szTemp[32];
	sprintf(szTemp, "�� S ��ʼ��Ϸ");
	TextOutA(hdc, x1 + 50, y1 + 300, szTemp, strlen(szTemp));
}

// ������Ϸ��������
void GameOver(HDC hdc, int x, int y)
{
	const char* filename = "image/Game_Over_1.bmp";
	const char* filename2 = "image/restart_button.bmp";
	const char* filename3 = "image/menu.bmp";
	int w = 216, h = 216;
	int x1 = x - w / 2 - 20, y1 = y - h - 60;

	DrawImage(hdc, x1, y1, w, h, filename);
	DrawImage(hdc, x1, y1 + 280, 216, 57, filename2);
	ShowScoring(hdc, x1 + 50, y1 + 180, iScoring, iFail);
	DrawImage(hdc, x1, y1 + 410, 216, 57, "image/Restart.bmp");
	DrawImage(hdc, x1 + 80, y1 + 345, 50, 50, filename3);
}

// ��ʾ�÷�
void ShowScoring(HDC hdc, int x, int y, int iScoring, int iFail)
{
	char szTemp[32];
	TextOutA(hdc, x, y, "��ǰ�÷֣�", strlen("��ǰ�÷֣�")); \
		y += 20;
	//sprintf(szTemp, "%d", iScoring);
	_itoa(iScoring, szTemp, 10);
	TextOutA(hdc, x, y, szTemp, strlen(szTemp));
	y += 20;
	TextOutA(hdc, x, y, "��ǰʧ��", strlen("��ǰʧ��"));
	y += 20;
	sprintf(szTemp, "%d", iFail);
	TextOutA(hdc, x, y, szTemp, strlen(szTemp));
}

// ���ƴ��Ч��
void Fire(HDC hdc, int x, int y1, int y2)
{
	HPEN hOldPen, hNewPen = CreatePen(PS_DASHDOTDOT, 1, RGB(255, 0, 0));
	hOldPen = (HPEN)SelectObject(hdc, hNewPen);
	MoveToEx(hdc, x, y1, NULL);
	LineTo(hdc, x, y2);
	Sleep(100);
	HPEN hNewPen2 = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	SelectObject(hdc, hNewPen2);
	MoveToEx(hdc, x, y1, NULL);
	LineTo(hdc, x, y2);
	SelectObject(hdc, hOldPen);
	DeleteObject(hNewPen);
	DeleteObject(hNewPen2);
}