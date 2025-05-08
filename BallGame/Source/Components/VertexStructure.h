#pragma once

#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//	May Remove COLOR
struct Vertex
{
	D3DXVECTOR3	Position;
	D3DXVECTOR3 Normal;

	D3DCOLOR	Color;	
	D3DXVECTOR2	TexCoord;

	Vertex()
		:	Position(0, 0, 0), Normal(0, 1, 0), 
			Color(0xffffffff), TexCoord(0, 0)
	{
	}
};


//Shader help
//#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX0)
//
//struct Vertex
//{
//	D3DXVECTOR3	Position;
//	D3DXVECTOR3 Normal;
//	D3DXVECTOR2	TexCoord;
//};