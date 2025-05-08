#pragma once

class	SpriteImageInfo
{
public:
	size_t				Height;
	size_t				Width;

	size_t				FrameX;
	size_t				FrameY;
	
	RECT				Rectangle;

	//	Creates Information based on the texture loaded
	SpriteImageInfo(DXTEXTURE Texture);
};