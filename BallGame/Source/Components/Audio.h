#pragma once

class AudioHandle	:	public	Abstract_Single<AudioHandle>, public Abstract_SubProgram
{
	friend class Abstract_Single<AudioHandle>;
protected:
	audiere::AudioDevicePtr		m_pDevice;
	audiere::MIDIDevicePtr		m_pMidiDevice;

	audiere::OutputStreamPtr	m_pBGMStream;

	float						m_fBGMVolume;

	std::string					m_CurrentBGM;

	bool						m_bPaused;

	AudioHandle();
public:
	virtual ~AudioHandle();

	inline	bool	Paused()			{	return	m_bPaused;	}
	inline	void	Pause(bool pause)	
	{	
		m_bPaused = pause;	
		if(m_pBGMStream) 
		{
			if(m_bPaused)
				m_pBGMStream->stop();
			else
				m_pBGMStream->play();
		}
	}

	virtual void	Update(const float & Interval);

	//	Load a BGM
	virtual	void	LoadBGM(const std::string & FilePath);
	//	@param : 0.0 ~ 1.0
	virtual	void	SetBGMVolume(const float & Percentage);

	//	Provides a pointer to a sound effect, specify type for Multiple snd or single snd
	//	Pointer is handled automatically, do not delete.
	audiere::SoundEffectPtr	GetSoundEffect(const std::string & File, audiere::SoundEffectType Type);
};