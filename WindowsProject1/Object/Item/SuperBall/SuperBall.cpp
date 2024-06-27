#include "../../../Header/framework.h"
#include "SuperBall.h"
#include "../../../Manager/ImageManager.h"
#include "../../../Manager/CharicManager.h"
#include "../../../Manager/BlockManager.h"
#include "../../../Object/Charic/Charic.h"

CSuperBall::CSuperBall()
	:m_FNomal({ 0.f, 0.05f, 0, 1, false, false })
	, m_FCollision({ 0.f, 0.1f, 0, 2, false, false })
	, m_LR(0)
	, m_fTime(0.f)
{
	m_ITag = CItem::ID::SUPERBALL;
	m_Info.Velo = Coordi(-200.f, 0.f);
	m_Info.RendScale = Coordi(40.f, 40.f);
	m_Info.CollidScale = Coordi(25.f, 25.f);
	m_FNomal.start();
}

CSuperBall::~CSuperBall()
{
}

void CSuperBall::Start()
{
	CPlayer* player = CCharicManager::Get_Instance()->Get_Player();
	if (player->Get_Info().Velo.fx < 0.f)
		m_LR = -1;
	else if (player->Get_Info().Velo.fx > 0.f)
		m_LR = 1;

	m_Info.Velo = {m_LR * 300.f, 300.f};
	m_Info.Posi = player->Get_Info().Posi + Coordi{ 25.f * m_LR, -25.f };
	m_bDead = false;
	m_bScreenOut = false;
}


void CSuperBall::Time_Update(float deltaTime)
{
	if (m_bDead)
		return;
	m_fTime += deltaTime;
	if(m_fTime>5.f)
		Set_ScreenOut();

	m_FNomal.Check_Time(deltaTime);
	m_FCollision.Check_Time(deltaTime);

	if (m_FNomal.bAct) {
		m_Info.Move(deltaTime);
	}
	if (m_FCollision.bAct && m_FCollision.iCount == m_FCollision.iFrame) {
		Set_Dead();
		Set_ScreenOut();
	}
}



void CSuperBall::Update()
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
				m_Info.Velo.fy *= -1.f;
			else if (Collid & 0x0011) {
				m_Info.Velo.fx *= -1.f;
			}
		}
	}
	m_Info.Update_Domain();

}

void CSuperBall::Render(HDC hDC, Coordi Scroll)
{
	if (m_bDead)
		return;
	m_Info.Update_Domain();
	HDC hItem = nullptr;

	if (m_FNomal.bAct)
		hItem = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Playable, 1 + 17 * 21 +2, 111, 12, 12);
	//else if (m_FCollision.bAct)
	//	hItem = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Object, 1 + 238 + 17 * (m_FCollision.iCount % 3), 1, 16, 16);

	GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
		hItem, { 12,12 }, RGB(147, 187, 236));
}

void CSuperBall::Release()
{
}

USHORT CSuperBall::Collision(CObject* other)
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
