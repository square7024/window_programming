#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR	IpszWindowName = L"Window Programming Lab";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR IpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = IpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(IpszClass, IpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

#define MAX_POINTS 10

typedef struct {
	int x;
	int y;
} Point;

int is_duplicate(Point points[], int count, int x, int y) {
	for (int i = 0; i < count; i++) {
		if (points[i].x == x && points[i].y == y) {
			return 1;
		}
	}
	return 0;
}

void generate_unique_points(Point points[], int max_points) {
	int count = 0;
	while (count < max_points) {
		int x = (rand() % 81) * 10;
		int y = (rand() % 61) * 10;

		if (!is_duplicate(points, count, x, y)) {
			points[count].x = x;
			points[count].y = y;
			count++;
		}
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	TCHAR str[100];
	int num = 0;
	int x, y;

	switch (iMessage) {
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		srand(time(NULL));
		num = 0;
		x = 400;
		y = 300;

		wsprintf(str, L"%d: (%d, %d)", num, x, y);
		TextOut(hDC, x, y, str, lstrlen(str));

		Point points[MAX_POINTS];
		generate_unique_points(points, MAX_POINTS);
		
		for (int i = 0; i < MAX_POINTS; i++) {
			wsprintf(str, L"%d: (%d, %d)", i + 1, points[i].x, points[i].y);
			TextOut(hDC, points[i].x, points[i].y, str, lstrlen(str));

		}
		
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}