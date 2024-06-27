#include "../../../Header/framework.h"
#include "Goal.h"
#include "../../../Manager/ImageManager.h"
#include "../../../Manager/BlockManager.h"
#include "../../../Manager/CharicManager.h"
CGoal::CGoal()
	: m_FGoal({ 0.f, 0.1f, 0, 100, false, false })
	, m_Flag()
	, m_Pole()
	, m_Castle()
	, m_HalfCastle()
{
	m_BTag = CBlock::ID::GOAL;
	m_Info.RendScale = Coordi(50.f, 50.f);
	m_Info.CollidScale = Coordi(50.f, 50.f);
}

CGoal::~CGoal()
{
	Release();
}

void CGoal::Start()
{
	m_Info.Posi = Coordi{ static_cast<float>((m_Space.x * 50) + 25), static_cast<float>((m_Space.y * 50) + 25) };
	m_Flag.Posi = m_Info.Posi + Coordi(-25.f, -450.f);
	m_Flag.RendScale = Coordi(50.f, 50.f);
	m_Flag.CollidScale = Coordi(0.f, 0.f);
	m_Pole.Posi = m_Info.Posi + Coordi(0.f, -250.f);
	m_Pole.RendScale = Coordi(50.f, 550.f);
	m_Pole.CollidScale = Coordi(10.f, 500.f);
	m_Castle.Posi = m_Info.Posi + Coordi(350.f, -100.f);
	m_Castle.RendScale = Coordi(250.f, 250.f);
	m_Castle.CollidScale = Coordi(0.f, 0.f);
	m_HalfCastle.Posi = m_Castle.Posi + Coordi(62.5f, 62.5f);
	m_HalfCastle.RendScale = Coordi(125.f, 125.f);
	m_HalfCastle.CollidScale = Coordi(0.f, 0.f);
	m_bScreenOut = false;

	m_Info.Update_Domain();
	m_Flag.Update_Domain();
	m_Pole.Update_Domain();
	m_Castle.Update_Domain();
	m_HalfCastle.Update_Domain();

	m_FGoal.end();
}

void CGoal::Time_Update(float deltaTime)
{
	m_FGoal.Check_Time(deltaTime);

	if (m_FGoal.bAct)
		if (m_FGoal.iCount == 1 && m_FGoal.bTrigger) {
			m_Flag.Velo = { 0.f, 400.f };
		}
		else if (m_FGoal.iCount == 10 && m_FGoal.bTrigger) {
			m_Flag.Velo = { 0.f, -400.f };
		}
		else if (m_FGoal.iCount == 20 && m_FGoal.bTrigger) {
			m_Flag.Velo = { 0.f, 0.f };
		}
		else if (m_FGoal.iCount < 10) {
			m_Flag.Move(deltaTime);
			m_Flag.Update_Domain();
		}
		else if (m_FGoal.iCount < 20) {
			m_Flag.Move(deltaTime);
			if (m_Flag.Posi.fy < m_fPY)
				m_Flag.Posi.fy = m_fPY;
			if (m_Flag.Posi.fy < m_Info.Posi.fy - 450.f)
				m_Flag.Posi.fy = m_Info.Posi.fy - 450.f;
			m_Flag.Update_Domain();
		}
}

void CGoal::Update()
{

	if (m_FGoal.bAct)
		return;
	CPlayer* player = CCharicManager::Get_Instance()->Get_Player();
	if (player && !player->Dead_Checker())
		if (Collisison_Pole(player)) {
			m_FGoal.start();
			player->Goal_In();
			player->Get_Info().Posi.fx = m_Info.Posi.fx + 10;
			if (player->Get_Info().Posi.fy < m_Info.Posi.fy - 450.f) {
				player->Get_Info().Posi.fy = m_Info.Posi.fy - 450.f;
				m_fPY = player->Get_Info().Posi.fy;
			}
		}

}

void CGoal::Render(HDC hDC, Coordi Scroll)
{
	//Output_Rectangle(hDC, m_Pole.CollidDomain, Scroll.Point(), RGB(0, 0, 0));
	HDC hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Object, 1 + 45 * 17, 9 + 38 * 17, 16, 16);
	GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
		hBlock, { 16,16 }, RGB(147, 187, 236));
	hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Object, 1 + 45 * 17, 9 + 29 * 17, 16, 176);
	GdiTransparentBlt(hDC, Scroll.Point(), m_Pole.RendDomain, m_Pole.RendScale.Point(),
		hBlock, { 16,176 }, RGB(147, 187, 236));
	if(m_FGoal.bAct&& m_FGoal.iCount > 10)
		hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Object, 1 + 46 * 17, 9 + 28 * 17, 16, 16);
	else
		hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Object, 1 + 45 * 17, 9 + 28 * 17, 16, 16);
	GdiTransparentBlt(hDC, Scroll.Point(), m_Flag.RendDomain, m_Flag.RendScale.Point(),
		hBlock, { 16,16 }, RGB(147, 187, 236));
	hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Object, 6 + 15 * 17, 4 + 35 * 17, 80, 80);
	GdiTransparentBlt(hDC, Scroll.Point(), m_Castle.RendDomain, m_Castle.RendScale.Point(),
		hBlock, { 80,80 }, RGB(147, 187, 236));
}

void CGoal::Release()
{
}

void CGoal::Goal_Render(HDC hDC, Coordi Scroll)
{
	HDC hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Object, 87 + 15 * 17, 44 + 35 * 17, 40, 40);
	GdiTransparentBlt(hDC, Scroll.Point(), m_HalfCastle.RendDomain, m_HalfCastle.RendScale.Point(),
		hBlock, { 40,40 }, RGB(147, 187, 236));
}

USHORT CGoal::Collision(CObject* other)
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

	return Collision;
}

bool CGoal::Collisison_Pole(CObject* other)
{
	RECT intersect = {};
	if (IntersectRect(&intersect, &m_Pole.CollidDomain, &other->Get_Info().CollidDomain)) {
		return true;
	}
	return false;
}
