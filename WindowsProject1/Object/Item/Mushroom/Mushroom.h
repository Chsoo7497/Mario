#pragma once
#include "../Item.h"
class CMushroom final :
	public CItem
{
public:

protected:
	Frame m_FNomal;
	Frame m_FCollision;
	bool m_hit;
	
public:
	explicit CMushroom();
	virtual ~CMushroom();

public:
	virtual void Start();
	virtual void Time_Update(float deltaTime);
	virtual void Update();
	virtual void Render(HDC hDC, Coordi Scroll);
	virtual void Release();

	virtual USHORT Collision(CObject* other); 

};

