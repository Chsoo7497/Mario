#pragma once

class CKeyManager
{
private:
	ULONGLONG m_ullKey;
	ULONGLONG m_ullKey_Up;
	ULONGLONG m_ullKey_Down;
public:
	CKeyManager();
	~CKeyManager();
public:
	void Key_Input();

	bool Key_Up(ULONGLONG ullKey);
	bool Key_Down(ULONGLONG ullKey);
	bool Key_Press(ULONGLONG ullKey);
};

