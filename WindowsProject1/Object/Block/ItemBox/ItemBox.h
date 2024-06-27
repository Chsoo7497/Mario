#pragma once
#include "../Block.h"
#include "../../../Manager/ItemManager.h"
class CItem;
class CItemBox final:
	public CBlock
{
private:
	Frame m_FNomal;
	Frame m_FCollision;
	bool m_hit;
	CItem* m_Item;
	short m_sMove;
public:
	explicit CItemBox();
	virtual ~CItemBox();
private:

public:
	// CObject을(를) 통해 상속됨
	virtual void Start() override;
	virtual void Time_Update(float deltaTime) override;
	virtual void Update() override;
	virtual void Render(HDC hDC, Coordi Scroll) override;
	virtual void Release() override;

	virtual USHORT Collision(CObject* other);
	void Set_Item(CItem::ID itag);

};

