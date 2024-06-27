#include "../../../Header/framework.h"
#include "ItemBox.h"
#include "../../../Manager/ImageManager.h"
#include "../../../Manager/BlockManager.h"
#include "../../../Manager/CharicManager.h"
#include "../../../Manager/SoundManager.h"
#include "../../../Object/Item/Coin/Coin.h"
#include "../../../Object/Item/Mushroom/Mushroom.h"
#include "../../../Object/Item/FireFlower/FireFlower.h"
#include "../../../Object/Item/SuperFlower/SuperFlower.h"
CItemBox::CItemBox()
	:m_FNomal({ 0.f, 0.2f, 0, 3, false, false })
	,m_FCollision({ 0.f, 0.01f, 0, 10, false, false })
	, m_hit(false)
	, m_Item()
	, m_sMove(1)
{
	m_BTag = CBlock::ID::ITEMBOX;
	m_Info.RendScale = Coordi(50.f, 50.f);
	m_Info.CollidScale = Coordi(50.f, 50.f);
	m_FNomal.start();
}

CItemBox::~CItemBox()
{
	Release();
}

void CItemBox::Start()
{
	m_Info.Posi = Coordi{ static_cast<float>((m_Space.x * 50) + 25), static_cast<float>((m_Space.y * 50) + 25) };
	m_bScreenOut = false;

	m_Info.Update_Domain();
}

void CItemBox::Time_Update(float deltaTime)
{

	m_FNomal.Check_Time(deltaTime);
	m_FCollision.Check_Time(deltaTime);
	if (m_FCollision.bAct && m_FCollision.bTrigger) {
		switch (m_FCollision.iCount) {
		case 0:
			m_Info.Update_Domain();
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			m_Info.Posi -= {0.f, 2.f * m_sMove};
			m_Info.Update_Domain();
			break;
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			m_Info.Posi += {0.f, 2.f * m_sMove};
			m_Info.Update_Domain();
			break;
		}
		if (m_Item) {
			m_Item->Get_Info().Posi.fy -= 5.f * m_sMove;
			m_Item->Get_Info().Update_Domain();
		}
	}
}

void CItemBox::Update()
{

	if (m_hit) {
		m_FNomal.end();
		m_FCollision.start();
		CSoundManager::Get_Instance()->StopSound(CSoundManager::CHANNELID::EFFECT);
		CSoundManager::Get_Instance()->PlaySound(L"Item sprouting.wav", CSoundManager::CHANNELID::EFFECT);
		m_hit = false;
	}
	if (m_FCollision.bAct && m_FCollision.iCount == m_FCollision.iFrame) {
		m_FCollision.end();
		if (m_Item) {
  			CItemManager::Get_Instance()->Add_Item(m_Item);
			if (m_sMove > 0)
				m_Item->Get_Info().Posi = Coordi{ static_cast<float>((m_Space.x * 50) + 25), static_cast<float>((m_Space.y * 50) - 25) };
			if (m_sMove < 0)
				m_Item->Get_Info().Posi = Coordi{ static_cast<float>((m_Space.x * 50) + 25), static_cast<float>((m_Space.y * 50) + 75) };
			if (m_Item->Get_ITag() == CItem::ID::COIN)
				static_cast<CCoin*>(m_Item)->hit();
			m_Item = nullptr;
		}
	}
}

void CItemBox::Render(HDC hDC, Coordi Scroll)
{
	//1+17*i,23+17*j
	HDC hBlock = nullptr;

	if(m_FNomal.bAct)
		hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Object, 1 + 17 * m_FNomal.iCount, 1, 16, 16);
	else if (m_FCollision.bAct) {
		if (m_Item)
			m_Item->Render(hDC, Scroll);
		hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Object, 1, 1, 16, 16);
	}
	else
		hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Tile, 86, 23, 16, 16);

	GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
		hBlock, { 16,16 }, RGB(147, 187, 236));
}

void CItemBox::Release()
{
	ptr_delete(m_Item);
}

USHORT CItemBox::Collision(CObject* other)
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
	if (m_FNomal.bAct && other->GetTag() == CObject::ID::CHARIC)
		switch (static_cast<CCharic*>(other)->Get_CTag())
		{
		case CCharic::ID::PLAYER:
			if (Collision & 0x0100) {
				m_sMove = 1;
				m_hit = true;
			}
			if (static_cast<CPlayer*>(other)->Check_Stamp() && Collision & 0x1000) {
				m_sMove = -1;
				m_hit = true;
			}
		case CCharic::ID::ONGGUM:
		case CCharic::ID::REDONGGUM:
			if (Collision & 0x0111 && static_cast<CCharic*>(other)->Check_Slide())
				m_hit = true;
			break;
		default:
			break;
		}
	return Collision;
}

void CItemBox::Set_Item(CItem::ID itag)
{
	m_Item = nullptr;
	switch (itag)
	{
	case CItem::ID::COIN:
		m_Item = new CCoin;
		break;
	case CItem::ID::MUSHROOM:
		m_Item = new CMushroom;
		break;
	case CItem::ID::FIREFLOWER:
		m_Item = new CFireFlower;
		break;
	case CItem::ID::SUPERFLOWER:
		m_Item = new CSuperFlower;
		break;
	case CItem::ID::END:
	default:
		ptr_delete(m_Item);
		break;
	}
	if (m_Item) {
		m_Item->Set_Space({-1,-1});
		m_Item->Get_Info().Posi = Coordi{ static_cast<float>((m_Space.x * 50) + 25), static_cast<float>((m_Space.y * 50) + 25) };
	}
}

