#include "../Header/framework.h"
#include "MapManager.h"
#include "CharicManager.h"
#include "BlockManager.h"
#include "ItemManager.h"
CMapManager* CMapManager::m_pInstance = nullptr;

CMapManager::CMapManager()
	:m_SavePoint({ 0,SCREENSIZE_Y * 2 })
	, m_Scroll()
	, m_map()
{
}

CMapManager::~CMapManager()
{
	_Release();
}

void CMapManager::_Ready()
{
	m_SavePoint = { 0,SCREENSIZE_Y * 2 };
	Set_Scroll(m_SavePoint);
	m_map = new CMap;
}

void CMapManager::_Update(float deltaTime)
{
	POINT xy = (m_Scroll / 50).Point();
	for (long i = xy.x - 20; i < xy.x + 20; i++)
	{
		for (long j = xy.y - 20; j < xy.y + 10; j++)
		{
			Tags temp = m_map->Get_Tags({ i,j });
			switch (temp.Object_Tag)
			{
			case CObject::ID::CHARIC:
				CCharicManager::Get_Instance()->Add_Charic({ i,j }, static_cast<CCharic::ID>(temp.Name_Tag), temp.Sub_Tag);
				break;
			case CObject::ID::BLOCK:
				CBlockManager::Get_Instance()->Add_Block({ i,j }, static_cast<CBlock::ID>(temp.Name_Tag), temp.Sub_Tag);
				break;
			case CObject::ID::ITEM:
				CItemManager::Get_Instance()->Add_Item({ i,j }, static_cast<CItem::ID>(temp.Name_Tag), temp.Sub_Tag);
				break;
			case CObject::ID::END:
			default:
				break;
			}
		}
	}

	CPlayer* player = CCharicManager::Get_Instance()->Get_Player();
	if (player == nullptr) {
		Set_Scroll(m_SavePoint);
		return;
	}
	else if (!player->Dead_Checker())
		Set_Scroll(player->Get_Info().Posi);
}

void CMapManager::_Render(HDC hDC)
{
	//Set_Scroll(m_Player.GetPosi());
	m_map->BackGround_Render(hDC, m_Scroll);
}

void CMapManager::_Release()
{
	m_map->Release();
	ptr_delete(m_map);
}

void CMapManager::Set_Scroll(Coordi Scroll)
{
	m_Scroll = Scroll;
	if (m_Scroll.fx < SCREENCENTER_X)
		m_Scroll.fx = SCREENCENTER_X;
	if (m_Scroll.fx > (SCREENSIZE_X * 6) + SCREENCENTER_X)
		m_Scroll.fx = (SCREENSIZE_X * 6) + SCREENCENTER_X;
	if (m_Scroll.fy < SCREENCENTER_Y)
		m_Scroll.fy = SCREENCENTER_Y;
	if (m_Scroll.fy > (SCREENSIZE_Y * 1) + SCREENCENTER_Y)
		m_Scroll.fy = (SCREENSIZE_Y * 1) + SCREENCENTER_Y;
}

					  
