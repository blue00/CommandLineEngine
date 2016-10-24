#include "gameObject.h"
#include "engine.h"

GameObject::GameObject() //konstruktor
{

}

GameObject::~GameObject() //destruktor
{
	
}

void GameObject::Update()
{
	//if update is not overwritten, it is not in use -> remove object from updatevector
	engine->gameData.RemoveUpdate(this);
}

void GameObject::Start()
{
	//
}

//This function is called when the GameObject will be destroyed
void GameObject::OnDestroy()
{
	//
}

void GameObject::Destroy()
{
	//@TODO: inform the gameData that this object should be destroyed
}
