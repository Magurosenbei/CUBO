#pragma once

class Quad3D
{
protected:
	LPDIRECT3DDEVICE9		m_Device;
	Vertex					mVertice[4];
	LPDIRECT3DVERTEXBUFFER9	Buffer;
public:
	Quad3D();
	virtual ~Quad3D();

	virtual	bool Initialize();
	virtual	void Render();
};