#pragma once
#include "GraphicsDevice_DX.h"
class Shader;
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
	Scene(GraphicsDevice_DX* const graphicsInstance);
	~Scene();
	HRESULT LoadScene(HWND const g_hWnd);
	void UpdateScene();
	void RenderScene();
private:

	GraphicsDevice_DX* gm;
	Shader* shader;
	ID3D11Buffer* g_pVertexBuffer = nullptr;
	ID3D11Buffer* g_pIndexBuffer = nullptr;
	ID3D11Buffer* g_pConstantBuffer = nullptr;
	XMMATRIX                g_World = XMMatrixIdentity();
	XMMATRIX                g_View = XMMatrixIdentity();
	XMMATRIX                g_Projection = XMMatrixIdentity();
};
