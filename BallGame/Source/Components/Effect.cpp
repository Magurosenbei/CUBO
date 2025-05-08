#include "stdafx.h"
#include "Effect.h"

EffectParameter::EffectParameter()
:	m_pParentEffect(NULL)
,	m_Name("")
,	m_Handle(NULL)
{
}

EffectParameter::EffectParameter(LPD3DXEFFECT Parent, const std::string & Name)
:	m_pParentEffect(Parent), m_Name(Name.c_str()), m_Handle(NULL)
{
	m_Handle = m_pParentEffect->GetParameterByName(m_Handle, Name.c_str());
	ASSERT(m_Handle != NULL, "Effect Parameter not found");
}

EffectParameter::~EffectParameter()
{
	m_pParentEffect = NULL;
	m_Handle = NULL;
}

Effect::Effect()
:	m_pEffect(NULL)
{

}

Effect::~Effect()
{
	m_pEffect->Release();
}

LPD3DXEFFECT Effect::GetEffect() const
{
	return m_pEffect;
}

EffectParameter Effect::GetEffectParameter(const std::string Name)
{
	return EffectParameter(m_pEffect, Name);
}

bool Effect::Prepare(const std::string & File)
{
	HRESULT Result = D3DXCreateEffectFromFileA(DxDevice::Instance()->Device(), 
		File.c_str(), NULL, NULL, NULL, NULL, &m_pEffect, NULL);
	ASSERT(Result == S_OK && m_pEffect != NULL, "Unable to create Effect from file");
	if(Result != S_OK) return false;
	return true;
}