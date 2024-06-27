#pragma once
#include "../Object.h"
class CCharic;
class CBlock:
	public CObject

{
public:
	enum ID : unsigned int
	{
		HALFGROUND,
		GROUND,
		NOMALBLOCK,
		ITEMBLOCK,
		ITEMBOX,
		GOAL,
		PIPE,
		END
	};
protected:
	ID m_BTag;
	bool m_bTop;
	bool m_bBottom;
	bool m_bLeft;
	bool m_bRight;
public:
	explicit CBlock();
	virtual ~CBlock();

public:
	// CObject을(를) 통해 상속됨
	virtual void Start() = 0;
	virtual void Time_Update(float deltaTime) = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hDC, Coordi Scroll) = 0;
	virtual void Release() = 0;

	ID	Get_BTag() { return m_BTag; }

	virtual USHORT Collision(CObject* other);

	void Collision_way();
protected:
	bool TopCollision(CObject* other);
	bool BottomCollision(CObject* other);
	bool LeftCollision(CObject* other);
	bool RightCollision(CObject* other);
};

