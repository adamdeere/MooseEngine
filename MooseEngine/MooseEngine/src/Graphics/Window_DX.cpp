#include "pch.h"
#include "Window_DX.h"

Window_DX::Window_DX(long width, long height) :
	m_Width(width), m_Height(height), g_hWnd(nullptr), g_hInst(nullptr), gm(nullptr), scene(nullptr)
{
}

Window_DX::Window_DX(const Window_DX& source) :
	m_Width(source.m_Width), m_Height(source.m_Height), g_hWnd(source.g_hWnd), g_hInst(source.g_hInst)
	, gm(source.gm), scene(source.scene)
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
	gm = source.gm;
	scene = source.scene;
	return *this;
}

Window_DX::~Window_DX()
{
	delete gm;
	delete scene;
}

LRESULT CALLBACK WndProc(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam)
{
	switch (message)
	{
	case WM_CHAR:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
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
	wcex.lpszClassName = L"MooseEngineWindow";
	wcex.hIconSm = nullptr;
	hr = RegisterClassEx(&wcex);
	if (FAILED(hr))
		return hr;

	// Create window
	g_hInst = hInstance;
	RECT rc = { 0, 0, m_Width, m_Height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	g_hWnd = CreateWindow(L"MooseEngineWindow", L"Moose Engine DX",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
		nullptr);

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	return hr;
}

HRESULT Window_DX::InitDevice()
{
	HRESULT hr;

	gm = new GraphicsDevice_DX();

	hr = gm->InitilizeDrivers();
	if (FAILED(hr))
		return hr;

	hr = gm->InitilizeFactory(g_hWnd);
	if (FAILED(hr))
		return hr;

	hr = gm->InitilizeTargetView(g_hWnd);
	if (FAILED(hr))
		return hr;

	hr = gm->CreateDepthStencil(g_hWnd);
	if (FAILED(hr))
		return hr;

	scene = new Scene(gm);
	hr = scene->LoadScene(g_hWnd);
	if (FAILED(hr))
		return hr;

	return hr;
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
			scene->UpdateScene();
			scene->RenderScene();
		}
	}
	return (int)msg.wParam;
}