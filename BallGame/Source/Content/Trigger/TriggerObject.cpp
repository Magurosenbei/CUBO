#include "stdafx.h"
#include "TriggerObjects.h"

TriggerObject::TriggerObject()
:	m_pBody(NULL)
{

}

TriggerObject::~TriggerObject()
{
	m_pBody.reset(NULL);
	m_pBody.release();
}

void TriggerObject::Initialize(const btVector3 & Position, const btQuaternion & Quaternion, btCollisionShape * Shape)
{
	ASSERT(Shape != NULL, "Trigger object given a NULL SHAPE");
	m_pBody = SmartPtr<btGhostObject>(new btGhostObject);
	m_pBody->setCollisionShape(Shape);
	m_pBody->setCollisionFlags(btCollisionObject::CO_GHOST_OBJECT);

	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(Position);	
	Transform.setRotation(Quaternion);
	m_pBody->setWorldTransform(Transform);
}

bool TriggerObject::CheckCollideWith(btBroadphaseProxy * Target)
{
	btBroadphasePair * Pair;
	Pair = Physics::Instance()->World()->getPairCache()->findPair(Target, m_pBody->getBroadphaseHandle());
	if(!Pair) return false;
	return true;
	//btManifoldArray Contacts;
	//if(!Pair->m_algorithm) return false;
	//Pair->m_algorithm->getAllContactManifolds(Contacts);
	//if(Contacts.size() < 1)
	//	return false;

	//btPersistentManifold * Pt;
	//float Direction;
	//bool Collided = false;
	//for(int i = 0; i < Contacts.size() && !Collided; i++)
	//{	
	//	Pt = Contacts[i];
	//	Direction = (Pt->getBody0() == m_pBody.get())? btScalar(1.0) : btScalar(-1.0);
	//	for(int j = 0; j < Pt->getNumContacts() && !Collided; j++)
	//	{
	//		if(Pt->getContactPoint(j).getDistance() < 0.0f)
	//			Collided = true;
	//	}
	//}
	//return Collided;
}

void TriggerObject::AddToSystem()
{
	Physics::Instance()->World()->addCollisionObject(m_pBody.get(), btBroadphaseProxy::SensorTrigger);
}

void TriggerObject::RemoveFromSystem()
{
	Physics::Instance()->World()->removeCollisionObject(m_pBody.get());
}