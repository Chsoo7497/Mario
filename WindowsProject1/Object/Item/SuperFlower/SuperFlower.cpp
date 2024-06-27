#include "../../../Header/framework.h"
#include "SuperFlower.h"
#include "../../../Manager/ImageManager.h"
#include "../../../Manager/CharicManager.h"
#include "../../../Manager/BlockManager.h"
#include "../../../Object/Charic/Charic.h"

CSuperFlower::CSuperFlower()
	:m_FNomal({ 0.f, 0.2f, 0, 2, false, 1 })
	, m_FCollision({ 0.f, 0.1f, 0, 20, false, 1 })
	, m_hit(false)
{
	m_ITag = CItem::ID::SUPERFLOWER;
	m_Info.RendScale = Coordi(50.f, 50.f);
	m_Info.CollidScale = Coordi(40.f, 40.f);
	m_FNomal.start();
}

CSuperFlower::~CSuperFlower()
{
}

void CSuperFlower::Start()
{
	m_Info.Posi = Coordi{ static_cast<float>((m_Space.x * 50) + 25), static_cast<float>((m_Space.y * 50) + 25) };
	m_bDead = false;
	m_bScreenOut = false;
}


void CSuperFlower::Time_Update(float deltaTime)
{
	if (m_bDead)
		return;
	m_FNomal.Check_Time(deltaTime);
	m_FCollision.Check_Time(deltaTime);

	if (m_FNomal.bAct) {
		m_Info.Move(deltaTime);
		m_Info.Get_Force(Coordi(0.f, 0.9f * deltaTime * 1000.f));
	}
	if (m_FCollision.bAct && m_FCollision.iCount == m_FCollision.iFrame)
		Set_Dead();
}



void CSuperFlower::Update()
{
	if (m_bDead)
		return;
	CObject* temp = nullptr;

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
	if (player && !player->Dead_Checker()) {
		USHORT Collid = Collision(player);
		if (Collid && player->Power_Check()) {
			m_FNomal.end();
			m_FCollision.start();
		}
	}
}

void CSuperFlower::Render(HDC hDC, Coordi Scroll)
{
	if (m_bDead)
		return;
	m_Info.Update_Domain();
	HDC hItem = nullptr;

	if (m_FNomal.bAct)
		hItem = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Playable, 1 + 17 * 4 + 17 * m_FNomal.iCount, 597 + 17, 16, 16);
	//else if (m_FCollision.bAct)
	//	hItem = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Object, 1 + 238 + 17 * (m_FCollision.iCount % 3), 1, 16, 16);

	GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
		hItem, { 16,16 }, RGB(147, 187, 236));
}

void CSuperFlower::Release()
{
}

USHORT CSuperFlower::Collision(CObject* other)
{
	USHORT Collision = 0;	
	if (m_FCollision.bAct)
		return Collision;

	if (TopCollision(other))
		Collision |= 0x1000;
	if (BottomCollision(other))
		Collision |= 0x0100;
	if (LeftCollision(other))
		Collision |= 0x0010;
	if (RightCollision(other))
		Collision |= 0x0001;
	if (Collision) {
		m_FNomal.end();
		m_FCollision.start();
	}
	return Collision;
}
