#pragma  once

class Screen_Master : public Abstract_Overlay, public Abstract_SubProgram
{
protected:
	SmartPtr<InputHandle>	m_InputRef;
	std::deque<Sprite>		m_Sprites;
	std::deque<Button>		m_Buttons;

	LPD3DXSPRITE			m_pSpriteBatch;

	float					m_fRatio;
	float					m_fElapsedTime;

	short					m_Selection;
	short					m_TotalButtons;


public:
	Screen_Master();

	virtual ~Screen_Master();

	virtual	void	Update(const float & Interval);
	virtual void	Render();
};