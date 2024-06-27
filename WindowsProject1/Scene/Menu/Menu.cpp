#include "../../Header/framework.h"
#include "Menu.h"
#include "../../Manager/ImageManager.h"
#include "../../Manager/SceneManager.h"
CMenu::CMenu()
	:m_bMake({ 500 ,500 }, { 100,100 })
	,m_bPlay({ 700 ,500 }, { 100,100 })
{
}

CMenu::~CMenu()
{
}

int CMenu::Ready()
{
	CSoundManager::Get_Instance()->StopAll();
	CSoundManager::Get_Instance()->PlayBGM(L"1-03 Title.mp3");
    CImageManager::Get_Instance()->Insert_Sheet(L"../Sheet/Butten/MakeButten.bmp", CImageMap::sheet::Butten_Make);
    CImageManager::Get_Instance()->Insert_Sheet(L"../Sheet/Butten/PLayButten.bmp", CImageMap::sheet::Butten_Play);
	CImageManager::Get_Instance()->Insert_Sheet(L"../Sheet/Main.bmp", CImageMap::sheet::Main);

    return 0;
}

void CMenu::Update(float deltaTime)
{
	if (m_bMake.Click_Butten())
	{
		CSceneManager::Get_Instance()->Scene_Change(CSceneManager::ID::SCENE_STAGE);
	}
	if (m_bPlay.Click_Butten())
	{
		CSceneManager::Get_Instance()->Scene_Change(CSceneManager::ID::SCENE_STAGE);
	}
}

void CMenu::Render(HDC hDC)
{
	HDC hMemDC = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Main,0,0,1200,700);
	BitBlt(hDC, 0, 0, SCREENSIZE_X, SCREENSIZE_Y, hMemDC, 0, 0, SRCCOPY);

	if (m_bMake.On_Butten()) {
		HDC Butten_Make = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Butten_Make, 200, 0, 200, 200);
		GdiTransparentBlt(hDC, m_bMake.RendDomain(), m_bMake.RendScale(),
			Butten_Make, { 200,200 }, RGB(27, 89, 153));
	}
	else {
		HDC Butten_Make = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Butten_Make, 0, 0, 200, 200);
		GdiTransparentBlt(hDC, m_bMake.RendDomain(), m_bMake.RendScale(),
			Butten_Make, { 200,200 }, RGB(27, 89, 153));
	}
	if (m_bPlay.On_Butten()) {
		HDC Butten_Play = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Butten_Play, 200, 0, 200, 200);
		GdiTransparentBlt(hDC, m_bPlay.RendDomain(), m_bPlay.RendScale(),
			Butten_Play, { 200,200 }, RGB(27, 89, 153));
	}
	else {
		HDC Butten_Play = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Butten_Play, 0, 0, 200, 200);
		GdiTransparentBlt(hDC, m_bPlay.RendDomain(), m_bPlay.RendScale(),
			Butten_Play, { 200,200 }, RGB(27, 89, 153));
	}
}

void CMenu::Release()
{
}

