#include "../Header/framework.h"
#include "ItemManager.h"
#include "../Object/Item/Coin/Coin.h"
#include "../Object/Item/Mushroom/Mushroom.h"
#include "../Object/Item/FireFlower/FireFlower.h"
#include "../Object/Item/Fire/Fire.h"
#include "../Object/Item/SuperFlower/SuperFlower.h"
#include "../Object/Item/SuperBall/SuperBall.h"
CItemManager* CItemManager::m_pInstance = nullptr;


CItemManager::CItemManager()
	: ItemLists()
{
}

CItemManager::~CItemManager()
{
	_Release();
}


void CItemManager::Add_Item(CItem* Item)
{
	assert(!(Item == nullptr));
	Item->Start();
	Item->Get_Info().Update_Domain();
	if (Item->Get_Space().x >= 0 && Item->Get_Space().y >= 0)
		for (int i = 0; i < CItem::ID::END; i++)
		{
			for (list<CItem*>::iterator iter = ItemLists[i].begin(); iter != ItemLists[i].end(); iter++)
			{
				if ((*iter)->Get_Space().x == Item->Get_Space().x &&
					(*iter)->Get_Space().y == Item->Get_Space().y) {
					ptr_delete(Item);
					return;
				}
			}
		}
	switch (Item->Get_ITag())
	{
	case CItem::ID::COIN:
		ItemLists[CItem::ID::COIN].emplace_back(Item);
		break;
	case CItem::ID::MUSHROOM:
		ItemLists[CItem::ID::MUSHROOM].emplace_back(Item);
		break;
	case CItem::ID::FIREFLOWER:
		ItemLists[CItem::ID::FIREFLOWER].emplace_back(Item);
		break;
	case CItem::ID::FIRE:
		ItemLists[CItem::ID::FIRE].emplace_back(Item);
		break;
	case CItem::ID::SUPERFLOWER:
		ItemLists[CItem::ID::SUPERFLOWER].emplace_back(Item);
		break;
	case CItem::ID::SUPERBALL:
		ItemLists[CItem::ID::SUPERBALL].emplace_back(Item);
		break;
	case CItem::ID::END:
	default:
		ptr_delete(Item);
		break;
	}
}

void CItemManager::Add_Item(POINT Posi, CItem::ID itag, unsigned int sub_tag)
{
	CItem* Item = nullptr;
	switch (itag)
	{
	case CItem::ID::COIN:
		Item = new CCoin;
		break;
	case CItem::ID::MUSHROOM:
		Item = new CMushroom;
		break;
	case CItem::ID::FIREFLOWER:
		Item = new CFireFlower;
		break;
	case CItem::ID::FIRE:
		Item = new CFire;
		break;
	case CItem::ID::SUPERFLOWER:
		Item = new CSuperFlower;
		break;
	case CItem::ID::SUPERBALL:
		Item = new CSuperBall;
		break;
	case CItem::ID::END:
	default:
		ptr_delete(Item);
		break;
	}
	if (Item == nullptr)
		return;
	Item->Set_Space(Posi);
	Item->Get_Info().Posi = { static_cast<float>(Posi.x) , static_cast<float>(Posi.y) };
	Add_Item(Item);
}


void CItemManager::_Update(float deltaTime)
{
	// 업데이트
	for (int i = 0; i < CItem::ID::END; i++)
	{
		list<CItem*>::iterator iter = ItemLists[i].begin();
		while (iter != ItemLists[i].end())
		{
			// 죽은 오브젝트 삭제
			if ((*iter)->Get_ScreenOut())
			{
				ptr_delete(*iter);
				iter = ItemLists[i].erase(iter);
			}
			else
			{
				(*iter)->Time_Update(deltaTime);
				(*iter)->Update();
				iter++;
			}
		}
	}

}

void CItemManager::_Render(HDC hDC, Coordi Scroll)
{
	// 렌더

	for (int i = 0; i < CItem::ID::END; i++)
	{
		for (CItem* Item : ItemLists[i])
		{
			Item->Render(hDC, Scroll);

			//Output_Rectangle(hDC, Item->Get_Info().CollidDomain, Scroll.Point(), RGB(0, 0, 0));
		}
	}
	for (int i = 1; i < CItem::ID::END; i++)
	{
		for (CItem* Item : ItemLists[i])
		{
			if ((Item->Get_Dead() || (Item->Get_Info().Posi - Scroll).Length() > 2000.f) && (Item->Get_Space().x < 0 || Item->Get_Space().y < 0))
				Item->Set_ScreenOut();
		}
	}
}

void CItemManager::_Release()
{
	// 메모리 해제
	for (int i = 0; i < CItem::ID::END; i++)
	{
		for (list<CItem*>::iterator iter = ItemLists[i].begin(); iter != ItemLists[i].end(); iter++)
		{
			ptr_delete(*iter);
		}

		ItemLists[i].clear();
	}
}
