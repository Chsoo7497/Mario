#pragma once
#include "../Object/Object.h"
#include "../Image/ImageMap.h"
class CImageManager
{
public:

	static CImageManager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CImageManager;
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
private:
	static CImageManager* m_pInstance;
	map< CImageMap::sheet, CImageMap* > m_ImageMap;
private:
	 CImageManager();
	 ~CImageManager();
public:
	HDC Find_Sheet(const CImageMap::sheet ImageKey, int x, int y, int xsize, int ysize);
	HDC Find_Sheet(const CImageMap::sheet ImageKey, int x, int y, int xsize, int ysize, float angle);
	void Insert_Sheet(const TCHAR* pPath, const CImageMap::sheet ImageKey);
	void Release_Sheet();
public:

public:
};

