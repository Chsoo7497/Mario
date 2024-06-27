#pragma once
#include "../Item.h"
class CCoin final :
	public CItem
{
public:

protected:
	Frame m_FNomal;
	Frame m_FCollision;
	bool m_hit;
	
public:
	explicit CCoin();
	virtual ~CCoin();

public:
	virtual void Start();
	virtual void Time_Update(float deltaTime);
	virtual void Update();
	virtual void Render(HDC hDC, Coordi Scroll);
	virtual void Release();

	virtual USHORT Collision(CObject* other); 

	void hit() {
		m_FNomal.end();
		m_FCollision.start();
		CSoundManager::Get_Instance()->StopSound(CSoundManager::CHANNELID::EFFECT);
		CSoundManager::Get_Instance()->PlaySound(L"Coin.wav", CSoundManager::CHANNELID::EFFECT);
	}
};

