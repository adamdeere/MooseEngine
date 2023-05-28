#pragma once
#include "framework.h"
#include "GraphicsDevice_DX.h"
#include "Scene.h"
class Window_DX
{
public:
	Window_DX(long width, long height);
	Window_DX(const Window_DX& source);
	Window_DX& operator= (const Window_DX& source);
	~Window_DX();

	HRESULT InitWindow(const HINSTANCE hInstance, const int nCmdShow);
	HRESULT InitDevice();
	int Run();
private:
	long m_Width;
	long m_Height;
	HWND g_hWnd;
	HINSTANCE g_hInst;

	GraphicsDevice_DX* gm;
	Scene* scene;
};
