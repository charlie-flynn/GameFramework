#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
public:
	void start() override;
	void update(float deltaTime) override;

private:
	int m_sceneIndex;

	void startGame();
};
