#pragma once
#include "../Item.h"
class CFire final :
	public CItem
{
public:

protected:
	Frame m_FNomal;
	Frame m_FCollision;
	short m_LR;
	
public:
	explicit CFire();
	virtual ~CFire();

public:
	virtual void Start();
	virtual void Time_Update(float deltaTime);
	virtual void Update();
	virtual void Render(HDC hDC, Coordi Scroll);
	virtual void Release();

	virtual USHORT Collision(CObject* other); 

};

