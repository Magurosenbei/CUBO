#pragma once


class Window	:	public Abstract_Single<Window>
{
	friend	class Abstract_Single<Window>;
	friend	int		WINAPI	WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
	friend	LRESULT	WINAPI	DefaultWndProc(HWND hWnd, UINT	uMsg,	WPARAM	wParam,	LPARAM	lParam);

	HINSTANCE	m_hInstance, m_hPrevInstance;
	HWND		m_hWnd;
	WNDCLASSEX	m_WCEX;

	RECT		m_WndRect;

	bool		m_StopWindow;
	bool		m_VSync;
	float		m_ClockRate;
	float		m_DrawRate;

	float		m_fInterval;
	float		m_fPrevInterval;

	size_t		m_FPS;
	size_t		m_UPS;
protected:
	typedef std::map<std::string, Abstract_SubProgram *>	SubProgramsList;
	
	Abstract_Renderer	*	m_pRenderingDevice;
	SubProgramsList			m_SubPrograms;

	virtual	LRESULT		WndProc(HWND HWnd,	const unsigned int & uMsg, WPARAM	wParam,	LPARAM	lParam);

	Window();
public:
			void		RegisterRenderDevice(Abstract_Renderer	*	Device);
			void		RegisterSubProgram(const std::string & Name, Abstract_SubProgram	*	SubProgram);
			void		UnRegisterSubProgram(const std::string & Name, Abstract_SubProgram	*	SubProgram);

	Abstract_SubProgram *	FindSubProgram(const std::string & Name);
			
	inline	HINSTANCE	GetWindowInstance()	const	{	return m_hInstance;	}
	inline	HWND		GetWindowHandle()	const	{	return m_hWnd;		}
	inline	RECT		GetWindowRect()		const	{	return m_WndRect;	}

	inline	void		SetClockRate(const float & Clock)	{	m_ClockRate	=	Clock;	}
	inline	float		GetClockRate()		const			{	return m_ClockRate;		}

	inline	void		SetRenderRate(const float & Clock)	{	m_DrawRate	=	Clock;	}
	inline	float		GetRenderRate()		const			{	return m_DrawRate;		}
	
	inline	bool		IsVSync()			const			{	return	m_VSync;		}
	inline	void		SetVSync(bool onff)					{	m_VSync = onff;			}

	inline	size_t		FPS()				const			{	return	m_FPS;			}
	inline	size_t		UPS()				const			{	return	m_UPS;			}
	inline	float		Interval()			const			{	return	m_fInterval;	}
	inline	float		PrevInterval()		const			{	return	m_fPrevInterval;}

	//	Boots up the Renderer
	virtual	void		Initialize(HINSTANCE Instance, const unsigned int & BackBufferWidth, const unsigned int & BackBufferHeight, void * ProcAddr);
	virtual void		Shutdown();
	virtual	int			Run();
};


