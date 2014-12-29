#pragma once
#include<list>

class Scene
{
public:
	Scene(int sceneId, std::list<int> objectsId);
	~Scene();

	int getSceneId();
	std::list<int> getObjectsId();

private:

	int sceneId;
	std::list<int> objectsId;

};

