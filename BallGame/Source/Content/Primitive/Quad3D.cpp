#include "stdafx.h"
#include "Quad3D.h"

Quad3D::Quad3D()
{

}
Quad3D::~Quad3D()
{
	m_Device = NULL;
	Buffer->Release();
}

bool Quad3D::Initialize()
{
	m_Device = DxDevice::Instance()->Device();
	LRESULT Result = m_Device->CreateVertexBuffer(4 * sizeof(Vertex), 
		D3DUSAGE_WRITEONLY, CUSTOMFVF, D3DPOOL_MANAGED, &Buffer, NULL);
	ASSERT(Result == S_OK, "VertexBuffer Error");

	mVertice[0].Position = D3DXVECTOR3(-0.5f,	-0.5f,	0);
	mVertice[1].Position = D3DXVECTOR3(0.5f,	-0.5f,	0);
	mVertice[2].Position = D3DXVECTOR3(-0.5f,	0.5f,	0);
	mVertice[3].Position = D3DXVECTOR3(0.5f,	0.5f,	0);

	mVertice[0].Color = ARGB(100, 255, 255, 255);
	mVertice[1].Color = ARGB(100, 255, 255, 255);
	mVertice[2].Color = ARGB(100, 255, 255, 255);
	mVertice[3].Color = ARGB(100, 255, 255, 255);

	mVertice[0].Normal = VECTOR3_Z;
	mVertice[1].Normal = VECTOR3_Z;
	mVertice[2].Normal = VECTOR3_Z;
	mVertice[3].Normal = VECTOR3_Z;

	mVertice[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	mVertice[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	mVertice[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
	mVertice[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	void * Memory;
	Buffer->Lock(0, 0, &Memory, 0);
	memcpy(Memory, mVertice, sizeof(Vertex) * 4);
	Buffer->Unlock();
	return true;
}

void Quad3D::Render()
{
	m_Device->SetFVF(CUSTOMFVF);
	m_Device->SetStreamSource(0, Buffer, 0, sizeof(Vertex));
	m_Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
