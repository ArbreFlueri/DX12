#pragma once

class Scene;

class SceneManager
{
	DECLARE_SINGLE(SceneManager);

public:
	void Update();
	void LoadScene(wstring sceneName);


public :
	shared_ptr<Scene> GetActiveScene() { return _activeScene; }

private://테스트를 위한 것
	shared_ptr<Scene> LoadTestScene(); 

private:
	shared_ptr<Scene> _activeScene;
};

