#pragma  once

class Screen_Help : public Screen_Master
{
	int						m_HelpTotalAlpha;

	SmartPtr<FontText>		m_pTextFont;

public:
	Screen_Help();

	virtual ~Screen_Help();

	virtual	void	Update(const float & Interval);
	virtual void	Render();
};