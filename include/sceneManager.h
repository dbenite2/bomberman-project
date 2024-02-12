#pragma once
#include "scene.h"
#include <vector>

class SceneManager {
public:
	void Update(const float& deltaMS);
private:
	std::vector<Scene*> m_scenes{ nullptr };
};