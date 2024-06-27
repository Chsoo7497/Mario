#include "../../../Header/framework.h"
#include "HalfGround.h"
#include "../../../Manager/ImageManager.h"
#include "../../../Manager/BlockManager.h"
#include "../../../Manager/CharicManager.h"
#include "../../../Object/Item/Coin/Coin.h"
#include "../../../Object/Item/Mushroom/Mushroom.h"
#include "../../../Object/Item/FireFlower/FireFlower.h"
#include "../../../Object/Item/SuperFlower/SuperFlower.h"
CHalfGround::CHalfGround()
{
	m_BTag = CBlock::ID::HALFGROUND;
	m_Info.RendScale = Coordi(50.f, 50.f);
	m_Info.CollidScale = Coordi(50.f, 50.f);
}

CHalfGround::~CHalfGround()
{
	Release();
}

void CHalfGround::Start()
{
	m_Info.Posi = Coordi{ static_cast<float>((m_Space.x * 50) + 25), static_cast<float>((m_Space.y * 50) + 25) };
	m_bScreenOut = false;

	m_Info.Update_Domain();
}

void CHalfGround::Time_Update(float deltaTime)
{

}

void CHalfGround::Update()
{
	CBlock* temp = nullptr;
	m_bBottom = false; 
	m_bLeft = false; 
	m_bRight = false;

}

void CHalfGround::Render(HDC hDC, Coordi Scroll)
{
	//1+17*i,23+17*j
	HDC hBlock = nullptr;
	hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Tile, 1 + 17 * 11, 23 + 17 * 3, 16, 16);
	GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
		hBlock, { 16,16 }, RGB(147, 187, 236));
	for (LONG i = 1; i < 28 - m_Space.y; i++)
	{
		hBlock = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Tile, 1 + 17 * 11, 23 + 17 * 4, 16, 16);
		GdiTransparentBlt(hDC, Scroll.Point(), { m_Info.RendDomain.left, m_Info.RendDomain.top + (i * 50), m_Info.RendDomain.right, m_Info.RendDomain.bottom + (i * 50) },
			m_Info.RendScale.Point(), hBlock, { 16,16 }, RGB(147, 187, 236));

	}
}

void CHalfGround::Release()
{
	//ptr_delete(m_Item);
}

USHORT CHalfGround::Collision(CObject* other)
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

