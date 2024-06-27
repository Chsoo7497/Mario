#include "../../Header/framework.h"
#include "Charic.h"


CCharic::CCharic()
	: m_CTag(CCharic::ID::END)
	, m_bDead(false)
	, m_FDead({ 0.f, 0.05f, 0, 500, false, false })
	, m_FMove({ 0.f, 0.2f, 0, 1, true, false })
	, m_FSleep({ 0.f, 0.1f, 0, 100, false, false })
	, m_FSlide({ 0.f, 0.1f, 0, 3, false, false })
{
	m_Tag = CObject::ID::CHARIC;
}

CCharic::~CCharic()
{
}

bool CCharic::TopCollision(CObject* other)
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

bool CCharic::BottomCollision(CObject* other)
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

bool CCharic::LeftCollision(CObject* other)
{
	RECT intersect = {};
	if (IntersectRect(&intersect, &Get_Info().CollidDomain, &other->Get_Info().CollidDomain) &&
		other->Get_Info().Posi.fx < Get_Info().Posi.fx)
	{
		return true;
	}
	return false;
}

bool CCharic::RightCollision(CObject* other)
{
	RECT intersect = {};
	if (IntersectRect(&intersect, &Get_Info().CollidDomain, &other->Get_Info().CollidDomain) &&
		other->Get_Info().Posi.fx > Get_Info().Posi.fx)
	{
		return true;
	}
	return false;
}

bool CCharic::Dead_Checker(float deltaTime)
{
	if (!m_FDead.bAct)
		return m_FDead.bAct;
	m_FDead.Check_Time(deltaTime);
	if (m_FDead.iCount == m_FDead.iFrame)
		Set_ScreenOut();
	else {
		Do_Dead(deltaTime);
	}
	return m_FDead.bAct;
}

