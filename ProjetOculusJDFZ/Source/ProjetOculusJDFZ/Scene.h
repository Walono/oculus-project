/**
* Bachelor Project: Development and Implementation of 
* an Oculus Rift Frontend for Audio-Visual VR Applications
* Scene
* Purpose: It's  a  container  for  a  set  of  objects
* 
* @author Julie Djeffal & Fabien Zellweger
*/
#pragma once
#include<list>

class Scene
{
public:

/* Constructors and Desctructor */

	Scene(int sceneId, std::list<int> objectsId);
	Scene();
	~Scene();

/* Getter */

	int getSceneId();

private:

	int sceneId;
	std::list<int> objectsId;

};

