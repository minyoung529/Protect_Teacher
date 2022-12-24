#pragma once
struct tEvent
{
	EVENT_TYPE  eEven;
	DWORD_PTR	lParam;
	DWORD_PTR	wParam;
};

class Object;

class EventMgr
{
private:
	vector<tEvent> m_vecEvent;
	vector<Object*> m_vecDead;
public:
	SINGLE(EventMgr);
private:
	EventMgr();
	~EventMgr();
public:
	bool FindVecDead(Object* obj)
	{
		return find(m_vecDead.begin(), m_vecDead.end(), obj) != m_vecDead.end();
	}
	void Update();
	void AddEvent(const tEvent& _eve)
	{
		m_vecEvent.push_back(_eve);
	}
	void Delete();
private:
	void Excute(const tEvent& _eve);
};

