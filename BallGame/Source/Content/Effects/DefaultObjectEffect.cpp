#include "stdafx.h"
#include "DefaultObjectEffect.h"

DefaultObjectEffect::DefaultObjectEffect()
{
	m_pEffect = SmartPtr<Effect>(new Effect);
	m_pEffect->Prepare("Data/DefaultShader.fx");
	
	param_matWorld = m_pEffect->GetEffectParameter("matWorld");
	param_matView = m_pEffect->GetEffectParameter("matView");
	param_matProjection = m_pEffect->GetEffectParameter("matProjection");
	
	param_Color = m_pEffect->GetEffectParameter("vColor");

	param_Scale	=	m_pEffect->GetEffectParameter("vScale");

	param_Texture = m_pEffect->GetEffectParameter("InputTexture");
}

DefaultObjectEffect::~DefaultObjectEffect()
{
	m_pEffect.reset(NULL);
	m_pEffect.release();
}