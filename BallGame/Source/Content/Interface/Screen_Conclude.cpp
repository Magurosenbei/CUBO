#include "stdafx.h"
#include "Screen_Conclude.h"

Screen_Conclude::Screen_Conclude()
:Screen_Master() //inherite cmd
{
	m_pTextFont = SmartPtr<FontText>(new FontText);
	m_pTextFont->Initialize("Data/Interface/FixedSys.ttf", "Fixedsys", 16, 800, 600);
}

Screen_Conclude::~Screen_Conclude()
{
	System_Utility::FormatText("Characters: %c %c \n", 'a', 65);
}

void	Screen_Conclude::Update(const float & Interval)
{

}

void	Screen_Conclude::Render()
{
	//Text//
	m_pTextFont->WriteText(200, 100, "Conclude", 0xffffffff);
}