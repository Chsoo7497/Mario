#include "../Header/framework.h"
#include "Cursor.h"
POINT CCursor::m_Posi = {};
POINT CCursor::m_RendScale = { 10,10 };
RECT  CCursor::m_RendDomain = {};
CCursor::CCursor()
{
}

CCursor::~CCursor()
{
	Release();  
}

void CCursor::Update()
{
	ShowCursor(FALSE);
	POINT pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	m_Posi = pt;
}

void CCursor::Render(HDC hDC)
{
	m_RendDomain.left	= (m_Posi.x - (m_RendScale.x / 2));
	m_RendDomain.right	= (m_Posi.x + (m_RendScale.x / 2));
	m_RendDomain.top	= (m_Posi.y - (m_RendScale.y / 2));
	m_RendDomain.bottom = (m_Posi.y + (m_RendScale.y / 2));
	Output_Ellipse(hDC, m_RendDomain);
}

void CCursor::Release()
{
}
