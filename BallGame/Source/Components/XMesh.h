#pragma once

class XMesh	:	public Abstract_Mesh
{
	LPDIRECT3DDEVICE9	m_pDevice;
protected:
	LPD3DXMESH		m_pMesh;
	DWORD			m_MaterialCount;

	std::vector<D3DMATERIAL9>			m_Materials;
	std::vector<LPDIRECT3DTEXTURE9>		m_Textures;
public:
	XMesh();
	virtual ~XMesh();


	bool	Load(const std::string & FilePath);
	void	Render();
};