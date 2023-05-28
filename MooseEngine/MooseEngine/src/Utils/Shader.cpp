#include "pch.h"
#include "Shader.h"

Shader::Shader(GraphicsDevice_DX* graphics) :
	m_Graphics(graphics)
{
}

Shader::~Shader()
{
	if (g_pVertexShader)g_pVertexShader->Release();
	if (g_pPixelShader)g_pPixelShader->Release();
	if (g_pVertexLayout)g_pVertexLayout->Release();
}

HRESULT Shader::InitShader(ShaderProperties props)
{
	ID3D11Device* device = m_Graphics->getDevice();
	HRESULT hr = S_OK;
	// Compile the vertex shader
	ID3DBlob* pVSBlob = nullptr;
	hr = CompileShaderFromFile(props.szFileName, props.vsEntryPoint, props.vsShaderModel, &pVSBlob);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the vertex shader
	hr = device->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &g_pVertexShader);
	if (FAILED(hr))
	{
		pVSBlob->Release();
		return hr;
	}

	// Create the input layout
	hr = device->CreateInputLayout(props.layout, props.numElements, pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(), &g_pVertexLayout);
	pVSBlob->Release();

	if (FAILED(hr))
		return hr;

	// Set the input layout
	m_Graphics->getContext()->IASetInputLayout(g_pVertexLayout);

	// Compile the pixel shader
	ID3DBlob* pPSBlob = nullptr;
	hr = CompileShaderFromFile(props.szFileName, props.psEntryPoint, props.pzShaderModel, &pPSBlob);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the pixel shader
	hr = device->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &g_pPixelShader);
	pPSBlob->Release();
	if (FAILED(hr))
		return hr;

	return hr;
}

void Shader::SetShaders()
{
	ID3D11DeviceContext* g_pImmediateContext = m_Graphics->getContext();
	g_pImmediateContext->VSSetShader(g_pVertexShader, nullptr, 0);
	g_pImmediateContext->PSSetShader(g_pPixelShader, nullptr, 0);
}

HRESULT Shader::CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows
	// the shaders to be optimized and to run exactly the way they will run in
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return hr;
}