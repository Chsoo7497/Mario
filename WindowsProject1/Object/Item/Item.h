#pragma once
#include "../Object.h"
class CItem abstract :
	public CObject
{
public:
	enum ID : unsigned int
	{
		COIN,
		MUSHROOM,
		FIREFLOWER,
		SUPERFLOWER,
		FIRE,
		SUPERBALL,
		END
	};
protected:
	
	ID m_ITag;
	bool m_bDead;
public:
	explicit CItem();
	virtual ~CItem();

public:
	virtual void Start() = 0;
	virtual void Time_Update(float deltaTime) = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hDC, Coordi Scroll) = 0;
	virtual void Release() = 0;


	Info& Get_Info() { return m_Info; }
	ID	Get_ITag() { return m_ITag; }
	const bool	Get_Dead() const { return m_bDead; }
	void Set_Dead() { m_bDead = true; }

	virtual USHORT Collision(CObject* other); 

protected:
	bool TopCollision(CObject* other);
	bool BottomCollision(CObject* other);
	bool LeftCollision(CObject* other);
	bool RightCollision(CObject* other);
};

