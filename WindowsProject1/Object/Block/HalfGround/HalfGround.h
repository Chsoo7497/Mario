#pragma once
#include "../Block.h"
#include "../../../Manager/ItemManager.h"
class CItem;
class CHalfGround final:
	public CBlock
{
public:

public:
	explicit CHalfGround();
	virtual ~CHalfGround();
private:

public:
	// CObject을(를) 통해 상속됨
	virtual void Start() override;
	virtual void Time_Update(float deltaTime) override;
	virtual void Update() override;
	virtual void Render(HDC hDC, Coordi Scroll) override;
	virtual void Release() override;

	virtual USHORT Collision(CObject* other);

};

