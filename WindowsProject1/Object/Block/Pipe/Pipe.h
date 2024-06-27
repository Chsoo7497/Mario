#pragma once
#include "../Block.h"
#include "../../../Manager/ItemManager.h"
class CItem;
class CPipe final:
	public CBlock
{
public:
	enum ID : unsigned int
	{
		F_LU,F_LD,
		F_RU,F_RD,
		B_U,B_D,
		F_UR,F_UL,
		F_DR,F_DL,
		B_L,B_R,
		END
	};
private:
	CPipe::ID m_ID;
public:
	explicit CPipe();
	virtual ~CPipe();
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

