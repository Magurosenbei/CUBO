#include "stdafx.h"
#include "ObstacleDropper.h"


BoxDropper::BoxDropper(const size_t & Amount, const btVector3 & Min, const btVector3 & Max)
{
	m_bActivated = false;
	m_fDropTime	 = 0.0f;
	m_pBoxTexture = TextureHolder::Instance()->AddTexture("Data/Obstacle.png");
	for(size_t i = 0; i < Amount; i++)
	{
		float X = System_Utility::RandomFloat(Min.getX(), Max.getX());
		float Z = System_Utility::RandomDouble(Min.getZ(), Max.getZ());
		Box * _Box = new Box();
		_Box->Initialize(btVector3(X, 30, Z), 150.0f, btVector3(1, 1, 1), false, false, true);
		m_Boxes.push_back(_Box);
	}
	m_pEffect = SmartPtr<DefaultObjectEffect>(new DefaultObjectEffect);
	m_pEffect->Texture()->SetTexture(m_pBoxTexture);
}

BoxDropper::~BoxDropper()
{
	m_pBoxTexture = NULL;
	m_pEffect.reset(NULL);
	m_pEffect.release();
}

void BoxDropper::Update(const float & Interval)
{
	if(!m_bActivated) return;

	m_fDropTime += Interval;
	if(m_fDropTime > 3.0f)
	{
		size_t amount = rand() % 4 + 1;
		for(size_t i = 0; i < amount; i++)
		{
			if(m_Boxes.size() < 1) break;
			Box * _Box = m_Boxes.front();
			_Box->AddToSystem();
			m_ActiveBoxes.push_back(_Box);
			m_Boxes.pop_front();
		}
	}

	for(size_t i = 0; i < m_ActiveBoxes.size(); i++)
		m_ActiveBoxes[i]->Update(Interval);
}

void BoxDropper::Render()
{
	D3DXMATRIX	matView			= Camera::Instance()->ViewMatrix();
	D3DXMATRIX	matProjection	= Camera::Instance()->ProjectionMatrix();

	size_t Passes = 0;

	m_pEffect->Matrix_View()->SetMatrix(&matView);
	m_pEffect->Matrix_Projection()->SetMatrix(&matProjection);

	m_pEffect->FX()->Begin(&Passes, NULL);
	{
		for(size_t i = 0; i < m_ActiveBoxes.size(); i++)
		{
			if(!m_ActiveBoxes[i]->IsVisible()) continue;
			m_pEffect->Scale()->SetVector(m_ActiveBoxes[i]->Scale());
			m_pEffect->Color()->SetVector(m_ActiveBoxes[i]->COLOR());
			m_pEffect->Matrix_World()->SetMatrix(m_ActiveBoxes[i]->Matrix_World());

			m_pEffect->FX()->BeginPass(0);
			m_ActiveBoxes[i]->RenderModel();
			m_pEffect->FX()->EndPass();
		}
	}
	m_pEffect->FX()->End();
}
