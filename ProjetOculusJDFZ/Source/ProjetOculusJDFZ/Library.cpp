#include"ProjetOculusJDFZ.h"
#include "Library.h"

Library * Library::_singletonInst = new Library();

Library * Library::getLibrary() {
	return _singletonInst;

}

void Library::add_face(std::list<float> position,
	std::list<std::list<float>> coordinates, int texture, int faceId) {
	Face newFace = Face::Face(position, coordinates, texture, faceId);
	faces[faceId] = newFace;
	//TODO Remove duplicata in facesToSpawn?
	facesToSpawn.Add(newFace);
}

void Library::remove_face(int faceId) {
	//Add a part to remove it in the editor
	std::map<int, Face>::iterator it = faces.find(faceId);
	if (it != faces.end()) {
		sounds.erase(faceId);
	}
}


void Library::move_face(std::list<float> newPosition, int faceId) {
	std::map<int, Face>::iterator it = faces.find(faceId);
	if (it != faces.end()) {
		Face newFace = Face::Face(faces.at(faceId));
		//add a part to move it in the editor
		faces.at(faceId) = newFace;
	}
}

void Library::add_sound_source(std::string name,
	std::list<float> position,
	std::vector<float> viewDirection,
	std::vector<float> upDirection, int sourceId) {

	Sound newSound = 
		Sound::Sound(name, position, viewDirection, upDirection, sourceId);
	sounds[sourceId] = newSound;
}

void Library::remove_sound_source(int sourceId) {
	//Add a part to remove it in the editor
	std::map<int, Sound>::iterator it = sounds.find(sourceId);
	if (it != sounds.end()) {
		sounds.erase(sourceId);
	}
}

void Library::move_source(std::list<float> newPosition,
	std::vector<float> newViewDirection,
	std::vector<float> newUpDirection, int sourceId) {
	
	//add a part to move it in the editor
	std::map<int, Sound>::iterator it = sounds.find(sourceId);
	if (it != sounds.end()) {
		Sound newSound = Sound::Sound(sounds.at(sourceId));
		sounds.at(sourceId) = newSound;
	}
}

//TODO Define method
void Library::enable_sound(bool enable, int sourceId) {}

//TODO Define method
void Library::set_initial_position(std::list<float> position) {}

//TODO Define method
void Library::reset_position() {}

void Library::addPolyhedron(std::list<int> facesId, int polyhedronId) {
	Polyhedron newPolyhedron =
		Polyhedron::Polyhedron(facesId, polyhedronId);
	polyhedrons[polyhedronId] = newPolyhedron;
}

void Library::removePolyhedron(int polyhedronId) {
	std::map<int, Polyhedron>::iterator it = polyhedrons.find(polyhedronId);
	if (it != polyhedrons.end()) {
		polyhedrons.erase(polyhedronId);
	}
}

void Library::addScene(int sceneId, std::list<int> objectsId) {
	Scene newScene =
		Scene::Scene(sceneId, objectsId);
	scenes[sceneId] = newScene;
}

void Library::removeScene(int sceneId) {
	std::map<int, Scene>::iterator it = scenes.find(sceneId);
	if (it != scenes.end()) {
		sounds.erase(sceneId);
	}
}

Face Library::getNextFaceToSpawn() {
	return facesToSpawn[0];
}
bool Library::isFacesToSpawnEmpty() {
	if (facesToSpawn.Num() == 0) {
		return true;
	}
	else {
		return false;
	}
}
void Library::deleteFaceSpawned() {
	facesToSpawn.RemoveAt(0);
}

