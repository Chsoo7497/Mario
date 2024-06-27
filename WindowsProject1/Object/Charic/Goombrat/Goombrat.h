#pragma once
#include "..//Charic.h"
class CGoombrat final:
	public CCharic

{
private:
public:
	explicit CGoombrat();
	virtual ~CGoombrat();
public:
	// CObject을(를) 통해 상속됨
	virtual void Start() override;
	virtual void Time_Update(float deltaTime) override;
	virtual void Update() override;
	virtual void Render(HDC hDC, Coordi Scroll) override;
	virtual void Release() override;

	virtual USHORT Collision(CObject* other);

private:
	virtual void Do_Dead(float deltaTime);
};

