#include "../Header/framework.h"
#include "KeyManager.h"

CKeyManager::CKeyManager()
	:m_ullKey()
	, m_ullKey_Up()
	, m_ullKey_Down()
{
}

CKeyManager::~CKeyManager()
{
}

void CKeyManager::Key_Input()
{
	m_ullKey = 0;
	if (GetAsyncKeyState(VK_LEFT)	& 0x8000)
		m_ullKey |= KEY_LEFT;
	if (GetAsyncKeyState(VK_RIGHT)	& 0x8000)
		m_ullKey |= KEY_RIGHT;
	if (GetAsyncKeyState(VK_UP)		& 0x8000)
		m_ullKey |= KEY_UP;
	if (GetAsyncKeyState(VK_DOWN)	& 0x8000)
		m_ullKey |= KEY_DOWN;
	if (GetAsyncKeyState('Q')		& 0x8000)
		m_ullKey |= KEY_Q;
	if (GetAsyncKeyState('W')		& 0x8000)
		m_ullKey |= KEY_W;
	if (GetAsyncKeyState('E')		& 0x8000)
		m_ullKey |= KEY_E;
	if (GetAsyncKeyState('R')		& 0x8000)
		m_ullKey |= KEY_R;
	if (GetAsyncKeyState('A')		& 0x8000)
		m_ullKey |= KEY_A;
	if (GetAsyncKeyState('S')		& 0x8000)
		m_ullKey |= KEY_S;
	if (GetAsyncKeyState('D')		& 0x8000)
		m_ullKey |= KEY_D;
	if (GetAsyncKeyState('F')		& 0x8000)
		m_ullKey |= KEY_F;
	if (GetAsyncKeyState('Z')		& 0x8000)
		m_ullKey |= KEY_Z;
	if (GetAsyncKeyState('X')		& 0x8000)
		m_ullKey |= KEY_X;
	if (GetAsyncKeyState('C')		& 0x8000)
		m_ullKey |= KEY_C;
	if (GetAsyncKeyState('V')		& 0x8000)
		m_ullKey |= KEY_V;
	if (GetAsyncKeyState(VK_SPACE)	& 0x8000)
		m_ullKey |= KEY_SPACE;
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		m_ullKey |= KEY_MOUSE_L;
	if (GetAsyncKeyState(VK_MBUTTON) & 0x8000)
		m_ullKey |= KEY_MOUSE_M;
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		m_ullKey |= KEY_MOUSE_R;
}

bool CKeyManager::Key_Up(ULONGLONG ullKey)
{
	if (m_ullKey & ullKey)
	{
		m_ullKey_Up |= ullKey;
		return false;
	}
	else if (m_ullKey_Up & ullKey)
	{
		m_ullKey_Up ^= ullKey;
		return true;
	}
	return false;
}

bool CKeyManager::Key_Down(ULONGLONG ullKey)
{
	if (m_ullKey & ullKey && !(m_ullKey_Down & ullKey))
	{
		m_ullKey_Down |= ullKey;
		return true;
	}
	else if (!(m_ullKey & ullKey) && (m_ullKey_Down & ullKey))
	{
		m_ullKey_Down ^= ullKey;
		return false;
	}
	return false;
}

bool CKeyManager::Key_Press(ULONGLONG ullKey)
{
	if (m_ullKey & ullKey)
		return true;
	return false;
}


