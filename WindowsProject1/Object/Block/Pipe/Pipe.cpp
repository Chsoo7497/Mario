#include "../../../Header/framework.h"
#include "Pipe.h"
#include "../../../Manager/ImageManager.h"
#include "../../../Manager/BlockManager.h"
#include "../../../Manager/CharicManager.h"
#include "../../../Object/Item/Coin/Coin.h"
#include "../../../Object/Item/Mushroom/Mushroom.h"
#include "../../../Object/Item/FireFlower/FireFlower.h"
#include "../../../Object/Item/SuperFlower/SuperFlower.h"
CPipe::CPipe()
{
	m_BTag = CBlock::ID::ITEMBLOCK;
	m_Info.RendScale = Coordi(50.f, 50.f);
	m_Info.CollidScale = Coordi(50.f, 50.f);
}

CPipe::~CPipe()
{
	Release();
}

void CPipe::Start()
{
	m_Info.Posi = Coordi{ static_cast<float>((m_Space.x * 50) + 25), static_cast<float>((m_Space.y * 50) + 25) };
	m_bScreenOut = false;

	m_Info.Update_Domain();
}

void CPipe::Time_Update(float deltaTime)
{

	//m_FNomal.Check_Time(deltaTime);
	//m_FCollision.Check_Time(deltaTime);
	//if (m_FCollision.bAct && m_FCollision.bTrigger) {
	//	switch (m_FCollision.iCount) {
	//	case 0:
	//		m_Info.Update_Domain();
	//		break;
	//	case 1:
	//	case 2:
	//	case 3:
	//	case 4:
	//	case 5:
	//		m_Info.Posi -= {0.f, 2.f};
	//		m_Info.Update_Domain();
	//		break;
	//	case 6:
	//	case 7:
	//	case 8:
	//	case 9:
	//	case 10:
	//		m_Info.Posi += {0.f, 2.f};
	//		m_Info.Update_Domain();
	//		break;
	//	}
	//	if (m_Item) {
	//		m_Item->Get_Info().Posi.fy -= 5.f;
	//		m_Item->Get_Info().Update_Domain();
	//	}
	//}
}

void CPipe::Update()
{
	CObject* temp = nullptr;

	temp = CBlockManager::Get_Instance()->Get_Object({ m_Space.x,m_Space.y - 1 });
	if (temp == nullptr || temp->GetTag() != CObject::ID::BLOCK)	m_bTop = true;

	temp = CBlockManager::Get_Instance()->Get_Object({ m_Space.x,m_Space.y + 1 });
	if (temp == nullptr || temp->GetTag() != CObject::ID::BLOCK) m_bBottom = true;

	temp = CBlockManager::Get_Instance()->Get_Object({ m_Space.x - 1,m_Space.y });
	if (temp == nullptr || temp->GetTag() != CObject::ID::BLOCK) m_bLeft = true;

	temp = CBlockManager::Get_Instance()->Get_Object({ m_Space.x + 1,m_Space.y });
	if (temp == nullptr || temp->GetTag() != CObject::ID::BLOCK) m_bRight = true;

	//if (m_hit) {
	//	m_FNomal.end();
	//	m_FCollision.start();
	//	m_hit = false;
	//}
	//if (m_FCollision.bAct && m_FCollision.iCount == m_FCollision.iFrame) {
	//	m_FCollision.end();
	//	if (m_Item) {
 // 			CItemManager::Get_Instance()->Add_Item(m_Item);
	//		m_Item->Get_Info().Posi = Coordi{ static_cast<float>((m_Space.x * 50) + 25), static_cast<float>((m_Space.y * 50) - 25) };
	//		if (m_Item->Get_ITag() == CItem::ID::COIN)
	//			static_cast<CCoin*>(m_Item)->hit();
	//		m_Item = nullptr;
	//	}
	//}
}

