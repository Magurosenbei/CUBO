#include "stdafx.h"
#include "Input.h"

SmartPtr<InputHandle> Abstract_Single<InputHandle>::m_pInstance;

InputHandle::InputHandle()
:Abstract_SubProgram()
{
	m_bHasInput = false;
	m_bDelete = false;
	memset(&m_bPrevKeyboard,	0x00, 256);
	memset(&m_bKeyboard,		0x00, 256);
	memset(m_bMouseButton,		0x00, 2);
	memset(m_bPrevMouseButton,	0x00, 2);

	m_MousePoint.x = 0,		m_MousePoint.y = 0;
	m_MouseDiff.x = 0,		m_MouseDiff.y = 0;
	m_PrevMousePoint.x = 0, m_PrevMousePoint.y = 0;
}

InputHandle::~InputHandle()
{
}

void InputHandle::Update(const float & Interval)
{
	Interval;
	memcpy(m_bPrevKeyboard, m_bKeyboard, 256);
	memcpy(m_bPrevMouseButton, m_bMouseButton, 2);
	memcpy(&m_PrevMousePoint, &m_MousePoint, sizeof(POINT));

	GetCursorPos(&m_MousePoint);

	m_MouseDiff.x = m_MousePoint.x - m_PrevMousePoint.x;
	m_MouseDiff.y = m_MousePoint.y - m_PrevMousePoint.y;

	m_bMouseButton[0] = KeyDown(VK_LBUTTON);
	m_bMouseButton[1] = KeyDown(VK_RBUTTON);

//#pragma omp parallel for
	m_bHasInput = false;
	for(size_t i = 0; i < 256; i++)
	{
		m_bKeyboard[i] = (GetAsyncKeyState(i)&0x8000)? true : false;
		if(m_bKeyboard[i] && i != 242)	//	No idea but 242 is always pressed
			m_bHasInput = true;
	}
	if(m_bKeyboard[VK_ESCAPE])
		PostMessage(Window::Instance()->GetWindowHandle(), WM_QUIT, NULL, NULL);
}

void InputHandle::Render()
{
}