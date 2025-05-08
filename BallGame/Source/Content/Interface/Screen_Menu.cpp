#include "stdafx.h"
#include "Screen_Menu.h"
#include "Interface.h"

Screen_Menu::Screen_Menu()
:Screen_Master()
{
	m_Selection = 0;
	m_TotalButtons = 0;
	m_bDelete = false;
	m_TotalAlpha4 = 0;
	m_fElapsedTime = 0.0f;

	m_fRatio = 0.0f;

	m_CameraPosition = VECTOR4(0, 0, 0, 1);
	//draw CUBO LOGO//
	m_Sprites.push_back(
		Sprite(TextureHolder::Instance()->AddTexture("Data/Interface/logo_CUBO.png"),
		VECTOR3(570, 100, 0),
		VECTOR3(1.0f, 1.0f, 1.0f),
		0.0f,
		ARGB(255, 255, 255, 255)));

	//draw NYPSIDM LOGO//
	m_Sprites.push_back(
		Sprite(TextureHolder::Instance()->AddTexture("Data/Interface/logo_NYPSIDM.png"),
		VECTOR3(60, 560, 0),
		VECTOR3(1.0f, 1.0f, 1.0f),
		0.0f,
		ARGB(255, 255, 255, 255)));

	//draw Menu_Instruction//
	m_Sprites.push_back(
		Sprite(TextureHolder::Instance()->AddTexture("Data/Interface/logo_menu_instructions.png"),
		VECTOR3(655, 585, 0),
		VECTOR3(1.0f, 1.0f, 1.0f),
		0.0f,
		ARGB(0, 255, 255, 255)));

	//draw Start button//
	m_Buttons.push_back(
		Button(TextureHolder::Instance()->AddTexture("Data/Interface/button_start.png"),
		VECTOR3(706, 200, 0)));

	//draw Help button//
	m_Buttons.push_back(
		Button(TextureHolder::Instance()->AddTexture("Data/Interface/button_help.png"),
		VECTOR3(716, 255, 0))),

	m_TotalButtons = m_Buttons.size() - 1;
}

Screen_Menu::~Screen_Menu()
{

}

void	Screen_Menu::Update(const float & Interval)
{
	//Camera Rotation start//
	VECTOR4 P (130, 65, 130, 1);
	P.x = 130 * sin(Interface::Instance()->Rotation());
	P.z = 130 * cos(Interface::Instance()->Rotation());

	Camera::Instance()->Position(P);
	Interface::Instance()->StoreCameraPosition(P);
	//Camera Rotation end//

	m_fElapsedTime += Interval;

	//idle function start//
	if (m_fElapsedTime > 30.0f)
	{
		Interface::Instance()->SetState(Interface::MENU_STATE::MENU_SPLASH);
		m_fElapsedTime = 0;
		m_TotalAlpha4 = 0;
	}
	//idle function end//

	m_Sprites[2].Color = SETA(m_Sprites[2].Color, m_TotalAlpha4);

	m_TotalAlpha4 += 8;
	(m_TotalAlpha4 > 255)? m_TotalAlpha4 = 255 : m_TotalAlpha4;

	//Blinking Buttons start//
	for(size_t i = 0; i < m_Buttons.size(); i++)
	{
		if(m_Selection == static_cast<short>(i))
			m_Buttons[i].ChangeState(Button::SELECTED);
		else
			m_Buttons[i].ChangeState(Button::IDLE);
		m_Buttons[i].Update(Interval);
	}
	//Blinking Buttons end//
	
	//Button Functions start//
	if(m_InputRef->KeyPressed(VK_UP))
	{
		((m_Selection - 1) <= 0)? m_Selection = 0 : m_Selection--;
		m_fElapsedTime = 0.0f;
	}
	else if(m_InputRef->KeyPressed(VK_DOWN))
	{
		((m_Selection + 1) >= m_TotalButtons)? m_Selection = m_TotalButtons : m_Selection++;
		m_fElapsedTime = 0.0f;
	}

	if ((m_InputRef->KeyPressed(VK_RETURN) && m_fElapsedTime > 0.5f)) 	//&& = AND, || = OR
	{
		m_CameraPosition = Camera::Instance()->Position();
		
		switch(m_Selection)
		{
		case 0:
			{
				Interface::Instance()->SetState(Interface::MENU_STATE::GAME);
				Interface::Instance()->RestartWholeGame();
				Game * _Game = (Game *)Window::Instance()->FindSubProgram("Game");
				_Game->SetGameSTAT(Game::GAME_STAT::LOAD);
			}
			
			break;
		case 1:
			Interface::Instance()->SetState(Interface::MENU_STATE::MENU_HELP);
			break;
		}
	}
	//Button Functions end//
}

void	Screen_Menu::Render()
{
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