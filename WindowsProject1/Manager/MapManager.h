#pragma once
#include"../Map/Map.h"
class CMapManager
{
private:
	CMapManager();
	~CMapManager();
	static CMapManager* m_pInstance;
	Coordi m_SavePoint;
	Coordi m_Scroll;
	CMap* m_map;
public:
	static CMapManager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CMapManager;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
public:
	void _Ready();
	void _Update(float deltaTime);
	void _Render(HDC hDC);
	void _Release();

	void Set_Scroll(Coordi Scroll);
	Coordi Get_Scroll() { return m_Scroll; }

};

