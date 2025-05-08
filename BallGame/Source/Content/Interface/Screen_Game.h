#pragma  once

class Screen_Game : public Screen_Master
{
	int						m_GameCUBOAlpha;
	int						m_GameTotalAlpha2;
	int						m_GameAnyKeyAlpha3;
	int						m_GameBlackAlpha;
	int						m_GameBlackAlpha2;
	int						m_GameCompleteAlpha;
	int						m_GameWin1Alpha;
	int						m_GameWin2Alpha;
	float					m_fcomplateElasped;

	SmartPtr<FontText>		m_pTextFont;
	audiere::SoundEffectPtr	m_pSoundEffect;

	VECTOR4					m_StoredCameraPosition;
	VECTOR4					m_TargetCameraPosition;

	bool					m_bGameStarted;
	bool					m_bcomplete;
public:
	Screen_Game();

	virtual ~Screen_Game();

	void			ResetAll();
	void			ResetVisual();

	inline	void	SetCameraTargetPosition(const VECTOR4 & Position)	{	m_TargetCameraPosition	=	Position;	}

	inline	void	StoreCameraPosition(const VECTOR4	& Position)	{	m_StoredCameraPosition = Position;	}

	virtual	void	Update(const float & Interval);
	virtual void	Render();
};