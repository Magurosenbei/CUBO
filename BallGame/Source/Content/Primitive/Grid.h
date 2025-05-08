#pragma once

class Grid
{
	struct Vertex
	{
		D3DXVECTOR3	Position;
		D3DCOLOR	Color;	
	};
	size_t Personal_FVF;
protected:
	LPDIRECT3DDEVICE9		m_Device;
	Vertex					mVertice[90];
	LPDIRECT3DVERTEXBUFFER9	Buffer;
public:
	Grid();
	virtual ~Grid();

	virtual	bool Initialize();
	virtual	void Render();
};