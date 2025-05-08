#include "stdafx.h"
#include "Game.h"

Grid	*		grid;

Abstract_Mesh * Sky(NULL);
Abstract_Mesh * Sky2(NULL);
DXTEXTURE		SkyImage(NULL);
DXTEXTURE		SkyImage2(NULL);

float l_fRotate	=	0.0f;

Game::Game()
:		Abstract_SubProgram(), m_GAME_STAT(GAME_STAT::MENU),
		m_pArena(NULL), m_fTimeLimit(15.0f), m_fTime(15.0f)
{
	m_pPhysicsRef	= SmartPtr<Physics>(Physics::Instance());
	m_pInputRef		= SmartPtr<InputHandle>(InputHandle::Instance());
	m_pRenderRef	= SmartPtr<DxDevice>(DxDevice::Instance());

	MeshHolder::Instance()->AddMesh("Data/Cube1x1_sub10.obj", MeshHolder::OBJFILE);
	MeshHolder::Instance()->AddMesh("Data/Cube1x1.obj", MeshHolder::OBJFILE);
	MeshHolder::Instance()->AddMesh("Data/Sphere_R1.obj", MeshHolder::OBJFILE);
	MeshHolder::Instance()->AddMesh("Data/Sphere_R1_sub4.obj", MeshHolder::OBJFILE);
	MeshHolder::Instance()->AddMesh("Data/skybox.obj", MeshHolder::OBJFILE);
	MeshHolder::Instance()->AddMesh("Data/outter_background.obj", MeshHolder::OBJFILE);

	Sky = MeshHolder::Instance()->GetMesh("Data/skybox.obj");
	SkyImage = TextureHolder::Instance()->AddTexture("Data/background.png");
	Sky2 = MeshHolder::Instance()->GetMesh("Data/outter_background.obj");
	SkyImage2 = TextureHolder::Instance()->AddTexture("Data/outter_background.png");
	grid = new Grid();
	grid->Initialize();

	m_Level = 1;
	m_MaxLevel = 6;
	DxDevice::Instance()->RegisterToTarget(0, "Game", this);
}

Game::~Game()
{
	SkyImage = NULL;
	Sky = NULL;
	UnloadData();

	delete grid;
	MeshHolder::Instance()->ClearMeshes();

	m_pPhysicsRef.release();
	m_pInputRef.release();
	m_pRenderRef.release();
}

void	Game::Update(const float & Interval)
{
	if(m_pInputRef->KeyPressed(VK_F4))
		m_GAME_STAT = NEXTLEVEL;
	
	float	_Interval = Interval;

	(l_fRotate < 6.284f)? l_fRotate += Interval * 0.1f : l_fRotate = 0;

	switch (m_GAME_STAT)
	{
	case GAME_STAT::MENU:

		//	If Interface returns says load Game
		//m_GAME_STAT = GAME_STAT::LOAD;
		break;

	case GAME_STAT::LOAD:
		
		LoadData(System_Utility::FormatText("Data/Levels/Level_%i.xml", m_Level));
		AudioHandle::Instance()->Pause(false);
		m_GAME_STAT = GAME_STAT::PAUSE;
		break;

	case GAME_STAT::FINISH:
		WriteCommandLine("Game Completed");
		Interface::Instance()->SetState(Interface::MENU_STATE::MENU_MAIN);
		UnloadData();
		m_Level = 1;
		m_fTime = 0.0f;
		m_fTimeLimit = 15.0f;

		m_GAME_STAT = GAME_STAT::MENU;
		break;

	case GAME_STAT::NEXTLEVEL:
		{
			UnloadData();
			(m_fTimeLimit > 60.0f)? m_fTimeLimit = 60.0f : m_fTimeLimit += 3.0f;
			m_fTime = m_fTimeLimit;
			m_Level++;
			if(m_Level > m_MaxLevel)
				m_GAME_STAT = GAME_STAT::FINISH;
			else
				m_GAME_STAT = GAME_STAT::LOAD;
		}
		break;

	case GAME_STAT::RESTART:
		{
			m_fTime = m_fTimeLimit;
			//	Try Again, Yes do the bottom
			UnloadData();
			m_GAME_STAT = GAME_STAT::LOAD;
		}

		break;

	case GAME_STAT::PAUSE:
		_Interval = 0;
	case GAME_STAT::PLAY:
		//	Update game
		PlayGame(_Interval);
		break;

	default:
		break;
	}
}	

