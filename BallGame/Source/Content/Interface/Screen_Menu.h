#pragma  once

class Screen_Menu : public Screen_Master
{
	int						m_TotalAlpha4;
	VECTOR4					m_CameraPosition;

public:
	Screen_Menu();

	virtual ~Screen_Menu();

	inline	VECTOR4	CameraPosition()	const	{	return m_CameraPosition;	}

	virtual	void	Update(const float & Interval);
	virtual void	Render();
};