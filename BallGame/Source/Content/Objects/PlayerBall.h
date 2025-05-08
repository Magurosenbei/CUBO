#pragma once

class PlayerBall	:	public	Abstract_PhysicsObject, public	Abstract_DisplayObject
{	
	SmartPtr<InputHandle>			m_pInputRef;
protected:
	float							m_fSpeed;
	btVector3						m_vAngularVelocity;

	btVector3						m_vBallOriginPosition;

	ColorTransistion				m_ColorEffect;
	float							m_fColorElapsedTime;
	size_t							m_ColorCode;
public:
	PlayerBall();
	virtual ~PlayerBall();

	inline	size_t		COLORCODE()		{	return	m_ColorCode;				}
	inline	bool		COLORCOMPLETE()	{	return	m_ColorEffect.Completed();	}
	inline	VECTOR4		COLOR()			{	return	m_ColorEffect.Color();		}

	virtual	bool Initialize(const btVector3 & Position, const float & Mass, const float & Size);
	virtual	void Update(const float & Interval);
	virtual	void Render();
};