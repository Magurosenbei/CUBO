#include "stdafx.h"
#include "RenderTargets.h"

RenderTarget::RenderTarget(const size_t & Width, const size_t & Height, const size_t & ID, D3DFORMAT Format)
:	m_pDeviceRef(NULL), m_pSurface(NULL), m_pSurfaceTexture(NULL), 
	m_Format(Format), m_ID(ID), m_Width(Width), m_Height(Height) 
{

}
RenderTarget::~RenderTarget()
{
	m_pDeviceRef = NULL;
	m_pSurfaceTexture->Release();
	m_pSurface->Release();
}


void RenderTarget::Subscribe(const std::string & Key, Abstract_Renderable * Address)
{
	m_Subscribers.insert(std::make_pair(Key.c_str(), Address));
}

void RenderTarget::UnSubscribe(const std::string & Key, Abstract_Renderable * Address)
{
	SubscriberList::iterator it = m_Subscribers.find(Key.c_str());
	if(it->second == Address)
		m_Subscribers.erase(it);
	else
		WriteCommandLine("Warning >> %s : %p not found, unable to unsubscribe from RenderTarget", Key.c_str(), Address);
}


bool RenderTarget::Initialize()
{
	m_pDeviceRef = DxDevice::Instance()->Device();
	HRESULT Result = m_pDeviceRef->CreateTexture(	m_Width, m_Height, 1, 
													D3DUSAGE_RENDERTARGET, 
													m_Format, 
													D3DPOOL_DEFAULT, 
													&m_pSurfaceTexture, NULL);

	ASSERT(Result == S_OK, "Fail to make renderTarget Texture");

	Result = m_pSurfaceTexture->GetSurfaceLevel(0, &m_pSurface);
	ASSERT(Result == S_OK, "Fail to make Link surface to Texture");
	WriteCommandLine("RenderTarget %ix%i Created ", m_Width, m_Height);
	
	m_pDeviceRef->GetViewport(&m_Viewport);

	// Clean the Target, else the vcard will retain them
	D3DVIEWPORT9 vp = m_Viewport;
	vp.Height = m_Height;
	vp.Width = m_Width;
	m_pDeviceRef->SetRenderTarget(m_ID, m_pSurface);
	m_pDeviceRef->SetViewport(&vp);
	m_pDeviceRef->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, ARGB(0, 0, 0, 0), 1.0f, 0.0f);
	m_pDeviceRef->SetRenderTarget(m_ID, NULL);
	m_pDeviceRef->SetViewport(&m_Viewport);

	m_Rectangle.left = 0;
	m_Rectangle.top = 0;
	m_Rectangle.right = m_Width;
	m_Rectangle.bottom = m_Height;
	// Set this to draw in center of picture
	//m_Viewport.Width = m_Width;
	//m_Viewport.Height = m_Height;
	//m_Viewport.X = (m_Width - m_Viewport.Width) >> 1;
	//m_Viewport.Y = (m_Height - m_Viewport.Height) >> 1;
	return (Result == S_OK);
}

void RenderTarget::Render()
{
	HRESULT Result = m_pDeviceRef->SetRenderTarget(m_ID, m_pSurface);
	ASSERT(Result == S_OK, "Render Target Invalid")

	m_pDeviceRef->SetViewport(&m_Viewport);
	m_pDeviceRef->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, ARGB(255, 0, 0, 40), 1.0f, 0.0f);
	m_pDeviceRef->BeginScene();
	
	SubscriberList::iterator it = m_Subscribers.begin();
	for(; it != m_Subscribers.end(); it++)
		it->second->Render(m_ID, m_Width, m_Height);

	m_pDeviceRef->EndScene();
	m_pDeviceRef->SetRenderTarget(m_ID, NULL);
}