#include "../../../Header/framework.h"
#include "Goomba.h"
#include "../../../Manager/ImageManager.h"
#include "../../../Manager/BlockManager.h"
#include "../../../Manager/CharicManager.h"
#include "../../../Manager/ItemManager.h"

CGoomba::CGoomba()
{
	m_CTag = CCharic::ID::GOOMBA;
	m_Info.Velo = Coordi(-50.f, 0.f);
	m_Info.RendScale = Coordi(50.f, 50.f);
	m_Info.CollidScale = Coordi(40.f, 30.f);
}

CGoomba::~CGoomba()
{
	Release();
}

void CGoomba::Start()
{
	m_Info.Posi = Coordi{ static_cast<float>((m_Space.x * 50) + 25), static_cast<float>((m_Space.y * 50) + 25) };
	m_bDead = false;
	m_bScreenOut = false;
	m_FMove.start();
}

void CGoomba::Time_Update(float deltaTime)
{
	Dead_Checker(deltaTime);

	if (m_bDead)
		return;


	if (m_FMove.bAct) {
		m_Info.Move(deltaTime);
		m_Info.Get_Force(Coordi(0.f, 0.9f * deltaTime * 1000.f));
	}
	m_FMove.Check_Time(deltaTime);
}

void CGoomba::Update()
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
			if (temp == nullptr)
				continue;
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
		if (Collid & 0x1000) {
			m_FDead.start();
			m_FMove.end();
		}
	}

	for (CCharic* monster : *CCharicManager::Get_Instance()->Get_MonsterList(CCharic::ID::ONGGUM))
	{
		USHORT Collid = Collision(monster);
		if(monster->Check_Slide())
			if (Collid & 0x0011) {
				m_FDead.start();
				m_FMove.end();
				return;
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

void CGoomba::Render(HDC hDC, Coordi Scroll)
{
	if (m_bDead)
		return;
	m_Info.Update_Domain();
	HDC hMonster = nullptr;
	int ytemp = 17;
	if (m_FDead.bAct) {
		hMonster = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Enemy, 98, 1, 16, ytemp);

	}
	else if (m_Info.Velo.fy < 0.f) {
		ytemp = 19;
		hMonster = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Enemy, 56, 1, 16, ytemp);
	}
	else if (m_Info.Velo.fy > 50.f) {
		hMonster = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Enemy, 39, 1, 16, ytemp);
	}
	else if (m_FMove.bAct) {
		hMonster = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Enemy, 1 + m_FMove.iCount * 17, 1, 16, ytemp);
	}
	GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
		hMonster, { 16,ytemp }, RGB(147, 187, 236));
}

void CGoomba::Release()
{
}

USHORT CGoomba::Collision(CObject* other)
{
	USHORT Collision = 0;

	if(m_FDead.bAct || m_bDead)
		return Collision;

	if (TopCollision(other))
		Collision |= 0x1000;
	if (BottomCollision(other))
		Collision |= 0x0100;
	if (LeftCollision(other))
		Collision |= 0x0010;
	if (RightCollision(other))
		Collision |= 0x0001;

	return Collision;
}

void CGoomba::Do_Dead(float deltaTime)
{
	m_FMove.end();
	if (m_FDead.bTrigger && m_FDead.iCount == 1) {
		CSoundManager::Get_Instance()->StopSound(CSoundManager::CHANNELID::MONSTER);
		CSoundManager::Get_Instance()->PlaySound(L"smw_kick.wav", CSoundManager::CHANNELID::MONSTER);
	}
	if (m_FDead.iCount == 20)
		m_bDead = true;
}
