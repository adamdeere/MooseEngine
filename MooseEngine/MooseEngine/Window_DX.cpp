#include "pch.h"
#include "Window_DX.h"

Window_DX::Window_DX(long width,  long height) :
	m_Width(width), m_Height(height), g_hWnd(nullptr), g_hInst(nullptr)
{
}

Window_DX::Window_DX(const Window_DX& source) :
	m_Width(source.m_Width), m_Height(source.m_Height), g_hWnd(source.g_hWnd), g_hInst(source.g_hInst)
{
}

Window_DX& Window_DX::operator=(const Window_DX& source)
{
	if (this == &source)
	{
		return *this;
	}
	g_hWnd = source.g_hWnd;
	g_hInst = source.g_hInst;
	m_Width = source.m_Width;
	m_Height = source.m_Height;
	return *this;
}

Window_DX::~Window_DX()
{
}

LRESULT CALLBACK WndProc(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam)
{
	switch (message)
	{
	case WM_CHAR:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

HRESULT Window_DX::InitWindow(const HINSTANCE hInstance, const int nCmdShow)
{
	HRESULT hr;

	WNDCLASSEX wcex{};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"TutorialWindowClass";
	wcex.hIconSm = nullptr;
	hr = RegisterClassEx(&wcex);
	if (FAILED(hr))
		return hr;

	// Create window
	g_hInst = hInstance;
	RECT rc = { 0, 0, m_Width, m_Height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	HWND g_hWnd = CreateWindow(L"TutorialWindowClass", L"Direct3D 11 Tutorial 1: Direct3D 11 Basics",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
		nullptr);

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);
	return hr;
}

HRESULT Window_DX::InitDevice()
{
	return E_NOTIMPL;
}

int Window_DX::Run()
{
	MSG msg = { nullptr };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
		}
		
	}
	return (int)msg.wParam;
}