void CPipe::Render(HDC hDC, Coordi Scroll)
{
	//1+17*i,23+17*j
	HDC hBlock = nullptr;

	switch (m_ID)
	{
	case CPipe::F_LU:
		hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Tile, 1 + 17 * 12, 23 + 17 * 0, 16, 16);
		break;
	case CPipe::F_LD:
		hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Tile, 1 + 17 * 12, 23 + 17 * 1, 16, 16);
		break;
	case CPipe::F_RU:
		hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Tile, 1 + 17 * 14, 23 + 17 * 0, 16, 16);
		break;
	case CPipe::F_RD:
		hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Tile, 1 + 17 * 14, 23 + 17 * 1, 16, 16);
		break;
	case CPipe::B_U:
		hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Tile, 1 + 17 * 13, 23 + 17 * 0, 16, 16);
		break;
	case CPipe::B_D:
		hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Tile, 1 + 17 * 13, 23 + 17 * 1, 16, 16);
		break;
	case CPipe::F_UR:
		hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Tile, 1 + 17 * 15, 23 + 17 * 0, 16, 16);
		break;
	case CPipe::F_UL:
		hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Tile, 1 + 17 * 16, 23 + 17 * 0, 16, 16);
		break;
	case CPipe::F_DR:
		hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Tile, 1 + 17 * 15, 23 + 17 * 2, 16, 16);
		break;
	case CPipe::F_DL:
		hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Tile, 1 + 17 * 16, 23 + 17 * 2, 16, 16);
		break;
	case CPipe::B_L:
		hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Tile, 1 + 17 * 15, 23 + 17 * 1, 16, 16);
		break;
	case CPipe::B_R:
		hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Tile, 1 + 17 * 16, 23 + 17 * 1, 16, 16);
		break;
	case CPipe::END:
		break;
	default:
		break;
	}
	GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
		hBlock, { 16,16 }, RGB(147, 187, 236));
}

void CPipe::Release()
{
	//ptr_delete(m_Item);
}

USHORT CPipe::Collision(CObject* other)
{
	USHORT Collision = 0;
	if (m_bTop)
		if (TopCollision(other)) {
			other->Get_Info().Posi.fy = m_Info.Posi.fy - ((m_Info.RendScale.fy + other->Get_Info().RendScale.fy) / 2.f);
			Collision |= 0x1000;
		}
	if (m_bBottom)
		if (BottomCollision(other)) {
			other->Get_Info().Posi.fy = m_Info.Posi.fy + ((m_Info.RendScale.fy + other->Get_Info().RendScale.fy) / 2.f);
			Collision |= 0x0100;
		}
	if (m_bLeft)
		if (LeftCollision(other)) {
			other->Get_Info().Posi.fx = m_Info.Posi.fx - ((m_Info.RendScale.fx + other->Get_Info().RendScale.fx) / 2.f);
			Collision |= 0x0010;
		}
	if (m_bRight)
		if (RightCollision(other)) {
			other->Get_Info().Posi.fx = m_Info.Posi.fx + ((m_Info.RendScale.fx + other->Get_Info().RendScale.fx) / 2.f);
			Collision |= 0x0001;
		}
	//if (m_FNomal.bAct && other->GetTag() == CObject::ID::CHARIC)
	//	switch (static_cast<CCharic*>(other)->Get_CTag())
	//	{
	//	case CCharic::ID::PLAYER:
	//		if (Collision & 0x0100)
	//			m_hit = true;
	//		break;
	//	default:
	//		break;
	//	}
	return Collision;
}

void CPipe::Set_Item(CItem::ID itag)
{
	//m_Item = nullptr;
	//switch (itag)
	//{
	//case CItem::ID::COIN:
	//	m_Item = new CCoin;
	//	break;
	//case CItem::ID::MUSHROOM:
	//	m_Item = new CMushroom;
	//	break;
	//case CItem::ID::FIREFLOWER:
	//	m_Item = new CFireFlower;
	//	break;
	//case CItem::ID::SUPERFLOWER:
	//	m_Item = new CSuperFlower;
	//	break;
	//case CItem::ID::END:
	//default:
	//	ptr_delete(m_Item);
	//	break;
	//}
	//if (m_Item) {
	//	m_Item->Set_Space({-1,-1});
	//	m_Item->Get_Info().Posi = Coordi{ static_cast<float>((m_Space.x * 50) + 25), static_cast<float>((m_Space.y * 50) + 25) };
	//}
}

