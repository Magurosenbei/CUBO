#pragma once

class EffectParameter
{
protected:
	LPD3DXEFFECT	m_pParentEffect;
	std::string		m_Name;
	D3DXHANDLE		m_Handle;

public:
	EffectParameter();
	EffectParameter(LPD3DXEFFECT Parent, const std::string & Name);
	virtual ~EffectParameter();
	inline	std::string Name()	const {	return m_Name;	}

	inline	void	SetValue(const float & scalar)			{	m_pParentEffect->SetFloat(m_Handle,	scalar);			}
	inline	void	SetValue(float * scalar, size_t Count)	{	m_pParentEffect->SetFloatArray(m_Handle, scalar, Count);}
	inline	void	SetVector(const VECTOR4 & v)			{	m_pParentEffect->SetVector(m_Handle, &v);				}
	inline	void	SetVector(VECTOR4 *  v,	size_t Count)	{	m_pParentEffect->SetVectorArray(m_Handle, v, Count);	}
	inline	void	SetMatrix(D3DXMATRIX * m)				{	m_pParentEffect->SetMatrix(m_Handle, m);				}
	inline	void	SetMatrix(D3DXMATRIX * m, size_t Count)	{	m_pParentEffect->SetMatrixArray(m_Handle, m, Count);	}
	inline	void	SetTexture(DXTEXTURE texture)			{	m_pParentEffect->SetTexture(m_Handle, (texture));		}
};

class Effect
{
protected:
	LPD3DXEFFECT	m_pEffect;
public:
	Effect();
	virtual ~Effect();	

	LPD3DXEFFECT		GetEffect() const;
	EffectParameter		GetEffectParameter(const std::string Name);
	virtual	bool		Prepare(const std::string & File);
};