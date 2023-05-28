#pragma once
#include "GraphicsDevice_DX.h"

struct ShaderProperties
{
	const WCHAR* szFileName;
	LPCSTR vsEntryPoint;
	LPCSTR psEntryPoint;
	LPCSTR vsShaderModel;
	LPCSTR pzShaderModel;
	D3D11_INPUT_ELEMENT_DESC* layout;
	UINT numElements;
};

class Shader
{
public:
	Shader(GraphicsDevice_DX* graphics);
	~Shader();

	HRESULT InitShader(ShaderProperties* props);
	void SetShaders();

private:
	GraphicsDevice_DX* m_Graphics;
	ID3D11VertexShader* g_pVertexShader = nullptr;
	ID3D11PixelShader* g_pPixelShader = nullptr;
	ID3D11InputLayout* g_pVertexLayout = nullptr;
	HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
};

