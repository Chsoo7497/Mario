#pragma once
#include "../Object/Charic/Charic.h"
#include "../Object/Item/Item.h"
class CItemManager
{

public:
	static CItemManager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CItemManager;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CItemManager* m_pInstance;
	list<CItem*> ItemLists[CItem::ID::END];
private:
	CItemManager();
	~CItemManager();
public:
	list<CItem*>* Get_ItemList(CItem::ID Item) { return &ItemLists[Item]; }

public:
	void Add_Item(CItem* Item);
	void Add_Item(POINT Posi, CItem::ID itag, unsigned int sub_tag = NULL);

public:
	void _Update(float deltaTime);
	void _Render(HDC hDC, Coordi Scroll);
	void _Release();
};

