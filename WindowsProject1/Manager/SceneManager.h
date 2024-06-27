#pragma once
#include"../Map/Map.h"
class CScene;
class CSceneManager
{
private:
	CSceneManager();
	~CSceneManager();
	static CSceneManager* m_pInstance;
public:
	static CSceneManager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CSceneManager;
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
	enum ID { SCENE_LOADING, 
		SCENE_MENU, 
		SCENE_STAGE,
		SCENE_GAMEOVER,
		SCENE_CLEAR,
		SCENE_END 
	};
	void Scene_Change(ID eNextID);
	void Update(float deltaTime);
	void Render(HDC hDC);
	void Release();
private:
	CScene* m_pScene;
	ID m_eCurScene;
	ID m_eNextScene;
};

