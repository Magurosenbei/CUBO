#pragma  once

class Screen_Splash : public Screen_Master //inherite cmd
{
	int						m_TotalAlpha;
	int						m_TotalAlpha2;
	int						m_TotalAlpha3;
	float					m_TotalAlpha3Number;

public:
	Screen_Splash();

	virtual ~Screen_Splash();

	virtual	void	Update(const float & Interval);
	virtual void	Render();
};