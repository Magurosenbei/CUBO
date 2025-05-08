#include "stdafx.h"
#include "Interface.h"

SmartPtr<Interface> Abstract_Single<Interface>::m_pInstance;

Interface::Interface()
{
	m_Selection = 0;
	m_TotalButtons = 2;
	m_bDelete = false;

	m_fRatio = 0.0f;

	m_State = MENU_SPLASH;

	m_InputRef = SmartPtr<InputHandle>(InputHandle::Instance());

	m_pScreen_Splash = SmartPtr<Screen_Splash>(new Screen_Splash());
	m_pScreen_Menu = SmartPtr<Screen_Menu>(new Screen_Menu());
	m_pScreen_Help = SmartPtr<Screen_Help>(new Screen_Help());
	m_pScreen_Conclude = SmartPtr<Screen_Conclude>(new Screen_Conclude());
	m_pScreen_Game = SmartPtr<Screen_Game>(new Screen_Game());
	m_pScreen_Game = SmartPtr<Screen_Game>(new Screen_Game());
	m_pScreen_Pause = SmartPtr<Screen_Pause>(new Screen_Pause());

	HRESULT Result = D3DXCreateSprite(DxDevice::Instance()->Device(), &m_pSpriteBatch);
	ASSERT(Result == S_OK, "Unable to create sprite batch");
	m_pTextFont = SmartPtr<FontText>(new FontText);
	m_pTextFont->Initialize("Data/Interface/Fixedsys.ttf", "Fixedsys", 16, 800, 600);
}

Interface::~Interface()
{
	m_InputRef.release();
	m_Sprites.clear();

	m_pScreen_Menu->CameraPosition();

	m_pScreen_Splash.reset(NULL);
	m_pScreen_Splash.release();
	m_pScreen_Menu.reset(NULL);
	m_pScreen_Menu.release();
	m_pScreen_Help.reset(NULL);
	m_pScreen_Help.release();
	m_pScreen_Conclude.reset(NULL);
	m_pScreen_Conclude.release();
	m_pScreen_Game.reset(NULL);
	m_pScreen_Game.release();

	m_pTextFont.reset(NULL);
	m_pTextFont.release();
	m_pSpriteBatch->Release();
}

void Interface::Update(const float & Interval)
{
	//m_fRatio = 0.0f; //this will stop the rotation

	//Camera Rotation start//
	if (m_State == MENU_SPLASH ||
		m_State == MENU_MAIN)
	{
		(m_fRatio < 6.284f)  ? m_fRatio += 0.0015f : m_fRatio = 6.284f;
		(m_fRatio == 6.284f) ? m_fRatio = 0.0f : 0;
	}
	//Camera Rotation end//

	//Console::Instance()->FeedText(System_Utility::FormatText("m_fRatio = %f", m_fRatio));

	for(size_t i = 0; i < m_Sprites.size(); i++)
	{
		if(m_Selection == static_cast<short>(i))
			m_Buttons[i].ChangeState(Button::SELECTED);
		else
			m_Buttons[i].ChangeState(Button::IDLE);
		m_Buttons[i].Update(Interval);
	}

	if(m_InputRef->KeyPressed(VK_UP))
		(m_Selection + 1 >= m_TotalButtons)? m_Selection = 0 : m_Selection++;
	else if(m_InputRef->KeyPressed(VK_DOWN))
		(m_Selection - 1 <= 0)? m_Selection = m_TotalButtons - 1 : m_Selection--;

	switch(m_State)
	{
	case MENU_SPLASH:
		m_pScreen_Splash->Update(Interval);
		AudioHandle::Instance()->LoadBGM("Data/MainBGM.ogg");
		break;

	case MENU_MAIN:
		m_pScreen_Menu->Update(Interval);
		AudioHandle::Instance()->LoadBGM("Data/MainBGM.ogg");
		break;

	case MENU_HELP:
		m_pScreen_Help->Update(Interval);
		AudioHandle::Instance()->LoadBGM("Data/MainBGM.ogg");
		break;

	case GAME:
		//m_pScreen_Game->StoreCameraPosition(m_pScreen_Menu->CameraPosition());
		m_pScreen_Game->Update(Interval);
		AudioHandle::Instance()->LoadBGM("Data/GameBGM.ogg");
		break;

	case MENU_CONCLUDE:
		break;

	case PAUSE:
		m_pScreen_Pause->Update(Interval);
		//AudioHandle::Instance()->LoadBGM("Data/GameBGM.ogg");
		break;
	}
}

void Interface::Render()
{
	switch(m_State)
	{
	case MENU_SPLASH:
		m_pScreen_Splash->Render();
		break;

	case MENU_MAIN:
		m_pScreen_Menu->Render();
		break;

	case MENU_HELP:
		m_pScreen_Help->Render();
		break;

	case GAME:
		m_pScreen_Game->Render();
		break;

	case MENU_CONCLUDE:
		break;

	case PAUSE:
		m_pScreen_Pause->Render();
		break;
	}

	m_pSpriteBatch->Begin(NULL);

	Sprite * Ref(NULL);

	for(size_t i = 0; i < m_Sprites.size(); i++)
	{
		Ref = &m_Sprites[i];
		
		m_pSpriteBatch->SetTransform(&Ref->Transform);
		m_pSpriteBatch->Draw(Ref->Image, 
			&Ref->Infomation.Rectangle, 
			&Ref->Center, NULL, 
			Ref->Color);
	}

	for(size_t i = 0; i < m_Buttons.size(); i++)
	{
		Ref = &m_Buttons[i];

		m_pSpriteBatch->SetTransform(&Ref->Transform);
		m_pSpriteBatch->Draw(Ref->Image, 
			&Ref->Infomation.Rectangle, 
			&Ref->Center, NULL, 
			Ref->Color);
	}

	m_pSpriteBatch->End();
}