#include "stdafx.h"
#include "Screen_Help.h"

Screen_Help::Screen_Help()
:Screen_Master()
{
	m_HelpTotalAlpha = 255;

	m_pTextFont = SmartPtr<FontText>(new FontText);
	m_pTextFont->Initialize("Data/Interface/FixedSys.ttf", "Fixedsys", 40, 800, 600);
	m_fElapsedTime = 0.0f;

	//draw Blank Black//
	m_Sprites.push_back(
		Sprite(TextureHolder::Instance()->AddTexture("Data/Interface/screen_black.png"),
		VECTOR3(0, 0, 0),
		VECTOR3(800.0f, 600.0f, 1.0f),
		0.0f,
		ARGB(64, 255, 255, 255)));

	//draw Help_Instruction start//
	m_Sprites.push_back(
		Sprite(TextureHolder::Instance()->AddTexture("Data/Interface/logo_help_instructions.png"),
		VECTOR3(655, 585, 0),
		VECTOR3(1.0f, 1.0f, 1.0f),
		0.0f,
		ARGB(255, 255, 255, 255)));
	//draw Help_Instruction end//

	//draw CUBO LOGO start//
	m_Sprites.push_back(
		Sprite(TextureHolder::Instance()->AddTexture("Data/Interface/logo_CUBO.png"),
		VECTOR3(570, 100, 0),
		VECTOR3(1.0f, 1.0f, 1.0f),
		0.0f,
		ARGB(255, 255, 255, 255)));
	//draw CUBO LOGO end//

	//draw NYPSIDM LOGO//
	m_Sprites.push_back(
		Sprite(TextureHolder::Instance()->AddTexture("Data/Interface/logo_NYPSIDM.png"),
		VECTOR3(60, 560, 0),
		VECTOR3(1.0f, 1.0f, 1.0f),
		0.0f,
		ARGB(255, 255, 255, 255)));
	//draw NYPSIDM end//
	
	//draw Controls start//
	m_Sprites.push_back(
		Sprite(TextureHolder::Instance()->AddTexture("Data/Interface/logo_help_arrows.png"),
		VECTOR3(114, 226, 0),
		VECTOR3(0.8f, 0.8f, 1.0f),
		0.0f,
		ARGB(255, 255, 255, 255)));
	//draw Controls end//
}

Screen_Help::~Screen_Help()
{
	
}

void	Screen_Help::Update(const float & Interval)
{
	m_fElapsedTime += Interval;

	//Camera fix position start//
	VECTOR4 Position(130, 65, 130, 1.0f);
	Camera::Instance()->Position(Position);
	//Camera fix position end//
	
	//Backspace : Back start//
	if (m_InputRef->KeyPressed(VK_BACK) && m_fElapsedTime > 0.1f)
	{
		m_Selection = 0;
		m_TotalButtons = 2;
		m_bDelete = false;
		m_fElapsedTime = 0.0f;

		m_fRatio = 0.0f;
		m_HelpTotalAlpha = 255;
		Interface::Instance()->SetState(Interface::MENU_STATE::MENU_MAIN);
	}
	//Backspace : Back end//

	//image fade effect start//
	m_Sprites[2].Color = SETA(m_Sprites[2].Color, m_HelpTotalAlpha);

	m_HelpTotalAlpha -= 20;
	(m_HelpTotalAlpha < 64)? m_HelpTotalAlpha = 64 : m_HelpTotalAlpha;
	//image fade effect end//
}

void	Screen_Help::Render()
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

	m_pTextFont->WriteText(50, 180, "Controls", ARGB(255, 255, 255, 255));
	m_pTextFont->WriteText(180, 210, ":Move", ARGB(255, 255, 255, 255));
	m_pTextFont->WriteText(50, 270, "Instructions", ARGB(255, 255, 255, 255));
	m_pTextFont->WriteText(50, 300, "> Move the ball to the correct tile to", ARGB(255, 255, 255, 255));
	m_pTextFont->WriteText(50, 330, "  stay alive.", ARGB(255, 255, 255, 255));
	m_pTextFont->WriteText(50, 390, "> Survive the level till the time runs out.", ARGB(255, 255, 255, 255));
}