void	Game::Render(const size_t & RenderTargetID, const size_t & Width, const size_t & Height)
{
	D3DXMATRIX	matView = Camera::Instance()->ViewMatrix();
	D3DXMATRIX	matProjection = Camera::Instance()->ProjectionMatrix();

	D3DXMATRIX	matRotate;
	D3DXMatrixRotationY(&matRotate, l_fRotate);

	DxDevice::Instance()->Device()->SetTransform(DXWORLD, &matRotate);
	DxDevice::Instance()->Device()->SetTexture(0, SkyImage2);
	Sky2->Render();
	DxDevice::Instance()->Device()->SetTransform(DXWORLD, MatrixHelper::IDENTITY());
	DxDevice::Instance()->Device()->SetTexture(0, SkyImage);
	Sky->Render();

	DxDevice::Instance()->Device()->SetTexture(0, NULL);
	switch (m_GAME_STAT)
	{
	case GAME_STAT::MENU:
		m_fTimeLimit = 15.0f;
		m_fTime = m_fTimeLimit;
		m_Level = 1;
		break;

	case GAME_STAT::LOAD:
		//	Draw Loading Screen?
		break;

	case GAME_STAT::NEXTLEVEL:
		//	Draw Loading Screen?
		break;

	case GAME_STAT::PAUSE:
	case GAME_STAT::PLAY:
		{
			if(m_pArena.get() != NULL)
			m_pArena->Render();
		}
		break;

	default:
		break;
	}
}

void Game::LoadData(const std::string & DefinitionFile)
{
	g_fBoxDropDuration = STD_BOXDROPDURATION;
	g_fColorChangeFactor = STD_COLORCHANGEFACTOR;


	WriteCommandLine("Loading Level %s", DefinitionFile.c_str());
	System_HiResTimer	Timer;
	Timer.Start();
	//	Read Definition File
	XML	File(DefinitionFile.c_str());
	ASSERT(File.IntegrityTest() && File.ParseStatus() == NULL, "Error Reading XML file");
	//File.CompressMemory();

	//	Essential Elements for parsing more data
	XMLElement	*	Root = File.GetRootElement();
	XMLElement	*	PlayerElement	= Root->FindElementZ("Player");
	XMLElement	*	MapElement		= Root->FindElementZ("Map");
	XMLElement	*	EffectElement	= Root->FindElementZ("Effects");
	
	ASSERT(	PlayerElement != NULL &&
			MapElement	!= NULL &&
			EffectElement != NULL, "Essential Elements not found");
	// ............. TO BE DONE XML whatever

	//	Create Arena
	m_pArena = SmartPtr<Arena>(new Arena);
	m_pArena->Initialize(PlayerElement, MapElement);

	//	Create Effects 
	//	.....
	PlayGame(0);
	Interface::Instance()->SetTargetCameraPosition(Camera::Instance()->Position());
	Interface::Instance()->RestartGame();
	WriteCommandLine("Load Time Taken : %f ms", Timer.End());
}

void Game::UnloadData()
{
	Physics::Instance()->ActivatePhysics(false);
	System_HiResTimer	Timer;
	Timer.Start();

	m_pArena.reset(NULL);

	m_pPhysicsRef->ClearBodies();

	WriteCommandLine("Unload Time Taken : %f ms", Timer.End());
}

void Game::PlayGame(const float & Interval)
{
	m_pArena->Update(Interval);

	PlayerBall *	_PlayerBall = m_pArena->GetObjectHandler()->GetPlayerBall();
	btTransform		_PlayerWorldTransform = _PlayerBall->Body()->getWorldTransform();

	// Died
	// Check for game over etc
	bool PlayerDied = !_PlayerBall->IsVisible();
	if(PlayerDied)
	{
		WriteCommandLine("PlayerDied");
		m_GAME_STAT = GAME_STAT::RESTART;
		m_fTime = m_fTimeLimit;
		
		return;
	}
	if(_PlayerBall->Body()->getWorldTransform().getOrigin().getY() < -5.0f)
		return;
	if(m_fTime - Interval < 0)
	{
		
	}
	else
	{
		m_fTime -= Interval;
		m_fDifficultyElapsed -= Interval;
		if(m_fDifficultyElapsed < 0)
		{
			m_fDifficultyElapsed = STD_DIFFICULTYELAPSED;
			(g_fColorChangeFactor < STD_COLORCHANGEFACTOR_MAX)? g_fColorChangeFactor = STD_COLORCHANGEFACTOR_MAX : g_fColorChangeFactor *= 0.75f;
			(g_fBoxDropDuration < STD_BOXDROPDURATION)? g_fBoxDropDuration = STD_BOXDROPDURATION : g_fBoxDropDuration *= 0.85f;
			//Console::Instance()->FeedText(System_Utility::FormatText("Color : %f\nBox : %f", g_fColorChangeFactor, g_fColorChangeFactor));
		}
	}
	//Console::Instance()->FeedText(System_Utility::FormatText("Time Remaining : %f", m_fTime));
}