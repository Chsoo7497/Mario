#include "../../../Header/framework.h"
#include "RedOnggum.h"
#include "../../../Manager/ImageManager.h"
#include "../../../Manager/BlockManager.h"
#include "../../../Manager/CharicManager.h"
#include "../../../Manager/ItemManager.h"
CRedOnggum::CRedOnggum()
	: m_LR(-1)
{
	m_CTag = CCharic::ID::REDONGGUM;
	m_Info.Velo = Coordi(-50.f, 0.f);
	m_Info.RendScale = Coordi(50.f, 75.f);
	m_Info.CollidScale = Coordi(40.f, 50.f);
}

CRedOnggum::~CRedOnggum()
{
	Release();
}

void CRedOnggum::Start()
{
	m_Info.Posi = Coordi{ static_cast<float>(m_Space.x * 50.f + 25.f), static_cast<float>(m_Space.y * 50.f) };
	m_bDead = false;
	m_bScreenOut = false;
	m_FMove.start();
	m_FSleep.end();
	m_FSlide.end();
	m_FDead.end();
}

void CRedOnggum::Time_Update(float deltaTime)
{
	Dead_Checker(deltaTime);
	
	if (m_FSlide.bAct) {
		m_FMove.end();
		m_FSleep.end();
	}
	m_FMove.Check_Time(deltaTime);
	m_FSlide.Check_Time(deltaTime);
	m_FSleep.Check_Time(deltaTime);

	if (m_FDead.bAct)
		return;


	m_Info.Move(deltaTime);
	m_Info.Get_Force(Coordi(0.f, 0.9f * deltaTime * 1000.f));
	if (m_Info.Velo.fx < 0.f)
		m_LR = -1;
	else if (m_Info.Velo.fx > 0.f)
		m_LR = +1;

	if (m_FSleep.bTrigger) {
		if (m_FSleep.iCount == 100) {
			m_Info.Velo = Coordi(-50.f, 0.f);
			m_FSleep.end();
			m_FSlide.end();
			m_FMove.start();
			m_Info.RendScale = Coordi(50.f, 75.f);
			m_Info.CollidScale = Coordi(40.f, 50.f);
		}
		else if (m_FSleep.iCount >= 95) {
 			m_Info.Velo.fx = 0.f;
		}
		else if (m_FSleep.iCount >= 80) {
			if (m_FSleep.iCount % 2 == 0)
				m_Info.Posi.fx += 2.f;
			if (m_FSleep.iCount % 2 == 1)
				m_Info.Posi.fx -= 2.f;
		}
	}
}

void CRedOnggum::Update()
{
	if (m_FDead.bAct)
		return;
	m_Info.Update_Domain();
	POINT xy = (m_Info.Posi / 50.f).Point();
	for (long i = -1; i <= +1; i++)
	{
		for (long j = -1; j <= +1; j++)
		{
			CObject* temp = CBlockManager::Get_Instance()->Get_Object({ xy.x + i, xy.y + j });
			if (temp == nullptr) {
				if (m_FMove.bAct) {
					if (CBlockManager::Get_Instance()->Get_Object({ xy.x + 0, xy.y + 1 }) != nullptr && i == -1 && j == 1) {//_Info.Velo.fx < 0.f && ((m_Info.Posi.fx / 50.f - xy.x) < 0.2f)
						if (m_Info.Velo.fx < 0.f && ((m_Info.Posi.fx / 50.f - xy.x) < 0.2f))
							m_Info.Velo.fx *= -1.f;
					}
					if (CBlockManager::Get_Instance()->Get_Object({ xy.x + 0, xy.y + 1 }) != nullptr && i == 1 && j == 1) {//_Info.Velo.fx < 0.f && ((m_Info.Posi.fx / 50.f - xy.x) < 0.2f)
						if (m_Info.Velo.fx > 0.f && ((m_Info.Posi.fx / 50.f - xy.x) > 0.8f))
							m_Info.Velo.fx *= -1.f;
					}
				}
				continue;
			}
			USHORT Collid = temp->Collision(this);
			if (Collid & 0x1100)
				m_Info.Velo.fy = 0.f;
			else if (Collid & 0x0011)
				m_Info.Velo.fx *= -1.f;
		}
	}
	m_Info.Update_Domain();

	CPlayer* player = CCharicManager::Get_Instance()->Get_Player();
	if (player && !player->Dead_Checker() && !player->Power_Check()) {
		USHORT Collid = Collision(player);
		if (m_FMove.bAct || m_FSlide.bAct) {
			if (Collid & 0x1000) {
				m_FSleep.start();
				m_FMove.end();
				m_FSlide.end();
				m_Info.RendScale = Coordi(50.f, 50.f);
				m_Info.CollidScale = Coordi(40.f, 30.f);
				m_Info.Velo.fx = 0.f;
			}
		}
		else if (m_FSleep.bAct) {
			if (Collid & 0x0010)
				m_Info.Velo.fx = 300.f;
			if (Collid & 0x0001)
				m_Info.Velo.fx = -300.f;
			if (m_Info.Velo.Length() > 200.f && !Collid) {
				m_FSlide.start();

			}
		}
	}

	for (CCharic* monster : *CCharicManager::Get_Instance()->Get_MonsterList(CCharic::ID::ONGGUM))
	{
		if (Get_Space().x == monster->Get_Space().x &&
			Get_Space().y == monster->Get_Space().y)
			continue;
		USHORT Collid = Collision(monster);
		if (monster->Check_Slide()) {
			RECT intersect{};
			if (IntersectRect(&intersect, &Get_Info().CollidDomain, &monster->Get_Info().CollidDomain)) {
				m_FDead.start();
				return;
			}
		}
	}

	for (CCharic* monster : *CCharicManager::Get_Instance()->Get_MonsterList(CCharic::ID::REDONGGUM))
	{
		USHORT Collid = Collision(monster);
		if (monster->Check_Slide())
			if (Collid & 0x0011) {
				m_FDead.start();
				m_FMove.end();
				return;
			}
	}

	for (CItem* item : *CItemManager::Get_Instance()->Get_ItemList(CItem::ID::FIRE))
	{
		USHORT Collid = Collision(item);
		if (Collid) {
			m_FDead.start();
			m_FMove.end();
			item->Set_Dead();
			item->Set_ScreenOut();
			return;
		}
	}

	for (CItem* item : *CItemManager::Get_Instance()->Get_ItemList(CItem::ID::SUPERBALL))
	{
		USHORT Collid = Collision(item);
		if (Collid) {
			m_FDead.start();
			m_FMove.end();
			item->Set_Dead();
			item->Set_ScreenOut();
			return;
		}
	}

}

