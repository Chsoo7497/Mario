#pragma once
#include "../Charic.h"
#include "../../Manager/KeyManager.h"
class CPlayer final:
	public CCharic

{
private:
	bool m_bGoal;
	short m_LR;
	short m_sPower;
	short m_sPrevPower;
	float m_time;
	Frame m_FJump;
	Frame m_FDown;
	Frame m_FStamp;
	Frame m_FPower;
	Frame m_FFire;
	Frame m_FGoal;
	CKeyManager keymanager;
public:
	explicit CPlayer();
	virtual ~CPlayer();
public:
	// CObject을(를) 통해 상속됨
	virtual void Start() override;
	virtual void Time_Update(float deltaTime) override;
	virtual void Update() override;
	virtual void Render(HDC hDC, Coordi Scroll) override;
	virtual void Release() override;


	virtual USHORT Collision(CObject* other);

	short Power() { return m_sPower; }
	bool Power_Check();
	bool Check_Move() { return m_FMove.bAct; }
	bool Check_Jump() { return m_FJump.bAct; }
	bool Check_Down() { return m_FDown.bAct; }
	bool Check_Stamp() { return m_FStamp.bAct; }
	bool Check_Goal() { return m_FGoal.bAct; }
	bool Get_Goal() { return m_bGoal; }

	void Goal_In() { m_FGoal.start(); }
	void Game_Over() { 
		m_FDead.start();
	}
private:
	virtual void Do_Dead(float deltaTime);
	void Power_Up(short Power);
	void Power_Down();

	void _Move(float deltaTime);
	void Find_Sheet_Power(HDC hDC, Coordi Scroll, int number, short LR, short Power);

	void _Goal(float deltaTime);
};

