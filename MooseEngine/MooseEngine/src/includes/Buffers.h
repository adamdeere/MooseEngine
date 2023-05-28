#pragma once
#include "GraphicsDevice_DX.h"
struct SimpleVertex
{
};
struct ColourVertex : SimpleVertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};