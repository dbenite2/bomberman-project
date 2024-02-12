#pragma once
#include "player.h"

class PlayerManager {
public:
	void Update(const float& deltaMS);
private:
	Player* m_player;
};