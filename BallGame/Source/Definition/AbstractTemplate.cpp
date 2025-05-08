#include "stdafx.h"
#include "AbstractTemplate.h"

void Abstract_PhysicsObject::Delete()
{
	RemoveFromSystem();
	m_pBody.reset(NULL);
}

bool Abstract_PhysicsObject::CheckCollideWith(btBroadphaseProxy * Target)
{
	//	Scan for a pair
	btBroadphasePair * Pair;
	Pair = Physics::Instance()->World()->getPairCache()->findPair(Target, m_pBody->getBroadphaseHandle());
	if(!Pair) return false;

	//	Scan for Contact points
	btManifoldArray Contacts;
	if(!Pair->m_algorithm) return false;
	Pair->m_algorithm->getAllContactManifolds(Contacts);
	if(Contacts.size() < 1)
		return false;

	//	See if contact points intersect
	btPersistentManifold * Pt;
	float Direction;
	for(int i = Contacts.size() - 1; i > -1; i--)
	{	
		Pt = Contacts[i];
		Direction = (Pt->getBody0() == m_pBody.get())? btScalar(1.0) : btScalar(-1.0);
		for(int j = Pt->getNumContacts() - 1; j > -1; j--)
		{
			if(Pt->getContactPoint(j).getDistance() < 0.098f)
				return true;
		}
	}
	return false;
}

void Abstract_PhysicsObject::AddToSystem()
{
	ASSERT(m_pBody.get() != NULL, "Physics body is deleted or missing")
	if(!m_pBody->isInWorld())
		Physics::Instance()->World()->addRigidBody(m_pBody.get());
}

void Abstract_PhysicsObject::RemoveFromSystem()
{
	ASSERT(m_pBody.get() != NULL, "Physics body is deleted or missing")
	if(m_pBody->isInWorld())
		Physics::Instance()->World()->removeRigidBody(m_pBody.get());
}


Abstract_DisplayObject::Abstract_DisplayObject()
:	m_pMesh(NULL), m_vScale(1, 1, 1, 1), m_bVisible(true)
{
	D3DXMatrixIdentity(&m_World);
	D3DXMatrixScaling(&m_Scale, m_vScale.x, m_vScale.y, m_vScale.z);
}