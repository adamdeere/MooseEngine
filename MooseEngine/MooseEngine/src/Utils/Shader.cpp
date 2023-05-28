#include "pch.h"
#include "Shader.h"

Shader::Shader(GraphicsDevice_DX* graphics): 
    m_Graphics(graphics)
{
}

Shader::~Shader()
{
    if(g_pVertexShader)g_pVertexShader->Release();
    if (g_pPixelShader)g_pPixelShader->Release();
//C:\Users\adamd\source\repos\MooseEngine\MooseEngine\MooseEngine\Shaders\Tutorial04.fx
}

HRESULT Shader::InitShader(ShaderProperties* props)
{
    ID3D11Device* device = m_Graphics->getDevice();
    HRESULT hr = S_OK;
    // Compile the vertex shader
    ID3DBlob* pVSBlob = nullptr;
    hr = CompileShaderFromFile(props->szFileName, props->vsEntryPoint, props->vsShaderModel, &pVSBlob);
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
    hr = device->CreateInputLayout(props->layout, props->numElements, pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(), &g_pVertexLayout);
    pVSBlob->Release();

    if (FAILED(hr))
        return hr;

    // Set the input layout
    m_Graphics->getContext()->IASetInputLayout(g_pVertexLayout);

    // Compile the pixel shader
    ID3DBlob* pPSBlob = nullptr;
    hr = CompileShaderFromFile(props->szFileName, props->psEntryPoint, props->psEntryPoint, &pPSBlob);
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
    return E_NOTIMPL;
}
