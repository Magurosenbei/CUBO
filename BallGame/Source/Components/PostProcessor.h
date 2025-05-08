#pragma once

class PostProcessor
{
	Effect m_Effect;
	EffectParameter m_ParamFrameTexture;
	EffectParameter m_ParamWindowWidth;
	EffectParameter m_ParamWindowHeight;

public:
	PostProcessor();
	virtual ~PostProcessor();

	virtual void Initialize(std::string EffectFile);
	virtual void Update(float Interval);
	virtual void Draw();
};