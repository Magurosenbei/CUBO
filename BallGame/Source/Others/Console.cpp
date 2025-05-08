#include "stdafx.h"
#include "console.h"

SmartPtr <Console>	Abstract_Single<Console>::m_pInstance;

Console::Console()
:	m_pText(NULL), m_fElapsedTime(0)
{
	//m_Messages.assign(25, "ABD");
}

Console::~Console()
{
	m_pText.reset(NULL);
	m_pText.release();
}

void Console::Initialize()
{
	m_pText = SmartPtr<FontText>(new FontText);
	m_pText->Initialize("Data/Hymmnos.ttf", "FixedSys", 12, DxDevice::Instance()->ViewPort().Width, DxDevice::Instance()->ViewPort().Height);
}

void Console::FeedText(const std::string & Text)
{
	m_Messages.push_front(Text.c_str());
	if(m_Messages.size() > 10)
		m_Messages.pop_back();
}

void Console::Update(const float & Interval)
{
	m_fElapsedTime += Interval;
	if(m_fElapsedTime > 5.0f)
	{
		if(m_Messages.size() > 0)
			m_Messages.pop_back();
		m_fElapsedTime = 0;
	}
}

void Console::Render()
{
	float Height = DxDevice::Instance()->ViewPort().Height - 16.0f;
	for(size_t i = 0; i < m_Messages.size(); i++)
		m_pText->WriteText(0, Height - (i * 16), m_Messages[i], 0xffffffff);
}