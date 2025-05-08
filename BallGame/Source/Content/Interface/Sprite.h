#pragma  once

class	Sprite
{
public:
	Sprite(DXTEXTURE pTexture, VECTOR3 pPosition, VECTOR3 pScale, float pRotation, size_t pColor);
	virtual ~Sprite();
	//	Values
	DXTEXTURE			Image;
	SpriteImageInfo		Infomation;

	VECTOR3				Position;
	VECTOR3				Center;

	size_t				Color;

	D3DXMATRIX			Transform;
};