#pragma once

class MeshHolder	:	public	Abstract_Single<MeshHolder>
{
	friend class Abstract_Single<MeshHolder>;
protected:
	std::map<std::string, Abstract_Mesh *>	m_Meshes;	
public:
	enum MESHTYPE	{	XFILE, OBJFILE	 };

	//	Use this at the start
	void			AddMesh(std::string FilePath, size_t Type);
	//	Remove all mesh
	void			ClearMeshes();

	//	Get Instance of the mesh
	Abstract_Mesh * GetMesh(std::string FilePath);
};