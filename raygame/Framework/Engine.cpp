#include "Engine.h"
#include "raylib.h"
#include "Transform2D.h"
#include "SampleScene.h"
#include "DynamicArray.h"
#include "Actor.h"
#include "Pathfinding/PathScene.h"
#include <random>
#include <chrono>

bool Engine::m_applicationShouldClose = false;
DynamicArray<Scene*> Engine::m_scenes = DynamicArray<Scene*>();
DynamicArray<Actor*> Engine::m_actorsToDelete = DynamicArray<Actor*>();
int Engine::m_sceneCount = 0;
int Engine::m_currentSceneIndex = 0;


Engine::Engine()
{
	m_applicationShouldClose = false;
	m_scenes = DynamicArray<Scene*>();
	m_camera = new Camera2D();
	m_currentSceneIndex = 0;
	m_sceneCount = 0;
}

void Engine::start()
{
	//Initialize window
	int screenWidth = 700;
	int screenHeight = 800;
	InitWindow(screenWidth, screenHeight, "AI Demo");
	SetTargetFPS(0);

	// Seed randomizer
	srand(time(0));

	//Start the scene
	m_currentSceneIndex = addScene(new SampleScene());
	m_scenes[m_currentSceneIndex]->start();
}

void Engine::update(float deltaTime)
{
	//Clean up actors marked for destruction
	destroyActorsInList();

	//Update scene
	m_scenes[m_currentSceneIndex]->update(deltaTime);
	m_scenes[m_currentSceneIndex]->updateUI(deltaTime);
}

void Engine::draw()
{
	BeginDrawing();

	ClearBackground(BLACK);

	m_scenes[m_currentSceneIndex]->draw();
	m_scenes[m_currentSceneIndex]->drawUI();

	EndDrawing();
}

void Engine::end()
{
	m_scenes[m_currentSceneIndex]->end();
	CloseWindow();
}

void Engine::run()
{
	//Create window and start scene
	start();

	//Loop while the application shouldn't end
	while (!m_applicationShouldClose && !RAYLIB_H::WindowShouldClose())
	{
		//Calculate deltatime
		float deltaTime = RAYLIB_H::GetFrameTime();

		//Update scene
		update(deltaTime);

		//Draw current scene
		draw();
	}

	end();
}

Scene* Engine::getScene(int index)
{
	//Return nullptr if the scene is out of bounds
	if (index < 0 || index >= m_sceneCount)
		return nullptr;

	return m_scenes[index];
}

Scene* Engine::getCurrentScene()
{
	return m_scenes[m_currentSceneIndex];
}

int Engine::getCurrentSceneIndex()
{
	return m_currentSceneIndex;
}

int Engine::addScene(Scene* scene)
{
	///If the scene is null then return before running any other logic
	if (!scene)
		return -1;

	m_scenes.Add(scene);

	return m_scenes.Length() - 1;

	// old deprecated code
	/*
	//Create a new temporary array that one size larger than the original
	Scene** tempArray = new Scene * [m_sceneCount + 1];

	//Copy values from old array into new array
	for (int i = 0; i < m_sceneCount; i++)
	{
		tempArray[i] = m_scenes[i];
	}

	//Store the current index
	int index = m_sceneCount;

	//Sets the scene at the new index to be the scene passed in
	tempArray[index] = scene;

	delete m_scenes;

	//Set the old array to the tmeporary array
	m_scenes = tempArray;
	m_sceneCount++;
	*/
}

void Engine::addActorToDeletionList(Actor* actor)
{
	m_actorsToDelete.Add(actor);

	for (int i = 0; i < actor->getTransform()->getChildCount(); i++)
	{
		m_actorsToDelete.Add(actor->getTransform()->getChildren()[i]->getOwner());
	}


	/*
	//return if the actor is already going to be deleted
	if (m_actorsToDelete.Contains(actor))
		return;

	//Add actor to deletion list
	m_actorsToDelete.addActor(actor);

	//Add all the actors children to the deletion list
	for (int i = 0; i < actor->getTransform()->getChildCount(); i++)
	{
		m_actorsToDelete.addActor(actor->getTransform()->getChildren()[i]->getOwner());
	}
	*/
}

bool Engine::removeScene(Scene* scene)
{
	return m_scenes.Remove(scene);


	/*
	//If the scene is null then return before running any other logic
	if (!scene)
		return false;

	bool sceneRemoved = false;

	//Create a new temporary array that is one less than our original array
	Scene** tempArray = new Scene * [m_sceneCount - 1];

	//Copy all scenes except the scene we don't want into the new array
	int j = 0;
	for (int i = 0; i < m_sceneCount; i++)
	{
		if (tempArray[i] != scene)
		{
			tempArray[j] = m_scenes[i];
			j++;
		}
		else
		{
			sceneRemoved = true;
		}
	}

	//If the scene was successfully removed set the old array to be the new array
	if (sceneRemoved)
	{
		m_scenes = tempArray;
		m_sceneCount--;
	}


	return sceneRemoved;
	*/
}

void Engine::setCurrentScene(int index)
{
	//If the index is not within the range of the the array return
	if (index < 0 || index >= m_sceneCount)
		return;

	//Call end for the previous scene before changing to the new one
	if (m_scenes[m_currentSceneIndex]->getStarted())
		m_scenes[m_currentSceneIndex]->end();

	//Update the current scene index
	m_currentSceneIndex = index;
}

bool Engine::getKeyDown(int key)
{
	return RAYLIB_H::IsKeyDown((KeyboardKey)key);
}

bool Engine::getKeyPressed(int key)
{
	return RAYLIB_H::IsKeyPressed((KeyboardKey)key);
}

void Engine::destroy(Actor* actor)
{
	addActorToDeletionList(actor);
}

void Engine::destroyActorsInList()
{
	//Iterate through deletion list
	for (int i = 0; i < m_actorsToDelete.Length(); i++)
	{
		//Remove actor from the scene
		Actor* actorToDelete = m_actorsToDelete[i];

		getCurrentScene()->removeActor(actorToDelete);
		getCurrentScene()->removeUIElement(actorToDelete);

		//Call actors clean up functions
		actorToDelete->end();
		actorToDelete->onDestroy();

		//Delete the actor
		// TO DO: make it call the destructor of the type it actually is and not just the actor destructor
		delete actorToDelete;
	}

	//Clear the array
	m_actorsToDelete.Clear();
}

void Engine::CloseApplication()
{
	Engine::m_applicationShouldClose = true;
}