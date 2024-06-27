#include "../../Header/framework.h"
#include "Item.h"


CItem::CItem()
	: m_ITag(CItem::ID::END)
	, m_bDead(false)
{
	m_Tag = CObject::ID::ITEM;
}

CItem::~CItem()
{
}


USHORT CItem::Collision(CObject* other)
{
	USHORT Collision = 0;

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

bool CItem::TopCollision(CObject* other)
{
	RECT intersect = {};
	if (IntersectRect(&intersect, &Get_Info().CollidDomain, &other->Get_Info().CollidDomain) &&
		intersect.bottom - intersect.top <= intersect.right - intersect.left &&
		other->Get_Info().Posi.fy < Get_Info().Posi.fy)
	{
		return true;
	}
	return false;
}

bool CItem::BottomCollision(CObject* other)
{
	RECT intersect = {};
	if (IntersectRect(&intersect, &Get_Info().CollidDomain, &other->Get_Info().CollidDomain) &&
		intersect.bottom - intersect.top <= intersect.right - intersect.left &&
		other->Get_Info().Posi.fy > Get_Info().Posi.fy)
	{
		return true;
	}
	return false;
}

bool CItem::LeftCollision(CObject* other)
{
	RECT intersect = {};
	if (IntersectRect(&intersect, &Get_Info().CollidDomain, &other->Get_Info().CollidDomain) &&
		other->Get_Info().Posi.fx <= Get_Info().Posi.fx)
	{
		return true;
	}
	return false;
}

bool CItem::RightCollision(CObject* other)
{
	RECT intersect = {};
	if (IntersectRect(&intersect, &Get_Info().CollidDomain, &other->Get_Info().CollidDomain) &&
		other->Get_Info().Posi.fx >= Get_Info().Posi.fx)
	{
		return true;
	}
	return false;
}
