#pragma once

class Interface : public Abstract_Overlay, public Abstract_SubProgram, public Abstract_Single<Interface>
{
public:
	enum	MENU_STATE {	MENU_SPLASH = 0, MENU_MAIN, MENU_HELP, MENU_CONCLUDE, GAME, PAUSE  };
private:
	friend class Abstract_Single<Interface>;
	SmartPtr<InputHandle>	m_InputRef;
protected:
	LPD3DXSPRITE			m_pSpriteBatch;
	
	SmartPtr<FontText>		m_pTextFont;

	std::deque<Sprite>		m_Sprites;
	std::deque<Button>		m_Buttons;

	short					m_Selection;
	short					m_TotalButtons;

	MENU_STATE				m_State;

	float					m_fRatio;



	SmartPtr<Screen_Splash>		m_pScreen_Splash;
	SmartPtr<Screen_Menu>		m_pScreen_Menu;
	SmartPtr<Screen_Help>		m_pScreen_Help;
	SmartPtr<Screen_Conclude>	m_pScreen_Conclude;
	SmartPtr<Screen_Game>		m_pScreen_Game;
	SmartPtr<Screen_Pause>		m_pScreen_Pause;

	Interface();
public:

	virtual ~Interface();

	inline	void	SetTargetCameraPosition(const VECTOR4 & position)	{	m_pScreen_Game->SetCameraTargetPosition(position);	}
	inline	void	StoreCameraPosition(const VECTOR4 & position)		{	m_pScreen_Game->StoreCameraPosition(position);	}
	inline	void	RestartGame()										{	m_pScreen_Game->ResetVisual();	}
	inline	void	RestartWholeGame()									{	m_pScreen_Game->ResetAll();	}

	inline	float		Rotation()			{	return	m_fRatio;	}
	inline	void		SetState(MENU_STATE pState)	{	m_State = pState;	}
	inline	MENU_STATE	GetState()	{	return	m_State;	}

	inline	short	GetSelection() const	{	return m_Selection;	}

	virtual	void	Update(const float & Interval);
	virtual void	Render();
};