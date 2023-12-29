#define _CRT_SECURE_NO_WARNINGS
// Windows ͷ�ļ�
#include "myfunc.h"


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


void DrawBk(HDC hdc, int left, int top, int right, int bottom)
{
    Rectangle(hdc, left, top, right, bottom);
    char s[100] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    TextOutA(hdc, left + 5, bottom - 25, s, strlen(s));
}

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

void GameOver(HDC hdc, int x, int y)
{
    COLORREF OldColor, NewColor = RGB(rand() % 255, rand() % 255, rand() % 255);
    OldColor = SetTextColor(hdc, NewColor);
    TextOutA(hdc, x, y, "Game Over!", strlen("Game Over!"));
    SetTextColor(hdc, OldColor);
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