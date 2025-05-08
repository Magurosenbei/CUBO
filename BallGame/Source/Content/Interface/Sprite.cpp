#include "stdafx.h"
#include "Sprite.h"

Sprite::Sprite(DXTEXTURE pTexture, VECTOR3 pPosition, VECTOR3 pScale, float pRotation, size_t pColor)
:	Image(pTexture), Infomation(pTexture), Position(pPosition), Center(0, 0, 0), Color(pColor)
{
	Center.x = Infomation.Width >> 1;
	Center.y = Infomation.Height >> 1;

	D3DXMATRIX matScale;
	D3DXMATRIX matTranslation;
	D3DXMATRIX matRotation;

	D3DXMatrixTranslation(&matTranslation, pPosition.x, pPosition.y, pPosition.z);
	D3DXMatrixScaling(&matScale, pScale.x, pScale.y, pScale.z);
	D3DXMatrixRotationZ(&matRotation, pRotation);

	D3DXMatrixMultiply(&matTranslation, &matRotation, &matTranslation);
	D3DXMatrixMultiply(&Transform, &matScale, &matTranslation);
}

Sprite::~Sprite()
{
	Image = NULL;
}