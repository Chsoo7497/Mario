#pragma once
#include "../Object/Object.h"
class CImageMap
{
public:
	enum class sheet
	{
		Buffer,
		Main,
		BackGround,
		Enemy,
		Playable,
		Object,
		Tile,
		Game_Over,
		Course_Clear,
		Butten_Play,
		Butten_Make
	};
private:
	HDC		m_hImegeSheet; // 다른 도화지에 그림 그려둘 것. 
	HBITMAP m_hSheetBitmap;
	HBITMAP m_hSheetOldBitmap;

	HDC		m_hImegeClear; //추출한 이미지 지우개
	HBITMAP m_hClearBitmap;
	HBITMAP m_hClearOldBitmap;

	HDC		m_hImege; //sheet에서 사용할 이미지를 불러옴
	HBITMAP m_hBitmap; // 실질적으로 그림에 대한 정보를 가지고 있을놈. 
	HBITMAP m_hOldBitmap; // 추후 지우기 위해 사용할 놈. 

	HDC		m_hSubImege; 
	HBITMAP m_hSubBitmap;
	HBITMAP m_hSubOldBitmap; 
public:
	explicit CImageMap();
	virtual ~CImageMap();
public:
	HDC choice_Image(int x, int y, int xsize, int ysize);
	HDC choice_Image(int x, int y, int xsize, int ysize, float angle);
	// wchar_t*
	void Insert_Bitmap(const TCHAR* pFilePath);
	void Release_Bitmap();

};

