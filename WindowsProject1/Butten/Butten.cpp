#include "../Header/framework.h"
#include "Butten.h"
#include "../Cursor/Cursor.h"
CButten::CButten()
	:Posi()
	,Scale()
	,Domain()
	, m_Key()
{
}

CButten::CButten(POINT posi, POINT rendscale)
	:Posi()
	, Scale()
	, Domain()
	, m_Key()
{
	Posi = posi;
	Scale = rendscale;
	Domain.left =	static_cast<LONG>(Posi.x - (Scale.x >> 1));
	Domain.right =	static_cast<LONG>(Posi.x + (Scale.x >> 1));
	Domain.top =	static_cast<LONG>(Posi.y - (Scale.y >> 1));
	Domain.bottom = static_cast<LONG>(Posi.y + (Scale.y >> 1));
}

CButten::~CButten()
{
	Release();
}

bool CButten::Click_Butten()
{
	m_Key.Key_Input();
	if (m_Key.Key_Up(KEY_MOUSE_L)) {
		return PtInRect(&Domain, CCursor::Cursor_Posi());
	}
	return false;
}

bool CButten::On_Butten()
{
	return PtInRect(&Domain, CCursor::Cursor_Posi());
}


void CButten::Release()
{
}
