#pragma once

class Console : public Abstract_Single<Console>
{
	friend class Abstract_Single<Console>;
protected:
	std::deque<std::string>	m_Messages;
	SmartPtr<FontText>		m_pText;	
	Console();

	float					m_fElapsedTime;
public:
	virtual ~Console();

	void Initialize();
	void FeedText(const std::string & Text);

	virtual void Update(const float & Interval);
	virtual void Render();
};