#include "ProjetOculusJDFZ.h"
#include "Scene.h"

/* Constructor and Destructor */

Scene::Scene(int sceneId, std::list<int> objectsId):
sceneId(sceneId), objectsId(objectsId)
{}

Scene::Scene()
{}

Scene::~Scene()
{
}

/* Getter */

int Scene::getSceneId() {
	return sceneId;
}
