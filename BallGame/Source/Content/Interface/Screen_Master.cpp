#include "stdafx.h"
#include "Screen_Master.h"

Screen_Master::Screen_Master()
{
	m_fRatio = 0.0f;

	m_InputRef = SmartPtr<InputHandle>(InputHandle::Instance());

	HRESULT Result = D3DXCreateSprite(DxDevice::Instance()->Device(), &m_pSpriteBatch);
	ASSERT(Result == S_OK, "Unable to create sprite batch");
}

Screen_Master::~Screen_Master()
{
	m_InputRef.release();
	m_pSpriteBatch->Release();
}

void	Screen_Master::Update(const float & Interval)
{

}

void	Screen_Master::Render()
{

}