#include "stdafx.h"
#include "Box.h"

Box::Box()
:	Abstract_PhysicsObject(), m_vColor(1, 1, 1, 1), m_ColorEffect(), 
	m_bSink(false), m_fSinkElapsedTime(0), m_fShake(0), m_ColorCode(0), 
	m_pSoundEffect(NULL), 
	m_bPlayedSound(false)
{
}

Box::~Box()
{
	m_pMesh.release();

	//m_pBody.reset(NULL);	// Might not need to delete if let Physics do the clearing else DIY
	m_pBody.release();
}

void Box::Initialize(
const btVector3 &	Position, 
const float		&	Mass, 
const btVector3 &	Extents, 
bool				IsKinematic,
bool				RandomColor,
bool				Display)
{
	m_bVisible = Display;
	m_vScale = VECTOR4(Extents.getX(), Extents.getY(), Extents.getZ(), 1.0f);
	D3DXMatrixScaling(&m_Scale, Extents.getX(), Extents.getY(), Extents.getZ());

	btCollisionShape	*	Shape = new btBoxShape(Extents);
	Shape = Physics::Instance()->GetCollisionShape(
		System_Utility::FormatText("Box_%f_%f_%f", 
		Extents.getX(), Extents.getY(), Extents.getZ()), 
		Shape);

	btVector3 Initer(0, 0, 0);
	if(Mass > 0)
		Shape->calculateLocalInertia(Mass, Initer);
	Shape->setMargin(0.04f);

	m_pBody = SmartPtr<btRigidBody>(new btRigidBody(Mass, NULL, Shape, Initer));
	
	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(Position);	
	m_pBody->setWorldTransform(Transform);
	m_pBody->setFriction(0.0f);
	m_pBody->setRestitution(0.0f);

	if(Mass <= 0)
	{
		if(IsKinematic)
		{
			m_pBody->setCollisionFlags(m_pBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
			m_pBody->setActivationState(DISABLE_DEACTIVATION);
		}
		else
			m_pBody->getWorldTransform().getOpenGLMatrix((float *)m_World.m);
	}
	
	m_pSoundEffect = AudioHandle::Instance()->GetSoundEffect("Data/DropBox.wav", audiere::SoundEffectType::MULTIPLE);
	Abstract_Mesh * Mesh = MeshHolder::Instance()->GetMesh("Data/Cube1x1.obj");
	ASSERT(Mesh != NULL, "Box Mesh not found");
	m_pMesh = SmartPtr<Abstract_Mesh>(Mesh);

	if(RandomColor)
	{
		m_ColorCode = rand() % 3;
		switch(m_ColorCode)
		{
		case 0:
			m_vColor = COLOR_RED;
			break;
		case 1:
			m_vColor = COLOR_GREEN;
			break;
		case 2:
			m_vColor = COLOR_BLUE;
			break;
		}
	}
	m_ColorEffect = ColorTransistion(m_vColor);
	m_fColorElapsedTime = rand() % 1 + 2;
}

void Box::Update(const float & Interval)
{
	btTransform World = m_pBody->getWorldTransform();

	if(World.getOrigin().getY() < -50.0f)
	{
		m_bVisible = false;
		return;
	}
	if(m_bVisible && m_pBody->isKinematicObject())
	{
		if(m_bSink)
		{
			if (m_fSinkElapsedTime > g_fBoxDropDuration)
			{
				if(!m_bPlayedSound)
				{
					m_pSoundEffect->play();
					m_bPlayedSound = true;
				}
				m_pBody->translate(btVector3(0, -5, 0) * Interval);
				m_fShake = 0;
			}
			else
			{
				m_fSinkElapsedTime += Interval;
				m_fShake = DEGTORAD((rand() % 40 - 20) * 0.5f);
			}
		}	
		
		m_pBody->getWorldTransform().getOpenGLMatrix((float *)m_World.m);
		D3DXMATRIX	Rotation;
		D3DXMatrixRotationZ(&Rotation, m_fShake);
		D3DXMatrixMultiply(&m_World, &Rotation, &m_World);

		// Colors
		m_fColorElapsedTime -= Interval;

		if(m_ColorEffect.Completed() && m_fColorElapsedTime <= 0)
		{
			m_fColorElapsedTime = System_Utility::RandomFloat(STD_COLORCHANGEFACTOR_MAX, max(g_fColorChangeFactor, STD_COLORCHANGEFACTOR_MAX)) + 1;
			m_ColorCode = rand() % 3;
			switch(m_ColorCode)
			{
			case 0:
				m_ColorEffect.ChangeColor(COLOR_RED);
				break;
			case 1:
				m_ColorEffect.ChangeColor(COLOR_GREEN);
				break;
			case 2:
				m_ColorEffect.ChangeColor(COLOR_BLUE);
				break;
			}
		}

		m_vColor = m_ColorEffect.Color();
		m_ColorEffect.Update(Interval);
	}
	else if(m_pBody->isStaticObject())
	{

	}
}

void Box::DropBox(bool Yes)
{
	if(m_fSinkElapsedTime > g_fBoxDropDuration)	return;	//	Sinking Already
	if(m_bSink && Yes)				return;	//	Already Made to Sink
	
	m_bSink = Yes;
	m_fSinkElapsedTime = 0;
	m_fShake = 0;
}

void Box::Render()
{
	D3DXMatrixMultiply(&m_World, &m_Scale, &m_World);
	DxDevice::Instance()->Device()->SetTransform(DXWORLD, &m_World);
	m_pMesh->Render();
}