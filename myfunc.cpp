#define _CRT_SECURE_NO_WARNINGS
// Windows 头文件
#include "myfunc.h"


void DrawBk(HDC hdc, int left, int top, int right, int bottom)
{
    Rectangle(hdc, left, top, right, bottom);
    char s[100] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    TextOutA(hdc, left + 5, bottom - 25, s, strlen(s));
}

void ShowScoring(HDC hdc, int x, int y, int iScoring, int iFail)
{
    char szTemp[32];
    TextOutA(hdc, x, y, "当前得分：", strlen("当前得分：")); \
        y += 20;
    sprintf(szTemp, "%d", iScoring);
    TextOutA(hdc, x, y, szTemp, strlen(szTemp));
    y += 20;
    TextOutA(hdc, x, y, "当前失误：", strlen("当前失误："));
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