#include "stdafx.h"
#include "ObjectHandler.h"

GameObjectHandler::GameObjectHandler()
{
}

GameObjectHandler::~GameObjectHandler()
{


}

void GameObjectHandler::Clear()
{
	for(size_t i = 0; i < m_Boxes.size(); i++)
	{
		delete m_Boxes[i];
		m_Boxes[i] = NULL;
	}
	m_Boxes.clear();
	if(m_pPlayerBall.get() != NULL)
	{
		m_pPlayerBall.reset(NULL);
		m_pPlayerBall.release();
	}
}

void GameObjectHandler::AddToSystem()
{
	for(size_t i = 0; i < m_Boxes.size(); i++)
		m_Boxes[i]->AddToSystem();

	m_pPlayerBall->AddToSystem();
}

Box * GameObjectHandler::CreateTile(const btVector3 &Position, const btVector3 &Size)
{
	Box * _Box = new Box();
	_Box->Initialize(Position, 0.0f, Size, true, true, true);
	m_Boxes.push_back(_Box);
	return _Box;
}

Box * GameObjectHandler::CreateWall(const btVector3 & Position, const btVector3 & Size)
{
	Box * _Box = new Box();
	_Box->Initialize(Position, 0.0f, Size, false, false, false);
	m_Boxes.push_back(_Box);
	return _Box;
}

PlayerBall	*	GameObjectHandler::CreatePlayerBall(const btVector3 &Position, const float & Mass, const float &Radius)
{
	m_pPlayerBall = SmartPtr<PlayerBall>(new PlayerBall);
	m_pPlayerBall->Initialize(Position, Mass, Radius);

	return m_pPlayerBall.get();
}