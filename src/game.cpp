#include "game.h"

Game::Game(std::map<std::string, std::string>& config) {
	// Initialization of managers and game state
	LoadGameTextures(config);
	InitSceneManager(config);
	InitPlayerManager(config);
	InitEnemyManager(config);
	m_gameExit = false;
}

void Game::Update(const float& deltaTime) const {
	m_enemyManager->Update(deltaTime);
	m_playerManager->Update(deltaTime);
	// m_sceneManager->Update(deltaTime);
}

void Game::Render(sf::RenderWindow& renderWindow) const {
	renderWindow.clear();
	m_sceneManager->Render(renderWindow);
	m_playerManager->Render(renderWindow);
	m_enemyManager->Render(renderWindow);
	renderWindow.display();
}

bool Game::ExitGame() const {
	return m_enemyManager->AllEnemiesDefeated() || m_playerManager->IsGameOver();
}

void Game::LoadTexture(const std::string& name, const std::string& route) {
	if(!m_assetManager.LoadTexture(name, route)) {
		throw std::runtime_error("Failed to load" + name + "texture");
	}
}

void Game::LoadGameTextures(std::map<std::string, std::string>& config) {
	LoadTexture(config["player_texture_name"], config["player_texture_path"]);
	LoadTexture(config["bomb_texture_name"], config["bomb_texture_path"]);
	LoadTexture(config["bomb_explosion_texture_name"], config["bomb_explosion_texture_path"]);
	LoadTexture(config["enemy_texture_name"], config["enemy_texture_path"]);
	LoadTexture(config["map_grass_texture_name"], config["map_grass_texture_path"]);
	LoadTexture(config["map_brick_texture_name"], config["map_brick_texture_path"]);
	LoadTexture(config["map_solid_texture_name"], config["map_solid_texture_path"]);
}

void Game::InitPlayerManager(std::map<std::string, std::string>& config) {
	const sf::Vector2f playerPosition = {std::stof(config["player_initial_position_x"]), std::stof(config["player_initial_position_y"])};
	const float playerSpeed = std::stof(config["player_speed"]);
	const sf::Vector2f playerSpriteDimensions = {std::stof(config["player_sprite_width"]), std::stof(config["player_sprite_height"])};
	const float playerSpriteScale = std::stof(config["player_sprite_scale"]);
	const sf::Vector2f bombSpriteDimensions = {std::stof(config["bomb_sprite_width"]),
				std::stof(config["bomb_sprite_height"])};
	const float bombSpriteScale = std::stof(config["bomb_sprite_scale"]);
	const float playerAdjustment = std::stof(config["player_adjustment"]);
	const float bombCountdown = std::stof(config["bomb_countdown"]);
	const int tileWidth = std::stoi(config["map_tile_width"]);
	const int tileHeight = std::stoi(config["map_tile_height"]);
	m_playerManager =
		std::make_unique<PlayerManager>(m_assetManager.GetTexture(config["player_texture_name"]),
			m_assetManager.GetTexture(config["bomb_texture_name"]),
			m_assetManager.GetTexture(config["bomb_explosion_texture_name"]),
			m_sceneManager.get(), playerSpeed, playerPosition, playerSpriteDimensions,
			playerSpriteScale, bombSpriteDimensions, bombSpriteScale, playerAdjustment,
			bombCountdown, tileWidth, tileHeight);
}

void Game::InitSceneManager(std::map<std::string, std::string>& config) {
	m_sceneManager =std::make_unique<SceneManager>(m_assetManager.GetTexture(config["map_brick_texture_name"]), m_assetManager.GetTexture(config["map_solid_texture_name"]), m_assetManager.GetTexture(config["map_grass_texture_name"]));
}

void Game::InitEnemyManager(std::map<std::string, std::string>& config) {
	m_enemyManager = std::make_unique<EnemyManager>(m_assetManager.GetTexture(config["enemy_texture_name"]), m_sceneManager.get(), m_playerManager.get(), std::stoi(config["enemy_count"]));
}
