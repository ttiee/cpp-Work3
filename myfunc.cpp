#define _CRT_SECURE_NO_WARNINGS
// Bug贼多。。。我真服了。。。
#include "myfunc.h"

extern int iScoring, iFail;


void PlayCorrectSound()
{
	PlaySound(TEXT("sound/correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void PlayWrongSound()
{
	PlaySound(TEXT("sound/wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void PlayStartSound()
{
	PlaySound(TEXT("sound/start.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void PlayGameOverSound()
{
	PlaySound(TEXT("sound/quack.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void PlayAboutSound()
{
	PlaySound(TEXT("sound/tuturu.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void PlayQuitSound()
{
	PlaySound(TEXT("sound/vk.wav"), NULL, SND_FILENAME | SND_ASYNC);
}


//void Draw_Ingame_rect(HDC hdc, int left, int top, int right, int bottom)
//{
//    Rectangle(hdc, left, top, right, bottom);
//    char s[100] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//    TextOutA(hdc, left + 5, bottom - 25, s, strlen(s));
//}

void DrawWhiteBack(HDC hdc, int left, int top, int right, int bottom)
{
	HBRUSH hOldBrush, hNewBrush = CreateSolidBrush(RGB(255, 255, 255));
	hOldBrush = (HBRUSH)SelectObject(hdc, hNewBrush);
	Rectangle(hdc, left, top, right, bottom);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hNewBrush);
}

void DrawImage(HDC hdc, int x, int y, int w, int h, const char* filename)
{
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = (HBITMAP)LoadImageA(NULL, filename, IMAGE_BITMAP, w, h, LR_LOADFROMFILE);
	SelectObject(hMemDC, hBitmap);
	BitBlt(hdc, x, y, w, h, hMemDC, 0, 0, SRCCOPY);
	DeleteDC(hMemDC);
	DeleteObject(hBitmap);
}

void Draw_Ingame_rect(HDC hdc, int left, int top, int right, int bottom)
{
	const char* filename = "image/Win_game_bk_e.bmp";
	DrawImage(hdc, left, top, right - left, bottom - top, filename);
}

void ShowScoring(HDC hdc, int x, int y, int iScoring, int iFail)
{
	char szTemp[32];
	TextOutA(hdc, x, y, "当前得分：", strlen("当前得分：")); \
		y += 20;
	//sprintf(szTemp, "%d", iScoring);
	_itoa(iScoring, szTemp, 10);
	TextOutA(hdc, x, y, szTemp, strlen(szTemp));
	y += 20;
	TextOutA(hdc, x, y, "当前失误：", strlen("当前失误："));
	y += 20;
	sprintf(szTemp, "%d", iFail);
	TextOutA(hdc, x, y, szTemp, strlen(szTemp));
}

//void GameOver(HDC hdc, int x, int y)
//{
//    COLORREF OldColor, NewColor = RGB(rand() % 255, rand() % 255, rand() % 255);
//    OldColor = SetTextColor(hdc, NewColor);
//    TextOutA(hdc, x, y, "Game Over!", strlen("Game Over!"));
//    SetTextColor(hdc, OldColor);
//}

void GameOver(HDC hdc, int x, int y)
{
	const char* filename = "image/Game_Over_1.bmp";
	int w = 216, h = 216;
	int x1 = x - w / 2 - 32, y1 = y - h;

	DrawImage(hdc, x1, y1, w, h, filename);
	ShowScoring(hdc, x1, y1 + 200, iScoring, iFail);
	DrawImage(hdc, x1, y1 + 300, 216, 57, "image/Restart.bmp");
}

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