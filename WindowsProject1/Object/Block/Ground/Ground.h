#pragma once
#include "../Block.h"
class CCharic;
class CGround:
	public CBlock

{
public:

protected:
public:

	explicit CGround();
	virtual ~CGround();
private:

public:
	// CObject을(를) 통해 상속됨
	virtual void Start() override;
	virtual void Time_Update(float deltaTime) override;
	virtual void Update() override;
	virtual void Render(HDC hDC, Coordi Scroll) override;
	virtual void Release() override;

	ID	GetBTag() { return m_BTag; }

	virtual USHORT Collision(CObject* other);
};

