#pragma  once

class ColorTransistion
{
protected:
	VECTOR4							m_vColor;
	VECTOR4							m_vColorCurrent;
	VECTOR4							m_vColorFinal;
	float							m_fColorRatio;
	float							m_fTransistionSpeed;
public:
	ColorTransistion()
		:	m_fColorRatio(1.0f), m_fTransistionSpeed(4.0f)
	{
		switch(rand() % 3)
		{
		case 0:
			m_vColor = COLOR_RED;
			break;

		case 1:
			m_vColor = COLOR_BLUE;
			break;

		case 2:
			m_vColor = COLOR_GREEN;
			break;
		}
		m_vColorCurrent = m_vColor;
		m_vColorFinal	= m_vColor;
	}

	ColorTransistion(const VECTOR4 & pColor)
		:	m_vColor(pColor), m_vColorCurrent(pColor), m_vColorFinal(pColor),
			m_fColorRatio(0.0f), m_fTransistionSpeed(4.0f)
	{
	}
	inline	VECTOR4	Color()			const	{	return	m_vColor;				}
	inline	bool	Completed()		const	{	return !(m_fColorRatio < 1.0f);	}
	
	inline	void	ChangeColor(const VECTOR4 & pColor)
	{
		m_vColorCurrent = m_vColorFinal;
		m_vColorFinal = pColor;
		m_fColorRatio = 0.0f;
	}

	inline	void	Update(const float & Interval)
	{
		/// <summary>
		///	Implementation of Color transition, goes by ratio.
		/// </summary>
		m_vColor =	m_vColorFinal * m_fColorRatio + 
					m_vColorCurrent * (1.0f - m_fColorRatio);
		m_vColor.w = 1.0f;
		if(m_fColorRatio < 1.0f)
			m_fColorRatio += Interval * m_fTransistionSpeed;
	}

};