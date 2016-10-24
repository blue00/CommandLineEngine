#include "gameData.h"
#include <algorithm>

//@TODO: maybe a vector is the wrong list for this, maybe linked list?

GameData::GameData()
{

}

void GameData::Create(GameObject *gameObject)
{
	gameObject->Initialize(engine);
	AddAlive(gameObject);
	AddUpdate(gameObject);
}

void GameData::AddAlive(GameObject *gameObject)
{
	aliveVec.push_back(gameObject);
}

void GameData::AddUpdate(GameObject *gameObject)
{
	updateVec.push_back(gameObject);
}

void GameData::RemoveUpdate(GameObject *gameObject)
{
	updateVec.erase(std::remove(updateVec.begin(), updateVec.end(), gameObject), updateVec.end());
}

void GameData::Tick()
{
	//check for dead objects
	for (std::vector<GameObject*>::iterator it = aliveVec.begin(); it != aliveVec.end();)
	{
		GameObject* currentBhv = (*it);

		if (!currentBhv->alive) //not alive?
		{
			//call OnDestroy
			currentBhv->OnDestroy();

			//do not destroy the object here! we cannot know if it was originally created with new
			//delete(currentBhv);

			//remove from all other lists
			updateVec.erase(std::remove(updateVec.begin(), updateVec.end(), currentBhv), updateVec.end());
			//todo: remove from other lists
			//...

			//remove object from alive vector (erase returns the next object)
			it = aliveVec.erase(it);

		}
		else
		{
			++it;
		}
	}

	//update loop
	for (unsigned i = updateVec.size(); i-- > 0;)
	{
		updateVec[i]->Update();
	}

	//todo: add other loops
	//...
}

