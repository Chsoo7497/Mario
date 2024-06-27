#include "../../Header/framework.h"
#include "Clear.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/ImageManager.h"
#include "../../Manager/SoundManager.h"

CClear::CClear()
	:m_FNomal({ 0.f, 0.1f, 0, 20, false, false })
{
}

CClear::~CClear()
{
}

int CClear::Ready()
{
	CImageManager::Get_Instance()->Insert_Sheet(L"../Sheet/CourseClear.bmp", CImageMap::sheet::Course_Clear);
	CSoundManager::Get_Instance()->StopAll();
	CSoundManager::Get_Instance()->PlayBGM(L"Thunder.wav");
	m_FNomal.start();
    return 0;
}

void CClear::Update(float deltaTime)
{
	m_FNomal.Check_Time(deltaTime);
	if (m_FNomal.iCount == m_FNomal.iFrame) {
		m_FNomal.end();
		CSceneManager::Get_Instance()->Scene_Change(CSceneManager::ID::SCENE_MENU);
	}
}

void CClear::Render(HDC hDC)
{
	HDC hMemDC = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Course_Clear, 0, 0, 1200, 700);
	BitBlt(hDC, 0, 0, SCREENSIZE_X, SCREENSIZE_Y, hMemDC, 0, 0, SRCCOPY);
}

void CClear::Release()
{
}
