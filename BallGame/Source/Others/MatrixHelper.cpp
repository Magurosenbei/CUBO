#include "stdafx.h"
#include "MatrixHelper.h"

D3DXMATRIX MatrixHelper::mat_IDENTITY;

void MatrixHelper::Initialize()
{
	D3DXMatrixIdentity(&mat_IDENTITY);
}