#include "../../../Header/framework.h"
#include "ItemBlock.h"
#include "../../../Manager/ImageManager.h"
#include "../../../Manager/BlockManager.h"
#include "../../../Manager/CharicManager.h"
#include "../../../Object/Item/Coin/Coin.h"
#include "../../../Object/Item/Mushroom/Mushroom.h"
#include "../../../Object/Item/FireFlower/FireFlower.h"
#include "../../../Object/Item/SuperFlower/SuperFlower.h"
CItemBlock::CItemBlock()
	:m_FNomal({ 0.f, 0.2f, 0, 0, false, false })
	,m_FCollision({ 0.f, 0.01f, 0, 10, false, false })
	, m_FCrush({ 0.f, 0.1f, 0, 20, false, false })
	, m_bCrush(false)
	, m_hit(false)
	, m_Item()
	, m_sMove(1)
	, m_piece()
{
	m_BTag = CBlock::ID::ITEMBLOCK;
	m_Info.RendScale = Coordi(50.f, 50.f);
	m_Info.CollidScale = Coordi(50.f, 50.f);
	m_FNomal.start();
}

CItemBlock::~CItemBlock()
{
	Release();
}

void CItemBlock::Start()
{
	m_Info.Posi = Coordi{ static_cast<float>((m_Space.x * 50) + 25), static_cast<float>((m_Space.y * 50) + 25) };
	m_bScreenOut = false;
	m_Info.Update_Domain();

	for (int i = 0; i < 4; i++)
	{
		m_piece[i] = m_Info;
	}
}

void CItemBlock::Time_Update(float deltaTime)
{
	m_FNomal.Check_Time(deltaTime);
	m_FCollision.Check_Time(deltaTime);
	m_FCrush.Check_Time(deltaTime);
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
	if (m_FCrush.bAct)
		if (m_FCrush.iCount == 0) {
			m_Info.RendScale = Coordi(0.f, 0.f);
			m_Info.CollidScale = Coordi(0.f, 0.f);
			m_bCrush = true;
		}
		if (m_FCrush.iCount == 1 && m_FCrush.bTrigger) {
			m_piece[0].Velo = Coordi(-100.f, -300.f);
			m_piece[1].Velo = Coordi(+100.f, -300.f);
			m_piece[2].Velo = Coordi(-100.f, -100.f);
			m_piece[3].Velo = Coordi(+100.f, -100.f);
			CSoundManager::Get_Instance()->StopSound(CSoundManager::CHANNELID::EFFECT);
			CSoundManager::Get_Instance()->PlaySound(L"Thunder.wav", CSoundManager::CHANNELID::EFFECT);
		}
		else if (m_FCrush.bTrigger && m_FCrush.iCount == 10)
			CSoundManager::Get_Instance()->StopSound(CSoundManager::CHANNELID::EFFECT);
		else if (m_FCrush.iCount > 0 && m_FCrush.iCount < 20) {
			for (int i = 0; i < 4; i++)
			{
				m_piece[i].Move(deltaTime);
				m_piece[i].Get_Force(Coordi(0.f, 0.9f * deltaTime * 1000.f));
			}
		}
		else if(m_FCrush.iCount>=20)
			m_FCrush.end();
}

void CItemBlock::Update()
{
	if (m_bCrush) {
		m_bTop = false;
		m_bBottom = false;
		m_bLeft = false;
		m_bRight = false;
		return;
	}

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
		else
			m_FNomal.start();
	}
}

void CItemBlock::Render(HDC hDC, Coordi Scroll)
{
	//1+17*i,23+17*j
	HDC hBlock = nullptr;
	m_Info.Update_Domain();

	if(m_FNomal.bAct)
		hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Object, 1 + 17 * 6, 1, 16, 16);
	else if (m_FCollision.bAct) {
		if (m_Item)
			m_Item->Render(hDC, Scroll);
		hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Object, 1 + 17 * 6, 1, 16, 16);
	}
	else if (m_FCrush.bAct) {
		for (int i = 0; i < 4; i++)
		{
			m_piece[i].Update_Domain();
			hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Tile, 1, 23 + 17*5, 
				(m_piece[i].Velo.fx<0?-1:1) * 16, 16, (m_piece[i].Velo.fx < 0 ? -1 : 1) * PI * m_FCrush.iCount / 10);
			GdiTransparentBlt(hDC, Scroll.Point(), m_piece[i].RendDomain, m_piece[i].RendScale.Point(),
				hBlock, { 16,16 }, RGB(147, 187, 236));
		}
	}	
	else if (m_bCrush) {
	}
	else
		hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Tile, 86, 23, 16, 16);
	GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
		hBlock, { 16,16 }, RGB(147, 187, 236));
}

void CItemBlock::Release()
{
	ptr_delete(m_Item);
}

USHORT CItemBlock::Collision(CObject* other)
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
			if (m_FNomal.bAct) {
				if (Collision & 0x0100) {
					m_sMove = 1;
					if (m_Item)
						m_hit = true;
					else if (static_cast<CPlayer*>(other)->Power() > 0) {
						m_FCrush.start();
						m_FNomal.end();
					}
				}
				if (static_cast<CPlayer*>(other)->Check_Stamp() && Collision & 0x1000) {
					m_sMove = -1;
					if (m_Item)
						m_hit = true;
					else if (static_cast<CPlayer*>(other)->Power() > 0) {
						m_FCrush.start();
						m_FNomal.end();
					}
				}
			}
			break;
		case CCharic::ID::ONGGUM:
		case CCharic::ID::REDONGGUM:
			if (Collision & 0x0111 && static_cast<CCharic*>(other)->Check_Slide())
				if (m_Item)
					m_hit = true;
				else if (Collision & 0x0011) {
					m_FCrush.start();
					m_FNomal.end();
				}
			break;
		default:
			break;
		}
	return Collision;
}

void CItemBlock::Set_Item(CItem::ID itag)
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

