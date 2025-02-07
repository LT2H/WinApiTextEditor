#include "Core/Core.h"
#include <windows.h>

LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

HWND hMainWindow{};

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	// MessageBox(nullptr, L"HELLO", L"My title", MB_OK);
	WNDCLASSW wc{};

	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"myWindowClass";
	wc.lpfnWndProc = WindowProc;

	if (!RegisterClassW(&wc))
		return -1;

	hMainWindow = CreateWindowW(wc.lpszClassName,
		L"My Title",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		100,
		100,
		800,
		900,
		nullptr,
		nullptr,
		nullptr,
		nullptr);

	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_CREATE:
		break;

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProcW(hwnd, msg, wp, lp);
	}
}