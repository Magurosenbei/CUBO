#pragma once

class BoxDropper
{
	std::deque<Box	*>				m_Boxes;
	std::deque<Box	*>				m_ActiveBoxes;
	LPDIRECT3DTEXTURE9				m_pBoxTexture;
	bool							m_bActivated;

	float							m_fDropTime;

	SmartPtr<DefaultObjectEffect>	m_pEffect;	
public:
	BoxDropper(	const size_t & Amount, 
				const btVector3 & Min, 
				const btVector3 & Max);

	virtual ~BoxDropper();

	inline	bool	IsActivated()	{	return	m_bActivated;	}
	inline	void	Activate()		{	m_bActivated = true;	}

	virtual	void	Update(const float & Interval);
	virtual	void	Render();
};