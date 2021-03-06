// homework_11.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Graph.h"

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GRAPH));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_GRAPH);
	wcex.lpszClassName = L"GraphDrawClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassExW(&wcex);

	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW(L"GraphDrawClass", L"그래프 그리기", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	HWND hWnd1 = CreateWindowW(L"GraphDrawClass", L"그래프 그리기1", WS_CHILD | WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS, 0, 0, 300, 300, hWnd, nullptr, hInstance, nullptr);
	HWND hWnd2 = CreateWindowW(L"GraphDrawClass", L"그래프 그리기2", WS_CHILD | WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS, 300, 0, 300, 300, hWnd, nullptr, hInstance, nullptr);
	HWND hWnd3 = CreateWindowW(L"GraphDrawClass", L"그래프 그리기3", WS_CHILD | WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS, 600, 0, 300, 300, hWnd, nullptr, hInstance, nullptr);
	HWND hWnd4 = CreateWindowW(L"GraphDrawClass", L"그래프 그리기4", WS_CHILD | WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS, 0, 300, 300, 300, hWnd, nullptr, hInstance, nullptr);
	HWND hWnd5 = CreateWindowW(L"GraphDrawClass", L"그래프 그리기5", WS_CHILD | WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS, 300, 300, 300, 300, hWnd, nullptr, hInstance, nullptr);

	SetWindowLongPtr(hWnd, GWLP_USERDATA, 1000);
	SetWindowLongPtr(hWnd1, GWLP_USERDATA, 0);
	SetWindowLongPtr(hWnd2, GWLP_USERDATA, 1);
	SetWindowLongPtr(hWnd3, GWLP_USERDATA, 2);
	SetWindowLongPtr(hWnd4, GWLP_USERDATA, 3);
	SetWindowLongPtr(hWnd5, GWLP_USERDATA, 4);

	if (!hWnd) return FALSE;

	ShowWindow(hWnd, nCmdShow);
	ShowWindow(hWnd1, nCmdShow);
	ShowWindow(hWnd2, nCmdShow);
	ShowWindow(hWnd3, nCmdShow);
	ShowWindow(hWnd4, nCmdShow);
	ShowWindow(hWnd5, nCmdShow);


	UpdateWindow(hWnd);
	UpdateWindow(hWnd1);
	UpdateWindow(hWnd2);
	UpdateWindow(hWnd3);
	UpdateWindow(hWnd4);
	UpdateWindow(hWnd5);


	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GRAPH));

	MSG msg;

	// 기본 메시지 루프입니다.
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

#include <queue>

std::queue<int> q[5];

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		SetTimer(hWnd, 0, 70, NULL);
	}
	break;
	case WM_TIMER:
	{
		if (GetWindowLongPtr(hWnd, GWLP_USERDATA) != 1000) {
			HDC hdc = GetDC(hWnd);

			int temp = rand() % 200;
			if (temp < 100) temp += 100;
			q[GetWindowLongPtr(hWnd, GWLP_USERDATA)].push(temp);

			while (q[GetWindowLongPtr(hWnd, GWLP_USERDATA)].size() >= 50)
			{
				q[GetWindowLongPtr(hWnd, GWLP_USERDATA)].pop();
			}

			InvalidateRect(hWnd, NULL, true);
			ReleaseDC(hWnd, hdc);
		}

	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.

		if (GetWindowLongPtr(hWnd, GWLP_USERDATA) != 1000) {
			std::queue<int> temp_q = q[GetWindowLongPtr(hWnd, GWLP_USERDATA)];


			int i = 0;
			while (!temp_q.empty())
			{
				int y = temp_q.front();
				if (i == 0)MoveToEx(hdc, i, y, NULL);
				else LineTo(hdc, i * 7, y);

				i++;
				temp_q.pop();
			}

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
