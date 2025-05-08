#pragma once

class InputHandle : public Abstract_SubProgram, public Abstract_Single<InputHandle>
{
	friend class Abstract_Single<InputHandle>;
protected:
	bool	m_bKeyboard[256],	m_bPrevKeyboard[256];

	POINT	m_MousePoint,		m_PrevMousePoint,	m_MouseDiff;
	bool	m_bMouseButton[2],	m_bPrevMouseButton[2];

	bool	m_bHasInput;
	InputHandle();
public:
	virtual ~InputHandle();

	inline	const	bool	HasInput()	const	{	return	m_bHasInput;	}

	inline	const	bool	KeyDown(int Key)	{	return m_bKeyboard[Key];	}
	inline	const	bool	KeyUp(int Key)		{	return !m_bKeyboard[Key];	}

	inline	const	bool	KeyPressed(int Key)		{	return m_bKeyboard[Key] && !m_bPrevKeyboard[Key];	}
	inline	const	bool	KeyReleased(int Key)	{	return !m_bKeyboard[Key] && m_bPrevKeyboard[Key];	}

	inline	const	bool	MousePressed(int Button)	{	return m_bMouseButton[Button] && !m_bPrevMouseButton[Button];	}
	inline	const	bool	MouseReleased(int Button)	{	return !m_bMouseButton[Button] && m_bPrevMouseButton[Button];	}

	inline	const	POINT	MousePosition()		const	{	return	m_MousePoint;		}
	inline	const	POINT	MousePrevPosition()	const	{	return	m_PrevMousePoint;	}
	inline	const	POINT	MouseDiffernce()	const	{	return	m_MouseDiff;		}

	virtual void	Update(const float & Interval);
	virtual	void	Render();	
};