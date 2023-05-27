#pragma once
#include "GraphicsDevice_DX.h"
//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct SimpleVertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};


struct ConstantBuffer
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;
};


class Scene
{
public:
	Scene();
	Scene (GraphicsDevice_DX* const graphicsInstance);
	~Scene();
	HRESULT LoadScene(HWND const g_hWnd);
	void UpdateScene();
	void RenderScene();
private:

	GraphicsDevice_DX* gm;

	ID3D11VertexShader* g_pVertexShader = nullptr;
	ID3D11PixelShader* g_pPixelShader = nullptr;
	ID3D11InputLayout* g_pVertexLayout = nullptr;
	ID3D11Buffer* g_pVertexBuffer = nullptr;
	ID3D11Buffer* g_pIndexBuffer = nullptr;
	ID3D11Buffer* g_pConstantBuffer = nullptr;
	XMMATRIX                g_World;
	XMMATRIX                g_View;
	XMMATRIX                g_Projection;

	HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
};

