#include "stdafx.h"
#include "OBJMesh.h"

OBJMesh::OBJMesh()
:	m_Device(NULL), Buffer(NULL)
{

}

OBJMesh::~OBJMesh()
{
	Buffer->Release();
	m_Device = NULL;
}

bool OBJMesh::Load(const std::string & FilePath)
{
	m_Device = DxDevice::Instance()->Device();
	FILE * file(NULL);
	fopen_s(&file, &FilePath[0], "rt");

	if(file == NULL)	return false;
	fseek(file, 0, SEEK_END);
	size_t end = ftell(file);
	fseek(file, 0, SEEK_SET);

	size_t bytes = 0;
	char * memory = NULL;

	memory = (char *) malloc(end);
	bytes = fread(memory, sizeof(char), end, file);
	fclose(file);

	if(bytes < 1) {free(memory); return false;}

	WriteCommandLine("Begin Parsing %s", FilePath.c_str());
	char* p = NULL, * e = NULL;

	p = memory;
	e = memory + bytes;

	std::vector<VECTOR3>	Vertices;
	std::vector<VECTOR3>	Normals;
	std::vector<VECTOR2>	TexCoord;
	std::vector<Triangle>	Triangles;

	float x(0), y(0), z(0);
	Triangle T;
	memset(&T, 0x00, sizeof(T));
	
	while (p != e)
	{
		if (memcmp(p, "vn", 2) == 0)
		{
			sscanf_s(p, "vn %f %f %f", &x, &y, &z);
			Normals.push_back(VECTOR3(x, y, z));
		}
		else if (memcmp(p, "vt", 2) == 0)
		{
			sscanf_s(p, "vt %f %f",		&x, &y);
			TexCoord.push_back(VECTOR2(x, -y));
		}
		else if (memcmp(p, "v", 1) == 0) /* or *p == 'v' */
		{
			sscanf_s(p, "v %f %f %f", &x, &y, &z);
			Vertices.push_back(VECTOR3(x, y, z));
		}
		else if (memcmp(p, "f", 1) == 0) /* or *p == 'f' */
		{

			sscanf_s(p, "f %d/%d/%d %d/%d/%d %d/%d/%d",	
				&T.Vertex[0],&T.TexCoord[0],&T.Normal[0],
				&T.Vertex[1],&T.TexCoord[1],&T.Normal[1],
				&T.Vertex[2],&T.TexCoord[2],&T.Normal[2]);

			Triangles.push_back(T);
		}
		while (*p++ != (char) 0x0A);
	}
	free(memory);
	m_NumTriangles = Triangles.size();
	m_Vertices.assign(m_NumTriangles * 3, Vertex());
	size_t vindex = 0;
	for(size_t index = 0; index < Triangles.size(); index++)
	{
		for(size_t sindex = 0; sindex < 3; sindex++)
		{
			m_Vertices[vindex].Position = Vertices[Triangles[index].Vertex[sindex] - 1];
			m_Vertices[vindex].Normal = Normals[Triangles[index].Normal[sindex] - 1];
			m_Vertices[vindex].TexCoord = TexCoord[Triangles[index].TexCoord[sindex] - 1];
			vindex++;
		}
	}
	WriteCommandLine("End Parsing %s", FilePath.c_str());

	m_Device = DxDevice::Instance()->Device();
	LRESULT Result = m_Device->CreateVertexBuffer(m_Vertices.size() * sizeof(Vertex), 
		D3DUSAGE_WRITEONLY, CUSTOMFVF, D3DPOOL_MANAGED, &Buffer, NULL);
	ASSERT(Result == S_OK, "VertexBuffer Error");

	void * Memory;
	Buffer->Lock(0, 0, &Memory, 0);
	memcpy(Memory, &m_Vertices[0], sizeof(Vertex) * m_Vertices.size());
	Buffer->Unlock();
	m_Vertices.clear();
	return true;
}

void OBJMesh::Render()
{
	m_Device->SetFVF(CUSTOMFVF);
	m_Device->SetStreamSource(0, Buffer, 0, sizeof(Vertex));
	m_Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_NumTriangles);
}