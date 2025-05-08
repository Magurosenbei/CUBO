#include "stdafx.h"
#include "Camera.h"

SmartPtr<Camera> Abstract_Single<Camera>::m_pInstance;

Camera::Camera()
:	m_pDeviceRef(NULL), m_pInputRef(NULL), m_fSpeed(60.0f)
{
	m_bDelete = false;
}

Camera::~Camera()
{
	m_pInputRef = NULL;
	m_pDeviceRef = NULL;
}

void Camera::Initialize()
{
	m_pDeviceRef = DxDevice::Instance()->Device();
	m_pInputRef = InputHandle::Instance();
	
	RECT WndRect = Window::Instance()->GetWindowRect();
	float AspectRatio = static_cast<float>(WndRect.right) / static_cast<float>(WndRect.bottom);
	//AspectRatio = (AspectRatio > 1.5)?  1.7777778f :  1.3333333f;
	D3DXMatrixPerspectiveFovRH(&matProjection, 0.25f * PI, AspectRatio, 1.0f, 1000.0f);
	m_pDeviceRef->SetTransform(D3DTRANSFORMSTATETYPE::D3DTS_PROJECTION, &matProjection);
	
	m_vEye = VECTOR4(0, 0, -100, 1);	
	m_vLook = VECTOR4(0, 0, 0, 1);	

	m_vFront = m_vLook - m_vEye;
	D3DXVec3Cross((VECTOR3 *)&m_vRight, (VECTOR3 *)&m_vFront, (VECTOR3 *)&VECTOR3_Y);
	D3DXVec3Cross((VECTOR3 *)&m_vUp,	(VECTOR3 *)&m_vFront, (VECTOR3 *)&m_vRight);

	D3DXVec4Normalize(&m_vFront,	&m_vFront);
	D3DXVec4Normalize(&m_vRight,	&m_vRight);
	D3DXVec4Normalize(&m_vUp,		&m_vUp);
	m_vUp = -m_vUp;
}

void Camera::Update(const float & Interval)
{
	if(m_pInputRef->KeyDown(VK_SPACE))
	{
		float Speed = Interval * m_fSpeed;

  		VECTOR4	Move(0, 0, 0, 1);
		if(m_pInputRef->KeyDown('W')) 
			Move = m_vFront * Speed;
		if(m_pInputRef->KeyDown('S'))
			Move = m_vFront * -Speed;

		if(m_pInputRef->KeyDown('D'))
			Move = m_vRight * Speed;
		if(m_pInputRef->KeyDown('A'))
			Move = m_vRight * -Speed;
		
		m_vEye	+= Move;
		m_vLook += Move;
		POINT MMove = m_pInputRef->MouseDiffernce();
		m_vLook += m_vRight * MMove.x * Interval * 25;
		m_vLook += -m_vUp	* MMove.y * Interval * 20;
	}
	m_vFront = m_vLook - m_vEye;
	D3DXVec3Cross((VECTOR3 *)&m_vRight, (VECTOR3 *)&m_vFront, (VECTOR3 *)&VECTOR3_Y);
	D3DXVec3Cross((VECTOR3 *)&m_vUp,	(VECTOR3 *)&m_vFront, (VECTOR3 *)&m_vRight);

	D3DXVec4Normalize(&m_vFront,	&m_vFront);
	D3DXVec4Normalize(&m_vRight,	&m_vRight);
	D3DXVec4Normalize(&m_vUp,		&m_vUp);
	m_vUp = -m_vUp;

	D3DXMatrixLookAtRH(&matView, (VECTOR3 *)&m_vEye, (VECTOR3 *)&m_vLook, (VECTOR3 *)&m_vUp);
	
	if(m_pInputRef->KeyDown(VK_LCONTROL))
	{
		if(m_pInputRef->KeyPressed('1'))
			DxDevice::Instance()->Device()->SetRenderState(DXRENDERSTATE::D3DRS_FILLMODE, D3DFILL_SOLID);
		if(m_pInputRef->KeyPressed('2'))
			DxDevice::Instance()->Device()->SetRenderState(DXRENDERSTATE::D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	m_pDeviceRef->SetTransform(D3DTRANSFORMSTATETYPE::D3DTS_VIEW, &matView);
	m_pDeviceRef->SetTransform(D3DTRANSFORMSTATETYPE::D3DTS_PROJECTION, &matProjection);
}

void Camera::Render(const size_t & RenderTargetID, const size_t & Width, const size_t & Height)
{
	m_pDeviceRef->SetTransform(D3DTRANSFORMSTATETYPE::D3DTS_VIEW, &matView);
	m_pDeviceRef->SetTransform(D3DTRANSFORMSTATETYPE::D3DTS_PROJECTION, &matProjection);
}