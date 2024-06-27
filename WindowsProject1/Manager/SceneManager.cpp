#include "../Header/framework.h"
#include "SceneManager.h"
#include "../Scene/Scene.h"
#include "../Scene/Loading/Loading.h"
#include "../Scene/Stage/Stage.h"
#include "../Scene/Menu/Menu.h"
#include "../Scene/GameOver/GameOver.h"
#include "../Scene/Clear/Clear.h"


CSceneManager* CSceneManager::m_pInstance = nullptr;
CSceneManager::CSceneManager()
	:m_eCurScene(SCENE_END)
	, m_eNextScene(SCENE_END)
	, m_pScene(nullptr)
{
}

CSceneManager::~CSceneManager()
{
	Release();
}

void CSceneManager::Scene_Change(ID eNextID)
{
	//FSM 유한 상태 기계 
	m_eNextScene = eNextID;
	// 이경우는 어떤 경우 ? 즉 씬이 변경되야 하는 상황. 
	if (m_eCurScene != m_eNextScene)
	{
		ptr_delete(m_pScene);
		switch (m_eNextScene)
		{
		case CSceneManager::SCENE_LOADING:
			m_pScene = new CLoading;
			break;
		case CSceneManager::SCENE_STAGE:
			m_pScene = new CStage;
			break;
		case CSceneManager::SCENE_MENU:
			m_pScene = new CMenu;
			break;
		case CSceneManager::SCENE_GAMEOVER:
			m_pScene = new CGameOver;
			break;		
		case CSceneManager::SCENE_CLEAR:
			m_pScene = new CClear;
			break;
		default:
			break;
		}
		m_pScene->Ready();
		m_eCurScene = m_eNextScene;
	}
}

void CSceneManager::Update(float deltaTime)
{
	m_pScene->Update(deltaTime);
}

void CSceneManager::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneManager::Release()
{
	ptr_delete(m_pScene);
}
