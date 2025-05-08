#include "stdafx.h"
#include "Window.h"


SmartPtr<Window> Abstract_Single<Window>::m_pInstance;

Window::Window()
:	m_StopWindow(false), m_VSync(true),
	m_ClockRate(1.0f / 60.0f),
	m_fInterval(0),
	m_FPS(0), m_UPS(0)
{
}

void Window::RegisterRenderDevice(Abstract_Renderer	*	Device)
{
	m_pRenderingDevice = Device;
}

void Window::RegisterSubProgram(const std::string & Name, Abstract_SubProgram	*	SubProgram)
{
	m_SubPrograms.insert(m_SubPrograms.begin(), std::make_pair(Name, SubProgram));
}

void Window::UnRegisterSubProgram(const std::string & Name, Abstract_SubProgram	*	SubProgram)
{
	SubProgramsList::iterator it = m_SubPrograms.find(Name);
	ASSERT(it != m_SubPrograms.end(), "Cannot unregister, Probably sub program unregistered");
	m_SubPrograms.erase(it);
}

Abstract_SubProgram *	Window::FindSubProgram(const std::string & Name)
{
	SubProgramsList::iterator it = m_SubPrograms.find(Name);
	if(it == m_SubPrograms.end())
		return NULL;
	return it->second;
}

void Window::Initialize(HINSTANCE Instance, const unsigned int & BackBufferWidth, const unsigned int & BackBufferHeight, void * ProcAddr)
{
	m_hInstance = Instance;
	m_WndRect.top		= (GetSystemMetrics(SM_CYSCREEN) >> 1) - (BackBufferHeight >> 1);
	m_WndRect.left		= (GetSystemMetrics(SM_CXSCREEN) >> 1) - (BackBufferWidth >> 1);
	m_WndRect.right		= BackBufferWidth + 8;
	m_WndRect.bottom	= BackBufferHeight + 32;

	m_WCEX.cbSize = sizeof(WNDCLASSEX);

	m_WCEX.style			= CS_HREDRAW | CS_VREDRAW;
	m_WCEX.lpfnWndProc		= (WNDPROC)ProcAddr;
	m_WCEX.cbClsExtra		= 0;
	m_WCEX.cbWndExtra		= 0;
	m_WCEX.hInstance		= m_hInstance;
	m_WCEX.hIcon			= LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_BALLGAME));
	m_WCEX.hCursor			= LoadCursor(NULL, IDC_ARROW);
	m_WCEX.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	m_WCEX.lpszMenuName		= NULL;
	m_WCEX.lpszClassName	= APP_CLASS;
	m_WCEX.hIconSm			= LoadIcon(m_WCEX.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	ATOM Registeration = RegisterClassEx(&m_WCEX);
	ASSERT(Registeration, "Failed To Register class");

	m_hWnd = CreateWindowEx(	WS_EX_APPWINDOW,
								APP_CLASS, APP_TITLE,
								WS_BORDER | WS_SYSMENU,
								m_WndRect.left, m_WndRect.top,
								m_WndRect.right, m_WndRect.bottom,
								NULL, NULL, m_hInstance, NULL);
	ShowWindow(m_hWnd, 1);
	UpdateWindow(m_hWnd);

	m_pRenderingDevice->Initialze(m_hInstance, m_hWnd);
}

void Window::Shutdown()
{
	for(SubProgramsList::iterator SubProg = m_SubPrograms.begin();	SubProg != m_SubPrograms.end();	SubProg++)
	{
		if(SubProg->second->CanDelete())
			delete SubProg->second;
		SubProg->second = NULL;
	}
	DestroyWindow(m_hWnd);
	UnregisterClass(APP_CLASS, m_hInstance);
	m_pRenderingDevice->Shutdown();
	m_pRenderingDevice = NULL;
}

int Window::Run()
{
	MSG	Msg;
	System_HiResTimer Timer;
	float	TimeElapsed = 0.0f;

	m_fInterval = 0.0f;
	float	Diffrence = 0.0f;
	m_fPrevInterval = 0.0f;

	float	DrawInterval = -1;
	int		Frames = 0;
	int		Steps = 0;

	SubProgramsList::iterator	SubProg;
	while(!m_StopWindow)
	{
		if(PeekMessage(&Msg, m_hWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
			continue;
		}
		Timer.Start();
		Console::Instance()->Update(m_fPrevInterval);
		for(SubProg = m_SubPrograms.begin();	SubProg != m_SubPrograms.end();	SubProg++)
			SubProg->second->Update(m_fPrevInterval);
		Steps++;

		//if((DrawInterval < 0 && m_fInterval <= m_ClockRate) || !m_VSync)
		{
			m_pRenderingDevice->Render();
			DrawInterval = m_DrawRate * 0.5f;
			Frames++;
		}
		m_fInterval = Timer.End() * 0.001f;
		TimeElapsed += m_fInterval;

		Diffrence = (m_ClockRate - m_fInterval);
		
		if(Diffrence > 0 && m_VSync)
			Sleep(Diffrence * 1000);
		//Sleep(1);
		Diffrence = max(Diffrence, 0);
		TimeElapsed += Diffrence;
		DrawInterval -= m_fInterval +  Diffrence;
		m_fPrevInterval = m_fInterval + Diffrence;
		
		if(TimeElapsed > 1.0f)
		{
			if(!m_VSync) m_ClockRate = 1.0f / Frames;
			TimeElapsed -= 1.0f;
			m_FPS = Frames;
			m_UPS = Steps;
			Steps = Frames = 0;
		}
	}
	return 0;
}

LRESULT	Window::WndProc(HWND HWnd, const unsigned int & uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
	case WM_QUIT:
		m_StopWindow = true;
		break;
	default:
		return DefWindowProc(HWnd, uMsg, wParam, lParam);
	}
	return 0;
}