#pragma once
#include "Resource.h"
#include "framework.h"
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>

using namespace DirectX;

class GraphicsDevice_DX
{
public:
	GraphicsDevice_DX();
	~GraphicsDevice_DX();

	GraphicsDevice_DX(const GraphicsDevice_DX&) = delete;
	GraphicsDevice_DX& operator=(const GraphicsDevice_DX&) = delete;

	HRESULT InitilizeDrivers();
	HRESULT InitilizeFactory(const HWND g_hWnd);
	HRESULT InitilizeTargetView(const HWND g_hWnd);
	HRESULT CreateDepthStencil(const HWND g_hWnd);

	ID3D11DeviceContext* getContext()const;
	ID3D11Device* getDevice()const;
	IDXGISwapChain* getSwapChain()const;
	ID3D11DepthStencilView* getDepthStencilView()const;
	ID3D11RenderTargetView* getRenderTargetView()const;
	D3D_DRIVER_TYPE getDriverType()const;

private:
	ID3D11Device* g_pd3dDevice = nullptr;
	ID3D11DeviceContext* g_pImmediateContext = nullptr;
	IDXGISwapChain* g_pSwapChain = nullptr;
	ID3D11RenderTargetView* g_pRenderTargetView = nullptr;
	ID3D11DepthStencilView* g_pDepthStencilView = nullptr;
	D3D_DRIVER_TYPE         g_driverType;
	D3D_FEATURE_LEVEL       g_featureLevel;
	ID3D11Device1* g_pd3dDevice1 = nullptr;
	ID3D11DeviceContext1* g_pImmediateContext1 = nullptr;
	IDXGISwapChain1* g_pSwapChain1 = nullptr;
	ID3D11Texture2D* g_pDepthStencil = nullptr;
};
