#include "stdafx.h"
#include "Physics.h"

SmartPtr<Physics> Abstract_Single<Physics>::m_pInstance;

Physics::Physics()
:	m_pbtCol_Config(NULL),		m_pbtCol_Dispatch(NULL), 
	m_pBtBroad_Interface(NULL), m_pbtConstraint_Solver(NULL),
	m_pbtDyn_World(NULL),		m_fPhysicsClock(1.0f / 60.0f)
{
	m_bDelete = false;
	m_bUpdate = false;
	bool Result = Initialize();
	ASSERT(Result == true, "Physics Failed to initialize");
}

Physics::~Physics()
{
	bool Result = Shutdown();
	ASSERT(Result == true, "Physics Failed to initialize");
}

btCollisionShape	*	Physics::GetCollisionShape(std::string Key, btCollisionShape * Shape)
{
	Key = System_Utility::LowerCase(Key);
	ShapeList::iterator it = m_Shapes.find(Key);
	bool Found = (it != m_Shapes.end());
	if(Shape != NULL)
	{
		if(Found)
		{
			delete Shape;
			Shape = NULL;
			return it->second;
		}
		else
		{
			m_Shapes.insert(std::make_pair(Key, Shape));
			return Shape;
		}
	}
	if(Found)
		return it->second;
	return NULL;
}

void Physics::ClearShapes()
{
	for(ShapeList::iterator it = m_Shapes.begin();
		it != m_Shapes.end(); it++)
	{
		delete it->second;
		it->second = NULL;
	}
	m_Shapes.clear();
}

void Physics::ClearBodies()
{
	btCollisionObjectArray & List = m_pbtDyn_World->getCollisionObjectArray();
	btRigidBody	*	B;
	for (int i = List.size() - 1; i >= 0 ; i--)
	{
		B = btRigidBody::upcast(List[i]);
		if(B && B->getMotionState())
			delete B->getMotionState();

		m_pbtDyn_World->removeCollisionObject(List[i]);
		List[i] = NULL;
		delete B;
	}
	List.clear();
}

bool Physics::Initialize()
{
	m_pbtCol_Config = new btDefaultCollisionConfiguration;
	m_pbtCol_Dispatch = new btCollisionDispatcher(m_pbtCol_Config);

	btVector3 axismin(-1000, -1000, -1000), axismax(1000, 1000, 1000);
	m_pBtBroad_Interface = new btAxisSweep3(axismin, axismax, 2048);

	m_pbtGhost_Callback = new btGhostPairCallback;
	m_pBtBroad_Interface->getOverlappingPairCache()->setInternalGhostPairCallback(m_pbtGhost_Callback);

	m_pbtConstraint_Solver = new btSequentialImpulseConstraintSolver;

	m_pbtDyn_World = new btDiscreteDynamicsWorld(	m_pbtCol_Dispatch, m_pBtBroad_Interface,
													m_pbtConstraint_Solver, m_pbtCol_Config);
	if(!m_pbtDyn_World)
		return false;
	m_pbtDyn_World->setGravity(btVector3(0, -9.8f, 0));
	WriteCommandLine("Physics Initialized");
	return true;
}

bool Physics::Shutdown()
{
	ClearBodies();
	ClearShapes();
	/* Clean up */
	try
	{
		delete m_pbtDyn_World;			m_pbtDyn_World = NULL;
		delete m_pbtConstraint_Solver;	m_pbtConstraint_Solver = NULL;
		delete m_pbtCol_Dispatch;		m_pbtCol_Dispatch = NULL;
		delete m_pBtBroad_Interface;	m_pBtBroad_Interface = NULL;
		delete m_pbtGhost_Callback;		m_pbtGhost_Callback = NULL;
		delete m_pbtCol_Config;			m_pbtCol_Config = NULL;
	}
	catch(std::exception & e)
	{
		UNREFERENCED_PARAMETER(e);
		WriteCommandLine("Problem -SysPhysics Shutdown : \n%s", e.what());
		return false;
	}
	return true;
}

void Physics::Update(const float &Interval)
{
	if(!m_bUpdate) return;
	m_pbtDyn_World->stepSimulation(Interval, 1, m_fPhysicsClock);
	//Console::Instance()->FeedText(System_Utility::FormatText("Physics : %f", Timer.End()));
}