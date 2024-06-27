#include "../Header/framework.h"
#include "Object.h"

CObject::CObject()
	: m_Space()
	, m_Info()
	, m_Tag(CObject::ID::END)
	, m_bScreenOut(true)
{
}

CObject::~CObject()
{
}
