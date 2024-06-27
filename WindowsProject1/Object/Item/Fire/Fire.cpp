#include "../../../Header/framework.h"
#include "Fire.h"
#include "../../../Manager/ImageManager.h"
#include "../../../Manager/CharicManager.h"
#include "../../../Manager/BlockManager.h"
#include "../../../Object/Charic/Charic.h"

CFire::CFire()
	:m_FNomal({ 0.f, 0.05f, 0, 15, false, false })
	, m_FCollision({ 0.f, 0.1f, 0, 2, false, false })
	, m_LR(0)
{
	m_ITag = CItem::ID::FIRE;
	m_Info.Velo = Coordi(-200.f, 0.f);
	m_Info.RendScale = Coordi(30.f, 30.f);
	m_Info.CollidScale = Coordi(25.f, 25.f);
	m_FNomal.start();
}

CFire::~CFire()
{
}

void CFire::Start()
{
	CPlayer* player = CCharicManager::Get_Instance()->Get_Player();
	if (player->Get_Info().Velo.fx < 0.f)
		m_LR = -1;
	else if (player->Get_Info().Velo.fx > 0.f)
		m_LR = 1;

	m_Info.Velo.fx = m_LR * 300.f+ player->Get_Info().Velo.fx*0.5f;
	m_Info.Posi = player->Get_Info().Posi + Coordi{ 25.f * m_LR, -25.f };
	m_bDead = false;
	m_bScreenOut = false;
}


void CFire::Time_Update(float deltaTime)
{
	if (m_bDead)
		return;
	m_FNomal.Check_Time(deltaTime);
	m_FCollision.Check_Time(deltaTime);

	if (m_FNomal.bAct) {
		m_Info.Move(deltaTime);
		m_Info.Get_Force(Coordi(0.f, 0.9f * deltaTime * 1000.f));
	}
	if (m_FCollision.bAct && m_FCollision.iCount == m_FCollision.iFrame) {
		Set_Dead();
		Set_ScreenOut();
	}
}



void CFire::Update()
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
				m_Info.Velo.fy = -300.f;
			else if (Collid & 0x0011) {
				m_FNomal.end();
				m_FCollision.start();
			}
		}
	}
	m_Info.Update_Domain();

}

void CFire::Render(HDC hDC, Coordi Scroll)
{
	if (m_bDead)
		return;
	m_Info.Update_Domain();
	HDC hItem = nullptr;

	if (m_FNomal.bAct)
		hItem = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Playable, 1 + 17 * 21, 76, -8 * m_LR, 8, - PI * m_FNomal.iCount / 8);
	//else if (m_FCollision.bAct)
	//	hItem = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Object, 1 + 238 + 17 * (m_FCollision.iCount % 3), 1, 16, 16);

	GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
		hItem, { 8,8 }, RGB(147, 187, 236));
}

void CFire::Release()
{
}

USHORT CFire::Collision(CObject* other)
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

	return Collision;
}
