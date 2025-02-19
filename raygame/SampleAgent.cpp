#include "SampleAgent.h"
#include "raylib.h"
#include "Transform2D.h"


void SampleAgent::start()
{
	behavior = new Seek(this, 1.0f, {100, 100});
	addComponent<Seek>(behavior);
}

void SampleAgent::update(float deltaTime)
{
	Agent::update(deltaTime);
}

void SampleAgent::draw()
{
	DrawPoly({ getTransform()->getWorldPosition().x,  getTransform()->getWorldPosition().x })
}
