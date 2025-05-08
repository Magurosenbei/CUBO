#pragma once

class Arena
{
protected:
	SmartPtr<DefaultObjectEffect>	m_pEffect;
	DXTEXTURE						m_pBoxImage;
	DXTEXTURE						m_pBallImage;

	SmartPtr<GameObjectHandler>		m_pGameObjectHandler;

	btVector3						m_vMinExtents;
	btVector3						m_vMaxExtents;

	virtual	void	CreateTiles(const char * pData, const btVector3 & Extents, const float & PlayerMass, const float & PlayerRadius);
public:
	Arena();
	virtual ~Arena();

	inline	GameObjectHandler * GetObjectHandler()	{	return	m_pGameObjectHandler.get();	}
	
	virtual	void	Initialize(XMLElement	*	PlayerElement, XMLElement	*	MapElement);

	virtual	void	Update(const float & Interval);
	virtual	void	Render();
};