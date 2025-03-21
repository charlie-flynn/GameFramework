#include "ActorPlacer.h"
#include "raylib.h"
#include "SpriteComponent.h"
#include "Transform2D.h"
#include "Engine.h"
#include "Scene.h"
#include "Walterberry.h"
#include "EMUDog.h"
#include "Alien.h"

ActorPlacer::ActorPlacer(Pathfinding::NodeMap* nodemap) : Actor(GetScreenWidth() / 2, 200, 5),
m_spriteOne(new SpriteComponent(this, "Images/walterberry.png")),
m_spriteTwo(new SpriteComponent(this, "Images/EMU dog.png")),
m_spriteThree(new SpriteComponent(this, "Images/purple alien.png")),
m_selected(WALTERBERRY),
m_nodeMap(nodemap)
{
}

void ActorPlacer::start()
{
	Actor::start();

	addComponent(m_spriteOne);
	addComponent(m_spriteTwo);
	addComponent(m_spriteThree);

	getTransform()->setScale({100.0f, 100.0f});
}

void ActorPlacer::update(float deltaTime)
{
	Actor::update(deltaTime);

	if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
	{
		MathLibrary::Vector2 mousePosition = { (float)GetMouseX(), (float)GetMouseY() };

		switch (m_selected)
		{
		case WALTERBERRY:
			Engine::getCurrentScene()->addActor(new Walterberry(mousePosition.x, mousePosition.y));
			break;
		case EMU_DOG:
			Engine::getCurrentScene()->addActor(new EMUDog(mousePosition.x, mousePosition.y));
			break;
		case ALIEN:
			Engine::getCurrentScene()->addActor(new Alien(m_nodeMap, mousePosition.x, mousePosition.y));
			break;
		default:
			break;
		}
	}
}

void ActorPlacer::draw()
{
	switch (m_selected)
	{
	case WALTERBERRY:
		m_spriteOne->draw();
		break;
	case EMU_DOG:
		m_spriteTwo->draw();
		break;
	case ALIEN:
		m_spriteThree->draw();
		break;
	default:
		break;
	}
}
