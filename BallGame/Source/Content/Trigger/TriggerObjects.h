#pragma once

//	Uses btGhostObjects
class TriggerObject
{
protected:
	SmartPtr<btGhostObject>	m_pBody;
public:
	TriggerObject();

	virtual ~TriggerObject();

	inline	btGhostObject	*	Body()	const	{	return	m_pBody.get();	}

	virtual	void	Initialize(const btVector3 & Position, const btQuaternion & Quaternion, btCollisionShape * Shape);

	virtual	bool	CheckCollideWith(btBroadphaseProxy * Target);

	virtual void	AddToSystem();
	virtual	void	RemoveFromSystem();
};