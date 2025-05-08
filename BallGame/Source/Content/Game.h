#pragma once

class Game	:	public	Abstract_SubProgram,	public	Abstract_Renderable
{
	friend	class Abstract_SubProgram;
public:
	enum	GAME_STAT	{ MENU, LOAD, NEXTLEVEL, RESTART, FINISH, PLAY, PAUSE };
protected:
	GAME_STAT						m_GAME_STAT;
	SmartPtr<Physics>				m_pPhysicsRef;
	SmartPtr<InputHandle>			m_pInputRef;
	SmartPtr<DxDevice>				m_pRenderRef;

	SmartPtr<Arena>					m_pArena;

	SmartPtr<DefaultObjectEffect>	m_pDefaultEffect;

	size_t							m_Level;
	size_t							m_MaxLevel;

	float							m_fTimeLimit;		//	Base 15.0
	float							m_fTime;			//	Copy from Limit and decrease this	
	float							m_fDifficultyElapsed;

public:
	Game();
	virtual ~Game();

	inline	void	SetGameSTAT(GAME_STAT	Stat)	{	m_GAME_STAT = Stat;	}
	
	inline	size_t	Level()			const	{	return	m_Level;		}
	inline	size_t	LevelLimit()	const	{	return	m_MaxLevel;		}

	inline	size_t	GameSTAT()	const	{	return	m_GAME_STAT;	}

	inline	size_t	TimeRemaining() 	{	return	static_cast<size_t>(m_fTime);		}
	inline	size_t	TimeLimit() 		{	return	static_cast<size_t>(m_fTimeLimit);	}

	//virtual	void	Reset();

	virtual	void	Update(const float & Interval);
	virtual	void	Render(const size_t & RenderTargetID, const size_t & Width, const size_t & Height);

	virtual	void	LoadData(const std::string & DefinitionFile);
	virtual	void	UnloadData();
	virtual	void	PlayGame(const float & Interval);
};