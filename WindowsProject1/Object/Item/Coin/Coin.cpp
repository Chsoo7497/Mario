#include "../../../Header/framework.h"
#include "Coin.h"
#include "../../../Manager/ImageManager.h"
#include "../../../Manager/CharicManager.h"
#include "../../../Manager/SoundManager.h"
#include "../../../Object/Charic/Charic.h"

CCoin::CCoin() 
	:m_FNomal({ 0.f, 0.2f, 0, 4, false, false })
	, m_FCollision({ 0.f, 0.1f, 0, 10, false, false })
	, m_hit(false)
{
	m_ITag = CItem::ID::COIN;
	m_Info.RendScale = Coordi(50.f, 50.f);
	m_Info.CollidScale = Coordi(25.f, 50.f);
	m_FNomal.start();
}

CCoin::~CCoin()
{
}

void CCoin::Start()
{
	m_Info.Posi = Coordi{ static_cast<float>((m_Space.x * 50) + 25), static_cast<float>((m_Space.y * 50) + 25) };
	m_bScreenOut = false;
}


void CCoin::Time_Update(float deltaTime)
{
	if (m_bDead)
		return;
	m_FNomal.Check_Time(deltaTime);
	m_FCollision.Check_Time(deltaTime);

}



void CCoin::Update()
{
	if (m_bDead)
		return;
	CObject* temp = nullptr;

	m_Info.Update_Domain();
	if (m_FCollision.bAct && m_FCollision.iCount == m_FCollision.iFrame)
		Set_Dead();

	CPlayer* player = CCharicManager::Get_Instance()->Get_Player();
	if (player && !player->Dead_Checker()) {
		USHORT Collid = Collision(player);
		if (Collid) {
			hit();
		}
	}
}

void CCoin::Render(HDC hDC, Coordi Scroll)
{
	if (m_bDead)
		return;
	HDC hItem = nullptr;

	if (m_FNomal.bAct)
		hItem = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Object, 1 + 153 + 17 * m_FNomal.iCount, 1, 16, 16);
	else if (m_FCollision.bAct)
		hItem = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Object, 1 + 238 + 17 * (m_FCollision.iCount % 3), 1, 16, 16);

	GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
		hItem, { 16,16 }, RGB(147, 187, 236));
}

void CCoin::Release()
{
}

USHORT CCoin::Collision(CObject* other)
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
