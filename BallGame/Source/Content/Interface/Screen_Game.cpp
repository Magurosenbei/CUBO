#include "stdafx.h"
#include "Screen_Game.h"

Screen_Game::Screen_Game()
:Screen_Master()
{
	m_pSoundEffect = AudioHandle::Instance()->GetSoundEffect("Data/pause.wav", audiere::SoundEffectType::MULTIPLE);
	m_fRatio = 0.0f;
	m_GameCUBOAlpha = 255;
	m_GameTotalAlpha2 = 255;
	m_GameAnyKeyAlpha3 = 0;
	m_GameBlackAlpha = 64;
	m_GameBlackAlpha2 = 0;
	m_GameCompleteAlpha = 0;
	m_GameWin1Alpha = 0;
	m_GameWin2Alpha = 0;

	m_fcomplateElasped = 0.0f;

	m_fElapsedTime = 0.0f;
	m_StoredCameraPosition = VECTOR4(0, 0, 0, 1);
	m_TargetCameraPosition = VECTOR4(0, 200, 100, 1.0f);
	m_pTextFont = SmartPtr<FontText>(new FontText);
	m_pTextFont->Initialize("Data/Interface/FixedSys.ttf", "Fixedsys", 41, 800, 600);

	//draw [0] Blank Black//
	m_Sprites.push_back(
		Sprite(TextureHolder::Instance()->AddTexture("Data/Interface/screen_black.png"),
		VECTOR3(0, 0, 0),
		VECTOR3(800.0f, 600.0f, 1.0f),
		0.0f,
		ARGB(64, 255, 255, 255)));

	//draw [1] CUBO LOGO start//
	m_Sprites.push_back(
		Sprite(TextureHolder::Instance()->AddTexture("Data/Interface/logo_CUBO.png"),
		VECTOR3(570, 100, 0),
		VECTOR3(1.0f, 1.0f, 1.0f),
		0.0f,
		ARGB(255, 255, 255, 255)));
	//draw CUBO LOGO end//

	//draw [2] NYPSIDM LOGO start//
	m_Sprites.push_back(
		Sprite(TextureHolder::Instance()->AddTexture("Data/Interface/logo_NYPSIDM.png"),
		VECTOR3(60, 560, 0),
		VECTOR3(1.0f, 1.0f, 1.0f),
		0.0f,
		ARGB(255, 255, 255, 255)));
	//draw NYPSIDM LOGO end//

	//draw [3] Press any key start//
	m_Sprites.push_back(
		Sprite(TextureHolder::Instance()->AddTexture("Data/Interface/logo_pressanykey.png"),
		VECTOR3(400, 475, 0),
		VECTOR3(1.0f, 1.0f, 1.0f),
		0.0f,
		ARGB(0, 255, 255, 255)));
	//draw Press any key end//

	//draw [4] Paused instruction start//
	m_Sprites.push_back(
		Sprite(TextureHolder::Instance()->AddTexture("Data/Interface/pause_instructions.png"),
		VECTOR3(655, 585, 0),
		VECTOR3(1.0f, 1.0f, 1.0f),
		0.0f,
		ARGB(255, 255, 255, 255)));
	//draw Paused instruction end//

	//draw [5] Complete message start//
	m_Sprites.push_back(
		Sprite(TextureHolder::Instance()->AddTexture("Data/Interface/logo_complete.png"),
		VECTOR3(400, 150, 0),
		VECTOR3(1.0f, 1.0f, 1.0f),
		0.0f,
		ARGB(0, 255, 255, 255)));
	//draw Complete message end//

	//draw [6] Blank Black6//
	m_Sprites.push_back(
		Sprite(TextureHolder::Instance()->AddTexture("Data/Interface/screen_black.png"),
		VECTOR3(0, 0, 0),
		VECTOR3(800.0f, 600.0f, 1.0f),
		0.0f,
		ARGB(0, 255, 255, 255)));

	//draw [7] win1 start//
	m_Sprites.push_back(
		Sprite(TextureHolder::Instance()->AddTexture("Data/Interface/logo_win1.png"),
		VECTOR3(400, 200, 0),
		VECTOR3(1.0f, 1.0f, 1.0f),
		0.0f,
		ARGB(0, 255, 255, 255)));
	//draw [7] win1 end//

	//draw [8] win1 start//
	m_Sprites.push_back(
		Sprite(TextureHolder::Instance()->AddTexture("Data/Interface/logo_win2.png"),
		VECTOR3(400, 300, 0),
		VECTOR3(1.0f, 1.0f, 1.0f),
		0.0f,
		ARGB(0, 255, 255, 255)));
	//draw [8] win1 end//
}

