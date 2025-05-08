#include "stdafx.h"
#include "PlayerBall.h"

PlayerBall::PlayerBall()
:	Abstract_PhysicsObject(), Abstract_DisplayObject(),
	m_fSpeed(8.5f), m_vAngularVelocity(0, 0, 0), m_ColorEffect(VECTOR4(1, 0, 0, 1)), m_fColorElapsedTime(0), m_ColorCode(0)
{
	m_pInputRef = SmartPtr<InputHandle>(InputHandle::Instance());
}

PlayerBall::~PlayerBall()
{
	m_pInputRef.release();
	m_pMesh.release();
	m_pBody.release();
}

bool PlayerBall::Initialize(const btVector3 & Position, const float & Mass, const float & Size)
{
	m_vScale = VECTOR4(Size, Size, Size, 1.0f);

	D3DXMatrixScaling(&m_Scale, m_vScale.x, m_vScale.y, m_vScale.z);

	btCollisionShape * Shape = new btSphereShape(Size);
	Shape = Physics::Instance()->GetCollisionShape(System_Utility::FormatText("Ball_%f", Size), Shape);
	btVector3 Initer(0, 0, 0);
	Shape->calculateLocalInertia(Mass, Initer);

	m_pBody = SmartPtr<btRigidBody>(new btRigidBody(Mass, NULL, Shape, Initer));
	m_pBody->setActivationState(DISABLE_DEACTIVATION);

	m_pBody->setRestitution(0.0f);
	m_pBody->setFriction(0.5f);
	m_pBody->setDamping(0.0f, 0.9f);

	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(Position);	
	m_pBody->setWorldTransform(Transform);

	Abstract_Mesh * Mesh = MeshHolder::Instance()->GetMesh("Data/Sphere_R1_sub4.obj");
	ASSERT(Mesh != NULL, "Box Mesh not found");
	m_pMesh = SmartPtr<Abstract_Mesh>(Mesh);

	return true;
}

void PlayerBall::Update(const float & Interval)
{
	btTransform World	= m_pBody->getWorldTransform();
	btVector3	Origin	= World.getOrigin();
	if(Origin.getY() < -3.0f)
		AudioHandle::Instance()->Pause(true);
	if(Origin.getY() < -20.0f)
		m_bVisible = false;

	World.getOpenGLMatrix((float *)m_World.m);
	
	/// <summary>
	///	Controls of the ball
	/// </summary>
	m_vAngularVelocity.setZero();

	if(m_pInputRef->KeyDown(VK_UP))
		m_vAngularVelocity.setX(m_fSpeed);
	else if(m_pInputRef->KeyDown(VK_DOWN))
		m_vAngularVelocity.setX(-m_fSpeed);

	if(m_pInputRef->KeyDown(VK_LEFT))
		m_vAngularVelocity.setZ(-m_fSpeed);
	else if(m_pInputRef->KeyDown(VK_RIGHT))
		m_vAngularVelocity.setZ(m_fSpeed);
	
	if(m_vAngularVelocity != btVector3(0, 0, 0))
		m_vAngularVelocity = m_vAngularVelocity.normalized() * m_fSpeed;
	m_pBody->setAngularVelocity(m_vAngularVelocity);
	
	m_ColorEffect.Update(Interval);
	/*if(m_ColorEffect.Completed())
	{
		if(m_pInputRef->KeyPressed('1'))
			m_ColorEffect.ChangeColor(COLOR_RED),	m_ColorCode = 0;
		if(m_pInputRef->KeyPressed('2'))
			m_ColorEffect.ChangeColor(COLOR_GREEN), m_ColorCode = 1;
		if(m_pInputRef->KeyPressed('3'))
			m_ColorEffect.ChangeColor(COLOR_BLUE),	m_ColorCode =  2;
	}*/
	m_fColorElapsedTime -= Interval;
	if(m_ColorEffect.Completed() && m_fColorElapsedTime <= 0)
	{
		m_fColorElapsedTime = rand() % 1 + 2;
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
	VECTOR4 Look(Origin.getX(), 0, Origin.getZ(), 1.0f);
	VECTOR4	Position(Look + VECTOR4(0, 15, -20, 1));
	if(Origin.getY() > -5.0f)
	{
		Camera::Instance()->Look(Look);
		Camera::Instance()->Position(Position);
	}
}

void PlayerBall::Render()
{
	D3DXMatrixMultiply(&m_World, &m_Scale, &m_World);
	DxDevice::Instance()->Device()->SetTransform(DXWORLD, &m_World);
	m_pMesh->Render();

	/*size_t Passes = 0;
	D3DXMATRIX	matView			= Camera::Instance()->ViewMatrix();
	D3DXMATRIX	matProjection	= Camera::Instance()->ProjectionMatrix();

	m_pEffect->Matrix_View()->SetMatrix(&matView);
	m_pEffect->Matrix_Projection()->SetMatrix(&matProjection);

	m_pEffect->Matrix_World()->SetMatrix(&m_World);
	m_pEffect->Scale()->SetVector(m_vScale);
	m_pEffect->Color()->SetVector(m_ColorEffect.Color());

	m_pEffect->FX()->Begin(&Passes, NULL);
	m_pEffect->FX()->BeginPass(0);
	m_pMesh->Render();
	m_pEffect->FX()->EndPass();
	m_pEffect->FX()->End();*/
}