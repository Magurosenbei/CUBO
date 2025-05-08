#pragma once

class Camera	:	public	Abstract_Single<Camera>, public	Abstract_SubProgram,	public	Abstract_Renderable
{
	friend class Abstract_Single<Camera>;
	LPDIRECT3DDEVICE9	m_pDeviceRef;
	InputHandle		*	m_pInputRef;
protected:
	D3DXMATRIX	matView;
	D3DXMATRIX	matProjection;

	D3DXVECTOR4	m_vEye;
	D3DXVECTOR4	m_vLook;

	D3DXVECTOR4	m_vFront;
	D3DXVECTOR4	m_vRight;
	D3DXVECTOR4	m_vUp;

	float		m_fSpeed;

	Camera();
public:
	virtual	~Camera();

	inline	D3DXMATRIX	ViewMatrix()		const {	return	matView;		}
	inline	D3DXMATRIX	ProjectionMatrix()	const {	return	matProjection;	}


	inline	D3DXVECTOR4	Position()	const	{	return m_vEye;	}
	inline	D3DXVECTOR4	Look()		const	{	return m_vLook;	}
	inline	D3DXVECTOR4	Front()		const	{	return m_vFront;}
	inline	D3DXVECTOR4	Right()		const	{	return m_vRight;}
	inline	D3DXVECTOR4	Up()		const	{	return m_vUp;	}

	inline	void	Position(const D3DXVECTOR4 & v)		{	m_vEye = v;	}
	inline	void	Look(const D3DXVECTOR4 & v)			{	m_vLook = v;}

	virtual	void	Initialize();
	virtual void	Update(const float & Interval);
	virtual void	Render(const size_t & RenderTargetID, const size_t & Width, const size_t & Height);
};