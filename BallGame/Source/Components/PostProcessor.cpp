#include "stdafx.h"
#include "PostProcessor.h"

PostProcessor::PostProcessor()
{
}

PostProcessor::~PostProcessor()
{
}

void PostProcessor::Initialize(std::string EffectFile)
{
	m_Effect.Prepare(EffectFile);

	m_ParamFrameTexture = m_Effect.GetEffectParameter("FrameTexture");
	m_ParamWindowWidth = m_Effect.GetEffectParameter("WindowWidth");
	m_ParamWindowHeight = m_Effect.GetEffectParameter("WindowHeight");
}

void PostProcessor::Update(float Interval)
{
	m_ParamFrameTexture.SetTexture(DxDevice::Instance()->GetRenderTarget(0)->TEXTURE());
	m_ParamWindowWidth.SetValue((float)DxDevice::Instance()->ViewPort().Width);
	m_ParamWindowHeight.SetValue((float)DxDevice::Instance()->ViewPort().Height);
}

void PostProcessor::Draw()
{
	size_t noOfPasses = 0;
	m_Effect.GetEffect()->Begin(&noOfPasses, 0);	

	for (size_t i = 0; i < noOfPasses; ++i)
	{
		m_Effect.GetEffect()->BeginPass(i);
		
		m_Effect.GetEffect()->EndPass();
	}
	m_Effect.GetEffect()->End();
}