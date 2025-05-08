#include "stdafx.h"
#include "XMesh.h"

XMesh::XMesh()
{

}

XMesh::~XMesh()
{
	m_pDevice = NULL;
	m_pMesh->Release();
}

bool	XMesh::Load(const std::string & FilePath)
{
	m_pDevice = DxDevice::Instance()->Device();
	LPD3DXBUFFER	MaterialBuffer;

	HRESULT Result = D3DXLoadMeshFromXA(FilePath.c_str(), D3DXMESH_SYSTEMMEM, 
		m_pDevice, NULL, &MaterialBuffer, NULL, &m_MaterialCount, &m_pMesh);
	ASSERT(Result == S_OK, "Unable to load XMesh");
	
	D3DXMATERIAL * Materials = (D3DXMATERIAL *)MaterialBuffer->GetBufferPointer();
	m_Textures.assign(m_MaterialCount, NULL);
	m_Materials.assign(m_MaterialCount, D3DMATERIAL9());
	for(DWORD i = 0; i < m_MaterialCount; i++)
	{
		m_Materials[i] = Materials[i].MatD3D;
		m_Materials[i].Ambient = m_Materials[i].Diffuse;
		if (Materials[i].pTextureFilename)
			D3DXCreateTextureFromFileA(m_pDevice, Materials[i].pTextureFilename,     &m_Textures[i]);
	}
	MaterialBuffer->Release();
	return true;
}

void	XMesh::Render()
{
	for(size_t i = 0; i < m_MaterialCount; i++)
	{
		m_pDevice->SetTexture(0, m_Textures[i]);
		m_pDevice->SetMaterial(&m_Materials[i]);
		m_pMesh->DrawSubset(i);
	}	
}