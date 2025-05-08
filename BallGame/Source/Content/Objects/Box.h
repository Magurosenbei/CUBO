#pragma once

class Box	:	public Abstract_PhysicsObject,	public	Abstract_DisplayObject
{
protected:
	VECTOR4				m_vColor;
	ColorTransistion	m_ColorEffect;

	float				m_fColorElapsedTime;

	bool				m_bSink;
	float				m_fSinkElapsedTime;

	float				m_fShake;

	size_t				m_ColorCode;

	audiere::SoundEffectPtr		m_pSoundEffect;
	bool						m_bPlayedSound;
public:
	Box();
	virtual ~Box();

	inline	size_t	COLORCODE()		{	return	m_ColorCode;				}
	inline	bool	COLORCOMPLETE()	{	return	m_ColorEffect.Completed();	}
	inline	VECTOR4	COLOR()	const	{	return m_vColor;					}

	virtual	void Initialize(const btVector3 &	Position, 
							const float		&	Mass, 
							const btVector3 &	Extents, 
							bool				IsKinematic = true,
							bool				RandomColor = true,
							bool				Display		= true);

	virtual	void Update(const float & Interval);
	virtual	void DropBox(bool Yes);

	virtual	void Render();
};