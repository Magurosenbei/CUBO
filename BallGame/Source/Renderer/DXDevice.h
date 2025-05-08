#pragma  once

class RenderTarget;
class DxDevice	:	public Abstract_Single<DxDevice>, public Abstract_Renderer
{
	friend class Abstract_Single<DxDevice>;
	LPDIRECT3D9							m_pD3D9;
	LPDIRECT3DDEVICE9					m_pDevice;

	LPD3DXSPRITE						m_pSpriteBatch;

	std::deque<RenderTarget *>			m_RenderTargets;
	LPDIRECT3DSURFACE9					m_pZBuffer;
	LPDIRECT3DSURFACE9					m_pBackBuffer;
	D3DVIEWPORT9						m_ViewPort;

	VECTOR3								m_ScreenOffset;

	SmartPtr<Abstract_Overlay>			m_pOverlay;
	
	SmartPtr<FontText>					m_pSystemText;
protected:
	DxDevice();
public:
	virtual ~DxDevice();
	inline	LPDIRECT3D9			D3D()			{	return m_pD3D9;			}
	inline	LPDIRECT3DDEVICE9	Device()		{	return m_pDevice;		}
	inline	LPD3DXSPRITE		SpriteBatch()	{	return m_pSpriteBatch;	}
	inline	D3DVIEWPORT9		ViewPort()		{	return m_ViewPort;		}

	inline Abstract_Overlay	*	Overlay()		{	return m_pOverlay.get();}

	inline void		Overlay(Abstract_Overlay * Overlay)	{	m_pOverlay = SmartPtr<Abstract_Overlay>(Overlay);	}

	virtual void	Resize();
	virtual bool	Initialze(HINSTANCE Instance, HWND	Hwnd);
	virtual	bool	Shutdown();
	virtual void	Render();

	virtual void	RegisterToTarget(const size_t & ID, const std::string & Key, Abstract_Renderable * Address);
	virtual void	UnRegisterToTarget(const size_t & ID, const std::string & Key, Abstract_Renderable * Address);

	inline RenderTarget * GetRenderTarget(const size_t & ID)	{	return m_RenderTargets[ID];	}
};

extern const D3DXVECTOR3	VECTOR3_X;
extern const D3DXVECTOR3	VECTOR3_Y;
extern const D3DXVECTOR3	VECTOR3_Z;

extern const D3DXVECTOR4	VECTOR4_X;
extern const D3DXVECTOR4	VECTOR4_Y;
extern const D3DXVECTOR4	VECTOR4_Z;

extern const D3DXVECTOR4	COLOR_RED;
extern const D3DXVECTOR4	COLOR_BLUE;
extern const D3DXVECTOR4	COLOR_GREEN;
extern const D3DXVECTOR4	COLOR_WHITE;
extern const D3DXVECTOR4	COLOR_BLACK;