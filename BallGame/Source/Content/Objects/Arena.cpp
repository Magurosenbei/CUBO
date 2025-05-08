#include "stdafx.h"
#include "Arena.h"

Arena::Arena()
{

}

Arena::~Arena()
{
	if(m_pGameObjectHandler.get() != NULL)
	{
		m_pGameObjectHandler->Clear();
		m_pGameObjectHandler.reset(NULL);
		m_pGameObjectHandler.release();
	}
	m_pBoxImage = NULL;
	m_pBallImage = NULL;

	m_pEffect.reset(NULL);
	m_pEffect.release();
}

void Arena::Initialize(XMLElement	*	PlayerElement, XMLElement	*	MapElement)
{
	m_pGameObjectHandler = SmartPtr<GameObjectHandler>(new GameObjectHandler);
	
	float PlayerMass	=	PlayerElement->FindVariableZ("mass")->GetValueFloat();
	float PlayerRadius	=	PlayerElement->FindVariableZ("radius")->GetValueFloat();

	XMLElement	*	TileElement		= MapElement->FindElementZ("Tile");
	XMLElement	*	ObstalcleElement= MapElement->FindElementZ("Obstacles");

	ASSERT(	TileElement	!= NULL &&
			ObstalcleElement != NULL, "Map Elements not found");

	btVector3	vTileExtent(0, 0, 0);
	XMLElement	*	TileExtent = TileElement->FindElementZ("Size");
	vTileExtent.setX(TileExtent->FindVariableZ("x")->GetValueFloat());
	vTileExtent.setY(TileExtent->FindVariableZ("y")->GetValueFloat());
	vTileExtent.setZ(TileExtent->FindVariableZ("z")->GetValueFloat());
	
	XMLElement	*	Placement = TileElement->FindElementZ("Placement");
	XMLContent **	Contents = Placement->GetContents();
	size_t	ContentAmount = Placement->GetContentsNum();
	
	//	Extract Map Data
	char Buffer[1024];
	Contents[0]->GetValue(&Buffer[0]);
	CreateTiles(&Buffer[0], vTileExtent, PlayerMass, PlayerRadius);
	m_pGameObjectHandler->AddToSystem();
	
	m_pBoxImage		= TextureHolder::Instance()->AddTexture("Data/Cubemap.png");
	m_pBallImage	= TextureHolder::Instance()->AddTexture("Data/BallTexture.png");

	m_pEffect = SmartPtr<DefaultObjectEffect>(new DefaultObjectEffect);
	
	m_pEffect->Texture()->SetTexture(m_pBallImage);
}

void Arena::Update(const float & Interval)
{
	PlayerBall * _PlayerBall = m_pGameObjectHandler->GetPlayerBall();
	_PlayerBall->Update(Interval);

	std::deque<Box *> * _Boxes = m_pGameObjectHandler->GetBoxList();

	bool Sink = false;

	for(std::deque<Box *>::iterator it = _Boxes->begin(); it != _Boxes->end(); it++)
	{
		(*it)->Update(Interval);
		if(!_PlayerBall->COLORCOMPLETE())	continue;
		if(!(*it)->COLORCOMPLETE())			continue;
		if((*it)->Body()->getWorldTransform().getOrigin().getY() < 0.0f)
		{
			(*it)->DropBox(true);
			continue;
		}
		Sink = _PlayerBall->CheckCollideWith((*it)->Body()->getBroadphaseProxy());
		Sink = Sink && (_PlayerBall->COLORCODE() != (*it)->COLORCODE());
		(*it)->DropBox(Sink);
	}
}

void Arena::Render()
{
	std::deque<Box *>	*	_Boxes = m_pGameObjectHandler->GetBoxList();
	PlayerBall			*	_PlayerBall = m_pGameObjectHandler->GetPlayerBall();

	size_t Passes = 0;
	D3DXMATRIX	matView			= Camera::Instance()->ViewMatrix();
	D3DXMATRIX	matProjection	= Camera::Instance()->ProjectionMatrix();

	m_pEffect->Matrix_View()->SetMatrix(&matView);
	m_pEffect->Matrix_Projection()->SetMatrix(&matProjection);

	m_pEffect->FX()->Begin(&Passes, NULL);
	{
		m_pEffect->Texture()->SetTexture(m_pBoxImage);
		for(std::deque<Box *>::iterator it = _Boxes->begin(); it != _Boxes->end(); it++)
		{
			if(!(*it)->IsVisible())	continue;
			m_pEffect->Scale()->SetVector((*it)->Scale());
			m_pEffect->Color()->SetVector((*it)->COLOR());
			m_pEffect->Matrix_World()->SetMatrix((*it)->Matrix_World());

			m_pEffect->FX()->BeginPass(0);
			(*it)->RenderModel();
			m_pEffect->FX()->EndPass();
		}
		m_pEffect->Texture()->SetTexture(m_pBallImage);
		{
			m_pEffect->Scale()->SetVector(_PlayerBall->Scale());
			m_pEffect->Color()->SetVector(_PlayerBall->COLOR());
			m_pEffect->Matrix_World()->SetMatrix(_PlayerBall->Matrix_World());

			m_pEffect->FX()->BeginPass(0);
			_PlayerBall->RenderModel();
			m_pEffect->FX()->EndPass();
		}
	}
	m_pEffect->FX()->End();
}

void Arena::CreateTiles(const char * pData, const btVector3 & Extents, const float & PlayerMass, const float & PlayerRadius)
{
	size_t X(0), Z(0);
	const float XLen(Extents.getX()), ZLen(Extents.getZ());
	for(size_t i = 0; pData[i] != '\0'; i++)
	{
		btVector3 Position(X * XLen * - 2.0f, 0, Z * ZLen * - 2.0f);
		switch(pData[i])
		{	
		case 'B':
			{
				m_pGameObjectHandler->CreatePlayerBall(Position + btVector3(0, Extents.getY() * 2.0f, 0), PlayerMass, PlayerRadius);

				VECTOR4 Look(Position.getX(),  Extents.getY() * 2.0f, Position.getZ(), 1.0f);
				VECTOR4	Position(Look + VECTOR4(0, 10, -20, 1));
				Camera::Instance()->Look(Look);
				Interface::Instance()->SetTargetCameraPosition(Position);
			}
		case 'S':
			{
				Box * _Box = m_pGameObjectHandler->CreateTile(Position, Extents);
				_Box->Body()->setFriction(15.0f);
			}
			break;
		case 'W':
			{
				Box * _Box = m_pGameObjectHandler->CreateWall(Position, Extents + btVector3(0, 10, 0));
			}
			break;
		}
		X++;
		if(pData[i] == '\n')
		{
			X = 0;
			Z++;
		}
	}
	//Console::Instance()->FeedText(System_Utility::FormatText("X : %i Z : %i", X, Z));
}