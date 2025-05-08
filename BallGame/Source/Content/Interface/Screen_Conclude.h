#pragma  once

class Screen_Conclude : public Screen_Master
{
	SmartPtr<FontText>		m_pTextFont;

public:
	Screen_Conclude();

	virtual ~Screen_Conclude();

	virtual	void	Update(const float & Interval);
	virtual void	Render();
};