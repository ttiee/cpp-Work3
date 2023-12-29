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

int left = 100, top = 20, right = left + 250, bottom = top + 400;
char target_char, my_char;
int char_x = -1, char_y = -1;
int iScoring = 0, iFail = 0;
int gameover = 0;

int WindowWidth = 500;
int WindowHeight = 540;

enum GameState {
	StartScreen,
	InGame,
	GameOverScreen
};

GameState currentState = StartScreen;

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void Draw_Ingame_rect(HDC hdc, int left, int top, int right, int bottom);

void ShowScoring(HDC hdc, int x, int y, int iScoring, int iFail);

void GameOver(HDC hdc, int x, int y);

void Fire(HDC hdc, int x, int y1, int y2);

void PlayCorrectSound();

void PlayWrongSound();

void PlayStartSound();

void PlayGameOverSound();

void PlayAboutSound();

void PlayQuitSound();

void DrawWhiteBack(HDC hdc, int left, int top, int right, int bottom);

void SpawnChar() {
	target_char = rand() % 26 + 'A';
	char_x = left + 5 + (target_char - 'A') * 9;
	char_y = top;
}

void StartGame(HWND hWnd) {
	currentState = InGame;
	iScoring = 0;
	iFail = 0;
	SpawnChar();
	InvalidateRect(hWnd, 0, 0);
	//UpdateWindow(hWnd);
	PlayStartSound();
	SetTimer(hWnd, 1, 10, NULL);
}


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
	//MessageBoxW(NULL, TEXT("点击确定开始游戏"), TEXT("打字游戏 v0.5.0"), MB_OK);
	//if (MessageBoxW(NULL, TEXT("点击确定开始游戏"), TEXT("打字游戏 v0.5.0"), MB_OKCANCEL) == IDCANCEL)
	//	return 0;
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance(hInstance, nCmdShow))
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
	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HOMEWORK1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_HOMEWORK1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
			char_y = char_y + iScoring / 10 + 1;
			if (char_y > bottom - 40)
			{
				currentState = GameOverScreen;
				KillTimer(hWnd, 1);
				PlayGameOverSound();
				//SetTimer(hWnd, 2, 300, NULL);
			}
			InvalidateRect(hWnd, 0, 0);
			break;
		case 2:
			//KillTimer(hWnd, 2);
			InvalidateRect(hWnd, 0, 0);
			break;
		case 3:
			DestroyWindow(hWnd);
			break;
		}
		break;
	case WM_CHAR:
	{
		if (currentState == InGame) {
			if (wParam < 'a' || wParam > 'z')
				break;
			my_char = wParam - 'a' + 'A';
			HDC hdc = GetDC(hWnd);
			Fire(hdc, left + 5 + (my_char - 'A') * 9 + 4, top, bottom);
			ReleaseDC(hWnd, hdc);
			if (my_char == target_char)
			{
				SpawnChar();
				iScoring++;
				PlayCorrectSound();
			}
			else
			{
				iFail++;
				PlayWrongSound();
			}
		}
		else if (currentState == StartScreen)
		{
			if (wParam == 's' || wParam == 'S')
			{
				StartGame(hWnd);
			}
		}
		else
		{
			if (wParam == 'r' || wParam == 'R')
			{
				StartGame(hWnd);
				InvalidateRect(hWnd, 0, 0);
			}
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
			break;
		case ID_START:
			StartGame(hWnd);
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

		DrawWhiteBack(hdc, 0, 0, WindowWidth, WindowHeight);
		if (currentState == GameOverScreen) {
			GameOver(hdc, WindowHeight / 2, WindowWidth / 2);
			SetTimer(hWnd, 2, 300, NULL);
		}
		else if (currentState == StartScreen)
		{
			Draw_Ingame_rect(hdc, left, top, right, bottom);
		}
		else
		{
			Draw_Ingame_rect(hdc, left, top, right, bottom);
			ShowScoring(hdc, right + 20, top + 50, iScoring, iFail);
			char szTemp[8];
			sprintf(szTemp, "%c", target_char);
			TextOutA(hdc, char_x, char_y, szTemp, strlen(szTemp));
		}
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_CLOSE:
		SetTimer(hWnd, 3, 500, NULL);
		//HIDE_WINDOW(hWnd);
		PlayQuitSound();
		//DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		KillTimer(hWnd, 3);
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
