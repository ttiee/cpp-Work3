// HomeWork1.cpp : 定义应用程序的入口点。
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "framework.h"
#include "HomeWork1.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int left = 100, top = 20, right = left + 250, bottom = top + 400;
char c1, c2;
int x = -1, y = -1;
int iScoring = 0, iFail = 0;
int gameover = 0;

void DrawBk(HDC hdc, int left, int top, int right, int bottom);

void ShowScoring(HDC hdc, int x, int y, int iScoring, int iFail);

void GameOver(HDC hdc, int x, int y);

void Fire(HDC hdc, int x, int y1, int y2);

void PlayCorrectSound();

void PlayWrongSound();

void PlayStartSound();

void PlayGameOverSound();

void PlayAboutSound();

void PlayQuitSound();


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HOMEWORK1, szWindowClass, MAX_LOADSTRING);
    MessageBoxW(NULL, TEXT("点击确定开始游戏"), TEXT("打字游戏 v0.5.0"), MB_OK);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HOMEWORK1));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    //MessageBoxW(NULL, TEXT("游戏结束"), TEXT("打字游戏 v0.5.0"), MB_OK);
    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HOMEWORK1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HOMEWORK1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   int screenWidth = GetSystemMetrics(SM_CXSCREEN);
   int screenHeight = GetSystemMetrics(SM_CYSCREEN);

   int WindowWidth = 500;
   int WindowHeight = 540;

   int x = (screenWidth - WindowWidth) / 2;
   int y = (screenHeight - WindowHeight) / 2;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      x, y, WindowWidth, WindowHeight, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_TIMER:
        switch (wParam)
        {
            case 1:
				y = y + iScoring / 10 + 1;
                if (y > bottom - 40)
                {
                    gameover = 1;
                    KillTimer(hWnd, 1);
                    SetTimer(hWnd, 2, 300, NULL);
                }
				InvalidateRect(hWnd, 0, 0);
				break;
            case 2:
                KillTimer(hWnd, 2);
                PlayGameOverSound();
				InvalidateRect(hWnd, 0, 0);
				break;
            case 3:
                KillTimer(hWnd, 3);
				DestroyWindow(hWnd);
				break;
        }
        break;
    case WM_CHAR:
    {
        c2 = (wParam >= 'a' && wParam <= 'z') ? wParam + 'A' - 'a' : wParam;
        HDC hdc = GetDC(hWnd);
        Fire(hdc, left + 5 + (c2 - 'A')*9 + 4, top, bottom);
        ReleaseDC(hWnd, hdc);
        if (c2 == c1)
        {
			c1 = rand() % 26 + 'A';
			x = left + 5 + (c1 - 'A') * 9;
			y = top;
			iScoring++;
            PlayCorrectSound();
		}
        else
        {
			iFail++;
            PlayWrongSound();
		}
    }
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                PlayAboutSound();
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                PlayQuitSound();
                SetTimer(hWnd, 3, 500, NULL);
                //DestroyWindow(hWnd);
                break;
            case ID_START: 
                if (gameover == 1)
                    KillTimer(hWnd, 2);
                gameover = 0;
                iScoring = 0;
                iFail = 0;
                UpdateWindow(hWnd);
                PlayStartSound();
                c1 = rand() % 26 + 'A';
                x = left + 5 + (c1 - 'A') * 9;
                y = top;
                SetTimer(hWnd, 1, 10, NULL);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            DrawBk(hdc, left, top, right, bottom);
            ShowScoring(hdc, right + 20, top + 50, iScoring, iFail);
            if (gameover == 1)
				GameOver(hdc, right + 20, top + 130);
            else
            {
                char szTemp[8];
                sprintf(szTemp, "%c", c1);
                TextOutA(hdc, x, y, szTemp, strlen(szTemp));
            }
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
