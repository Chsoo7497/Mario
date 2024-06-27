#include "../Header/framework.h"
#include "ImageManager.h"
CImageManager* CImageManager::m_pInstance = nullptr;


CImageManager::CImageManager()
{

}

CImageManager::~CImageManager()
{
	Release_Sheet();
}

HDC CImageManager::Find_Sheet(const CImageMap::sheet ImageKey, int x, int y, int xsize, int ysize)
{
	map< CImageMap::sheet, CImageMap* >::iterator iter_find = m_ImageMap.find(ImageKey);
	if (iter_find == m_ImageMap.end())
		return nullptr;

	return iter_find->second->choice_Image(x,y,xsize,ysize);
}

HDC CImageManager::Find_Sheet(const CImageMap::sheet ImageKey, int x, int y, int xsize, int ysize, float angle)
{
	map< CImageMap::sheet, CImageMap* >::iterator iter_find = m_ImageMap.find(ImageKey);
	if (iter_find == m_ImageMap.end())
		return nullptr;

	return iter_find->second->choice_Image(x, y, xsize, ysize, angle);
}

void CImageManager::Insert_Sheet(const TCHAR* pPath, const CImageMap::sheet ImageKey)
{
	map< CImageMap::sheet, CImageMap* >::iterator iter_find = m_ImageMap.find(ImageKey);
	if (iter_find != m_ImageMap.end())
		return;
	CImageMap* pBitMap = new CImageMap;
	pBitMap->Insert_Bitmap(pPath);

	m_ImageMap.emplace(ImageKey, pBitMap);
}

void CImageManager::Release_Sheet()
{
	for (pair< CImageMap::sheet, CImageMap* >rPair : m_ImageMap)
		ptr_delete(rPair.second);
	m_ImageMap.clear();
}