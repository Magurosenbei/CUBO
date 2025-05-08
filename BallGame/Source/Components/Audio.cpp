#include "stdafx.h"
#include "Audio.h"

SmartPtr<AudioHandle> Abstract_Single<AudioHandle>::m_pInstance;

AudioHandle::AudioHandle()
:	m_pDevice(NULL), m_pMidiDevice(NULL),
	m_pBGMStream(NULL), m_bPaused(false),
	m_fBGMVolume(0.6f)
{
	m_bDelete = false;
	m_pDevice = audiere::OpenDevice();
	WriteCommandLine("Audio >>> %s Device Opened", m_pDevice->getName());
	m_pMidiDevice = audiere::OpenMIDIDevice(m_pDevice->getName());
	m_CurrentBGM = "NULL";
}

AudioHandle::~AudioHandle()
{
	m_pDevice = NULL;
	m_pMidiDevice = NULL;
	m_pBGMStream = NULL;
}

void AudioHandle::Update(const float &Interval)
{
	m_pDevice->update();
}

void AudioHandle::LoadBGM(const std::string & FilePath)
{
	if(m_CurrentBGM == FilePath || m_bPaused)	return;

	m_pBGMStream = audiere::OpenSound(m_pDevice, FilePath.c_str(), true);
	ASSERT(m_pBGMStream != NULL, "BGM Stream is empty")

	m_pBGMStream->setPosition(m_pBGMStream->getPosition() + 10);
	m_pBGMStream->setVolume(m_fBGMVolume);
	m_pBGMStream->setRepeat(true);
	m_pBGMStream->play();

	m_CurrentBGM = FilePath;
}

void AudioHandle::SetBGMVolume(const float & Percentage)
{
	ASSERT(m_pBGMStream != NULL, "BGM Stream is empty")
	m_fBGMVolume = Percentage;
	m_pBGMStream->setVolume(m_fBGMVolume);
}

audiere::SoundEffectPtr AudioHandle::GetSoundEffect(const std::string & File, audiere::SoundEffectType Type)
{
	audiere::SoundEffectPtr Sound = audiere::OpenSoundEffect(m_pDevice, File.c_str(), Type);
	Sound->setVolume(1.0f);
	return Sound;
}