#pragma once

class RenderTarget
{
	friend	class DxDevice;
	LPDIRECT3DDEVICE9	m_pDeviceRef;
protected:
	LPDIRECT3DSURFACE9	m_pSurface;
	LPDIRECT3DTEXTURE9	m_pSurfaceTexture;
	D3DVIEWPORT9		m_Viewport;
	D3DFORMAT			m_Format;
	size_t m_ID;
	size_t m_Width;
	size_t m_Height;

	RECT				m_Rectangle;

	typedef std::map<std::string, Abstract_Renderable *> SubscriberList;
	SubscriberList	m_Subscribers;
public:
	//	Defaults at 128bit colors
	RenderTarget(const size_t & Width, const size_t & Height, const size_t & ID, D3DFORMAT Format = D3DFORMAT::D3DFMT_A32B32G32R32F);
	virtual ~RenderTarget();

	//	RenderTarget Surface
	inline LPDIRECT3DSURFACE9	SURFACE()	const	{	return	m_pSurface;			}
	//	Texture of RenderTarget
	inline LPDIRECT3DTEXTURE9	TEXTURE()	const	{	return	m_pSurfaceTexture;	}

	//	Subscribe to this Render Target
	void	Subscribe(const std::string & Key, Abstract_Renderable * Address);
	//	Unsubscribe from this render target
	void	UnSubscribe(const std::string & Key, Abstract_Renderable * Address);

	//	Only use for Multi Target Rendering
	inline	void	ActivateTarget()	{	m_pDeviceRef->SetRenderTarget(m_ID, m_pSurface);	}
	//	Only use for Multi Target Rendering
	inline	void	DeactivateTarget()	{	m_pDeviceRef->SetRenderTarget(m_ID, NULL);			}

	virtual bool	Initialize();
	virtual void	Render();
};