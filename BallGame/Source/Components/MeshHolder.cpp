#include "stdafx.h"
#include "MeshHolder.h"

SmartPtr<MeshHolder> Abstract_Single<MeshHolder>::m_pInstance;

void MeshHolder::AddMesh(std::string FilePath, size_t Type)
{
	FilePath = System_Utility::LowerCase(FilePath.c_str());
	std::map<std::string, Abstract_Mesh *>::iterator it = m_Meshes.find(FilePath);
	if(it != m_Meshes.end())
	{
		WriteCommandLine("File Already Existed, Ignoring...");
		return;
	}
	Abstract_Mesh * Mesh(NULL);
	switch(Type)
	{
	case XFILE:
		Mesh = new XMesh;
		break;
	case OBJFILE:
		Mesh = new OBJMesh;
		break;
	default:
		Mesh = NULL;
		WriteCommandLine("File Type not supported");
		return;
	}
	bool Result = Mesh->Load(FilePath);
	ASSERT(Result, "Failed to load mesh file");
	m_Meshes.insert(std::make_pair(FilePath, Mesh));
}

Abstract_Mesh * MeshHolder::GetMesh(std::string FilePath)
{
	FilePath = System_Utility::LowerCase(FilePath.c_str());
	std::map<std::string, Abstract_Mesh *>::iterator it = m_Meshes.find(FilePath);
	if(it != m_Meshes.end())
		return it->second;
	WriteCommandLine("Warning >> Mesh Not found %s", FilePath.c_str());
	return NULL;
}

void MeshHolder::ClearMeshes()
{
	for(std::map<std::string, Abstract_Mesh *>::iterator it = m_Meshes.begin();
		it != m_Meshes.end();
		it++)
	{
		delete it->second;
		it->second = NULL;
	}
	m_Meshes.clear();
}