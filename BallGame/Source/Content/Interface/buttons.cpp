#include "stdafx.h"
#include "buttons.h"

Button::Button(DXTEXTURE pTexture, VECTOR3 pPosition)
:	Sprite(pTexture, pPosition, VECTOR3(1.0f, 1.0f, 1.0f), 0, 0xffffffff), 
	m_CurrentState(IDLE), m_Blinker(1),	m_fElpasedTime(0)
{

}

void Button::ChangeState(ButtonState NewState)
{
	if(NewState == m_CurrentState) return;
	//m_Blinker = 1;
	//m_fElpasedTime = 0.0f;
	m_CurrentState = NewState;
}

void Button::Update(const float & Interval)
{
	//D3DXMATRIX matScale;
	//D3DXMATRIX matTranslation;
	//D3DXMATRIX matRotation;

	//D3DXMatrixTranslation(&matTranslation, pPosition.x, pPosition.y, pPosition.z);
	//D3DXMatrixScaling(&matScale, pScale.x, pScale.y, pScale.z);
	//D3DXMatrixRotationZ(&matRotation, pRotation);

	//D3DXMatrixMultiply(&matTranslation, &matRotation, &matTranslation);
	//D3DXMatrixMultiply(&Transform, &matScale, &matTranslation);
	m_fElpasedTime += Interval;
	switch(m_CurrentState)
	{
	case IDLE:
			this->Color= ARGB(255, 255, 255, 255);
		break;

	case SELECTED:
		{
			
			this->Color= ARGB(255 * m_Blinker, 255, 255, 255);
			if(m_fElpasedTime > 0.6f)
			{
				m_Blinker ^= 0x01;
				m_fElpasedTime = 0;
			}
		}
		break;

	case DO:

		break;
	}
}