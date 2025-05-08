#include "stdafx.h"
#include "grid.h"

Grid::Grid()
:	Personal_FVF(D3DFVF_XYZ | D3DFVF_DIFFUSE)
{

}
Grid::~Grid()
{
	m_Device = NULL;
	Buffer->Release();
}

bool Grid::Initialize()
{
	m_Device = DxDevice::Instance()->Device();
	LRESULT Result = m_Device->CreateVertexBuffer(90 * sizeof(Grid::Vertex), 
		D3DUSAGE_WRITEONLY, CUSTOMFVF, D3DPOOL_MANAGED, &Buffer, NULL);
	ASSERT(Result == S_OK, "VertexBuffer Error");

	size_t index = 0;
	for(int x = -100; x < 110; x += 10)
	{
		mVertice[index].Position = D3DXVECTOR3(x, 0, -100);
		mVertice[index].Color = ARGB(255, 0, 150, 0);
		mVertice[index + 1].Position = D3DXVECTOR3(x, 0, 100);
		mVertice[index + 1].Color = ARGB(255, 0, 150, 0);
		index += 2;
	}
	for(int z = -100; z < 110; z += 10)
	{
		mVertice[index].Position = D3DXVECTOR3(-100, 0, z);
		mVertice[index].Color = ARGB(255, 0, 150, 0);
		mVertice[index + 1].Position = D3DXVECTOR3(100, 0, z);
		mVertice[index + 1].Color = ARGB(255, 0, 150, 0);
		index += 2;
	}
	// Y +
	mVertice[index].Position = D3DXVECTOR3(0, 0, 0);
	mVertice[index++].Color = ARGB(255, 255, 255, 0);
	mVertice[index].Position = D3DXVECTOR3(0, 20, 0);
	mVertice[index++].Color = ARGB(255, 255, 255, 0);

	// Z +
	mVertice[index].Position = D3DXVECTOR3(0, 10, 0);
	mVertice[index++].Color = ARGB(255, 0, 255, 255);
	mVertice[index].Position = D3DXVECTOR3(0, 10, 10);
	mVertice[index++].Color = ARGB(255, 0, 255, 255);

	// X + Red
	mVertice[index].Position = D3DXVECTOR3(0, 10, 0);
	mVertice[index++].Color = ARGB(255, 255, 0, 0);
	mVertice[index].Position = D3DXVECTOR3(10, 10, 0);
	mVertice[index].Color = ARGB(255, 255, 0, 0);
	
	void * Memory;
	Buffer->Lock(0, 0, &Memory, 0);
	memcpy(Memory, mVertice, sizeof(Grid::Vertex) * 90);
	Buffer->Unlock();
	return true;
}

void Grid::Render()
{
	m_Device->SetTexture(0, NULL);
	m_Device->SetFVF(Personal_FVF);
	m_Device->SetStreamSource(0, Buffer, 0, sizeof(Grid::Vertex));
	m_Device->DrawPrimitive(D3DPT_LINELIST, 0, 45);
}