Screen_Game::~Screen_Game()
{

}

void Screen_Game::ResetAll()
{
	m_GameCUBOAlpha = 255;
	m_Sprites[1].Color = SETA(m_Sprites[1].Color, m_GameCUBOAlpha);
	m_GameTotalAlpha2 = 255;
	m_GameAnyKeyAlpha3 = 0;
	m_GameBlackAlpha = 64;
	m_Sprites[0].Color = SETA(m_Sprites[0].Color, m_GameBlackAlpha);
	m_GameCompleteAlpha = 0;
	m_Sprites[5].Color = SETA(m_Sprites[5].Color, m_GameCompleteAlpha);
	m_GameBlackAlpha = 0;
	m_Sprites[6].Color = SETA(m_Sprites[6].Color, m_GameCompleteAlpha);
	m_GameWin1Alpha = 0;
	m_Sprites[7].Color = SETA(m_Sprites[7].Color, m_GameWin1Alpha);
	m_GameWin2Alpha = 0;
	m_Sprites[8].Color = SETA(m_Sprites[8].Color, m_GameWin2Alpha);

	m_fElapsedTime = 0.0f;

	m_fcomplateElasped = 0;
	m_fRatio = 0.0f;

	m_bGameStarted = false;
	m_bcomplete = false;
}

void Screen_Game::ResetVisual()
{
	m_GameTotalAlpha2 = 255;
	m_GameAnyKeyAlpha3 = 0;
	m_fElapsedTime = 0.0f;
	m_fcomplateElasped = 0;
	m_GameBlackAlpha = 64;
	m_Sprites[0].Color = SETA(m_Sprites[0].Color, m_GameBlackAlpha);
	m_GameCompleteAlpha = 0;
	m_Sprites[5].Color = SETA(m_Sprites[5].Color, m_GameCompleteAlpha);
	m_GameBlackAlpha = 0;
	m_Sprites[6].Color = SETA(m_Sprites[6].Color, m_GameCompleteAlpha);
	m_GameWin1Alpha = 0;
	m_Sprites[7].Color = SETA(m_Sprites[7].Color, m_GameWin1Alpha);
	m_GameWin2Alpha = 0;
	m_Sprites[8].Color = SETA(m_Sprites[8].Color, m_GameWin2Alpha);

	m_bGameStarted = false;
	m_bcomplete = false;
}

