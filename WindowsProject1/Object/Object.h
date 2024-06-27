#pragma once
class CCharic;
class CObject abstract
{
public:
	enum ID : unsigned int
	{
		CHARIC,
		BLOCK,
		ITEM,
		END
	};
protected:
	POINT m_Space;
	Info m_Info;
	ID    m_Tag;
	bool m_bScreenOut;
public:
	explicit CObject();
	virtual ~CObject();

public:
	virtual void Start() = 0;
	virtual void Time_Update(float deltaTime) = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hDC, Coordi Scroll) = 0;
	virtual void Release() = 0;

	POINT Get_Space() { return m_Space; }
	void Set_Space(POINT posi) { m_Space = posi; }
	Info& Get_Info() { return m_Info; }
	ID GetTag() { return m_Tag; }
	bool Get_ScreenOut() { return m_bScreenOut; }
	void Set_ScreenOut() { m_bScreenOut = true; }

	virtual USHORT Collision(CObject* other) = 0;

};

