#pragma once

class GameObjectHandler
{
protected:
	std::deque<Box	*>			m_Boxes;
	SmartPtr<PlayerBall>		m_pPlayerBall;
public:
	GameObjectHandler();
	virtual ~GameObjectHandler();

	inline	std::deque<Box *>	*	GetBoxList()	{	return	&m_Boxes;				}
	inline	PlayerBall			*	GetPlayerBall()	{	return	m_pPlayerBall.get();	}

	//	Remove all Data
	void			Clear();
	void			AddToSystem();

	Box	*			CreateTile(const btVector3 & Position, const btVector3 & Size);
	Box *			CreateWall(const btVector3 & Position, const btVector3	& Size);
	
	PlayerBall	*	CreatePlayerBall(const btVector3 & Position, const float & Mass, const float & Radius);
};