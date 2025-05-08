#pragma once

class DefaultObjectEffect
{
protected:
	SmartPtr<Effect>	m_pEffect;

	EffectParameter		param_matWorld;
	EffectParameter		param_matView;
	EffectParameter		param_matProjection;

	EffectParameter		param_Texture;
	EffectParameter		param_Color;

	EffectParameter		param_Scale;
public:
	DefaultObjectEffect();
	virtual	~DefaultObjectEffect();

	inline	LPD3DXEFFECT		FX()				{	return	m_pEffect->GetEffect();	}		
	inline	EffectParameter	*	Matrix_World()		{	return	&param_matWorld;		}
	inline	EffectParameter	*	Matrix_View()		{	return	&param_matView;			}
	inline	EffectParameter	*	Matrix_Projection()	{	return	&param_matProjection;	}

	inline	EffectParameter	*	Texture()			{	return	&param_Texture;			}
	inline	EffectParameter	*	Color()				{	return	&param_Color;			}
	inline	EffectParameter	*	Scale()				{	return	&param_Scale;			}
};