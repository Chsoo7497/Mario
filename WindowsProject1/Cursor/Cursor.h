#pragma once

class CCursor
{
private:
	static POINT m_Posi;
	static POINT m_RendScale;
	static RECT m_RendDomain;
	static Coordi m_Space;
public:
	explicit CCursor();
	virtual ~CCursor();

public:
	static POINT Cursor_Posi() { return m_Posi; }
	static void Update();
	static void Render(HDC hDC);
	static void Release();

};
