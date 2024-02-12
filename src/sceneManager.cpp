#include "sceneManager.h"

void SceneManager::Update(const float& deltaMS) {
	for (Scene* scenes : m_scenes) {
		scenes->Update(deltaMS);
	}
}
