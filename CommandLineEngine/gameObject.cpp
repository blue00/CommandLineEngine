#include "gameObject.h"
#include "engine.h"

GameObject::GameObject() : Token(-1,0) //konstruktor
{

}

GameObject::~GameObject() //destruktor
{

}

void GameObject::Initialize(Engine* _engine)
{
	engine = _engine;
	engine->gameObjectManager.Register(this);
	Start();
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

const std::wstring GameObject::ToString()
{
	return std::wstring(L"???");
}

//This function is called when the GameObject will be destroyed
void GameObject::OnDestroy()
{
	engine->gameObjectManager.Unregister(this);
}