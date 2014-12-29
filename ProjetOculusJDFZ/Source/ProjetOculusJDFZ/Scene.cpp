#include "Scene.h"


Scene::Scene(int sceneId, std::list<int> objectsId):
sceneId(sceneId), objectsId(objectsId)
{}


Scene::~Scene()
{
}

int Scene::getSceneId() {
	return sceneId;
}
std::list<int> getObjectsId() {
	return objectsId;
}