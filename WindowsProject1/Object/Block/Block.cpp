#include "../../Header/framework.h"
#include "Block.h"
#include "../../Manager/ImageManager.h"
#include "../../Manager/MapManager.h"
#include "../../Manager/BlockManager.h"
#include "./Ground/Ground.h"
#include "./ItemBlock/ItemBlock.h"
CBlock::CBlock()
	:m_BTag(ID::END)
	, m_bTop(false)
	, m_bBottom(false)
	, m_bLeft(false)
	, m_bRight(false)
{
	m_Tag = CObject::ID::BLOCK;
	m_Info.RendScale = Coordi(50.f, 50.f);
	m_Info.CollidScale = Coordi(50.f, 50.f);

}

CBlock::~CBlock()
{
}

USHORT CBlock::Collision(CObject* other)
{
	USHORT Collision = 0;
	if (m_bTop)
		if(TopCollision(other))
			Collision |= 0x1000;
	if (m_bBottom)
		if (BottomCollision(other))
			Collision |= 0x0100;
	if (m_bLeft)
		if (LeftCollision(other))
			Collision |= 0x0010;
	if (m_bRight)
		if (RightCollision(other))
			Collision |= 0x0001;

	return Collision;
}

void CBlock::Collision_way()
{
	CBlock* temp = nullptr;

	temp = CBlockManager::Get_Instance()->Get_Object({ m_Space.x,m_Space.y - 1 });
	if (temp == nullptr || 
		temp->Get_BTag() == CBlock::ID::HALFGROUND ||
		(temp->Get_BTag() == CBlock::ID::ITEMBLOCK && static_cast<CItemBlock*>(temp)->Get_Crush())
		)	m_bTop = true;

	temp = CBlockManager::Get_Instance()->Get_Object({ m_Space.x,m_Space.y + 1 });
	if (temp == nullptr ||
		temp->Get_BTag() == CBlock::ID::HALFGROUND ||
		(temp->Get_BTag() == CBlock::ID::ITEMBLOCK && static_cast<CItemBlock*>(temp)->Get_Crush())
		) m_bBottom = true;

	temp = CBlockManager::Get_Instance()->Get_Object({ m_Space.x - 1,m_Space.y });
	if (temp == nullptr ||
		temp->Get_BTag() == CBlock::ID::HALFGROUND ||
		(temp->Get_BTag() == CBlock::ID::ITEMBLOCK && static_cast<CItemBlock*>(temp)->Get_Crush())
		) m_bLeft = true;

	temp = CBlockManager::Get_Instance()->Get_Object({ m_Space.x + 1,m_Space.y });
	if (temp == nullptr ||
		temp->Get_BTag() == CBlock::ID::HALFGROUND ||
		(temp->Get_BTag() == CBlock::ID::ITEMBLOCK && static_cast<CItemBlock*>(temp)->Get_Crush())
		) m_bRight = true;
}

bool CBlock::TopCollision(CObject* other)
{
	RECT intersect = {};
	if (IntersectRect(&intersect, &Get_Info().RendDomain, &other->Get_Info().RendDomain) &&
		intersect.bottom - intersect.top < intersect.right - intersect.left &&
		other->Get_Info().RendDomain.bottom < Get_Info().Posi.fy && other->Get_Info().Velo.fy >= 0.f)
	{
		return true;
	}
	return false;
}

bool CBlock::BottomCollision(CObject* other)
{
	RECT intersect = {};
	if (IntersectRect(&intersect, &Get_Info().RendDomain, &other->Get_Info().RendDomain) &&
		intersect.bottom - intersect.top < intersect.right - intersect.left &&
		other->Get_Info().RendDomain.top > Get_Info().Posi.fy && other->Get_Info().Velo.fy <= 0.f)
	{
		return true;
	}
	return false;
}

bool CBlock::LeftCollision(CObject* other)
{
	RECT intersect = {};
	if (IntersectRect(&intersect, &Get_Info().RendDomain, &other->Get_Info().RendDomain) &&
		intersect.bottom - intersect.top > intersect.right - intersect.left &&
		other->Get_Info().RendDomain.right < Get_Info().Posi.fx && other->Get_Info().Velo.fx >= 0.f)
	{
		return true;
	}
	return false;
}
bool CBlock::RightCollision(CObject* other)
{
	RECT intersect = {};
	if (IntersectRect(&intersect, &Get_Info().RendDomain, &other->Get_Info().RendDomain) &&
		intersect.bottom - intersect.top > intersect.right - intersect.left &&
		other->Get_Info().RendDomain.left > Get_Info().Posi.fx && other->Get_Info().Velo.fx <= 0.f)
	{
		return true;
	}
	return false;
}

