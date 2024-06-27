#pragma once
#include "../Object.h"
class CCharic abstract :
	public CObject
{
public:
	enum ID : unsigned int
	{
		GOOMBA,
		GOOMBRAT,
		ONGGUM,
		REDONGGUM,
		PLAYER,
		END
	};
protected:
	
	ID m_CTag;
	bool m_bDead;
	Frame m_FDead;
	Frame m_FMove;
	Frame m_FSleep;
	Frame m_FSlide;
public:
	explicit CCharic();
	virtual ~CCharic();

public:
	virtual void Start() = 0;
	virtual void Time_Update(float deltaTime) = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hDC, Coordi Scroll) = 0;
	virtual void Release() = 0;


	Info& Get_Info() { return m_Info; }
	ID	Get_CTag() { return m_CTag; }
	const bool	Get_Dead() const { return m_bDead; }
	bool Check_Move() { return m_FMove.bAct; }
	bool Check_Sleep() { return m_FSleep.bAct; }
	bool Check_Slide() { return m_FSlide.bAct; }

	virtual USHORT Collision(CObject* other) = 0; 

	bool Dead_Checker(float deltaTime = NULL);
	void Set_Dead() { m_FDead.start(); }
protected:
	bool TopCollision(CObject* other);
	bool BottomCollision(CObject* other);
	bool LeftCollision(CObject* other);
	bool RightCollision(CObject* other);

	virtual void Do_Dead(float deltaTime) = 0;
};

