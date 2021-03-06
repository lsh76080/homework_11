// homework_11.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "homework_11.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	srand((unsigned)time(NULL));
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HOMEWORK11));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_HOMEWORK11);
	wcex.lpszClassName = L"LineTestClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassExW(&wcex);

	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW(L"LineTestClass", L"선 긋기", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd) return FALSE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HOMEWORK11));

	MSG msg;

	// 기본 메시지 루프입니다.
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

POINT old_point;
bool is_L_button_click;
bool is_R_button_click;
HPEN my_pen;
HPEN old_pen;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_CREATE:
		my_pen = CreatePen(PS_SOLID, 10, RGB(0, 0, 0));
		break;
	case WM_LBUTTONDOWN:
		old_point.x = LOWORD(lParam);
		old_point.y = HIWORD(lParam);
		is_L_button_click = true;
		break;
	case WM_LBUTTONUP:
		is_L_button_click = false;
		break;
	case WM_RBUTTONDOWN:
	{
		if (old_pen != NULL) DeleteObject(old_pen);

		unsigned char r, g, b;
		r = rand() % 256;
		g = rand() % 256;
		b = rand() % 256;

		my_pen = CreatePen(PS_SOLID, 10, RGB(r, g, b));
	}
	break;
	case WM_RBUTTONUP:
		is_R_button_click = false;
		break;
	case WM_MOUSEMOVE:
	{
		if (is_L_button_click) {
			HDC hdc = GetDC(hWnd);

			POINT p = { LOWORD(lParam) ,HIWORD(lParam) };
			old_pen = (HPEN)SelectObject(hdc, my_pen);

			MoveToEx(hdc, old_point.x, old_point.y, NULL);
			LineTo(hdc, p.x, p.y);

			old_point = p;

			ReleaseDC(hWnd, hdc);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
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