void	Screen_Game::Update(const float & Interval)
{
	//Camera Pan Start//
	VECTOR4 NPos(0, 0, 0, 1);

	NPos = m_fRatio * m_TargetCameraPosition + (1.0f - m_fRatio) * m_StoredCameraPosition;
	NPos.w = 1.0f;

	//if(!Physics::Instance()->IsActivated() && m_fRatio < 1.0f)
	Camera::Instance()->Position(NPos);
	(m_fRatio < 1.0f)? m_fRatio += 0.01f : m_fRatio = 1.0f;
	// Camera Pan End//

	if(!m_bGameStarted)
	{
		//image fade effect start//
		m_Sprites[1].Color = SETA(m_Sprites[1].Color, m_GameCUBOAlpha);

		m_GameCUBOAlpha -= 4;
		(m_GameCUBOAlpha < 0)? m_GameCUBOAlpha = 0 : m_GameCUBOAlpha;
		//image fade effect end//

		m_fElapsedTime += Interval;

		if (m_fElapsedTime > 1.5f)
		{
			m_Sprites[3].Color = SETA(m_Sprites[3].Color, m_GameAnyKeyAlpha3);

			m_GameAnyKeyAlpha3 = 255;
		}

		// Press any key function start//
		if (m_fRatio >= 1.0f && m_fElapsedTime > 2.0f && m_InputRef->HasInput())
		{
			m_GameBlackAlpha = 0;
			m_Sprites[0].Color = SETA(m_Sprites[0].Color, m_GameBlackAlpha);

			//m_GameAnyKeyAlpha3 = 0;
			//m_Sprites[4].Color = SETA(m_Sprites[4].Color, m_GameAnyKeyAlpha3);


			m_GameTotalAlpha2 = 0;
			m_Sprites[3].Color = SETA(m_Sprites[3].Color, m_GameTotalAlpha2);

			Physics::Instance()->ActivatePhysics(true);
			Game * _Game = (Game *)Window::Instance()->FindSubProgram("Game");
			_Game->SetGameSTAT(Game::GAME_STAT::PLAY);
			m_bGameStarted = true;
		}
		// Press any key function end//
	}
	else
	{
		Game * _Game = (Game *)Window::Instance()->FindSubProgram("Game");		
		if (_Game->TimeRemaining() == 0)
		{	
			_Game->SetGameSTAT(Game::GAME_STAT::PAUSE);
			Physics::Instance()->ActivatePhysics(false);
			m_fcomplateElasped += Interval;

			if(_Game->Level() == _Game->LevelLimit())
			{
				m_Sprites[6].Color = SETA(m_Sprites[6].Color, m_GameBlackAlpha2);
				m_GameBlackAlpha2 += 2;
				(m_GameBlackAlpha2 > 255)? m_GameBlackAlpha2 = 255 : m_GameBlackAlpha2;

				if(m_fcomplateElasped > 3.0f && m_fcomplateElasped < 10.0f)
				{
					m_Sprites[7].Color = SETA(m_Sprites[7].Color, m_GameWin1Alpha);
					m_GameWin1Alpha += 3;
					(m_GameWin1Alpha > 255)? m_GameWin1Alpha = 255 : m_GameWin1Alpha;
				}
			
				if(m_fcomplateElasped > 6.0f && m_fcomplateElasped < 10.0f)
				{
					m_Sprites[8].Color = SETA(m_Sprites[8].Color, m_GameWin2Alpha);
					m_GameWin2Alpha += 3;
					(m_GameWin2Alpha > 255)? m_GameWin2Alpha = 255 : m_GameWin2Alpha;
				}

				if(m_fcomplateElasped > 10.0f)
				{
					m_Sprites[7].Color = SETA(m_Sprites[7].Color, m_GameWin1Alpha);
					m_GameWin1Alpha -= 3;
					(m_GameWin1Alpha < 0)? m_GameWin1Alpha = 0 : m_GameWin1Alpha;

					m_Sprites[8].Color = SETA(m_Sprites[8].Color, m_GameWin2Alpha);
					m_GameWin2Alpha -= 3;
					(m_GameWin2Alpha < 0)? m_GameWin2Alpha = 0 : m_GameWin2Alpha;
				}
				if(m_fcomplateElasped > 13.0f)
				{
					_Game->SetGameSTAT(Game::GAME_STAT::NEXTLEVEL);
				}	
				//Console::Instance()->FeedText(System_Utility::FormatText("%f", m_fcomplateElasped));
			}
			else
			{
				AudioHandle::Instance()->Pause(true);
				m_GameCompleteAlpha = 255;
				m_Sprites[5].Color = SETA(m_Sprites[5].Color, m_GameCompleteAlpha);

				m_GameBlackAlpha = 64;
				m_Sprites[0].Color = SETA(m_Sprites[0].Color, m_GameBlackAlpha);

				if (m_GameCompleteAlpha = 255 && m_fcomplateElasped > 1.5f)
				{
					_Game->SetGameSTAT(Game::GAME_STAT::NEXTLEVEL);
					Physics::Instance()->ActivatePhysics(true);
					AudioHandle::Instance()->Pause(false);
				}
			}
		}
		// Backspace : Back start//
		if (m_InputRef->KeyPressed('P'))
		{
			m_fRatio = 0.0f;
			m_GameTotalAlpha2 = 255;
			m_GameAnyKeyAlpha3 = 0;
			Interface::Instance()->SetState(Interface::MENU_STATE::PAUSE);
			Physics::Instance()->ActivatePhysics(false);
			AudioHandle::Instance()->Pause(true);
			_Game->SetGameSTAT(Game::GAME_STAT::PAUSE);
			m_pSoundEffect->play();
		}
		// Backspace : Back end//
	}
}

void	Screen_Game::Render()
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

	Game * _Game = (Game *) Window::Instance()->FindSubProgram("Game");

	m_pSpriteBatch->End();

	if(!Physics::Instance()->IsActivated() && _Game->TimeRemaining() > 0)
	{
		m_pTextFont->WriteText(325, 225, System_Utility::FormatText("Level %i", _Game->Level()),		0xffffffff);
		m_pTextFont->WriteText(260, 285, "Time to survive:", 0xffffffff);
		m_pTextFont->WriteText(315, 315, System_Utility::FormatText("%i Seconds", _Game->TimeLimit()),	0xffffffff);
	}
	else if (Physics::Instance()->IsActivated())
		m_pTextFont->WriteText(256, 50, System_Utility::FormatText("Time Remaining: %i", _Game->TimeRemaining()), 0xffffffff);

}