void CRedOnggum::Render(HDC hDC, Coordi Scroll)
{
	if (m_bDead)
		return;
	m_Info.Update_Domain();
	HDC hMonster = nullptr;
	int ytemp = 25;
	if (m_FDead.bAct) {
		ytemp = 16;
		if (m_LR < 0)
			hMonster = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Enemy, 148 + 39, 50, +16, ytemp, -PI * m_FDead.iCount / 20);
		else if (m_LR > 0)
			hMonster = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Enemy, 148 + 39, 50, -16, ytemp, -PI * m_FDead.iCount / 20);
	}
	if (m_FMove.bAct) {
		ytemp = 25;
		if (m_LR < 0)
			hMonster = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Enemy, 148 + 1 + m_FMove.iCount * 17, 41, +16, ytemp);
		else if (m_LR > 0)
			hMonster = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Enemy, 148 + 0 + m_FMove.iCount * 17, 41, -16, ytemp);
	}
	else if (m_FSleep.bAct) {
		ytemp = 16;
		if (m_FSleep.iCount >= 95) {
			if (m_LR < 0)
				hMonster = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Enemy, 148 + 56, 50, +16, ytemp);
			else if (m_LR > 0)
				hMonster = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Enemy, 148 + 55, 50, -16, ytemp);
		}
		else {
			if (m_LR < 0)
				hMonster = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Enemy, 148 + 39, 50, +16, ytemp);
			else if (m_LR > 0)
				hMonster = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Enemy, 148 + 38, 50, -16, ytemp);
		}
	}
	else if (m_FSlide.bAct) {
		ytemp = 16;
		if (m_LR < 0)
			hMonster = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Enemy, 148 + 77 + m_FSlide.iCount * 17, 50, +16, ytemp);
		else if (m_LR > 0)
			hMonster = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Enemy, 148 + 76 + m_FSlide.iCount * 17, 50, -16, ytemp);
	
	}
	GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
		hMonster, { 16,ytemp }, RGB(147, 187, 236));
}

void CRedOnggum::Release()
{
}

USHORT CRedOnggum::Collision(CObject* other)
{
	USHORT Collision = 0;
	if(m_FDead.bAct)
		return Collision;
	other->Get_Info().Update_Domain();
	m_Info.Update_Domain();
	if (TopCollision(other))
		Collision |= 0x1000;
	if (BottomCollision(other))
		Collision |= 0x0100;

	if (m_FSlide.bAct)
		return Collision;

	if (LeftCollision(other))
		Collision |= 0x0010;
	if (RightCollision(other))
		Collision |= 0x0001;
	return Collision;
}

void CRedOnggum::Do_Dead(float deltaTime)
{
	if (m_FDead.bTrigger && m_FDead.iCount == 1) {
		CSoundManager::Get_Instance()->StopSound(CSoundManager::CHANNELID::MONSTER);
		CSoundManager::Get_Instance()->PlaySound(L"smw_kick.wav", CSoundManager::CHANNELID::MONSTER);
	}
	if (m_FDead.iCount == 1) {
		if (m_FDead.bTrigger)
			m_Info.Velo = {-m_LR * 50.f, -300.f };
		m_FMove.end();
		m_FSleep.end();
		m_FSlide.end();
		m_Info.RendScale = Coordi(50.f, 50.f);
		m_Info.CollidScale = Coordi(30.f, 30.f);
	}
	else if(m_FDead.iCount<20){
		m_Info.Move(deltaTime);
		m_Info.Get_Force(Coordi(0.f, 0.9f * deltaTime * 1000.f));
	}
	if (m_FDead.iCount == 20)
		m_bDead = true;
}
