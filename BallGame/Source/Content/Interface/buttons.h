#pragma  once

class	Button	:	public Sprite
{
public:
	enum	ButtonState {	IDLE, SELECTED, DO	};

	Button(DXTEXTURE pTexture, VECTOR3 pPosition);

	void	ChangeState(ButtonState NewState);
	void	Update(const float & Interval);

protected:
	ButtonState		m_CurrentState;

	size_t			m_Blinker;

	float			m_fElpasedTime;
};