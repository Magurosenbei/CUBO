#pragma once

class Abstract_SubProgram;
class Abstract_Renderer;

template <class T>
class Abstract_Single
{
protected:
	static SmartPtr <T> m_pInstance;
	std::string Label;
public:
	static T * Instance() 
	{ 
		if(!m_pInstance.get())
			 m_pInstance = SmartPtr<T>(new T);
		
		return m_pInstance.get();
	}
};

class Abstract_Mesh
{
public:
	Abstract_Mesh() {}
	virtual ~Abstract_Mesh() {}
	//	Only to be called by Holder
	virtual bool	Load(const std::string & FilePath) = 0;
	//	Draws mesh
	virtual void	Render() = 0;
};

class Abstract_SubProgram
{
protected:
	bool	m_bDelete;
public:
	Abstract_SubProgram(): m_bDelete(true) {}
	virtual ~Abstract_SubProgram(){}

	//	If	this is a global instance, it should be false
	inline	bool	CanDelete()	const	{	return	m_bDelete;	}
	
	virtual	void	Update(const float & Interval) = 0;
};

class Abstract_Renderable
{
public:
	virtual ~Abstract_Renderable(){}
	//	@params, the current render target ID, width and height
	virtual void	Render(const size_t & RenderTargetID, const size_t & Width, const size_t & Height) = 0;
};

class Abstract_Renderer
{
	friend	class	Window;
public:
	Abstract_Renderer() {}
	virtual	~Abstract_Renderer() {}
	virtual	void	Resize() = 0;

	virtual bool	Initialze(HINSTANCE Instance, HWND	Hwnd) = 0;
	virtual	bool	Shutdown() = 0;
	virtual void	Render() = 0;

	//	Register the instance to a Rendertarget, it is required for it to shown on screen
	virtual void	RegisterToTarget(const size_t & ID, const std::string & Key, Abstract_Renderable * Address) = 0;
	//	Unregister the instance from a Rendertarget
	virtual void	UnRegisterToTarget(const size_t & ID, const std::string & Key, Abstract_Renderable * Address) = 0;
};

//	This is an overlay abstract only accessed by Window
class Abstract_Overlay
{
public:
	virtual ~Abstract_Overlay() {}
	virtual	void	Render() = 0;
};

//	Typical Physics object
class Abstract_PhysicsObject
{
protected:
	SmartPtr<btRigidBody>	m_pBody;
public:
	Abstract_PhysicsObject()	:	m_pBody(NULL){}
	virtual ~Abstract_PhysicsObject() {}

	inline	btRigidBody	*	Body()	const	{	return	m_pBody.get();	}

	//	Remove from Physics System and delete the body
	virtual	void	Delete();

	//	Scans Contact points with a targeted object
	virtual	bool	CheckCollideWith(btBroadphaseProxy * Target);
	
	//	Add to Physics System, Checks if it is already added
	virtual void	AddToSystem();
	//	Remove from Physics System, Check if it is already Remove, *Warning : Does not delete Body
	virtual	void	RemoveFromSystem();
};

//	Typical Display Object, contains world and scale matrix
//	Syncronize world matrix with btWorldTransform to get correct output.
class Abstract_DisplayObject
{
protected:
	SmartPtr<Abstract_Mesh>	m_pMesh;
	D3DXMATRIX				m_World;
	D3DXMATRIX				m_Scale;

	VECTOR4					m_vScale;

	bool					m_bVisible;
public:
	Abstract_DisplayObject();
	virtual ~Abstract_DisplayObject() {};

	inline	bool			IsVisible()		{	return	m_bVisible;	}

	inline	D3DXMATRIX *	Matrix_World()	{	return	&m_World;	}
	inline	VECTOR4			Scale()			{	return	m_vScale;	}

	inline  void			RenderModel()	{	m_pMesh->Render();	}
};