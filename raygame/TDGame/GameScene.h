#pragma once
#include "Scene.h"

class GameScene : public Scene
{
public:
	void start() override;
	void update(float deltaTime) override;
	void end() override;

private:
	int m_waveNumber;
	int m_cash;

	int m_fireRatePrice;
	int m_damagePrice;

	int m_playerFireRate;
	int m_playerDamage;
	bool m_playerHasHoming;
	bool m_playerHasExplosive;

	static void buyHoming();
	static void buyFirerateUp();
	static void buyDamageUp();
	static void buyExplosive();

	static void startWave();

	static void openDebugMenu();
};