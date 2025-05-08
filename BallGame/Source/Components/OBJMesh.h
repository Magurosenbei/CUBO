#pragma once

class OBJMesh : public Abstract_Mesh
{
	LPDIRECT3DDEVICE9		m_Device;
protected:
	struct Triangle 
	{
		size_t Vertex[3];
		size_t Normal[3];
		size_t TexCoord[3];
	};
	std::vector	<Vertex>	m_Vertices;
	size_t					m_NumTriangles;
	LPDIRECT3DVERTEXBUFFER9	Buffer;
public:
	OBJMesh();
	virtual ~OBJMesh();

	bool	Load(const std::string & FilePath);
	void	Render();
};