#include "../../../Header/framework.h"
#include "Ground.h"
#include "../../../Manager/ImageManager.h"
#include "../../../Manager/BlockManager.h"
CGround::CGround()
{
	m_BTag = CBlock::ID::GROUND;
	m_Info.RendScale = Coordi(50.f, 50.f);
	m_Info.CollidScale = Coordi(50.f, 50.f);
}

CGround::~CGround()
{
	Release();
}

void CGround::Start()
{
	m_Info.Posi = Coordi{ static_cast<float>((m_Space.x * 50) + 25), static_cast<float>((m_Space.y * 50) + 25) };
	m_bScreenOut = false;

	m_Info.Update_Domain();
}

void CGround::Time_Update(float deltaTime)
{
	//m_ftime += deltaTime;
	//if (m_ftime > 0.2f) {
	//	m_icount++;
	//	m_ftime = 0.f;
	//	if (m_icount > 1)
	//		m_icount = 0;
	//}
}

void CGround::Update()
{
}

void CGround::Render(HDC hDC, Coordi Scroll)
{
	//1+17*i,23+17*j
	HDC hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Tile, 1, 244, 16, 16);
	GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
		hBlock, { 16,16 }, RGB(147, 187, 236));
}

void CGround::Release()
{
}

USHORT CGround::Collision(CObject* other)
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
