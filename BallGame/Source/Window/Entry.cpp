#include "stdafx.h"
#include "Window.h"


inline LRESULT	WINAPI	DefaultWndProc(HWND hWnd, UINT	uMsg,	WPARAM	wParam,	LPARAM	lParam)
{
	return Window::Instance()->WndProc(hWnd, uMsg, wParam,	lParam);
}

int		WINAPI	WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

	srand(time(NULL));
	WriteCommandLine("Random : %i", rand());
	WriteCommandLine("Random : %i", rand());
	WriteCommandLine("Random : %i", rand());

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nShowCmd);

	MatrixHelper::Initialize();

	Window	* Program(NULL);
	Program = Window::Instance();
	Program->SetClockRate(1.0f / 60.0f);
	Program->SetRenderRate(1.0f / 60.0f);
	Program->SetVSync(true);
	Program->RegisterRenderDevice(DxDevice::Instance());
	Program->RegisterSubProgram("InputHandler",	InputHandle::Instance());
	Program->RegisterSubProgram("Physics",	Physics::Instance());
	Program->RegisterSubProgram("Audio", AudioHandle::Instance());

	Program->Initialize(hInstance, 800, 600, &DefaultWndProc);
	DxDevice::Instance()->Overlay(Interface::Instance());
	Program->RegisterSubProgram("Interface",	Interface::Instance());

	Program->RegisterSubProgram("Game", new Game);
	
	int ReturnCode = Program->Run();
	Program->Shutdown();
	WriteCommandLine("Main Program exited with Code %i", ReturnCode);
	return ReturnCode;
}

