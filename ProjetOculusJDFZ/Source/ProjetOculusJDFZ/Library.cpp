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
	if (isInTArray(facesToSpawn, newFace.getFaceId()) == false) {
		facesToSpawn.Add(newFace.getFaceId());
	}

}

void Library::remove_face(int faceId) {
	std::map<int, Face>::iterator it = faces.find(faceId);
	if (it != faces.end()) {
		if (it->second.hasProceduralFaceActor) {
			facesToDelete.Add(it->first);
		}
		else {
			if (isInTArray(facesToSpawn, it->first)) {
				for (int i = 0; i < facesToSpawn.Num(); ++i) {
					if (facesToSpawn[i] == it->first) {
						facesToSpawn.RemoveAt(i);
						faces.erase(it->first);
						break;
					}
				}
			}
		}
	}
}


void Library::move_face(std::list<float> newPosition, int faceId) {
	std::map<int, Face>::iterator it = faces.find(faceId);
	if (it != faces.end()) {
		it->second.setPosition(newPosition);
		Face newFace = it->second;
		if (newFace.hasProceduralFaceActor) {
			facesToMove.Add(newFace.getFaceId());
		}
	}
}

void Library::add_sound_source(std::string name,
	std::list<float> position,
	std::vector<float> viewDirection,
	std::vector<float> upDirection, int sourceId) {

	Sound newSound =
		Sound::Sound(name, position, viewDirection, upDirection, sourceId);
	sounds[sourceId] = newSound;
	if (isInTArray(soundToSpawn, newSound.getSourceId()) == false) {
		soundToSpawn.Add(newSound.getSourceId());
	}
}

void Library::remove_sound_source(int sourceId) {
	std::map<int, Sound>::iterator it = sounds.find(sourceId);
	if (it != sounds.end()) {
		if (it->second.hasProceduralFaceActor) {
			soundToDelete.Add(it->first);
		}
		else {
			if (isInTArray(soundToSpawn, it->first)) {
				for (int i = 0; i < soundToSpawn.Num(); i++) {
					if (soundToSpawn[i] == it->first) {
						soundToSpawn.RemoveAt(i);
						sounds.erase(it->first);
						break;
					}
				}
			}
		}
	}
}

void Library::move_source(std::list<float> newPosition,
	std::vector<float> newViewDirection,
	std::vector<float> newUpDirection, int sourceId) {
	
	std::map<int, Sound>::iterator it = sounds.find(sourceId);
	if (it != sounds.end()) {
		it->second.setPosition(newPosition);
		it->second.setViewDirecton(newViewDirection);
		it->second.setUpDirection(newUpDirection);
		if (it->second.hasProceduralFaceActor) {
			soundToMove.Add(it->first);
		}
	}
}

//TODO Define method
void Library::enable_sound(bool enable, int sourceId) 
{
	std::map<int, Sound>::iterator it = sounds.find(sourceId);
	if (it != sounds.end()) {
		if (it->second.getSoundActivity() != enable) {
			soundToEnable.Add(sourceId);
		}
	}
}

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

Face* Library::getNextFaceToSpawn() {
	std::map<int, Face>::iterator it = faces.find(facesToSpawn[0]);
	return &it->second;
}

Sound* Library::getNextSoundToSpawn() {
	std::map<int, Sound>::iterator it = sounds.find(soundToSpawn[0]);
	return &it->second;
}

bool Library::isFacesToSpawnEmpty() {
	if (facesToSpawn.Num() == 0) {
		return true;
	}
	return false;
}

bool Library::isSoundToSpawnEmpty() {
	if (soundToSpawn.Num() == 0) {
		return true;
	}
	return false;
}

void Library::deleteFaceSpawned() {
	facesToSpawn.RemoveAt(0);
}

void Library::deleteSoundSpawned() {
	soundToSpawn.RemoveAt(0);
}

Face* Library::getNextFaceToMove() {
	std::map<int, Face>::iterator it = faces.find(facesToMove[0]);
	return &it->second;
}

Sound* Library::getNextSoundToMove() {
	std::map<int, Sound>::iterator it = sounds.find(soundToMove[0]);
	return &it->second;
}

bool Library::isFacesToMoveEmpty() {
	if (facesToMove.Num() == 0) {
		return true;
	}
	return false;
}

bool Library::isSoundToMoveEmpty() {
	if (soundToMove.Num() == 0) {
		return true;
	}
	return false;
}

void Library::deleteFaceMoved() {
	facesToMove.RemoveAt(0);	
}

void Library::deleteSoundMoved() {
	soundToMove.RemoveAt(0);
}

int Library::getNextFaceIdToDelete() {
	return facesToDelete[0];
}

int Library::getNextSoundIdToDelete() {
	return soundToDelete[0];
}

bool Library::isFacesToDeleteEmpty() {
	if (facesToDelete.Num() == 0) {
		return true;
	}
	return false;
}

bool Library::isSoundToDeleteEmpty() {
	if (soundToDelete.Num() == 0) {
		return true;
	}
	return false;
}


void Library::deleteFaceDeleted() {
	faces.erase(facesToDelete[0]);
	facesToDelete.RemoveAt(0);	
}

void Library::deleteSoundDeleted() {
	sounds.erase(soundToDelete[0]);
	soundToDelete.RemoveAt(0);
}

Sound* Library::getNextSoundIdToEnable(){
	std::map<int, Sound>::iterator it = sounds.find(soundToSpawn[0]);
	return &it->second;
}
bool Library::isSoundToEnableEmpty() {
	if (soundToEnable.Num() == 0) {
		return true;
	}
	return false;
}
void Library::deleteSoundEnabled() {
	soundToEnable.RemoveAt(0);
}


bool Library::isInTArray(TArray<int> facesId, int id) {

	for (int i = 0; i < facesId.Num(); ++i) {
		if (facesId[i] == id) {
			return true;
		}
	}

	return false;
}