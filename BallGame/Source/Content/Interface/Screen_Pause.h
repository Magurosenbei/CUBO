#pragma  once

class Screen_Pause : public Screen_Master //inherite cmd
{
	SmartPtr<FontText>		m_pTextFont;
	
public:
	Screen_Pause();

	virtual ~Screen_Pause();

	virtual	void	Update(const float & Interval);
	virtual void	Render();
};