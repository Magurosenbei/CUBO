#include "stdafx.h"
#include "Screen_Splash.h"

Screen_Splash::Screen_Splash()
:Screen_Master()
{
	m_TotalAlpha = 0;
	m_TotalAlpha2 = 255;
	m_TotalAlpha3 = 0;
	m_TotalAlpha3Number = 0.0f;
	m_fElapsedTime = 0.0f;

	m_fRatio = 0.0f;

	//draw Blank Black//
	m_Sprites.push_back(
		Sprite(TextureHolder::Instance()->AddTexture("Data/Interface/screen_black.png"),
		VECTOR3(0, 0, 0),
		VECTOR3(800.0f, 600.0f, 1.0f),
		0.0f,
		ARGB(255, 255, 255, 255)));

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

	//draw Press any key//
	m_Sprites.push_back(
		Sprite(TextureHolder::Instance()->AddTexture("Data/Interface/logo_pressanykey.png"),
		VECTOR3(570, 190, 0),
		VECTOR3(1.0f, 1.0f, 1.0f),
		0.0f,
		ARGB(0, 255, 255, 255)));

}

Screen_Splash::~Screen_Splash()
{

}

void	Screen_Splash::Update(const float & Interval)
{
	////rotation//
	VECTOR4 P (130, 65, 130, 1);
	P.x = 130 * sin(Interface::Instance()->Rotation());
	P.z = 130 * cos(Interface::Instance()->Rotation());
	Camera::Instance()->Position(P);

	m_fElapsedTime += Interval;

	m_Sprites[1].Color = SETA(m_Sprites[1].Color, m_TotalAlpha);

	m_TotalAlpha += 3;
	(m_TotalAlpha > 255)? m_TotalAlpha = 255 : m_TotalAlpha;

	if (m_TotalAlpha == 255)
	{
		m_Sprites[0].Color = SETA(m_Sprites[0].Color, m_TotalAlpha2);

		m_TotalAlpha2 -= 7;
		(m_TotalAlpha2 < 0)? m_TotalAlpha2 = 0 : m_TotalAlpha2;
	}

	if (m_TotalAlpha2 == 0)
	{
		m_Sprites[3].Color = SETA(m_Sprites[3].Color, m_TotalAlpha3);

		m_TotalAlpha3 += 4;
		(m_TotalAlpha3 > 255)? m_TotalAlpha3 = 255 : m_TotalAlpha3;
	}

	if (m_TotalAlpha3 == 255)
	{
		m_Sprites[3].Color = SETA(m_Sprites[3].Color, m_TotalAlpha3);

		m_TotalAlpha3 = (sin(m_TotalAlpha3Number) +1 ) *0.5f;
		(m_TotalAlpha3Number > 6.284)? m_TotalAlpha3Number =  0 : m_TotalAlpha3Number += 1.0f * Interval;
	}
	
	// Press any key function start//
	if (m_InputRef->HasInput() && m_fElapsedTime > 3.0f)
		Interface::Instance()->SetState(Interface::MENU_STATE::MENU_MAIN);
	// Press any key function end//
}

void	Screen_Splash::Render()
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