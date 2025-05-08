#pragma once


class Physics : public Abstract_SubProgram,	public Abstract_Single<Physics>
{
	friend class Abstract_Single<Physics>;
protected:
	//	Basic Setup Requirement _Do not care >.<
	btDefaultCollisionConfiguration	*	m_pbtCol_Config;
	btCollisionDispatcher			*	m_pbtCol_Dispatch;
	btBroadphaseInterface			*	m_pBtBroad_Interface;
	btGhostPairCallback				*	m_pbtGhost_Callback;
	btConstraintSolver				*	m_pbtConstraint_Solver;

	//	Main Component of Bullet Physics
	btDiscreteDynamicsWorld			*	m_pbtDyn_World;
	float								m_fPhysicsClock;

	typedef std::map	<std::string, btCollisionShape *>	ShapeList;
	ShapeList												m_Shapes;
	
	bool													m_bUpdate;
	Physics();
	virtual bool	Initialize();
	virtual bool	Shutdown();
public:
	virtual ~Physics();

	inline	bool	IsActivated()				{	return	m_bUpdate;	}
	inline	void	ActivatePhysics(bool OnOff)	{	m_bUpdate = OnOff;	}

	inline btDiscreteDynamicsWorld	* World()			const { return m_pbtDyn_World; }

	//	Search if the shape exist with given key,
	//	Format string according to Type
	//	Box = Box_W_H_D			- Box_10_10_10
	//	Ball = Ball_R			- Ball_10
	//	Mesh = Mesh_filename	- Mesh_Data/Ball.obj

	btCollisionShape	*	GetCollisionShape(std::string Key, btCollisionShape * Shape = NULL);

	//	Call these and you won't need to World()->Remove bla bla, just delete your body instances and NULL your shapes
	void			ClearShapes();
	//	Clear all bodies in the system, deletes instances
	void			ClearBodies();

	virtual void	Update(const float & Interval);
};