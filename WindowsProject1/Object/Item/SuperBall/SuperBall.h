#pragma once
#include "../Item.h"
class CSuperBall final :
	public CItem
{
public:

protected:
	Frame m_FNomal;
	Frame m_FCollision;
	short m_LR;
	float m_fTime;
	
public:
	explicit CSuperBall();
	virtual ~CSuperBall();

public:
	virtual void Start();
	virtual void Time_Update(float deltaTime);
	virtual void Update();
	virtual void Render(HDC hDC, Coordi Scroll);
	virtual void Release();

	virtual USHORT Collision(CObject* other); 

};

