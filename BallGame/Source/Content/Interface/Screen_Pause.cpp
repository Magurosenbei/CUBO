#include "stdafx.h"
#include "Screen_Pause.h"

Screen_Pause::Screen_Pause()
:Screen_Master()
{	
	m_pTextFont = SmartPtr<FontText>(new FontText);
	m_pTextFont->Initialize("Data/hymmnos.ttf", "Fixedsys", 16, 800, 600);
	m_fElapsedTime = 0.0f;

	//draw Blank Black//
	m_Sprites.push_back(
		Sprite(TextureHolder::Instance()->AddTexture("Data/Interface/screen_black.png"),
		VECTOR3(0, 0, 0),
		VECTOR3(800.0f, 600.0f, 1.0f),
		0.0f,
		ARGB(64, 255, 255, 255)));

	//draw NYPSIDM LOGO//
	m_Sprites.push_back(
		Sprite(TextureHolder::Instance()->AddTexture("Data/Interface/logo_NYPSIDM.png"),
		VECTOR3(60, 560, 0),
		VECTOR3(1.0f, 1.0f, 1.0f),
		0.0f,
		ARGB(255, 255, 255, 255)));
	//draw NYPSIDM end//

	//draw Paused LOGO//
	m_Sprites.push_back(
		Sprite(TextureHolder::Instance()->AddTexture("Data/Interface/logo_paused.png"),
		VECTOR3(400, 450, 0),
		VECTOR3(1.0f, 1.0f, 1.0f),
		0.0f,
		ARGB(255, 255, 255, 255)));
	//draw Paused end//

	//draw Paused instruction start//
	m_Sprites.push_back(
		Sprite(TextureHolder::Instance()->AddTexture("Data/Interface/pause_instructions2.png"),
		VECTOR3(655, 585, 0),
		VECTOR3(1.0f, 1.0f, 1.0f),
		0.0f,
		ARGB(255, 255, 255, 255)));
	//draw Paused instruction end//
}

Screen_Pause::~Screen_Pause()
{

}

void	Screen_Pause::Update(const float & Interval)
{
	m_fElapsedTime += Interval;

	//Backspace : Back start//
	if (m_InputRef->KeyPressed('P') && m_fElapsedTime > 0.1f)
	{
		m_fElapsedTime = 0.0f;
		Interface::Instance()->StoreCameraPosition(Camera::Instance()->Position());
		Interface::Instance()->SetState(Interface::MENU_STATE::GAME);
		Physics::Instance()->ActivatePhysics(true);
		Game * _Game = (Game *)Window::Instance()->FindSubProgram("Game");
		AudioHandle::Instance()->Pause(false);
		_Game->SetGameSTAT(Game::GAME_STAT::PLAY);
	}
	//Backspace : Back end//
}

void	Screen_Pause::Render()
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

	m_pSpriteBatch->End();
}