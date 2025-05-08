#include "stdafx.h"
#include "SpriteImageInfo.h"


SpriteImageInfo :: SpriteImageInfo(DXTEXTURE Texture)
:	Width(0),	Height(0),	FrameX(0), FrameY(0)
{
	D3DSURFACE_DESC SurfaceDesc;
	Texture->GetLevelDesc(0, &SurfaceDesc);
	Height = SurfaceDesc.Height;
	Width = SurfaceDesc.Width;
	
	Rectangle.left = 0;
	Rectangle.top = 0;

	Rectangle.bottom = Height;
	Rectangle.right = Width;
}