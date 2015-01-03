#pragma once
#include"Interface.h"
#include"Face.h"
#include"Polyhedron.h"
#include"Scene.h"
#include"Sound.h"
#include<list>
#include<vector>
#include<string>
#include<map>
#include"Runtime/Core/Public/Containers/Array.h"

class Library : public virtual Interface
{
public:
	/* Get the Library */
	static Library * getLibrary();

	/* Concerning the faces */
	virtual void add_face(std::list<float> position,
		std::list<std::list<float>> coordinates, int texture, int faceId);

	// Remove a face from the Environment
	virtual void remove_face(int faceId);

	//Move a face in the Environment
	virtual void move_face(std::list<float> newPosition, int faceId);

	 /* Concerning the sound sources */ 
	//Add a sound source to the environment
	virtual void add_sound_source(std::string name,
		std::list<float> position,
		std::vector<float> viewDirection,
		std::vector<float> upDirection, int sourceId);

	// Remove a sound source from the environment
	virtual void remove_sound_source(int sourceId);

	// Move a source sound from the environment
	virtual void move_source(std::list<float> newPosition,
		std::vector<float> newViewDirection,
		std::vector<float> newUpDirection, int sourceId);

	// Enable or disable the sound of a source sound
	virtual void enable_sound(bool enable, int sourceId);

	 /* Concerning the global environment*/
	// Set the initial position 
	virtual void set_initial_position(std::list<float> position);

	// Reset the position to the initial position
	virtual void reset_position();

	/* Concerning a Polyhedron */

	void addPolyhedron(std::list<int> facesId, int polyhedronId);

	void removePolyhedron(int polyhedronId);

	/* Concerning a scene */

	void addScene(int sceneId, std::list<int> objectsId);

	void removeScene(int sceneId);

	/* Concerning the Faces to Spawn */

	Face getNextFaceToSpawn();
	bool isFacesToSpawnEmpty();
	void deleteFaceSpawned();
	Face getNextFaceToMove();
	bool isFacesToMoveEmpty();
	void deleteFaceMoved();


private:

	static Library * _singletonInst;
	Library() {}
	Library(Library const&);
	void operator=(Library const&);

	std::map<int, Scene> scenes;
	std::map<int, Polyhedron> polyhedrons;
	std::map<int, Face> faces;
	std::map<int, Sound> sounds;
	TArray<Face> facesToSpawn;
	TArray<Face> facesToMove;

};

