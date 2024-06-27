#pragma once
#include "../Block.h"
class CCharic;
class CGoal:
	public CBlock

{
public:

protected:
	Frame m_FGoal;
	float m_fPY;
	Info m_Flag;
	Info m_Pole;
	Info m_Castle;
	Info m_HalfCastle;
public:

	explicit CGoal();
	virtual ~CGoal();
private:

public:
	// CObject을(를) 통해 상속됨
	virtual void Start() override;
	virtual void Time_Update(float deltaTime) override;
	virtual void Update() override;
	virtual void Render(HDC hDC, Coordi Scroll) override;
	virtual void Release() override;


	void Goal_Render(HDC hDC, Coordi Scroll);

	virtual USHORT Collision(CObject* other);
	bool Collisison_Pole(CObject* other);
};

